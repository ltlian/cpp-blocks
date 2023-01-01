#ifndef SHAPE_RENDER_H
#define SHAPE_RENDER_H

#include "GridArea.hpp"
#include "SDL.h"
#include "Vector2.hpp"
#include <vector>

class ShapeRender
{
  public:
  static int DrawGrid(SDL_Renderer *renderer, const GridArea &gridArea);
  static int DrawPointsAsBlocks(SDL_Renderer *renderer,
          const std::vector<Vector2> &        points,
          const GridArea &                    gridArea);
  static int DrawWalls(SDL_Renderer *renderer, const GridArea &gridArea);
};

#endif