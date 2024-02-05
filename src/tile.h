#ifndef tile_h_INCLUDED
#define tile_h_INCLUDED

#include "procgen.h"

typedef enum {
    TILE_WATER,
    TILE_SHORE,
    TILE_GRASS,
    TILE_MOUNTAIN,
} TileBaseType;

typedef enum {
    TILE_MOD_NONE,
    TILE_MOD_SNOWY,
} TileModifier;

typedef struct {
    TileBaseType baseType;
    TileModifier modifier;
} TileData;

TileData genToTile(TileGenData genData);
void drawTile(TileData tile, int x, int y);

#endif // tile_h_INCLUDED
