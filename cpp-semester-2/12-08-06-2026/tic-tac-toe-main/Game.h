#pragma once

#include <array>
#include <utility>

#include "Board.h"
#include "HumanPlayer.h"

class Game
{
public:
    Game(std::unique_ptr<Player> first, std::unique_ptr<Player> second, int boardSize)
        : board(boardSize)
    {
        players[0] = std::move(first);
        players[1] = std::move(second);
    }


    void run(std::ostream& out = std::cout)
    {
        board.reset();
        out << "player 1:" <<(*players[0]) << std::endl;
        out << "player 2:" <<(*players[1]) << std::endl;
        board.print(std::cout);
        board.print(out);


        int current = 0;
        while (true)
        {
            const Player& player = *players[current];

            auto [row, col] = player.readMove(board);

            out << current << ": " << player << " moves to (" << row << ", " << col << ")\n";
            if (!board.placeMark(row, col, player.getMark()))
            {
                std::cout << "This cell is already taken! Try again.\n";
                continue;
            }

            board.print(std::cout);

            board.print(out);
            if (board.hasWinner(player.getMark()))
            {
                std::cout << "\n******************************\n";
                out << "\n******************************\n";
                std::cout << "*" << player.getName() << " wins!*\n";
                out  << "*" << player.getName() << " wins!*\n";
                std::cout << "******************************\n\n";
                out << "******************************\n\n";
                break;
            }

            if (board.isFull())
            {
                std::cout << "\n******************************\n";
                std::cout << "It's a draw! \n";
                std::cout << "******************************\n\n";


                out << "\n******************************\n";
                out << "It's a draw! \n";
                out << "******************************\n\n";
                break;
            }

            current = 1 - current;
        }
    }

private:
    Board board;
    std::array<std::unique_ptr<Player>, 2> players;
};
