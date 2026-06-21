// Воркшоп «Цепочка логгеров»: workshop_logger_chain_tutorial.md
// Эталон с пояснениями: workshop_logger_chain_solution.cpp
//
// Ниже — рабочая программа с демонстрационными вызовами (как в эталоне), чтобы
// можно было сразу собрать, запустить и сравнить вывод. По туториалу классы
// можно удалить и восстановить самостоятельно, ориентируясь на main и на эталон.

#include <iostream>
#include <sstream>
#include <string>
#include "Logger.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "FilteringLogger.h"
#include "TimestampLogger.h"


int main() {
    // 1) Листья: прямой вызов log, FileLogger — накопление и dump()
    std::cout << "=== Прямые «листья» ===\n";
    ConsoleLogger console;
    console.log(LogLevel::Info, "прямой вызов ConsoleLogger");

    FileLogger fileOnly("log.txt");
    fileOnly.log(LogLevel::Warning, "строка только в буфер");
    fileOnly.dump();

    // 2) Декоратор + лист: фильтр по уровню, next->log — виртуальный вызов в консоль
    std::cout << "\n=== Фильтр -> консоль ===\n";
    ConsoleLogger backConsole;
    FilteringLogger toConsole(LogLevel::Warning, &backConsole);

    toConsole.log(LogLevel::Info, "не дойдёт до консоли");
    toConsole.log(LogLevel::Error, "дойдёт до консоли");

    // 3) Цепочка: метка времени -> фильтр -> буфер «файла»
    std::cout << "\n=== Метка -> фильтр -> файл ===\n";
    FileLogger fileSink;
    FilteringLogger severityGate(LogLevel::Warning, &fileSink);
    TimestampLogger pipeline(&severityGate);

    pipeline.log(LogLevel::Debug, "отладка");
    pipeline.log(LogLevel::Info, "информация");
    pipeline.log(LogLevel::Warning, "предупреждение");
    pipeline.log(LogLevel::Error, "ошибка");

    fileSink.dump();

    // 4) Полиморфизм: клиент emit(Logger&) не знает про декораторы
    std::cout << "\n=== Полиморфизм: Logger& на голове цепочки ===\n";
    Logger& root = pipeline;
    //emit(root, LogLevel::Error, "через ссылку на базу");
    fileSink.dump();

    // 5) dynamic_cast к листу (успех), доступ к API FileLogger
    std::cout << "\n=== dynamic_cast к «листу» ===\n";
    Logger* ptr = &console;
    if (auto* asConsole = dynamic_cast<ConsoleLogger*>(ptr)) {
        asConsole->log(LogLevel::Info, "восстановили тип ConsoleLogger");
    }

    Logger* filePtr = &fileSink;
    if (auto* asFile = dynamic_cast<FileLogger*>(filePtr)) {
        asFile->log(LogLevel::Info, "дописали через указатель после cast");
        asFile->dump();
    }

    // 6) dynamic_cast от головы цепочки к FileLogger — nullptr (тип — TimestampLogger)
    std::cout << "\n=== dynamic_cast по цепочке (ожидаем nullptr) ===\n";
    Logger* headPtr = &pipeline;
    if (dynamic_cast<FileLogger*>(headPtr)) {
        std::cout << "не должно напечататься\n";
    } else {
        std::cout << "голова цепочки — не FileLogger; нужен указатель на лист или обход\n";
    }

    return 0;
}
