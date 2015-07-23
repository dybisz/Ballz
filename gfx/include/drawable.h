#ifndef GFX_INCLUDE_DRAWABLE_H_
#define GFX_INCLUDE_DRAWABLE_H_

#include <vector>
#include "config.h"

class Drawable
{
public:
    virtual ~Drawable() {};
    virtual int render() = 0;
    virtual int handleInput(Config* config, std::vector<Drawable*> states) = 0;
};

#endif