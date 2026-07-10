#include "BankAccount.h"
#include <cmath>
#include <stdexcept>
#include <string>
#include <ostream>
#include <ctime>

using namespace std;

int BankAccount::accountCount = 0;

BankAccount::BankAccount(const std::string& ownerName, double initialDeposit)
    : ownerName(ownerName),
      accountNumber(generateAccountNumber()),
      balance(initialDeposit),
      history{}
{
    ValidateEmptyString(ownerName, "Owner name cannot be empty");
    validateAmountPositive(initialDeposit, "Initial deposit cannot be negative");

    accountCount++;
}

BankAccount::BankAccount(const std::string& ownerName)
    : BankAccount(ownerName, 0.0)
{
}

int BankAccount::getAccountCount()
{
    return accountCount;
}

const std::string& BankAccount::getOwnerName() const
{
    return ownerName;
}

const std::string& BankAccount::getAccountNumber() const
{
    return accountNumber;
}

double BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::deposit(double amount)
{
    validateAmountPositive(amount, "Deposit amount cannot be negative");
    validateAmountFinite(amount, "Amount must be finite");

    balance += amount;

    addToHistory(OperationType::Deposit, amount, "");
}

void BankAccount::withdraw(double amount)
{
    validateAmountPositive(amount, "Withdraw amount must be positive");
    validateAmountFinite(amount, "Amount must be finite");

    if (amount > balance)
    {
        throw runtime_error("Insufficient funds");
    }

    balance -= amount;

    addToHistory(OperationType::Withdraw, amount, "");
}

void BankAccount::transfer(BankAccount& targetAccount, double amount)
{
    if (this == &targetAccount)
    {
        throw logic_error("Cannot transfer to the same account");
    }

    validateAmountPositive(amount, "Transfer amount must be positive");
    validateAmountFinite(amount, "Amount must be finite");

    if (amount > balance)
    {
        throw runtime_error("Insufficient funds");
    }

    // списываем
    balance -= amount;

    try
    {
        // зачисляем
        targetAccount.balance += amount;

        // история
        addToHistory(OperationType::TransferOut, amount, targetAccount.accountNumber);
        targetAccount.addToHistory(OperationType::TransferIn, amount, accountNumber);
    }
    catch (...)
    {
        // rollback
        balance += amount;
        throw;
    }
}

void BankAccount::addToHistory(OperationType type, double amount, const std::string& accountNumber)
{
    if (historySize >= maxOperations)
    {
        return;
    }

    Operation op;
    op.type = type;
    op.amount = amount;
    op.accountNumber = accountNumber;
    op.date = std::time(nullptr);

    history[historySize++] = op;
}

size_t BankAccount::getHistorySize() const
{
    return historySize;
}

const Operation* BankAccount::getOperation(size_t i) const
{
    if (i >= historySize)
    {
        return nullptr;
    }

    return &history[i];
}

std::string BankAccount::generateAccountNumber()
{
    static int id = 1;
    return "ACC" + std::to_string(4000 + id++);
}

void BankAccount::ValidateEmptyString(const std::string& name, const std::string& message)
{
    if (name.empty())
    {
        throw invalid_argument(message);
    }
}

void BankAccount::validateAmountPositive(double value, const std::string& message)
{
    if (value < 0)
    {
        throw invalid_argument(message);
    }
}

void BankAccount::validateAmountFinite(double value, const std::string& message)
{
    if (!std::isfinite(value))
    {
        throw invalid_argument(message);
    }
}

std::ostream& operator<<(std::ostream& os, const BankAccount& account)
{
    return os << "[#"
        << account.getAccountNumber() << ", "
        << account.getOwnerName() << ", balance: "
        << account.getBalance() << "]\n";
}

std::ostream& operator<<(std::ostream& os, const OperationType& operation)
{
    switch (operation)
    {
    case OperationType::Deposit:
        os << "Deposit";
        break;
    case OperationType::Withdraw:
        os << "Withdraw";
        break;
    case OperationType::TransferOut:
        os << "TransferOut";
        break;
    case OperationType::TransferIn:
        os << "TransferIn";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Operation& operation)
{
    return os << "[" << operation.type
        << "] amount: " << operation.amount
        << ", account: " << operation.accountNumber
        << ", time: " << std::ctime(&operation.date);
}
