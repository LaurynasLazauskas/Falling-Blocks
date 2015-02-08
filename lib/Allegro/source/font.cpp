#include "../font.h"

Font::Font() {
	font = NULL;
}

void Font::loadFont(std::string fileName, int size) {
    font = al_load_font(fileName.c_str(), size, 0);
}

void Font::loadTtfFont(std::string fileName, int size) {
    font = al_load_ttf_font(fileName.c_str(), size, 0);
}

void Font::destroyFont() {
    if (font != NULL) {
        al_destroy_font(font);
        font = NULL;
    }
}

int Font::getLineHeight() {
	if (font != NULL)
		return al_get_font_line_height(font);
	else exit(1);
}

int Font::getAscent() {
	if (font != NULL)
		return al_get_font_ascent(font);
	else exit(1);
}

int Font::getDescent() {
	if (font != NULL)
		return al_get_font_descent(font);
	else exit(1);
}

int Font::getTextWidth(std::string text) {
	if (font != NULL)
		return al_get_text_width(font, text.c_str());
	else exit(1);
}

void Font::drawText(ALLEGRO_COLOR color, float x, float y, int flags, std::string text) {
    al_draw_text(font, color, x, y, flags, text.c_str());
}

ALLEGRO_FONT* Font::getPointer() {
	return font;
}

Font::~Font() {
	destroyFont();
}