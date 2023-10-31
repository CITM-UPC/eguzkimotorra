#include "Timer.h"
#include "SDL2/SDL.h"

Timer::Timer(bool to_start) {
    if (to_start)
        Start();
}

void Timer::Start() {
    running_ = true;
    ticks_started_ = SDL_GetTicks64();
}

void Timer::Stop() {
    running_ = false;
    ticks_stopped_ = SDL_GetTicks64();
}

uint Timer::Read() const {
    if (running_)
        return SDL_GetTicks64() - ticks_started_;
    else
        return ticks_stopped_ - ticks_started_;
}

float Timer::ReadSeconds() const {
    if (running_ == true)
		return (float)(SDL_GetTicks64() - ticks_started_) / 1000.0f;
	else
		return (float)(ticks_stopped_ - ticks_started_) / 1000.0f;
}
