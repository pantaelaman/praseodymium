#ifndef procgen_h_INCLUDED
#define procgen_h_INCLUDED

#include <stdbool.h>

extern int TILE_WIDTH;
extern int TILE_HEIGHT;

typedef struct {
    double altitude;
    bool isWater;
} TileGenData;

void initGeneration(int tileWidth, int tileHeight);
TileGenData getDataForTile(int x, int y);

#endif // procgen_h_INCLUDED
