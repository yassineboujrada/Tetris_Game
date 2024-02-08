#include "grid.h"
#include <iostream>
#include "colors.h"

Grid :: Grid() {
    nbrRow = 20;
    nbrCol = 10;
    cellSize = 30;
    startGrid();
    colors = GetCellColors();
}

// This function is used to initialize the grid with 0

void Grid::startGrid() {
    for (int row = 0; row < nbrRow; row++){
        for (int column = 0; column < nbrCol; column++){
            grid[row][column] = 0;
        }
    }
}

void Grid :: showGrid(){
    for (int row = 0; row < nbrRow; row++){
        for (int column = 0; column < nbrCol; column++){
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid :: drawGrid(){
    for (int row = 0; row < nbrRow; row++){
        for (int column = 0; column < nbrCol; column++){
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::isOutside(int row, int column) {
    if (row >= 0 && row < nbrRow && column >= 0 && column < nbrCol){
        return false;
    }
    return true;
}

bool Grid::isEmpty(int row, int column) {
    return (grid[row][column] == 0) ? true : false;
}

int Grid::clearAllRows(){
    int completed = 0;
    for (int row = nbrRow - 1; row >= 0; row--){
        if (IsRowFull(row)){
            ClearRow(row);
            completed++;
        }
        else if (completed > 0){
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row){
    for (int column = 0; column < nbrCol; column++){
        if (grid[row][column] == 0){
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row){
    for (int column = 0; column < nbrCol; column++){
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int nbrRow)
{
    for (int column = 0; column < nbrCol; column++)
    {
        grid[row + nbrRow][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
