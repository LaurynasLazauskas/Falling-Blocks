#ifndef AL_TIMER_H
#define AL_TIMER_H

// Allegro5
#include <allegro5/allegro.h>

class Timer {
public:
    Timer(double sec);
    Timer();

    void create(double sec);
    
    ALLEGRO_TIMER* pointer();
    ALLEGRO_EVENT_SOURCE* getEventSource();

    void changeSpeed(double sec);
    double getSpeed();
    
    void start();
    void stop();
    bool isStarted();
    
    int64_t getCount();
    void setCount(int64_t count);

    ~Timer();
private:
    ALLEGRO_TIMER *timer;
};

#endif
