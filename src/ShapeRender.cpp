#include "ShapeRender.hpp"
#include "GridArea.hpp"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <iterator>
#include <vector>

int ShapeRender::DrawGrid(SDL_Renderer *renderer, const GridArea &gridArea)
{
  for (size_t c = 0; c < (gridArea.size.x + 2) * (gridArea.cellSize.x);
          c += gridArea.cellSize.x)
  {
    if (SDL_RenderDrawLine(renderer,
                c + gridArea.renderOffset.x,
                0,
                c + gridArea.renderOffset.y,
                (gridArea.size.y * 2) * gridArea.cellSize.y) != 0)
      return -1;
  }

  for (size_t r = 0; r < (gridArea.size.y + 2) * gridArea.cellSize.y;
          r += gridArea.cellSize.y)
  {
    if (SDL_RenderDrawLine(renderer,
                0,
                r + gridArea.renderOffset.y,
                (gridArea.size.x + 2) * gridArea.cellSize.x,
                r) != 0)
      return -1;
  }

  return 0;
}

int ShapeRender::DrawWalls(SDL_Renderer *renderer, const GridArea &gridArea)
{
  SDL_Rect rects[] = { //

    { // Left wall
            gridArea.renderOffset.x,
            gridArea.renderOffset.y + gridArea.cellSize.y,
            gridArea.cellSize.x,
            gridArea.cellSize.y * gridArea.size.y },

    { // Right wall
            gridArea.renderOffset.x +
                    (gridArea.cellSize.x * (gridArea.size.x + 1)),
            gridArea.renderOffset.y + gridArea.cellSize.y,
            gridArea.cellSize.x,
            gridArea.cellSize.y * gridArea.size.y },
    { // Top wall
            gridArea.renderOffset.x,
            gridArea.renderOffset.y,
            gridArea.cellSize.x * (gridArea.size.x + 2),
            gridArea.cellSize.y },
    { // Bottom wall
            gridArea.renderOffset.x,
            gridArea.renderOffset.y +
                    (gridArea.cellSize.y * (gridArea.size.y + 1)),
            gridArea.cellSize.x * (gridArea.size.x + 2),
            gridArea.cellSize.y }
  };

  return SDL_RenderFillRects(renderer, rects, 4);
}

int ShapeRender::DrawPointsAsBlocks(SDL_Renderer *renderer,
        const std::vector<Vector2> &              points,
        const GridArea &                          gridArea)
{
  size_t                shape_size = sizeof(points);
  std::vector<SDL_Rect> rects      = std::vector<SDL_Rect>(shape_size);

  for (size_t i = 0; i < shape_size; i++)
  {
    rects[i] = { //
      (points[i].x * gridArea.cellSize.x) + gridArea.renderOffset.x,
      (points[i].y * gridArea.cellSize.y) + gridArea.renderOffset.y,
      gridArea.cellSize.x,
      gridArea.cellSize.y
    };
  }

  return SDL_RenderFillRects(renderer, rects.data(), shape_size);
}
