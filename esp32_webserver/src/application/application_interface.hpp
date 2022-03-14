#pragma once
#include <string>
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
    ApplicationInterface(std::string name, const int delay_in_ms = 1000) : _name(name),
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
        }
    }

    void start_task()
    {
        xTaskCreate(start_task_loop, _name.c_str(), 2048, this, 7, NULL);
    }

    virtual void Update() = 0;

protected:
    std::string _name;
    const int _x_delay;
};