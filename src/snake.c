#include "snake.h"

void init_snake(){
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->dir = SNAKE_UP;

    new->next = NULL;
    head = new;
    tail = new;
}

void increase_snake(){
    Snake *new = malloc(sizeof(Snake));
    new->x = tail->x;
    new->y = tail->y - 1;
    new->dir = tail->dir;

    new->next = NULL;
    tail->next = new;
    
    tail = new;
}

void move_snake(){

    int prev_x = head->x;
    int prev_y = head->y;

    switch(head->dir){
        case SNAKE_UP:
            head->y--;
            break;
        case SNAKE_DOWN:
            head->y++;
            break;
        case SNAKE_LEFT:
            head->x--;
            break;
        case SNAKE_RIGHT:
            head->x++;
            break;  
    }

    Snake *track = head;

    if(track->next != NULL){
        track = track->next;
    }

    while(track != NULL){ 

        int save_x = track->x;
        int save_y = track->y;

        track->x = prev_x;
        track->y = prev_y;   

        track = track->next;

        prev_x = save_x;
        prev_y = save_y;
    }
}

void generate_apple(){
    Apple.x = rand() % GRID_SIZE;
    Apple.y = rand() % GRID_SIZE;
}

void render_snake(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 255);
    int seg_size = WINDOW_HEIGHT / GRID_SIZE;

    SDL_Rect seg;
    seg.w = seg_size;
    seg.h = seg_size;

    Snake *track = head;

    while(track != NULL){
        seg.x = track->x * seg_size;
        seg.y = track->y * seg_size;
        SDL_RenderFillRect(renderer, &seg);

        track = track->next;
    }
}

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
    apple.x = x * apple_size;
    apple.y = y * apple_size;

    SDL_RenderFillRect(renderer, &apple);
}

int main(){
    srand(time(0));

    generate_apple();

    init_snake();
    increase_snake();

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
                        case SDLK_w:
                            if(head->dir != SNAKE_DOWN)
                                head->dir = SNAKE_UP;
                            break;
                        case SDLK_s:
                            if(head->dir != SNAKE_UP)
                                head->dir = SNAKE_DOWN;
                            break;
                        case SDLK_a:
                            if(head->dir != SNAKE_RIGHT)
                                head->dir = SNAKE_LEFT;
                            break;
                        case SDLK_d:
                            if(head->dir != SNAKE_LEFT)
                                head->dir = SNAKE_RIGHT;
                            break;
                    }
                    break;
            }
        }

        SDL_RenderClear(renderer);

        move_snake();

        //Render Loop
        render_grid(renderer);
        render_snake(renderer);
        render_apple(renderer, Apple.x, Apple.y);

        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 100);
        SDL_RenderPresent(renderer);

        SDL_Delay(150);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
