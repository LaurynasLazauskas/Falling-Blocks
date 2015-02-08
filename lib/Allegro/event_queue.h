#ifndef AL_EVENT_QUEUE_H_INCLUDED
#define AL_EVENT_QUEUE_H_INCLUDED

// Allegro5
#include <allegro5/allegro.h>

class EventQueue {
public:
    EventQueue();

    ALLEGRO_EVENT_QUEUE* getPointer();

    void registerSource(ALLEGRO_EVENT_SOURCE *source);
    void unregisterSource(ALLEGRO_EVENT_SOURCE *source);
    
    bool isEmpty();
    void flush();
    void wait(ALLEGRO_EVENT *event);
    void waitTimed(ALLEGRO_EVENT *event, float secs);
    
    ~EventQueue();
private:
    ALLEGRO_EVENT_QUEUE *eventQueue;
};

#endif