#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <map>

class Sprite;

class RenderWindow
{
    friend class Sprite;
public:
    RenderWindow(const char *p_title, int p_w, int p_h);
    ~RenderWindow();
    void clear();//clears the screen black
    void render(Sprite& sprite, int x, int y);//renders a sprite
    void display();//displays the back buffer I suppose 
    void renderText(std::string text, unsigned char r, unsigned char g, unsigned char b, int x, int y);//renders text
    bool run();//takes care of window messages and frame rate related bs
    bool keyPressed(char key);//checks if a key is pressed
    void setFps(int fps);//sets the fps

    static void InitAll();//initializes sdl related bs
    static void QuitAll();//destroy all resources allocated by InitAll()

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    std::map<char, bool> keyboard;
    float deltatime;
    Uint32 timer;
};
