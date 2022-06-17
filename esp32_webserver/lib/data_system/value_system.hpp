#pragma once
#include <time_system.hpp>

template <typename T>
class ValueSystem
{
public:
    ValueSystem() {}
    ValueSystem(std::string name, std::string id, T value, std::string unit = "") : _name(name),
                                                                                    _id(id),
                                                                                    _unit(unit),
                                                                                    _value_source_has_been_removed(false)
    {
        _value = new T(value);
        _unixtime_ms = new long long int(TimeSystem::get_current_unixtime_ms());
    }
    void set_value(T value)
    {
        *_value = value;
        *_unixtime_ms = TimeSystem::get_current_unixtime_ms();
    }

    void remove_value_source()
    {
        if (_value_source_has_been_removed)
            return;
        _value_source_has_been_removed = true;
        _value = new T();
        *_unixtime_ms = TimeSystem::get_current_unixtime_ms();
    }

    T get_value() const
    {
        return *_value;
    }

    std::string get_id() const
    {
        return _id;
    }

    std::string get_name() const
    {
        return _name;
    }
    std::string get_unit() const
    {
        return _unit;
    }

    long long int get_unixtime_ms()
    {
        return *_unixtime_ms;
    }

    void set_value_source(ValueSystem<T> *source)
    {
        _value = source->_value;
    }

    T *get_value_source()
    {
        return _value;
    }

protected:
    T *_value;
    std::string _name;
    std::string _id;
    std::string _unit;
    long long int *_unixtime_ms;
    bool _value_source_has_been_removed;
};