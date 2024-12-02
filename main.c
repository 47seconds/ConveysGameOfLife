#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdio.h>
#include <stdlib.h>

#define MAIN_WINDOW_WIDTH 900
#define MAIN_WINDOW_HEIGHT 600
#define COLOR_BLACK 0x00000000
#define COLOR_WHITE 0xffffffff
#define COLOR_GRAY 0x0f0f0f0f
#define LINE_WIDTH 1
#define CELL_SIZE 20
#define SIMULATION_SPEED 100

Uint32 CELL_COLOR = COLOR_WHITE;
Uint32 GRID_COLOR = COLOR_GRAY;
Uint32 CELL_BLACK = COLOR_BLACK;

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

void draw_cell(SDL_Surface* surface, int cellX, int cellY, Uint64 color) {
  int pixelX = cellX * CELL_SIZE + LINE_WIDTH, pixelY = cellY * CELL_SIZE + LINE_WIDTH;
  int CELL_IN_GRID_SIZE = CELL_SIZE - (2 * LINE_WIDTH);

  SDL_Rect cell = (SDL_Rect) {pixelX, pixelY, CELL_IN_GRID_SIZE, CELL_IN_GRID_SIZE};
  SDL_FillRect(surface, &cell, color);
}

int** make_grid(int rows, int cols) {
  int** grid = (int**)malloc(rows * sizeof(int*));
  for (int i = 0; i < rows; i++) grid[i] = (int*)malloc(cols * sizeof(int));
  if (!grid) {
    printf("ERROR: Unable to allocate memory to grid!");
    exit(1);
  }
  return grid;
}

int count_neighbours(int** grid, int rows, int cols, int y, int x) {
  int alive = 0;

  for (int i = y-1; i < y + 2; i++) {
    for (int j = x-1; j < x + 2; j++) {
      if (i == y && j == x) continue;
      else if (i >= 0 && j >= 0 && i < rows && j < cols && grid[i][j]) alive++;
    }
  }

  return alive;

}
void initialize_random_grid (int** grid, int rows, int cols) {
  for (int i = 0; i < rows; i++) {  
    for (int j = 0; j < cols; j++) grid[i][j] = rand() % 2;
  }
}

void backend_next_generation (int** grid, int rows, int cols) {
  int **temp_grid = (int**)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) temp_grid[i] = (int*)malloc(cols * sizeof(int));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int neighbours_alive = count_neighbours(grid, rows, cols, i, j);
      if (neighbours_alive < 2 || neighbours_alive > 3) temp_grid[i][j] = 0;
      else if (neighbours_alive == 3) temp_grid[i][j] = 1;
      else temp_grid[i][j] = grid[i][j];
    }
  }

  for(int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) grid[i][j] = temp_grid[i][j];
  }

  for(int i = 0; i < rows; i++) free(temp_grid[i]);
  free(temp_grid);
}
void draw_conveys_game_of_life (int** grid, int rows, int cols, SDL_Surface* surface) {
  for(int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      (grid[i][j]) ? draw_cell(surface, j, i, CELL_COLOR) : draw_cell(surface, j, i, CELL_BLACK);
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

    char* title = "Conway's Game of Life";
    SDL_Window* main_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT, 0);
    SDL_Surface* surface = SDL_GetWindowSurface(main_window);
    
    int cols = MAIN_WINDOW_WIDTH/CELL_SIZE, rows = MAIN_WINDOW_HEIGHT/CELL_SIZE;
    draw_grid(surface, cols, rows);
    
    int midX = cols/2, midY = rows/2;
    int** grid = make_grid(rows, cols);
    initialize_random_grid(grid, rows, cols);
    
    int simulation_running = 1;
    SDL_Event event;
    
    while (simulation_running) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) simulation_running = 0;
      }

      draw_conveys_game_of_life(grid, rows, cols, surface);
      backend_next_generation(grid, rows, cols);

      SDL_UpdateWindowSurface(main_window);    
      SDL_Delay(SIMULATION_SPEED);
    }

    SDL_DestroyWindow(main_window);
    SDL_Quit(); 
    delete_grid(grid, rows);
    return 0;
}


// gcc -o main main.c `sdl2-config --cflags --libs`
