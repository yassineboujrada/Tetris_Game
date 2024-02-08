#pragma once
#include <vector>
#include <raylib.h>

class Grid{
    public:
        Grid();
        void startGrid();
        void showGrid();
        void drawGrid();
        bool isOutside(int row, int column);
        bool isEmpty(int row, int column);
        int clearAllRows();
        int grid[20][10];

    private:
        bool IsRowFull(int row);
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);
        int nbrRow;
        int nbrCol;
        int cellSize;
        std::vector<Color> colors;
};