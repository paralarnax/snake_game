#include "snake.h"

struct snake{
    int x;
    int y;
    int dir;
};

typedef struct snake Snake;

Snake *nead;
Snake *tail;

void init_snake(){/*TODO*/}

void render_grid(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    int cell_size = WINDOW_HEIGHT / GRID_SIZE;

    SDL_Rect cell;
    cell.w = cell_size;
    cell.h = cell_size;
    for(size_t i = 0; i < GRID_SIZE; i++){
        for(size_t j = 0; j < GRID_SIZE; j++){
            cell.x = i * cell_size;
            cell.y = j * cell_size;
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

void render_apple(SDL_Renderer *renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 255);
    int apple_size = WINDOW_HEIGHT / GRID_SIZE;

    SDL_Rect apple;
    apple.w = apple_size;
    apple.h = apple_size;
    apple.x = x;
    apple.y = y;

    SDL_RenderDrawRect(renderer, &apple);

}

int main(){
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_INIT_VIDEO < 0){
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO");
    }

    window = SDL_CreateWindow(
        "SNAKE",
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_ALLOW_HIGHDPI
    );

    if(!window){
        fprintf(stderr, "ERROR: !window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
        fprintf(stderr, "ERROE: !window");
    }

    bool quit = false;
    SDL_Event event;

    while(!quit){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);

        //Render Loop
        render_grid(renderer);
        render_apple(renderer, 100, 100);

        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 100);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
