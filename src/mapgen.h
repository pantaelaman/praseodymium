#ifndef mapgen_h_INCLUDED
#define mapgen_h_INCLUDED

#include "procgen.h"
#include "tile.h"

extern int GRID_WIDTH;
extern int GRID_HEIGHT;

void generateMap(int width, int height, TileData*** map);

#endif // mapgen_h_INCLUDED
