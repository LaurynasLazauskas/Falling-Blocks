#include "../display.h"

Display::Display(int width, int height) {
    display = al_create_display(width, height);
}

ALLEGRO_DISPLAY* Display::getPointer() {
	return display;
}

int Display::getHeight() {
	if (display != NULL)
		return al_get_display_height(display);
	else exit(1);
}

int Display::getWidth() {
	if (display != NULL)
		return al_get_display_width(display);
	else exit(1);
}

void Display::setIcon(ALLEGRO_BITMAP *icon) {
	if (icon != NULL && display != NULL)
    	al_set_display_icon(display, icon);
}

void Display::flip() {
	if (display != NULL) 
		al_flip_display();
	else exit(1);
}

ALLEGRO_BITMAP* Display::getBackBuffer() {
	if (display != NULL) 
		return al_get_backbuffer(display);
	else exit(1);
}

void Display::resize(int width, int height) {
	if (display != NULL)
		al_resize_display(display, width, height);
	else exit(1);
}

void Display::setTitle(std::string title) {
    if (display != NULL)
        al_set_window_title(display, title.c_str());
    else exit(1);
}

ALLEGRO_EVENT_SOURCE* Display::getEventSource() {
	if (display != NULL)
		return al_get_display_event_source(display);
	else exit(1);
}

void Display::checkInit() {
    if (display == NULL)
        exit(1);
}

Display::~Display() {
	if (display != NULL)
    	al_destroy_display(display);
}