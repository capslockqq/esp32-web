#include <stdio.h>
#include <sys/socket.h>

#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "http_server.hpp"

#include <include/FreeRTOS.h>
#include <include/task.h>
#include <parameter_bank.hpp>
#define PORT 5050

HttpServer::HttpServer()
{
}

void HttpServer::register_get_endpoints(EndPointType &endpoints)
{
    _endpoints = endpoints;
}

void HttpServer::register_post_endpoints(std::string endpoints)
{
}

void HttpServer::update_webserver(void *unused)
{
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Only this line has been changed. Everything is same.

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    int optval = 1;
    if ((setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) == -1)
    {
        close(server_fd);
        perror("ERROR  SWM : Set Socket ReUSED ERROR \n");
        return;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            vTaskDelay(100);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        std::string response = buffer;
        bool endpoint_exists = false;
        response_container_t endpoint_container;
        for (auto &[key, value] : _endpoints)
        {
            if (response.find(key) != std::string::npos)
            {
                endpoint_exists = true;
                endpoint_container = value;
                break;
            }
        }
        std::string http_standard_response = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: *\nAccess-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept\nContent-Type:text/html, application/json\nContent-Length: ";
        std::string message = "";
        if (endpoint_exists)
        {
            if (response.find("POST /") != std::string::npos)
            {
                auto _parameter_bank = ParameterBank::get_instance();
                int start_index = response.find_first_of("{");
                int stop_index = response.find_last_of("}");
                nlohmann::json tmp;
                try
                {
                    nlohmann::json received_json = nlohmann::json::parse(response.substr(start_index, stop_index));
                    for (int i = 0; i < received_json["parameters"].size(); i++)
                    {
                        _parameter_bank->set_parameter_if_found(received_json["parameters"][i]);
                    }
                    tmp["status"] = "OK";
                }
                catch (const std::exception &e)
                {
                    tmp["status"] = "Bad json";
                }

                message = tmp.dump();
            }
            else
            {
                message = get_json_response_as_string(endpoint_container);
            }
            http_standard_response += std::to_string(message.length()) + "\n\n";
            if (!write(new_socket, http_standard_response.c_str(), strlen(http_standard_response.c_str())))
                return;
            if (!write(new_socket, message.c_str(), strlen(message.c_str())))
                return;
        }
        else
        {
            const char *page_not_found = "HTTP/1.1 404 Not Found\nContent-type: plain-text\nContent-Length: 10\n\n Page not found";
            if (!write(new_socket, page_not_found, strlen(page_not_found)))
                return;
        }
        close(new_socket);
        vTaskDelay(100);
    }
}

void HttpServer::start_webserver()
{
    xTaskCreate(this->update_webserver, "Webserver", 2048, NULL, 7, NULL);
}