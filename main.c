#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

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

int** make_grid(int rows, int cols) {
  int** grid = (int**)malloc(rows * sizeof(int*));
  for (int i = 0; i < rows; i++) grid[i] = (int*)malloc(cols * sizeof(int));
  if (!grid) {
    printf("ERROR: Unable to allocate memory to grid!");
    exit(1);
  }
  
  for (int i = 0; i < rows; i++) {  
    for (int j = 0; j < cols; j++) grid[i][j] = rand() % 2;
  }

  return grid;
}

void draw_conveys_game_of_life (int** grid, int rows, int cols, SDL_Surface* surface) {
  for(int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j]) draw_cell(surface, j, i);
    }
  }
}

void delete_grid(int** grid, int rows) {
  for(int i = 0; i < rows; i++) free(grid[i]);
  free(grid);
}

int main() {
    printf("Conway's Game of Life\n");
    SDL_Init(SDL_INIT_VIDEO);

    char* title = "Convey's Game of Life";
    SDL_Window* main_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(main_window);
    
    int cols = MAIN_WINDOW_WIDTH/CELL_SIZE, rows = MAIN_WINDOW_HEIGHT/CELL_SIZE;
    draw_grid(surface, cols, rows);
    
    int midX = cols/2, midY = rows/2;
    int** grid = make_grid(rows, cols);
    
    draw_conveys_game_of_life(grid, rows, cols, surface);

    SDL_UpdateWindowSurface(main_window);    
    SDL_Delay(5000);
    SDL_DestroyWindow(main_window);
    SDL_Quit(); 

    delete_grid(grid, rows);
    return 0;
}


// gcc -o main main.c `sdl2-config --cflags --libs`
