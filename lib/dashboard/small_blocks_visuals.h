#ifndef SMALL_BLOCKS_VISUALS_H_INCLUDED
#define SMALL_BLOCKS_VISUALS_H_INCLUDED

#include "../enum_names.h"

class SmallBlockVisual {
public:
	static void draw(int x, int y, int type) {
		switch (type) {
			case B_S:
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin);
				break;
			case B_Z:
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin+bWidth);
				break;
			case B_L:
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin);
				break;
			case B_J:
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin);
				break;
			case B_O:
				drawSmallBlock(x+lMargin+B2Margin,y+tMargin+B2Margin);
				drawSmallBlock(x+lMargin+B2Margin+bWidth,y+tMargin+B2Margin);
				drawSmallBlock(x+lMargin+B2Margin,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B2Margin+bWidth,y+tMargin+B2Margin+bWidth);
				break;
			case B_I:
				drawSmallBlock(x+lMargin,y+tMargin+B1Margin);
				drawSmallBlock(x+lMargin+bWidth,y+tMargin+B1Margin);
				drawSmallBlock(x+lMargin+bWidth*2,y+tMargin+B1Margin);
				drawSmallBlock(x+lMargin+bWidth*3,y+tMargin+B1Margin);
				break;
			case B_T:
				drawSmallBlock(x+lMargin+B3Margin,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth*2,y+tMargin+B2Margin+bWidth);
				drawSmallBlock(x+lMargin+B3Margin+bWidth,y+tMargin+B2Margin);
				break;
		}
	}

private:
	static void drawSmallBlock(int x, int y) {
		al_draw_filled_rectangle(x, y, x+10, y+10, al_map_rgb(50, 50, 50));
	}
	static const int bWidth = 11;
	static const int lMargin = 3;
	static const int tMargin = 5;
	static const int B1Margin = 18;
	static const int B2Margin = 12;
	static const int B3Margin = 6;
};

	// B_S, B_Z, B_L, B_J, B_O, B_I, B_T


#endif