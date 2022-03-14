#pragma once

class TimeSystem {
    public:
    static void set_initial_unixtime(long long int unixtime) {
        _unixtime = unixtime;
        _unixtime_ms = unixtime * 1000;
        _initial_unixtime = unixtime;
        _initial_unixtime_ms = unixtime * 1000;
    }
    static void update_unixtime_ms(long int ms_since_last_update) {
        _unixtime_ms += ms_since_last_update;
        _unixtime += ms_since_last_update / 1000;
    }

    static const long long int get_initial_unixtime() {
        return _initial_unixtime;
    }
    static const long long int get_current_unixtime() {
        return _unixtime;
    }
    static const long long int get_current_unixtime_ms() {
        return _unixtime_ms;
    }

    private:
    static inline long long int _initial_unixtime = 0;
    static inline long long int _initial_unixtime_ms = 0;
    static inline long long int _unixtime = 0;
    static inline long long int _unixtime_ms = 0;
};