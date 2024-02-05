#define FNL_IMPL
#include <fastnoise.h>
#include <math.h>

#define NUM_ALTITUDE_LAYERS 3

#include "procgen.h"
#include "mapgen.h"

fnl_state ALTITUDE;
int TILE_WIDTH;
int TILE_HEIGHT;

void initGeneration(int tileWidth, int tileHeight) {
    ALTITUDE = fnlCreateState();
    ALTITUDE.noise_type = FNL_NOISE_OPENSIMPLEX2;
    ALTITUDE.frequency = 0.002f;
    TILE_WIDTH = tileWidth;
    TILE_HEIGHT = tileHeight;
}

float combineNoiseLayers(int numLayers, fnl_state* states, int x, int y) {
    float noise = 0.0f;
    float avg = 0.0f;
    int p;
    for (int i = 0; i < numLayers; i++) {
        p = 1 << i;
        noise += fnlGetNoise2D(states, p * x * TILE_WIDTH, p * y * TILE_HEIGHT) / p;
        avg += 1.0f / p;
    }
    noise /= avg;
    return noise;
}

float lerp(float a, float b, float mix) {
    return a * (1 - mix) + b * (mix);
}

TileGenData getDataForTile(int x, int y) {
    float altitude = powf(fabsf(combineNoiseLayers(NUM_ALTITUDE_LAYERS, &ALTITUDE, x, y)), 1.5f);
    float nx = 2 * (float)x / GRID_WIDTH - 1;
    float ny = 2 * (float)y / GRID_HEIGHT - 1;
    float euclidsqrDist = (powf(nx, 2) + powf(ny, 2));
    euclidsqrDist = euclidsqrDist > 1.0f ? 1.0f : euclidsqrDist;
    altitude = lerp(altitude, 1-euclidsqrDist, (1-euclidsqrDist) * 0.5);
    bool isWater = altitude < 0.4;
    
    return (TileGenData) {
        .altitude = altitude,
        .isWater = isWater,
    };
}
