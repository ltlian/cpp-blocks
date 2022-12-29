#ifndef SHAPE_RENDER_H
#define SHAPE_RENDER_H
#include "SDL.h"
#include "Vector2.h"
#include <vector>

class ShapeRender
{
  public:
  static int draw_grid(
          SDL_Renderer *renderer, size_t grid_size, Vector2 bounds);
  static int triangle(SDL_Renderer *renderer);
  static int test0(SDL_Renderer *renderer);
  static int
  test1(SDL_Renderer *renderer, std::vector<Vector2> shape, size_t shape_size);
  static int
  test2(SDL_Renderer *renderer, std::vector<Vector2> shape, size_t shape_size);
  static int
  test3(SDL_Renderer *renderer, std::vector<Vector2> points, size_t shape_size);
};

#endif