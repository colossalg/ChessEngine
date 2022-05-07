#include <iostream>
#include <iterator>
#include <random>

#include "AsciiUI.h"
#include "Board.h"
#include "Game.h"
#include "Move.h"
#include "MoveGenerator.h"

using namespace ChessEngine;

int main()
{
    Game game;
    game.StartGame();

    return 0;
}