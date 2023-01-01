#include "SDL.h"
#include "ShapeRender.hpp"
#include <iostream>

#define WINDOW_TITLE "Hello SDL2!"

const GridArea GameArea =
        GridArea{ Vector2(4, 4), Vector2(32, 32), Vector2(0, 0) };

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize. Error: " << SDL_GetError()
              << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow( //
          WINDOW_TITLE,
          SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          (GameArea.cellSize.x * 2) + (GameArea.cellSize.x * GameArea.size.x),
          (GameArea.cellSize.y * 2) + (GameArea.cellSize.y * GameArea.size.y),
          SDL_WINDOW_SHOWN);

  if (window == nullptr)
  {
    std::cerr << "Window could not be created. Error: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return 1;
  }

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

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  bool                 isRunning = true;
  Vector2              input     = { 0, 0 };
  SDL_Event            e;
  std::vector<Vector2> playerBlocks = {
    { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, { 1, 2 }
  };

  // Main loop

  while (isRunning)
  {
    input.x = 0;
    input.y = 0;

    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        isRunning = false;
      }

      else if (e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
          input.x = -1;
          break;
        case SDLK_RIGHT:
          input.x = 1;
          break;
        case SDLK_UP:
          input.y = -1;
          break;
        case SDLK_DOWN:
          input.y = 1;
          break;
        default:
          break;
        }
      }
    }

    // Update state

    for (int i = 0; i < playerBlocks.size(); i++)
    {
      playerBlocks[i] += input;
    }

    // Render new state

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 130, 130, 30, SDL_ALPHA_OPAQUE);
    ShapeRender::DrawPointsAsBlocks(renderer, playerBlocks, GameArea);

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, SDL_ALPHA_OPAQUE);
    ShapeRender::DrawWalls(renderer, GameArea);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 20);
    ShapeRender::DrawGrid(renderer, GameArea);

    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(10);
  }

  return 0;
}
