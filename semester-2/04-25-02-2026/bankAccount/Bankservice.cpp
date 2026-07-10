#include "BankService.h"

#include <stdexcept>

using namespace std;

/**
 * Opens a new account and returns its ID.
 */
std::string BankService::openAccount(const std::string& ownerName, double initialDeposit)
{
    accounts.emplace_back(ownerName, initialDeposit);

    return accounts.back().getAccountNumber();
}

/**
 * Finds account by ID (modifiable).
 */
BankAccount* BankService::findById(const std::string& id)
{
    for (auto& acc : accounts)
    {
        if (acc.getAccountNumber() == id)
        {
            return &acc;
        }
    }

    return nullptr;
}

/**
 * Finds account by ID (read-only).
 */
const BankAccount* BankService::findById(const std::string& id) const
{
    for (const auto& acc : accounts)
    {
        if (acc.getAccountNumber() == id)
        {
            return &acc;
        }
    }

    return nullptr;
}

/**
 * Deposits money to the specified account.
 */
void BankService::deposit(const std::string& accountNumber, double amount)
{
    BankAccount* acc = findById(accountNumber);

    if (!acc)
    {
        throw runtime_error("Account not found");
    }

    acc->deposit(amount);
}

/**
 * Withdraws money from the specified account.
 */
void BankService::withdraw(const std::string& accountNumber, double amount)
{
    BankAccount* acc = findById(accountNumber);

    if (!acc)
    {
        throw runtime_error("Account not found");
    }

    acc->withdraw(amount);
}

/**
 * Transfers money between accounts.
 */
void BankService::transfer(const std::string& fromId, const std::string& toId, double amount)
{
    BankAccount* from = findById(fromId);
    BankAccount* to = findById(toId);

    if (!from || !to)
    {
        throw runtime_error("Account not found");
    }

    from->transfer(*to, amount);
}

/**
 * Returns account balance.
 */
double BankService::getBalance(const std::string& accountNumber) const
{
    const BankAccount* acc = findById(accountNumber);

    if (!acc)
    {
        throw runtime_error("Account not found");
    }

    return acc->getBalance();
}

/**
 * Returns total number of accounts.
 */
size_t BankService::getAccountCount() const
{
    return accounts.size();
}