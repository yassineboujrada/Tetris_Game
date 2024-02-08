#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int screenWidth = 600;
    const int screenHeight = 800;
    Color dARKBLUE = {44,44,127,255} ;

    cout << "Game Runing ... " << endl;

    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(dARKBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}