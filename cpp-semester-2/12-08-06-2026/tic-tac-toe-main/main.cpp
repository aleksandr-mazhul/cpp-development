#include <iostream>
#include <stdexcept>
#include <utility>

#include <fstream>

#include "Game.h"
#include "HumanPlayer.h"
#include "BotPlayer.h"
#include "SmartBotPlayer.h"

int main()
{
    std::cout << "Tic-Tac-Toe skeleton scenario\n";

    /*try {
        HumanPlayer playerX("Player 1", 'X');
        HumanPlayer playerO("Player 2", 'O');
        Game game(std::move(playerX), std::move(playerO),3);
        game.run();
    }
    catch (const std::logic_error& e) {
        std::cout << "Caught stub: " << e.what() << '\n';
        std::cout << "Implement the method and run again.\n";
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << '\n';
    }*/
    try
    {
        auto playerX = std::make_unique<HumanPlayer>("Yaroslav", 'X');
        auto playerO = std::make_unique<SmartBotPlayer>("Smart Bot", 'O');
        //auto playerX = std::make_unique<HumanPlayer>("Player 1", 'X');
        //auto playerO = std::make_unique<BotPlayer>("Player 2", 'O');
        Game game(std::move(playerO), std::move(playerX), 3);
        std::ofstream fout("player.txt");
        game.run(fout);
        fout.close();
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Caught stub: " << e.what() << '\n';
        std::cout << "Implement the method and run again.\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    return 0;
}
