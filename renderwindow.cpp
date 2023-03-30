#include "sldlib.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL), deltatime(1000/60)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to initialize. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Load fonts
    font = TTF_OpenFont("font.ttf", 24);
}

RenderWindow::~RenderWindow()
{
    //SDL_DestroyWindow(this->window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Sprite& sprite, int x, int y)
{
    SDL_Rect destrect;
    destrect.x = x;
    destrect.y = y;
    destrect.h = sprite.height;
    destrect.w = sprite.width;
    SDL_RenderCopy(renderer, sprite.texture, NULL, &destrect);
}

void RenderWindow::renderText(std::string text, unsigned char r, unsigned char g, unsigned char b, int x, int y){
    //create a surface using the font, the color and the text in order to create a texture
    SDL_Color color = {r, g, b};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    //free the surface
    SDL_FreeSurface(surface);

    // Render the texture onto the screen
    SDL_Rect destRect = {x, y, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    //free the texture
    SDL_DestroyTexture(texture);
}


void RenderWindow::display()
{
    SDL_RenderPresent(renderer);

    Uint32 timepassed = SDL_GetTicks() - timer;
    if(deltatime > timepassed){
        SDL_Delay(deltatime - timepassed);
    }
}

bool RenderWindow::run()
{
    timer = SDL_GetTicks();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
        {
            return false;
            break;
        }
        case SDL_KEYUP:
        {
            char keypressed = event.key.keysym.sym;
            keyboard[keypressed] = false;
            break;
        }
        case SDL_KEYDOWN:
        {
            char keypressed = event.key.keysym.sym;
            keyboard[keypressed] = true;
            break;
        }
        }
    }
    return true;
}

bool RenderWindow::keyPressed(char key){
    return this->keyboard[key];
}

void RenderWindow::setFps(int fps){
    this->deltatime = 1000.0f/fps;
}

void RenderWindow::InitAll(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "Error: SDL: ", SDL_GetError();
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	    std::cout << "Error SDL2_image: " << IMG_GetError();
    }

    if(TTF_Init() < 0){
        std::cout << "Error TTF: " << TTF_GetError();
    }
}

void RenderWindow::QuitAll(){
    // Shut down SDL2_ttf
    TTF_Quit();

    // Shut down SDL2_image
    IMG_Quit();

    // Shut down SDL2
    SDL_Quit();
}