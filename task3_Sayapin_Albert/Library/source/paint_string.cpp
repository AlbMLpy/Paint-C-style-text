#include "paint_string.h"

string paint_string(const string &str, Color paint)
{
    static string blue("\033[0;34m");
    static string pink("\033[0;35m");
    static string orange("\033[0;33m");
    static string yellow("\033[1;33m");
    static string green("\033[0;32m"); 
    static string red("\033[0;31m"); 
    static string brown("\033[0;33m");
    static string no_color("\033[0m");
    
    string buffer;
    switch (paint) {
    case BLUE:    
        buffer = blue;
        buffer += str;
        break;
    case PINK:
        buffer = pink;
        buffer += str;
        break;
    case ORANGE:
        buffer = orange;
        buffer += str;
        break;
    case YELLOW:
        buffer = yellow;
        buffer += str;
        break;
    case GREEN:
        buffer = green;
        buffer += str;
        break;
    case RED:
        buffer = red;
        buffer += str;
        break;
    case BROWN:
        buffer = brown;
        buffer += str;
        break;
    default:
        return str;
    };
    return buffer += no_color;
}  
