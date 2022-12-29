#include "ShapeRender.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <iterator>
#include <vector>

int ShapeRender::triangle(SDL_Renderer *renderer)
{
  Uint32 color = 0x8010FF80;

  return filledTrigonColor(renderer, 10, 10, 10, 500, 500, 500, color);
};

int ShapeRender::draw_grid(
        SDL_Renderer *renderer, size_t grid_size, Vector2 bounds)
{
  for (size_t c = 0; c < bounds.x; c += grid_size)
  {
    if (SDL_RenderDrawLine(renderer, c, 0, c, bounds.y) != 0)
      return -1;
  }

  for (size_t r = 0; r < bounds.y; r += grid_size)
  {
    if (SDL_RenderDrawLine(renderer, 0, r, bounds.x, r) != 0)
      return -1;
  }

  return 0;
}

int ShapeRender::test0(SDL_Renderer *renderer)
{
  Sint16 vx[]  = { 100, 300, 200 };
  Sint16 vy[]  = { 100, 100, 300 };
  Uint32 color = 0xA0101010;

  return filledPolygonColor(renderer, vx, vy, 3, color);
}

int ShapeRender::test1(
        SDL_Renderer *renderer, std::vector<Vector2> shape, size_t shape_size)
{
  SDL_Point *points = new SDL_Point[shape_size];

  points = new SDL_Point[shape_size];

  for (size_t i = 0; i < shape_size; i++)
  {
    points[i] = { shape[i].x, shape[i].y };
  }

  return SDL_RenderDrawLines(renderer, points, shape_size);
}

int ShapeRender::test2(
        SDL_Renderer *renderer, std::vector<Vector2> shape, size_t shape_size)
{
  Sint16 vx[shape_size];
  Sint16 vy[shape_size];

  for (size_t i = 0; i < shape_size; i++)
  {
    vx[i] = shape[i].x;
    vy[i] = shape[i].y;
  }

  Uint32 color = 0xFF10FF80;

  return filledPolygonColor(renderer, vx, vy, shape_size, color);
}

int ShapeRender::test3(
        SDL_Renderer *renderer, std::vector<Vector2> points, size_t shape_size)
{
  SDL_Rect rects[shape_size];

  for (size_t i = 0; i < shape_size; i++)
  {
    rects[i] = { points[i].x, points[i].y, 16, 16 };
  }

  return SDL_RenderFillRects(renderer, rects, shape_size);
}