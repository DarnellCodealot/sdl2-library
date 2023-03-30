#pragma once
#include <string>
#include "renderwindow.hpp"

class Sprite{
    friend class RenderWindow;
public:
    Sprite(std::string name, RenderWindow target);

private:
    SDL_Texture* texture;
    int width;
    int height;
};