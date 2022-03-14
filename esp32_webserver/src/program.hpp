#pragma once
#include <http_server_interface.hpp>
#include <parameter.hpp>
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
#include <application/application_interface.hpp>

class ProgramContainer {
    public:
    ProgramContainer(HttpServerInterface *implemetation);

    void add_application(ApplicationInterface *application);
    std::vector<ApplicationInterface*> get_applications();
    void start_appplications();
    private:
    std::vector<ApplicationInterface*> _applications;
};

void start_app(HttpServerInterface *http_server_implementation);
void start_threads();
ApplicationInterface* get_application_code(HttpServerInterface *http_implementation); 