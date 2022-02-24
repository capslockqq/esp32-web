#pragma once
template<typename T>
class HttpServerInterface {
    public:
    void start_webserver() {
        static_cast<T*>(this)->start_webserver();
    }
};