#pragma once
#include <string>
#include <condition_variable>
#ifdef ESP32
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#endif
#ifdef NATIVE
#include <include/FreeRTOS.h>
#include <include/task.h>
#include <source/portable/portmacro.h>
#define portTICK_PERIOD_MS 1
#endif


constexpr int get_delay_in_ms(const int delay_in_ms)
{
    return delay_in_ms / portTICK_PERIOD_MS;
}

class ApplicationInterface
{
public:
    ApplicationInterface(std::string name,
                         int delay_in_ms = 1000,  bool wait_for_other_task = false) :
    _name(name),                                                     
    _x_delay(get_delay_in_ms(delay_in_ms))
    {
    }

    ApplicationInterface(std::string name, std::condition_variable *cv, std::mutex *m, const int delay_in_ms = 1000, bool wait_for_other_task = false) :
    _cv(cv),
    _m(m),
    _wait_for_other_task(wait_for_other_task),
    _name(name),                                                     
    _x_delay(get_delay_in_ms(delay_in_ms))
    {

    }
    static void start_task_loop(void *_this)
    {
        auto class_ = static_cast<ApplicationInterface *>(_this);

        while (1)
        {
            class_->Update();
            vTaskDelay(class_->_x_delay);
            if (class_->_wait_for_other_task) {
                std::unique_lock<std::mutex> lk(*class_->_m);
                class_->_cv->notify_one();
                class_->_cv->wait(lk);
            }
        }
    }

    void start_task()
    {
        xTaskCreate(start_task_loop, _name.c_str(), 2048, this, 7, NULL);
    }

    virtual void Update() = 0;
    std::condition_variable* get_conditional() {
        return _cv;
    }

    std::mutex* get_mutex() {
        return _m;
    }
    


protected:
    std::condition_variable *_cv;
    std::mutex *_m;
    bool _wait_for_other_task;
    std::string _name;
    const int _x_delay;
};