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

void start_app(HttpServerInterface *http_server_implementation);
void start_threads();