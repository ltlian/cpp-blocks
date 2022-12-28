// #include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <SDL.h>
// #include <SDL2_gfxPrimitives.h>
#include <Vector.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GRID_SIZE 16
#define FALL_SPEED 1
#define TURN_RATE_MS 500
#define WINDOW_TITLE "Hello SDL2!"
#define WINDOW_TEXT "Hello World!"

SDL_Rect get_rect(Vector v)
{
  SDL_Rect rect;

  rect.x = v.x;
  rect.y = v.y;
  rect.w = 10;
  rect.h = 10;

  return rect;
}

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

  Vector grid_unit = Vector(GRID_SIZE, GRID_SIZE);
  Vector delta = grid_unit * Vector(0, FALL_SPEED);
  Vector block = Vector((SCREEN_WIDTH / 2) + (size / 2), 10);

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize. Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create the window
  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (window == nullptr)
  {
    std::cerr << "Window could not be created. Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create the renderer
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cerr << "Renderer could not be created. Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int tick = 0;
  int turn = 0;
  int next_turn = 0;

  clock_t c_start = clock();
  clock_t c_start_turn;
  clock_t c_dlt = clock() - c_start;

  Vector center = Vector(100, 100);

  Vector shapeSquare[] = {
      Vector(0, 0) + center,
      Vector(0, 10) + center,
      Vector(10, 10) + center,
      Vector(10, 0) + center,
      Vector(0, 0) + center};

  Vector shape[] = {
      Vector(0, 0) + center,
      Vector(10, 0) + center,
      Vector(10, -10) + center,
      Vector(20, -10) + center,
      Vector(20, -20) + center,
      Vector(-10, -20) + center,
      Vector(-10, -10) + center,
      Vector(0, -10) + center,
      Vector(0, 0) + center};

  size_t shape_size = sizeof(shape) / sizeof(shape[0]);

  SDL_Point *points = new SDL_Point[shape_size];

  bool running = true;

  while (running)
  {
    c_start_turn = clock();
    c_dlt = clock() - c_start;
    next_turn = (c_dlt / TURN_RATE_MS);
    Vector from_input = Vector(0, 0);

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
          std::cout << block.x;
          std::cout << block.y;
        case SDLK_LEFT:
          block.x -= GRID_SIZE;
          from_input.x = -1;
          break;
        case SDLK_RIGHT:
          block.x += GRID_SIZE;
          from_input.x = 1;
          break;
        case SDLK_UP:
          block.y -= GRID_SIZE;
          from_input.y = -1;
          break;
        case SDLK_DOWN:
          block.y += GRID_SIZE;
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

    for (size_t i = 0; i < shape_size; i++)
    {
      shape[i] += (from_input * grid_unit);
    }

    if (turn < next_turn)
    {
      for (size_t i = 0; i < shape_size; i++)
      {
        shape[i] += delta;
      }

      turn = next_turn;
    }

    points = new SDL_Point[shape_size];

    for (size_t i = 0; i < shape_size; i++)
    {
      points[i] = {shape[i].x, shape[i].y};
    }

    SDL_RenderDrawLines(renderer, points, shape_size);

    // TODO - Missing SDL_gfx
    // Uint32 color = SDL_MapRGBA(renderer->format, r, g, b, a);

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
