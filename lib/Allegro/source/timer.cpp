#include "../timer.h"

Timer::Timer(double sec) {
    timer = al_create_timer(sec);
}

Timer::Timer() {
    timer = NULL;
}

void Timer::create(double sec) {
    timer = al_create_timer(sec);
}

void Timer::changeSpeed(double sec) {
    if (timer != NULL)
        al_set_timer_speed(timer, sec);
    else exit(1);
}

double Timer::getSpeed() {
    if (timer != NULL)
        return al_get_timer_speed(timer);
    else exit(1);
}

void Timer::start() {
    if (timer != NULL)
        al_start_timer(timer);
    else exit(1);
}

void Timer::stop() {
    if (timer != NULL)
        al_stop_timer(timer);
    else exit(1);
}

int64_t Timer::getCount() {
    if (timer != NULL)
        return al_get_timer_count(timer);
    else exit(1);
}

void Timer::setCount(int64_t count) {
    if (timer != NULL)
        al_set_timer_count(timer, count);
    else exit(1);
}

ALLEGRO_TIMER* Timer::pointer() {
    return timer;
}

ALLEGRO_EVENT_SOURCE* Timer::getEventSource() {
    if (timer != NULL)
        return al_get_timer_event_source(timer);
    else exit(1);
}

bool Timer::isStarted() {
    if (timer != NULL)
        return al_get_timer_started(timer);
    else exit(1);
}

Timer::~Timer() {
    if (timer != NULL)
        al_destroy_timer(timer);
}
