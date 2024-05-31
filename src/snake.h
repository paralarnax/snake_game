#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Graphics 
#include <SDL2/SDL.h>

#define WINDOW_X 100
#define WINDOW_Y 100
#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 1000

#define GRID_SIZE 20

enum{
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_RIGHT,
    SNAKE_LEFT
};

struct snake{
    int x;
    int y;
    int dir;

    struct snake *next;
};

typedef struct snake Snake;

Snake *head;
Snake *tail;