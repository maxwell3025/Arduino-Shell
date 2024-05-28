#include "util.h"

bool is_printing(unsigned char c){
    return (c >= 32) && (c < 127);
}