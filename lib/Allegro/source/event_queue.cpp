#include "../event_queue.h"

EventQueue::EventQueue() {
    eventQueue = al_create_event_queue();
}

void EventQueue::registerSource(ALLEGRO_EVENT_SOURCE *source) {
    if (source != NULL)
        al_register_event_source(eventQueue, source);
    else exit(1);
}

void EventQueue::unregisterSource(ALLEGRO_EVENT_SOURCE *source) {
    if (source != NULL)
        al_unregister_event_source(eventQueue, source);
    else exit(1);
}
    
bool EventQueue::isEmpty() {
    return al_is_event_queue_empty(eventQueue);
}

void EventQueue::flush() {
    al_flush_event_queue(eventQueue);
}

void EventQueue::wait(ALLEGRO_EVENT *event) {
    if (event != NULL)
        al_wait_for_event(eventQueue, event);
    else exit(1);
}

void EventQueue::waitTimed(ALLEGRO_EVENT *event, float secs) {
    if (event != NULL)
        al_wait_for_event_timed(eventQueue, event, secs);
    else exit(1);
}

ALLEGRO_EVENT_QUEUE* EventQueue::getPointer() {
    return eventQueue;
}

EventQueue::~EventQueue() {
    if (eventQueue != NULL)
        al_destroy_event_queue(eventQueue);
}