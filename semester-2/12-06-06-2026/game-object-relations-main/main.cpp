#include <iostream>
#include <memory>
#include <stdexcept>

#include "Game.h"
#include "Player.h"
#include "ScoreManager.h"
#include "Weapon.h"

int main()
{
    std::cout << "Демонстрация сценария из задания\n";

    try
    {
        // 1) Оружие (может быть разделяемым между Player и Enemy).
        auto sharedWeapon = std::make_shared<Weapon>("Starter Sword");

        // 2) Сервис очков (используется через dependency).
        ScoreManager scoreManager;

        // 3) Игрок.
        Player player(sharedWeapon);

        // 4) Враги и уровень.
        auto enemy1 = std::make_unique<Enemy>(sharedWeapon, &player);
        auto enemy2 = std::make_unique<Enemy>(sharedWeapon, &player);

        player.setTarget(enemy1.get());
        player.rewardKill(scoreManager, 100);

        auto level = std::make_unique<Level>();
        level->addEnemy(std::move(enemy1));
        level->addEnemy(std::move(enemy2));

        // 5) Игра и уровни.
        Game game;
        game.addLevel(std::move(level));

        // 6) Контрольный вывод.
        std::cout << "Уровней в игре: " << game.levelsCount() << '\n';
        std::cout << "Оружие игрока: " << player.getWeapon().getName() << '\n';
        std::cout << "Текущий счет: " << scoreManager.getTotalScore() << '\n';
        std::cout << "Сценарий выполнен успешно.\n";
    }
    catch (const std::logic_error& e)
    {
        std::cout << "Поймана заглушка: " << e.what() << '\n';
        std::cout << "Реализуйте метод и запустите снова.\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << '\n';
    }

    return 0;
}
