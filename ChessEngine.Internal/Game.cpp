#include "pch.h"

#include "Game.h"

#include <exception>
#include <iostream>
#include <optional>
#include <regex>
#include <string>
#include <tuple>

#include "Helper.h"
#include "Move.h"
#include "MoveGenerator.h"
#include "Search.h"

namespace ChessEngine
{
    void Game::StartGame()
    {
        std::cout << "Welcome to Colossal_G's chess engine!!!" << std::endl;

        // Prompt the player for any information required to start the game, eg. what colour they want to play

        std::string playerColourStr;
        while (playerColourStr != "w" && playerColourStr != "b")
        {
            std::cout << "Would you like to play white or black? [w/b]: ";
            std::cin  >> playerColourStr;
        }
        m_isComputerWhite = (playerColourStr == "b");

        // Enter the game loop, prompting the player and the computer for
        // moves, updating the board accordingly until the game is over

        while (true)
        {
            if (m_isComputerWhite == m_board.GetWhiteToPlay())
            {
                const Move move = *GetComputerMove();
                m_board.MakeMove(move);
            }
            else
            {
                std::cout << m_tui.GetAscii(m_board);
                std::cout.flush();

                const Move move = *GetPlayerMove();

                if (m_isPlayerQuitting)
                {
                    break;
                }

                m_board.MakeMove(move);
            }
        }
    }

    std::optional<Move> Game::GetComputerMove()
    {
        std::pair<Move, int> searchResult = m_search.SearchPosition(m_board, 7);
        Move bestMove = searchResult.first;
        int  bestEval = searchResult.second;

        return bestMove;
    }

    std::optional<Move> Game::GetPlayerMove()
    {
        static const std::regex moveRegex("^([a-h][1-8])(x)?([a-h][1-8])$");

        std::string moveStr;
        while (!std::regex_match(moveStr, moveRegex) && moveStr != "o-o" && moveStr != "o-o-o" && moveStr != "quit")
        {
            std::cout << "Please enter your move: ";
            std::cin  >> moveStr;
        }
        std::cout << std::endl;

        std::optional<Move> playerMove;
        if (std::regex_match(moveStr, moveRegex))
        {
            std::smatch moveMatch;
            std::regex_match(moveStr, moveMatch, moveRegex);

            auto matchIt = moveMatch.begin();
            matchIt++;

            // BUG: En-passan is not currently working.
            if (moveMatch.size() == 2)
            {
                const Square init = Helper::SquareFromString(*matchIt);
                matchIt++;
                const Square dest = Helper::SquareFromString(*matchIt);

                playerMove = Move(init, dest);
            }
            else
            {
                const Square init = Helper::SquareFromString(*matchIt);
                matchIt++;
                matchIt++;
                const Square dest = Helper::SquareFromString(*matchIt);

                playerMove = Move(init, dest, true);
            }
        }
        else if (moveStr == "o-o")
        {
            const Square init = Helper::SquareFromString(m_board.GetWhiteToPlay() ? "e1" : "e8");
            const Square dest = Helper::SquareFromString(m_board.GetWhiteToPlay() ? "g1" : "g8");
            playerMove = Move(init, dest, Move::Special::KingsideCastles);
        }
        else if (moveStr == "o-o-o")
        {
            const Square init = Helper::SquareFromString(m_board.GetWhiteToPlay() ? "e1" : "e8");
            const Square dest = Helper::SquareFromString(m_board.GetWhiteToPlay() ? "c1" : "c8");
            playerMove = Move(init, dest, Move::Special::QueensideCastles);
        }
        else if (moveStr == "quit")
        {
            m_isPlayerQuitting = true;
        }
        else
        {
            throw std::runtime_error("Move provided was of illegal format: moveStr = " + moveStr);
        }

        return playerMove;
    }
}
