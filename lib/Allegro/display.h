#ifndef AL_DISPLAY_H_INCLUDED
#define AL_DISPLAY_H_INCLUDED

// Standart
#include <string>
// Allegro5
#include <allegro5/allegro.h>

class Display{
public:
    Display(int width, int height);

    void checkInit();

    ALLEGRO_DISPLAY* getPointer();
    ALLEGRO_BITMAP* getBackBuffer();
    ALLEGRO_EVENT_SOURCE *getEventSource();

    int getHeight();
    int getWidth();

    void resize(int width, int height);
    
    void setIcon(ALLEGRO_BITMAP *icon);
    void setTitle(std::string title);
    
    void flip();

    ~Display();
private:
    ALLEGRO_DISPLAY *display;
};

#endif
