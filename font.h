#ifndef FONT_H
#define FONT_H

struct font
{
	int texture;
	int cwidth, cheight;
	int chars_per_line;
};

// Shows text on the screen
// bx, by is the coordinates of the basepoint of the first character
void font_show_text(struct font* f, const char* str, float bx, float by);

#endif
