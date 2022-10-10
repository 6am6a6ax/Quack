#ifndef QUACK_TIMESTAP_H
#define QUACK_TIMESTAP_H

namespace Quack {
class Timestep {
public:
    Timestep(float time = .0f) : _time(time) {}

public:
    float GetSeconds() const { return _time; }
    float GetMiliseconds() const { return _time * 1000.f; }

private:
    float _time;
};
}

#endif
