#include <stdio.h>
#include <stdlib.h>

#include "mapgen.h"

int GRID_WIDTH;
int GRID_HEIGHT;

void generateMap(int width, int height, TileData*** map) {
    GRID_WIDTH = width;
    GRID_HEIGHT = height;
    *map = calloc(height, sizeof(TileData *));
    for (int y = 0; y < height; y++) {
        (*map)[y] = calloc(width, sizeof(TileData));
        for (int x = 0; x < width; x++) {
            (*map)[y][x] = genToTile(getDataForTile(x, y)); 
        }
    }
}
