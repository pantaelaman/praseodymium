#include <stdio.h>
#include <raylib.h>
#include <raygui.h>

#include "procgen.h"
#include "tile.h"
#include "mapgen.h"

#define DEF_TILE_SIZE 8
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GRID_SIZE 256

int main() {
    InitWindow(640, 480, "praseodymium");
    SetTargetFPS(60); 

    initGeneration(DEF_TILE_SIZE, DEF_TILE_SIZE);
    TileData** map;
    generateMap(GRID_SIZE, GRID_SIZE, &map);

    Camera2D camera = { 0 };
    camera.target = (Vector2) { DEF_TILE_SIZE * GRID_SIZE / 2, DEF_TILE_SIZE * GRID_SIZE / 2 };
    camera.offset = (Vector2) { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    int swidth, sheight;
    int x, y;
    int deltaX, deltaY;
    float deltaZ;
    float frameTime;
    while (!WindowShouldClose()) {
        sheight = GetScreenHeight();
        swidth = GetScreenWidth();

        camera.offset.x = swidth / 2;
        camera.offset.y = sheight / 2;

        deltaX =
            (IsKeyDown(KEY_RIGHT) | IsKeyDown(KEY_D)) -
            (IsKeyDown(KEY_LEFT) | IsKeyDown(KEY_A));
        deltaY =
            (IsKeyDown(KEY_DOWN) | IsKeyDown(KEY_S)) -
            (IsKeyDown(KEY_UP) | IsKeyDown(KEY_W));
        deltaZ =
            (GetMouseWheelMove() * 0.05f);

        camera.target.x += deltaX * 16 / camera.zoom;
        if (camera.target.x - camera.offset.x < 0) camera.target.x = camera.offset.x;
        else if ((camera.target.x - camera.offset.x + swidth) / camera.zoom > GRID_SIZE * DEF_TILE_SIZE) camera.target.x = GRID_SIZE * DEF_TILE_SIZE - camera.offset.x;
        camera.target.y += deltaY * 16 / camera.zoom;
        if (camera.target.y - camera.offset.y < 0) camera.target.y = camera.offset.y;
        else if (camera.target.y - camera.offset.y + sheight > GRID_SIZE * DEF_TILE_SIZE) camera.target.y = GRID_SIZE * DEF_TILE_SIZE - camera.offset.y;

        BeginDrawing();
        BeginMode2D(camera);

        ClearBackground(RAYWHITE);
        for (
            x = ((camera.target.x - camera.offset.x)) / (DEF_TILE_SIZE) - 1;
            x < ((camera.target.x + swidth - camera.offset.x)) / DEF_TILE_SIZE;
            x++
        ) {
            if (x >= GRID_SIZE) break;
            else if (x < 0) continue;
            for (
                y = ((camera.target.y - camera.offset.y)) / (DEF_TILE_SIZE) - 1;
                y < ((camera.target.y + sheight - camera.offset.y)) / DEF_TILE_SIZE;
                y++
            ) {
                if (y >= GRID_SIZE) break;
                else if (y < 0) continue;
                drawTile(map[y][x], x, y);
            }
        }

        EndMode2D();

        DrawFPS(10, 10);
        
        EndDrawing();
    }
}

