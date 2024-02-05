#include <raylib.h>
#include <stdio.h>

#include "procgen.h"
#include "tile.h"

TileData genToTile(TileGenData genData) {
    if (genData.isWater) {
        return (TileData) {TILE_WATER, TILE_MOD_NONE};
    }
    
    if (genData.altitude < 0.6) {
        return (TileData) {TILE_GRASS, TILE_MOD_NONE};
    } else if (genData.altitude < 0.7) {
        return (TileData) {TILE_MOUNTAIN, TILE_MOD_NONE};
    } else {
        return (TileData) {TILE_MOUNTAIN, TILE_MOD_SNOWY};
    }
}

void drawTile(TileData tile, int x, int y) {
    Color colour;
    switch (tile.baseType) {
        case TILE_WATER:
            colour = BLUE;
            break;
        case TILE_SHORE:
            colour = YELLOW;
            break;
        case TILE_GRASS:
            colour = GREEN;
            break;
        case TILE_MOUNTAIN:
            switch (tile.modifier) {
                case TILE_MOD_SNOWY:
                    colour = WHITE;
                    break;
                default:
                    colour = GRAY;
                    break;
            }
            break;
        default:
            colour = DARKGRAY;
    }

    DrawRectangle(x*TILE_WIDTH, y*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, colour);
}
