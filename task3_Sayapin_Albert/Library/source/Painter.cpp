#include "Painter.h"
#include "paint_string.h"

string
Painter::action(Token &token) 
{
    switch (token.get_type()) {
    case IDENT:
        return paint_string(token.get_string(), PINK);
    case KEY:
        return paint_string(token.get_string(), BLUE);
    case CONST_INT:
        return paint_string(token.get_string(), ORANGE);
    case CONST_CHAR:
        return paint_string(token.get_string(), YELLOW);
    case CONST_STR:
        return paint_string(token.get_string(), GREEN);
    case COMMENT:
        return paint_string(token.get_string(), BROWN);
    case PUNCT:
        return paint_string(token.get_string(), RED);
    default:
        return token.get_string();
    }
}
