#include <iterator>
#include <stdexcept>
#include <unistd.h>
#include <vector>

#include <iostream>

#include "SDL2_gfxPrimitives.h"
#include "ShapeRender.h"
#include "Vector2.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GRID_SIZE 16
#define FALL_SPEED 1
#define TURN_RATE_MS 500
#define WINDOW_TITLE "Hello SDL2!"
#define WINDOW_TEXT "Hello World!"

void PrintKeyInfo(SDL_KeyboardEvent *key)
{
  if (key->type == SDL_KEYUP)
    printf("Release:- ");
  else
    printf("Press:- ");

  printf("Scancode: 0x%02X", key->keysym.scancode);
  printf(", Name: %s", SDL_GetKeyName(key->keysym.sym));
  printf("\n");
}

int main(int argc, char *argv[])
{
  int size = 10;

  Vector2 grid_unit = Vector2(GRID_SIZE, GRID_SIZE);
  Vector2 delta     = grid_unit * Vector2(0, FALL_SPEED);

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize. Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  // Create the window
  SDL_Window *window = SDL_CreateWindow( //
          WINDOW_TITLE,
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          SCREEN_WIDTH,
          SCREEN_HEIGHT,
          SDL_WINDOW_SHOWN);

  if (window == nullptr)
  {
    std::cerr << "Window could not be created. Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create the renderer
  SDL_Renderer *renderer =
          SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr)
  {
    std::cerr << "Renderer could not be created. Error: " << SDL_GetError()
              << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int tick      = 0;
  int turn      = 0;
  int next_turn = 0;

  clock_t c_start = clock();
  clock_t c_start_turn;
  clock_t c_dlt = clock() - c_start;

  Vector2 center = Vector2(SCREEN_WIDTH / 2, 0);

  std::vector<Vector2> shape_line_hor = { //
    (Vector2(0, 0) * GRID_SIZE) + center,
    (Vector2(1, 0) * GRID_SIZE) + center,
    (Vector2(2, 0) * GRID_SIZE) + center,
    (Vector2(2, 0) * GRID_SIZE) + center
  };

  std::vector<Vector2> shape_cross = { //
    (Vector2(1, 0) * GRID_SIZE) + center,
    (Vector2(0, 1) * GRID_SIZE) + center,
    (Vector2(1, 1) * GRID_SIZE) + center,
    (Vector2(2, 1) * GRID_SIZE) + center,
    (Vector2(1, 2) * GRID_SIZE) + center,
    (Vector2(1, 2) * GRID_SIZE) + center
  };

  std::vector<Vector2> shape_l_rev = { //
    (Vector2(2, 0) * GRID_SIZE) + center,
    (Vector2(2, 1) * GRID_SIZE) + center,
    (Vector2(0, 2) * GRID_SIZE) + center,
    (Vector2(1, 2) * GRID_SIZE) + center,
    (Vector2(2, 2) * GRID_SIZE) + center
  };

  std::vector<Vector2> shape_line_ver = { //
    (Vector2(0, 0) * GRID_SIZE) + center,
    (Vector2(0, 1) * GRID_SIZE) + center,
    (Vector2(0, 2) * GRID_SIZE) + center,
    (Vector2(0, 3) * GRID_SIZE) + center
  };

  std::vector<Vector2> shape_square = { //
    (Vector2(0, 0) * GRID_SIZE) + center,
    (Vector2(0, 1) * GRID_SIZE) + center,
    (Vector2(0, 2) * GRID_SIZE) + center
  };

  std::vector<std::vector<Vector2>> shapes = {
    shape_line_hor, shape_cross, shape_l_rev, shape_line_ver, shape_square
  };

  size_t               next_shape      = 0;
  size_t               next_next_shape = 0;
  bool                 running         = true;
  std::vector<Vector2> shape           = shapes[next_shape];
  Vector2              bounds          = Vector2(SCREEN_WIDTH, SCREEN_HEIGHT);

  while (running)
  {
    size_t rnd        = rand() % std::size(shapes);
    size_t shape_size = std::size(shape);

    if (next_next_shape > next_shape)
    {
      next_shape = next_next_shape;
      shape      = shapes[next_shape % std::size(shapes)];
    }

    c_start_turn       = clock();
    c_dlt              = clock() - c_start;
    next_turn          = (c_dlt / TURN_RATE_MS);
    Vector2 from_input = Vector2(0, 0);

    tick++;

    SDL_Event event;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
          next_next_shape++;
        case SDLK_LEFT:
          from_input.x = -1;
          break;
        case SDLK_RIGHT:
          from_input.x = 1;
          break;
        case SDLK_UP:
          from_input.y = -1;
          break;
        case SDLK_DOWN:
          from_input.y = 1;
          break;
        default:
          break;
        }
        break;
      default:
        break;
      }
    }

    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 122, 0, SDL_ALPHA_OPAQUE);

    if (turn < next_turn)
    {
      std::string aoc_input = ">>><<><>><<<>><>>><<<>>><<<><<<>><>><<>>";

      char *dr = &aoc_input[turn % aoc_input.length()];
      switch (*dr)
      {
      case '>':
        from_input.x = 1;
        break;
      case '<':
        from_input.x = -1;
        break;
      default:
        throw std::out_of_range(dr);
      }

      for (size_t i = 0; i < shape_size; i++)
      {
        shape[i] += (from_input * grid_unit);
        shape[i] += delta;
      }

      turn = next_turn;
    }

    ShapeRender::draw_grid(renderer, GRID_SIZE, bounds);
    ShapeRender::triangle(renderer);
    SDL_SetRenderDrawColor(renderer, 122, 122, 255, SDL_ALPHA_OPAQUE);
    ShapeRender::test3(renderer, shape, shape_size);

    SDL_RenderPresent(renderer);

    SDL_UpdateWindowSurface(window);

    clock_t diff = clock() - c_start_turn;

    // SDL_Delay(diff + 100);
    SDL_Delay(100);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
