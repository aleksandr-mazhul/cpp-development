#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace
{
    // Небольшой набор ANSI-кодов для цветного вывода в консоль.
    // Это нужно только для наглядности: на математику не влияет.
    struct Color
    {
        static constexpr const char* reset = "\033[0m";
        static constexpr const char* bold = "\033[1m";
        static constexpr const char* blue = "\033[34m";
        static constexpr const char* red = "\033[31m";
        static constexpr const char* green = "\033[32m";
        static constexpr const char* yellow = "\033[33m";
        static constexpr const char* cyan = "\033[36m";
        static constexpr const char* magenta = "\033[35m";
        static constexpr const char* dim = "\033[2m";
    };

    // Результат адаптивного интегрирования.
    // Храним не только само значение интеграла, но и "служебную" информацию,
    // чтобы на защите можно было показать, как именно сходился метод.
    struct AdaptiveResult
    {
        double value = 0.0;
        int n_start = 0;
        int n_final = 0;
        double last_step_diff = 0.0;
        bool converged = false;
    };

    struct RunConfig
    {
        int n0 = 8;
        double eps_integral = 1e-6;
        double eps_sqrt = 1e-8;
        int max_refinements = 12;
        int max_newton_iter = 1000;
    };

    // Глобальные параметры для подстановки в функции, передаваемые через указатель.
    // Такой подход позволяет сохранить требование "указатель на функцию",
    // при этом подынтегральная функция получает нужные параметры через внешнее состояние.
    double t_value = 0.0;               // Текущее t для задачи sqrt(t).
    double c_value = 0.0;               // Текущий параметр c для интеграла варианта 5.
    double sqrt_eps = 1e-6;             // Точность вычисления sqrt(t) методом Ньютона.
    int max_newton_iterations = 1000;   // Защита от бесконечного цикла в Ньютоне.

    double f_sqrt(double y)
    {
        // Левая часть уравнения f(y)=0 для задачи sqrt(t):
        // y^2 - t = 0  =>  y = sqrt(t).
        return y * y - t_value;
    }

    double df_sqrt(double y)
    {
        // Производная f(y)=y^2-t: f'(y)=2y.
        return 2.0 * y;
    }

    double testLinear(double x)
    {
        // Простая тестовая функция для проверки формулы трапеций.
        return x;
    }

    bool isRootBracketed(double (*f)(double), double left, double right)
    {
        // Проверяем отделение корня "другим способом":
        // если f(left)<0 и f(right)>0, корень находится внутри [left, right].
        return f(left) < 0.0 && f(right) > 0.0;
    }

    double newtonSolve(double (*f)(double), double (*df)(double), double y0, double eps)
    {
        // Универсальный шаг метода Ньютона:
        // y_{k+1} = y_k - f(y_k)/f'(y_k)
        // Здесь f и df передаются именно через указатели на функции.
        double y_old = y0;
        double y_new = y0;

        for (int iteration = 0; iteration < max_newton_iterations; ++iteration)
        {
            const double derivative = df(y_old);
            if (std::abs(derivative) < std::numeric_limits<double>::epsilon())
            {
                // Если производная почти ноль, делить нельзя — выходим безопасно.
                break;
            }

            y_new = y_old - f(y_old) / derivative;
            if (std::abs(y_new - y_old) < eps)
            {
                // Критерий остановки из задания: |y_{k+1} - y_k| < eps.
                return y_new;
            }
            y_old = y_new;
        }

        return y_new;
    }

    double sqrtByNewton(double t, double eps)
    {
        // Эта функция решает y^2 - t = 0 методом Ньютона и возвращает sqrt(t).
        t_value = t;
        if (t < 0.0)
        {
            throw std::invalid_argument("sqrtByNewton: параметр t должен быть неотрицательным.");
        }
        if (t == 0.0)
        {
            return 0.0;
        }
        if (!isRootBracketed(f_sqrt, 0.0, t))
        {
            // Для t>0 корень sqrt(t) лежит в [0,t]. Проверяем это явно.
            throw std::runtime_error("sqrtByNewton: корень не отделен на отрезке [0, t].");
        }
        return newtonSolve(f_sqrt, df_sqrt, t, eps);
    }

    double verifySqrtEquation(double y, double t)
    {
        // Проверка найденного корня: чем ближе к нулю |y^2 - t|, тем лучше.
        return std::abs(y * y - t);
    }

    double integrand(double x)
    {
        // Подынтегральная функция варианта 5:
        // f(x) = sqrt(x^2 + c^2) / x.
        // Корень считаем НЕ std::sqrt, а через sqrtByNewton (требование задания).
        const double t = x * x + c_value * c_value;
        return sqrtByNewton(t, sqrt_eps) / x;
    }

    double primitiveF(double x, double c)
    {
        // Первообразная для sqrt(x^2+c^2)/x, нужна для аналитической проверки.
        const double root = std::sqrt(x * x + c * c);
        const double numerator = root - c;
        const double denominator = root + c;
        if (numerator <= 0.0 || denominator <= 0.0)
        {
            throw std::runtime_error("primitiveF: некорректный аргумент логарифма.");
        }
        return root + (c / 2.0) * std::log(numerator / denominator);
    }

    double analyticIntegral(double c)
    {
        // Аналитическое значение интеграла на [1,2].
        return primitiveF(2.0, c) - primitiveF(1.0, c);
    }

    double compositeTrapezoid(double (*f)(double), double a, double b, int n)
    {
        // Составная формула трапеций для произвольной f(x), переданной указателем:
        // I ≈ h * ( f(a)/2 + f(a+h) + ... + f(b)/2 ), h=(b-a)/n.
        if (n <= 0)
        {
            throw std::invalid_argument("compositeTrapezoid: n должно быть положительным.");
        }
        if (b < a)
        {
            throw std::invalid_argument("compositeTrapezoid: правая граница b должна быть >= a.");
        }

        const double h = (b - a) / static_cast<double>(n);
        double sum = 0.5 * (f(a) + f(b));
        for (int i = 1; i < n; ++i)
        {
            sum += f(a + i * h);
        }
        return h * sum;
    }

    AdaptiveResult adaptiveTrapezoid(
        double (*f)(double),
        double a,
        double b,
        int n0,
        double eps_integral,
        int max_refinements)
    {
        // "Повышенная сложность" (раздел 3.5.2):
        // считаем интеграл не при одном n, а при n, 2n, 4n, ...
        // останавливаемся, когда |I_prev - I_curr| < eps_integral.
        if (n0 <= 0)
        {
            throw std::invalid_argument("adaptiveTrapezoid: n0 должно быть положительным.");
        }
        if (eps_integral <= 0.0)
        {
            throw std::invalid_argument("adaptiveTrapezoid: eps_integral должно быть положительным.");
        }
        if (max_refinements <= 0)
        {
            throw std::invalid_argument("adaptiveTrapezoid: max_refinements должно быть положительным.");
        }

        int n = n0;
        double i_prev = compositeTrapezoid(f, a, b, n);
        double i_curr = compositeTrapezoid(f, a, b, n * 2);
        double last_diff = std::abs(i_prev - i_curr);

        AdaptiveResult result;
        result.n_start = n0;

        for (int step = 0; step < max_refinements; ++step)
        {
            n *= 2;
            i_curr = compositeTrapezoid(f, a, b, n);
            last_diff = std::abs(i_prev - i_curr);

            if (last_diff < eps_integral)
            {
                result.value = i_curr;
                result.n_final = n;
                result.last_step_diff = last_diff;
                result.converged = true;
                return result;
            }

            i_prev = i_curr;
        }

        result.value = i_curr;
        result.n_final = n;
        result.last_step_diff = last_diff;
        result.converged = false;
        return result;
    }

    std::string diffColor(double value)
    {
        if (value < 1e-6)
        {
            return Color::green;
        }
        if (value < 1e-4)
        {
            return Color::yellow;
        }
        return Color::red;
    }

    void printConfigSummary(const RunConfig& cfg)
    {
        std::cout << Color::dim
                  << "\nПараметры запуска: n0=" << cfg.n0
                  << ", eps_integral=" << std::scientific << cfg.eps_integral << std::fixed
                  << ", eps_sqrt=" << std::scientific << cfg.eps_sqrt << std::fixed
                  << ", max_удвоений=" << cfg.max_refinements
                  << ", max_Ньютон=" << cfg.max_newton_iter
                  << '\n'
                  << Color::reset;
    }

    void printDivider(const std::string& title = "")
    {
        std::cout << Color::dim << "==============================================================";
        if (!title.empty())
        {
            std::cout << "  " << title;
        }
        std::cout << Color::reset << '\n';
    }

    void printFormulaBlock()
    {
        std::cout << Color::bold << Color::cyan << "\nФОРМУЛЫ, ИСПОЛЬЗУЕМЫЕ В РЕШЕНИИ\n" << Color::reset;
        printDivider();
        std::cout << Color::yellow
                  << "1) Составная формула трапеций:\n"
                  << "   I ≈ h * ( f(a)/2 + f(a+h) + ... + f(a+(n-1)h) + f(b)/2 ),\n"
                  << "   где h = (b-a)/n.\n\n"
                  << "2) Подынтегральная функция (вариант 5):\n"
                  << "   f(x) = sqrt(x^2 + c^2) / x,  I(c) = ∫[1,2] f(x) dx.\n\n"
                  << "3) Вычисление sqrt(t) через уравнение y^2 - t = 0 (метод Ньютона):\n"
                  << "   y_(k+1) = y_k - (y_k^2 - t)/(2y_k),  y_0 = t,\n"
                  << "   остановка: |y_(k+1) - y_k| < eps_sqrt.\n\n"
                  << "4) Повышенная сложность (удвоение разбиений):\n"
                  << "   считаем I на n, 2n, 4n, ... до |I_prev - I_curr| < eps_integral.\n\n"
                  << "5) Аналитическая проверка:\n"
                  << "   F(x) = sqrt(x^2+c^2) + (c/2)*ln((sqrt(x^2+c^2)-c)/(sqrt(x^2+c^2)+c)),\n"
                  << "   I_analytic(c) = F(2) - F(1).\n"
                  << Color::reset;
        printDivider();
    }

    void printInterpretationBlock()
    {
        std::cout << Color::bold << Color::yellow
                  << "\nПОЯСНЕНИЕ К РЕЗУЛЬТАТАМ (ДЛЯ ПРОВЕРКИ)\n"
                  << Color::reset;
        std::cout << Color::dim
                  << "1) n0      — начальное число разбиений.\n"
                  << "2) n_fin   — итоговое число разбиений после удвоений n, 2n, 4n, ...\n"
                  << "3) I_num   — численно найденный интеграл (адаптивный метод трапеций).\n"
                  << "4) I_an    — аналитическое значение интеграла (эталон).\n"
                  << "5) |I-Ia|  — ошибка относительно аналитики: |I_num - I_an|.\n"
                  << "6) |dI|    — критерий остановки адаптивного метода: |I_prev - I_curr|.\n"
                  << "            При корректной работе должно выполняться: |dI| < eps_integral.\n"
                  << "7) err_sqrt — проверка вычисления sqrt(t): |y^2 - t|.\n"
                  << "             Чем ближе к нулю, тем точнее найден корень.\n"
                  << Color::reset;
        printDivider();
    }

    void printDetailedTeacherExplanation()
    {
        std::cout << Color::bold << Color::yellow
                  << "\nРАСШИФРОВКА ВЫВОДА ПО БЛОКАМ\n"
                  << Color::reset;

        std::cout
            << "\n1) Параметры запуска:\n"
            << "- n0=8 — стартовое число разбиений.\n"
            << "- eps_integral=1e-6 — точность остановки адаптивного интеграла.\n"
            << "- eps_sqrt=1e-8 — точность вычисления sqrt(t) (внутри подынтегральной функции).\n"
            << "- max_удвоений=12 — максимум шагов n -> 2n -> 4n -> ...\n"
            << "- max_Ньютон=1000 — максимум итераций Ньютона.\n"
            << "\n2) Таблица интеграла (главная):\n"
            << "Колонки:\n"
            << "- c — параметр задачи (1.0 ... 3.0).\n"
            << "- n0 — начальное разбиение.\n"
            << "- n_fin — итоговое число разбиений, при котором достигнута точность.\n"
            << "- I_num — численно найденный интеграл.\n"
            << "- I_an — аналитическое значение (эталон).\n"
            << "- |I-Ia| — ошибка относительно аналитики: |I_num - I_an|.\n"
            << "- |dI| — критерий адаптивной остановки: |I_prev - I_curr| на последнем шаге.\n"
            << "\nКак интерпретировать:\n"
            << "- n_fin больше n0 -> метод реально адаптивный (повышенная сложность выполнена).\n"
            << "- |dI| маленькое -> остановка по точности сработала правильно.\n"
            << "- |I-Ia| очень маленькое -> численный метод дает корректный результат.\n"
            << "\n3) Строка под таблицей:\n"
            << "- |I-Ia| = |I_num - I_an| — ошибка к аналитике.\n"
            << "- |dI| = |I_prev - I_curr| — внутренний критерий сходимости адаптивного метода.\n"
            << "- err_sqrt = |y^2 - t| — ошибка решения уравнения для sqrt(t).\n"
            << "\n4) Таблица 'Проверка решения уравнения y^2 - t = 0':\n"
            << "- t — тестовое значение.\n"
            << "- sqrt(t) — корень, найденный итерационно.\n"
            << "- err_sqrt — остаток |y^2 - t|.\n"
            << "\nerr_sqrt порядка 1e-16 ... 1e-15 — это очень точно.\n"
            << "\nЧто сказать преподавателю в 2 фразы:\n"
            << "\"Верхняя таблица доказывает адаптивный метод трапеций: n автоматически удваивается\n"
            << "до выполнения |I_prev-I_curr| < eps_integral.\n"
            << "Нижняя таблица подтверждает корректность вычисления sqrt(t) по варианту 4\n"
            << "через малый остаток |y^2-t|.\""
            << "\n";
        printDivider();
    }

    bool runSelfTests()
    {
        // Набор автопроверок:
        // 1) трапеции на простой функции,
        // 2) корректность Ньютона для sqrt,
        // 3) сходимость адаптивного критерия,
        // 4) сравнение варианта 5 с аналитикой.
        bool ok = true;

        std::cout << Color::bold << Color::cyan << "\n================== АВТОТЕСТЫ ==================\n"
                  << Color::reset;
        std::cout << Color::dim
                  << "В каждом тесте показаны входные данные, ожидаемый результат и фактически полученный.\n"
                  << Color::reset;

        const double trap_linear = compositeTrapezoid(testLinear, 0.0, 1.0, 10);
        const double trap_linear_expected = 0.5;
        const double trap_linear_diff = std::abs(trap_linear - trap_linear_expected);
        const bool trap_linear_ok = trap_linear_diff < 1e-12;
        std::cout << "\n" << Color::bold << Color::blue << "Тест 1. Метод трапеций на f(x)=x\n" << Color::reset
                  << "  Вход: a=0, b=1, n=10\n"
                  << "  Ожидаемое значение интеграла: 0.5\n"
                  << "  Получено программой: " << std::setprecision(12) << trap_linear << "\n"
                  << "  Абсолютная погрешность: " << std::scientific << trap_linear_diff << std::fixed << "\n"
                  << "  Статус: " << (trap_linear_ok ? Color::green : Color::red)
                  << (trap_linear_ok ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << Color::reset << "\n";
        ok = ok && trap_linear_ok;

        const double sqrt_value = sqrtByNewton(10.0, 1e-10);
        const double sqrt_diff = std::abs(sqrt_value - std::sqrt(10.0));
        const double sqrt_residual = verifySqrtEquation(sqrt_value, 10.0);
        const bool sqrt_ok = sqrt_diff < 1e-9;
        std::cout << "\n" << Color::bold << Color::blue << "Тест 2. Метод Ньютона для sqrt(t)\n" << Color::reset
                  << "  Вход: t=10, eps_sqrt=1e-10, y0=t\n"
                  << "  Эталон (std::sqrt): " << std::setprecision(12) << std::sqrt(10.0) << "\n"
                  << "  Получено программой: " << sqrt_value << "\n"
                  << "  |sqrt_newton - std::sqrt|: " << std::scientific << sqrt_diff << std::fixed << "\n"
                  << "  Проверка уравнения |y^2 - t|: " << std::scientific << sqrt_residual << std::fixed << "\n"
                  << "  Статус: " << (sqrt_ok ? Color::green : Color::red)
                  << (sqrt_ok ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << Color::reset << "\n";
        ok = ok && sqrt_ok;

        const AdaptiveResult adaptive_linear =
            adaptiveTrapezoid(testLinear, 0.0, 1.0, 2, 1e-8, 10);
        const bool adaptive_ok = adaptive_linear.converged
                                 && adaptive_linear.last_step_diff < 1e-8
                                 && std::abs(adaptive_linear.value - 0.5) < 1e-8;
        std::cout << "\n" << Color::bold << Color::blue
                  << "Тест 3. Адаптивное удвоение разбиений (повышенная сложность)\n"
                  << Color::reset
                  << "  Вход: f(x)=x, a=0, b=1, n0=2, eps_integral=1e-8\n"
                  << "  n_start: " << adaptive_linear.n_start << ", n_final: " << adaptive_linear.n_final << "\n"
                  << "  |I_prev - I_curr| на последнем шаге: "
                  << std::scientific << adaptive_linear.last_step_diff << std::fixed << "\n"
                  << "  Полученный интеграл: " << std::setprecision(12) << adaptive_linear.value << "\n"
                  << "  Критерий остановки выполнен: " << (adaptive_linear.converged ? "да" : "нет") << "\n"
                  << "  Статус: " << (adaptive_ok ? Color::green : Color::red)
                  << (adaptive_ok ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << Color::reset << "\n";
        ok = ok && adaptive_ok;

        c_value = 2.0;
        sqrt_eps = 1e-8;
        const AdaptiveResult var5_adaptive =
            adaptiveTrapezoid(integrand, 1.0, 2.0, 10, 1e-5, 12);
        const double var5_analytic = analyticIntegral(2.0);
        const double var5_diff = std::abs(var5_adaptive.value - var5_analytic);
        const bool var5_ok = var5_adaptive.converged && var5_diff < 1e-4;
        std::cout << "\n" << Color::bold << Color::blue
                  << "Тест 4. Вариант 5: адаптивное численное vs аналитическое\n"
                  << Color::reset
                  << "  Вход: c=2.0, a=1, b=2, n0=10, eps_integral=1e-5, eps_sqrt=1e-8\n"
                  << "  n_start: " << var5_adaptive.n_start << ", n_final: " << var5_adaptive.n_final << "\n"
                  << "  |I_prev - I_curr| на последнем шаге: "
                  << std::scientific << var5_adaptive.last_step_diff << std::fixed << "\n"
                  << "  Аналитический результат: " << std::setprecision(12) << var5_analytic << "\n"
                  << "  Получено адаптивным методом: " << var5_adaptive.value << "\n"
                  << "  Абсолютная разница: " << std::scientific << var5_diff << std::fixed << "\n"
                  << "  Статус: " << (var5_ok ? Color::green : Color::red)
                  << (var5_ok ? "ПРОЙДЕН" : "НЕ ПРОЙДЕН") << Color::reset << "\n";
        ok = ok && var5_ok;

        std::cout << "\n" << (ok ? Color::green : Color::red) << Color::bold
                  << (ok ? "ИТОГ: ВСЕ АВТОТЕСТЫ УСПЕШНО ПРОЙДЕНЫ.\n" : "ИТОГ: ЕСТЬ НЕПРОЙДЕННЫЕ АВТОТЕСТЫ.\n")
                  << Color::reset;
        return ok;
    }

    void printSqrtVerification()
    {
        // Отдельная табличка с остатками уравнения y^2 - t = 0.
        // Это иллюстрирует, что корень найден корректно.
        const double samples[] = {2.0, 5.0, 10.0};
        std::cout << Color::bold << Color::magenta
                  << "\n=== Проверка решения уравнения y^2 - t = 0 ===\n"
                  << Color::reset;
        std::cout << Color::dim
                  << "+------------+----------------------+----------------------+\n"
                  << Color::reset;
        std::cout << "|"
                  << std::setw(12) << " t"
                  << "|"
                  << std::setw(22) << " sqrt(t)"
                  << "|"
                  << std::setw(22) << " err_sqrt"
                  << "|\n";
        std::cout << Color::dim
                  << "+------------+----------------------+----------------------+\n"
                  << Color::reset;

        for (double t : samples)
        {
            const double root = sqrtByNewton(t, sqrt_eps);
            const double residual = verifySqrtEquation(root, t);
            std::cout << "|"
                      << std::setw(12) << std::setprecision(4) << std::fixed << t
                      << "|"
                      << std::setw(22) << std::setprecision(10) << root
                      << "|"
                      << diffColor(residual) << std::setw(22) << std::scientific << residual
                      << Color::reset << "|\n";
        }
        std::cout << Color::dim
                  << "+------------+----------------------+----------------------+\n"
                  << Color::reset;
    }

    RunConfig getPresetConfig(int preset)
    {
        // Пресеты уменьшают ручной ввод.
        // 1 - быстрый показ, 2 - баланс, 3 - точный расчет.
        if (preset == 1)
        {
            return RunConfig{4, 1e-5, 1e-7, 10, 700};
        }
        if (preset == 3)
        {
            return RunConfig{8, 1e-8, 1e-10, 14, 1500};
        }
        return RunConfig{8, 1e-6, 1e-8, 12, 1000};
    }

    RunConfig readCustomConfig()
    {
        RunConfig cfg{};
        std::cout << "Введите n0: ";
        std::cin >> cfg.n0;
        std::cout << "Введите eps_integral: ";
        std::cin >> cfg.eps_integral;
        std::cout << "Введите eps_sqrt: ";
        std::cin >> cfg.eps_sqrt;
        std::cout << "Введите max удвоений n (0 = 12): ";
        std::cin >> cfg.max_refinements;
        std::cout << "Введите max итераций Ньютона (0 = 1000): ";
        std::cin >> cfg.max_newton_iter;

        if (cfg.max_refinements <= 0)
        {
            cfg.max_refinements = 12;
        }
        if (cfg.max_newton_iter <= 0)
        {
            cfg.max_newton_iter = 1000;
        }
        if (cfg.n0 <= 0 || cfg.eps_integral <= 0.0 || cfg.eps_sqrt <= 0.0)
        {
            throw std::invalid_argument("n0, eps_integral и eps_sqrt должны быть положительными.");
        }
        return cfg;
    }

    void runVariant5(const RunConfig& cfg)
    {
        // Основной рабочий сценарий: вариант 5 повышенной сложности.
        std::cout << Color::bold << Color::cyan
                  << "=== Вариант 5 (повышенная сложность): I(c)=∫[1,2] sqrt(x^2+c^2)/x dx ===\n"
                  << Color::reset;
        printConfigSummary(cfg);
        printDetailedTeacherExplanation();
        printInterpretationBlock();

        sqrt_eps = cfg.eps_sqrt;
        max_newton_iterations = cfg.max_newton_iter;

        std::cout << std::fixed << std::setprecision(8);
        std::cout << Color::bold << Color::cyan
                  << "\n=== Таблица результатов (адаптивный метод трапеций) ===\n"
                  << Color::reset;
        std::cout << Color::dim
                  << "+------+------+--------+------------+------------+------------+------------+\n"
                  << Color::reset;
        std::cout << "|"
                  << std::setw(6) << "c"
                  << "|"
                  << std::setw(6) << "n0"
                  << "|"
                  << std::setw(8) << "n_fin"
                  << "|"
                  << std::setw(12) << "I_num"
                  << "|"
                  << std::setw(12) << "I_an"
                  << "|"
                  << std::setw(12) << "|I-Ia|"
                  << "|"
                  << std::setw(12) << "|dI|"
                  << "|\n";
        std::cout << Color::dim
                  << "+------+------+--------+------------+------------+------------+------------+\n"
                  << Color::reset;

        for (double c = 1.0; c <= 3.0 + 1e-9; c += 0.2)
        {
            // Для каждого c считаем численное значение, аналитику и ошибки.
            c_value = c;
            const AdaptiveResult adaptive =
                adaptiveTrapezoid(integrand, 1.0, 2.0, cfg.n0, cfg.eps_integral, cfg.max_refinements);
            const double i_analytic = analyticIntegral(c);
            const double diff_num_an = std::abs(adaptive.value - i_analytic);

            std::cout << "|"
                      << std::setw(6) << std::setprecision(1) << c
                      << "|"
                      << std::setw(6) << adaptive.n_start
                      << "|"
                      << std::setw(8) << adaptive.n_final
                      << "|"
                      << std::setw(12) << std::setprecision(8) << adaptive.value
                      << "|"
                      << std::setw(12) << i_analytic
                      << "|"
                      << diffColor(diff_num_an) << std::setw(12) << diff_num_an << Color::reset
                      << "|"
                      << diffColor(adaptive.last_step_diff) << std::setw(12) << adaptive.last_step_diff
                      << Color::reset
                      << "|\n";
        }

        std::cout << Color::dim
                  << "+------+------+--------+------------+------------+------------+------------+\n"
                  << Color::reset;

        std::cout << Color::dim
                  << "|I-Ia| = |I_num - I_an|, |dI| = |I_prev - I_curr| на последнем шаге, err_sqrt = |y^2 - t|\n"
                  << Color::reset;

        printSqrtVerification();
    }
}

int main()
{
    try
    {
        // Главное меню программы.
        std::cout << Color::bold << Color::magenta
                  << "==============================================\n"
                  << " ЛАБОРАТОРНАЯ РАБОТА: МЕТОД ТРАПЕЦИЙ И НЬЮТОН \n"
                  << " Вариант 5, повышенная сложность (3.5.2)        \n"
                  << "==============================================\n"
                  << Color::reset;
        std::cout << Color::bold << Color::cyan
                  << "1. Быстрый запуск (минимум ввода)\n"
                  << "2. Автотесты\n"
                  << "5. Ручной ввод всех параметров\n"
                  << "Выбор: "
                  << Color::reset;

        int mode = 1;
        std::cin >> mode;

        if (mode == 1)
        {
            runVariant5(getPresetConfig(2));
        }
        else if (mode == 2)
        {
            // Только самопроверка.
            return runSelfTests() ? 0 : 2;
        }
        else if (mode == 5)
        {
            runVariant5(readCustomConfig());
        }
        else
        {
            std::cerr << Color::red << "Неизвестный режим.\n" << Color::reset;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << Color::red << "Ошибка: " << e.what() << '\n' << Color::reset;
        return 1;
    }

    return 0;
}
