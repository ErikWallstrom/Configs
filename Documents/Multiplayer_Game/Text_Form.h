#ifndef TEXT_FORM_H
#define TEXT_FORM_H

#include "Button.h"

#define INPUT_ALL (INPUT_ALPHA | INPUT_NUM | INPUT_SYM)
extern const char* const TEXT_FORM_NAME;

enum Input_Type
{
	INPUT_ALPHA = 1,
	INPUT_NUM = 1 << 1,
	INPUT_SYM = 1 << 2
};

typedef struct Text_Form Text_Form;
struct Text_Form
{
	struct Button;
	Vec(char) input;
	Vec(char) default_text;
	size_t input_max;
	enum Input_Type input_type;
	int max_width;
	int ret_pressed;
};

struct Text_Form* Text_Form_ctor(struct Text_Form* self, enum Reg_Point r_point, struct Point pos, TTF_Font* font, char* default_text, enum Input_Type input_type, size_t input_max);
void Text_Form_update(struct Entity* e);
void Text_Form_dtor(struct Text_Form* self);

#endif
