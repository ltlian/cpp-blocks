#include "ShapeRender.h"
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"

void ShapeRender::triangle(SDL_Renderer *renderer)
{
  filledTrigonRGBA(renderer, 10, 10, 10, 500, 500, 500, 0, 100, 200, 122);
};