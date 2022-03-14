#include "program.hpp"
#include "web/setup_webserver.hpp"
#include <parameter_bank.hpp>
#include <time_system.hpp>
#include <thread>
#include <application/application.hpp>
#include <tasks/application_tasks.hpp>

void wait_for_unixtime()
{
    while (!TimeSystem::get_current_unixtime())
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void start_app(HttpServerInterface *http_server_implementation)
{
    wait_for_unixtime();
    Parameter<int> pa_on_time("LED on time", "OFF", 1, "seconds");
    Parameter<int> pa_off_time("LED off time", "ON", 1, "seconds");
    Parameter<int> pa_off_time3("LED off time", "ON2", 44, "hunde");
    ApplicationInterface *application_code = new Application("some name", http_server_implementation);
    Tasks tasks(std::vector<ApplicationInterface*>{application_code});
    start_threads();

    // Configure pin
    // gpio_config_t io_conf;
    // io_conf.intr_type = (gpio_int_type_t)GPIO_PIN_INTR_DISABLE;
    // io_conf.mode = GPIO_MODE_OUTPUT;
    // io_conf.pin_bit_mask = (1ULL << LED);
    // io_conf.pull_down_en = (gpio_pulldown_t)0;
    // io_conf.pull_up_en = (gpio_pullup_t)0;
    // gpio_config(&io_conf);
    // // Main loop
    // while (true)
    // {
    //     // std::cout << "Test" << std::endl;
    //     // gpio_set_level((gpio_num_t)LED, 0);
    //     vTaskDelay(1);
    //     // std::cout << "Hej med dig" << std::endl;
    //     // gpio_set_level((gpio_num_t)LED, 1);
    //     vTaskDelay(1);
    // }
    // thread1.join();
}