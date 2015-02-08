#ifndef AL_FONT_H_INCLUDED
#define AL_FONT_H_INCLUDED

// Standart
#include <string>

// Allegro5
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

class Font {
public:
    Font();

    void loadFont(std::string fileName, int size);
    void loadTtfFont(std::string fileName, int size);
    
    ALLEGRO_FONT* getPointer();

    int getLineHeight();
    int getAscent();
    int getDescent();
    int getTextWidth(std::string text);
    
    void drawText(ALLEGRO_COLOR color, float x, float y, int flags, std::string text);
    
    void destroyFont();
    
    ~Font();
private:
    ALLEGRO_FONT *font;
};

#endif
