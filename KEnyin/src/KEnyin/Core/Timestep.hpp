#pragma once

namespace KEnyin
{
    class Timestep
    {
    public:
        Timestep(double time = 0.0f)
            : _time(time)
        {
        }

        operator double() const { return _time; }

        double GetSeconds() const { return _time; }
        double GetMilliseconds() const { return _time * 1000.0f; }
    private:
        double _time;
    };
}