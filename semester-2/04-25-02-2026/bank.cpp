#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

/**
 * Stub of BankAccount: same public interface as BankAccount.
 * Bank account with owner name and balance; supports deposit, withdraw, and transfer.
 * In this stub, all methods except the constructors are not implemented and throw std::logic_error.
 */
class BankAccount
{
public:
    /**
     * Constructs an account with the given owner name and initial deposit.
     * @param ownerName non-empty owner name
     * @param initialDeposit initial balance (must be >= 0)
     * @throws std::invalid_argument if ownerName is empty or initialDeposit is negative
     */
    BankAccount(const std::string& ownerName, double initialDeposit)
        : ownerName(ownerName)
          , balance(initialDeposit)

    {
        ValidateEmptyString(ownerName, "BankAccount cant be empty");

        validateAmountPositive(initialDeposit, "BankAccount count be negative");
    }

    /**
     * Constructs an account with the given owner name and zero initial balance.
     * Delegates to the two-parameter constructor.
     * @param ownerName non-empty owner name
     * @throws std::invalid_argument if ownerName is empty
     */
    BankAccount(const std::string& ownerName)
        : BankAccount(ownerName, 0.0)
    {
    }

    /**
     * Returns the total number of accounts created so far (shared across all instances).
     * Not implemented; throws std::logic_error.
     * @throws std::logic_error always
     */
    static int getAccountCount()
    {
    }

    /**
     * Returns the owner name of this account.
     * Not implemented; throws std::logic_error.
     * @throws std::logic_error always
     */
    const std::string& getOwnerName() const
    {
        return this->ownerName;
    }

    /**
     * Adds the given amount to the balance.
     * @param amount must be positive (in the real BankAccount)
     * @throws std::invalid_argument if amount <= 0 (in the real BankAccount)
     * Not implemented; this stub always throws std::logic_error.
     * @throws std::logic_error always
     */
    void deposit(double amount)
    {
        (void)amount;
        validateAmountPositive(amount, "amount count be negative");

        isAmountFinite(amount, "Cant be infinite");
        this->balance += amount;
    }

    /**
     * Subtracts the given amount from the balance.
     * @param amount must be positive and not exceed the current balance (in the real BankAccount)
     * @throws std::invalid_argument if amount <= 0 (in the real BankAccount)
     * @throws std::runtime_error if amount > balance (insufficient funds) (in the real BankAccount)
     * Not implemented; this stub always throws std::logic_error.
     * @throws std::logic_error always
     */
    void withdraw(double amount)
    {
        (void)amount;
        if (amount <= 0)
        {
            throw std::invalid_argument("BankAccountStub::withdraw: Not implemented");
        }
        validateAmountPositive(amount, "amount count be negative");

        isAmountFinite(amount, "Cant be infinite");

        this->deposit(amount);
    }

    /**
     * Transfers the given amount from this account to targetAccount.
     * On failure of the credit step, the debit is rolled back (in the real BankAccount).
     * @param targetAccount the account to credit (must not be this account in the real BankAccount)
     * @param amount must be positive and not exceed the current balance (in the real BankAccount)
     * @throws std::invalid_argument if amount <= 0 (in the real BankAccount)
     * @throws std::logic_error if targetAccount is this account (in the real BankAccount)
     * @throws std::runtime_error if amount > balance (insufficient funds) (in the real BankAccount)
     * Not implemented; this stub always throws std::logic_error.
     * @throws std::logic_error always
     */
    void transfer(BankAccount& targetAccount, double amount)
    {
        if (this == &targetAccount)
        {
            throw std::logic_error("BankAccountStub::transfer");
            chalidateAmountPositive(amount, "amount count be negative");
            isAmountFinite(amount, "Cant be infinite");
        }
        this->withdraw(amount);
        try
        {
            targetAccount.deposit(amount);
        }
        catch (const std::exception& e)
        {
            this->deposit(amount);
        }
    }

    /**
     * Returns the current balance.
     * Not implemented; throws std::logic_error.
     * @throws std::logic_error always
     */
    double getBalance() const
    {
        return this->balance;
    }

private:
    std::string ownerName;
    double balance;
    static int count;

    inline static void ValidateEmptyString(const string& name, const string& message)
    {
        if (name.empty())
        {
            throw std::invalid_argument("BankAccount: owner name cannot be empty");
        }
    }

    inline void validateAmountPositive(double value, const string& message)
    {
        if (value < 0)
        {
            throw std::invalid_argument("BankAccountStub: initial deposit cannot be negative");
        }
    }

    inline void isAmountFinite(double amount, const string& message)
    {
        if (!std::isfinite(amount))
        {
            throw std::invalid_argument("Ammount can't be infinitive");
        }
    }
};

int BankAccount::count = 0;

int main()
{
    double num;
    while (true)
    {
        std::cin >> num;
        if (num > 0)
        {
            break;
        }
    }

    try
    {
        BankAccount acc("Alice", num);
        BankAccount acc1("jac", num);
        BankAccount acc2("john", num);
        acc1.deposit(300.0);
        std::cout << acc1.getAccountCount() << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << '\n';
    }

    /*// Успешное создание и операции
    try
    {
        BankAccount acc("Alice", 100.0);
        std::cout << acc.getOwnerName() << ": balance " << acc.getBalance() << std::endl;
        acc.deposit(50.0);
        acc.withdraw(30.0);
        std::cout << "Balance: " << acc.getBalance() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Конструктор с депозитом по умолчанию: один аргумент — только имя, баланс 0
    try
    {
        BankAccount zeroBalance("Bob");
        std::cout << zeroBalance.getOwnerName() << " (default deposit): " <<
    zeroBalance.getBalance() << std::endl; std::cout << "Total accounts so far: " <<
    BankAccount::getAccountCount() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Ошибка: пустое имя владельца (invalid_argument)
    try
    {
        BankAccount bad("", 100.0);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }

    // Ошибка: отрицательный начальный депозит (invalid_argument)
    try
    {
        BankAccount bad("Bob", -10.0);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }

    // Ошибка: снятие больше баланса (runtime_error)
    try
    {
        BankAccount acc("Bob", 50.0);
        acc.withdraw(100.0);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }

    // Успешный перевод между счетами
    try
    {
        BankAccount alice("Alice", 200.0);
        BankAccount bob("Bob", 50.0);
        alice.transfer(bob, 30.0);
        std::cout << "After transfer: Alice " << alice.getBalance() << ", Bob " << bob.getBalance()
    << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    // Ошибка: перевод на тот же счёт (logic_error)
    try
    {
        BankAccount acc("Alice", 100.0);
        acc.transfer(acc, 10.0);
    }
    catch (const std::logic_error& e)
    {
        std::cerr << "Logic error: " << e.what() << std::endl;
    }

    // Ошибка: недостаточно средств для перевода (runtime_error)
    try
    {
        BankAccount alice("Alice", 20.0);
        BankAccount bob("Bob", 50.0);
        alice.transfer(bob, 50.0);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }

    return 0;*/
}

// Функция	         NaN	 +∞	     −∞	   обычное число
// std::isnan(x)	    true	false	false	false
// std::isinf(x)	    false	true	true	false
// std::isfinite(x)	false	false	false	true
