#ifndef __DRAWABLE__
#define __DRAWABLE__

#include <vector>
#include "config.hpp"

class Drawable
{
public:
    virtual ~Drawable() {};
    virtual int render() = 0;
    virtual int handleInput(Config* config, std::vector<Drawable*> states) = 0;
};

#endif