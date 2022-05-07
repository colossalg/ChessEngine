#pragma once

#include "AsciiUI.h"
#include "Board.h"

namespace ChessEngine
{
    class Game
    {
    public:

        // Start the game, get player options (colour to play, etc.) then enter game loop
        void StartGame();

    private:

        // Get the computer's move for this turn
        std::optional<Move> GetComputerMove();

        // Get the player's move for this turn
        std::optional<Move> GetPlayerMove();

        bool m_isPlayerQuitting = false;    // Whether the player is in the act of quitting the game

        bool m_isComputerWhite; // Whether the computer is playing white or not

        Board m_board;  // The current board for this game

        AsciiUI m_tui;  // The tui for this game
    };
}
