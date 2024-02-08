#include "game.h"
#include <random>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

// if we destroy the game object, we need to free the memory of the sounds and music
Game::~Game(){
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock(){
    if (blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.drawGrid();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed){
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft(){
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight(){
    if (!gameOver){
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown(){
    if (!gameOver){
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        if (grid.isOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if (!gameOver){
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false){
            currentBlock.UndoRotation();
        }
        else{
            PlaySound(rotateSound);
        }
    }
}

void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.clearAllRows();
    if (rowsCleared > 0){
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles){
        if (grid.isEmpty(item.row, item.column) == false){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.startGrid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch (linesCleared){
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        default:
            break;
    }

    score += moveDownPoints;
}
