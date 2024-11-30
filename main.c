#include <SDL2/SDL.h>
#include <stdio.h>

#define MAIN_WINDOW_WIDTH 900
#define MAIN_WINDOW_HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_GRAY 0x0f0f0f0f
#define LINE_WIDTH 1
#define CELL_SIZE 20

Uint32 CELL_COLOR = COLOR_WHITE;
Uint32 GRID_COLOR = COLOR_GRAY;

void draw_grid(SDL_Surface* surface, int cols, int rows) {
  for (int i = 0; i < rows; i++) {
    SDL_Rect line = (SDL_Rect) {0, i*CELL_SIZE, MAIN_WINDOW_WIDTH, LINE_WIDTH};
    SDL_FillRect(surface, &line, GRID_COLOR);
  }

  for (int i = 0; i < cols; i++) {
    SDL_Rect line = (SDL_Rect) {i*CELL_SIZE, 0, LINE_WIDTH, MAIN_WINDOW_HEIGHT};
    SDL_FillRect(surface, &line, GRID_COLOR);
  }
}

void draw_cell(SDL_Surface* surface, int cellX, int cellY) {
  int pixelX = cellX * CELL_SIZE + LINE_WIDTH, pixelY = cellY * CELL_SIZE + LINE_WIDTH;
  int CELL_IN_GRID_SIZE = CELL_SIZE - (2 * LINE_WIDTH);

  SDL_Rect cell = (SDL_Rect) {pixelX, pixelY, CELL_IN_GRID_SIZE, CELL_IN_GRID_SIZE};
  SDL_FillRect(surface, &cell, CELL_COLOR);
}

int main() {
    printf("Conway's Game of Life\n");
    SDL_Init(SDL_INIT_VIDEO);

    char* title = "Convey's Game of Life";
    SDL_Window* main_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(main_window);
    
    // SDL_Rect rect = (SDL_Rect){30, 40, 30, 30};
    // SDL_FillRect(surface, &rect, color_white);
    
    int cols = MAIN_WINDOW_WIDTH/CELL_SIZE, rows = MAIN_WINDOW_HEIGHT/CELL_SIZE;
    draw_grid(surface, cols, rows);
    
    int midX = cols/2, midY = rows/2;
    draw_cell(surface, midX, midX);
    draw_cell(surface, midX + 1, midX + 1);
    draw_cell(surface, midX + 1, midX - 1);
    draw_cell(surface, midX + 2, midX);

    SDL_UpdateWindowSurface(main_window);    
    SDL_Delay(5000);
    SDL_DestroyWindow(main_window);
    SDL_Quit();
}


// gcc -o main main.c `sdl2-config --cflags --libs`
