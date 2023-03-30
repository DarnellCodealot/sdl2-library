#define SDL_MAIN_HANDLED
#include "sldlib.hpp"
//#include "sprite.hpp"

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720

/*
int main(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
	    std::cout << "Error SDL2_image Initialization";
	    return 2;
    }
    
    SDL_Window *window = SDL_CreateWindow("SDL test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
    
    SDL_Surface* lettuce_sur = SDL_LoadBMP("lettuce.bmp");
    SDL_Texture* lettuce_tex = SDL_CreateTextureFromSurface(renderer, lettuce_sur);
    if (lettuce_tex == NULL) {
	    std::cout << "Error creating texture";
	    return 6;
    }
    SDL_FreeSurface(lettuce_sur);

    bool running = true;
    while(running){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    running = false;
                    break;

                default:
                    break;
                
                case SDL_KEYDOWN:
                    std::cout << (char)event.key.keysym.sym << std::endl;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, lettuce_tex, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    return 0;
}
*/

struct Vector2
{
    Vector2()
    :x(0.0f), y(0.0f)
    {}

    Vector2(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    float x, y;
};

int main(){
    //init library
    RenderWindow::InitAll();

    //create window
    RenderWindow window("MARIOANA EROINA COCAINA CRACK", 1280, 720);
    window.setFps(60);

    // Load the sprite
    Sprite lettuce("lettuce.png", window);
    Vector2 letpos;

    //Main loop
    while (window.run())
    {
        if(window.keyPressed('a')){
            letpos.x -= 1.5;
        }
        if(window.keyPressed('d')){
            letpos.x += 1.5;
        }
        if(window.keyPressed('w')){
            letpos.y -= 1.5;
        }
        if(window.keyPressed('s')){
            letpos.y += 1.5;
        }

        window.clear();
        window.render(lettuce, letpos.x, letpos.y);
        window.renderText("I am here", 255,255,255, 100, 200);
        window.display();
    }

    //Clean up
    RenderWindow::QuitAll();
    return 0;
}

