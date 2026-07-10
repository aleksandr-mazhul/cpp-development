#pragma once

#include "BankAccount.h"

#include <string>
#include <vector>

/**
 * Service class that manages multiple bank accounts.
 */
class BankService
{
public:
    /**
     * Opens a new account.
     * @param ownerName owner name
     * @param initialDeposit initial balance (default = 0.0)
     * @return generated account ID
     */
    std::string openAccount(const std::string& ownerName, double initialDeposit = 0.0);

    /**
     * Deposits money to the specified account.
     * @param accountNumber account identifier
     * @param amount amount to deposit
     */
    void deposit(const std::string& accountNumber, double amount);

    /**
     * Withdraws money from the specified account.
     * @param accountNumber account identifier
     * @param amount amount to withdraw
     */
    void withdraw(const std::string& accountNumber, double amount);

    /**
     * Transfers money between accounts.
     * @param fromId source account ID
     * @param toId target account ID
     * @param amount amount to transfer
     */
    void transfer(const std::string& fromId, const std::string& toId, double amount);

    /**
     * Returns account balance.
     * @param accountNumber account identifier
     * @return current balance
     */
    double getBalance(const std::string& accountNumber) const;

    /**
     * Finds account by ID (modifiable).
     * @param id account identifier
     * @return pointer to account or nullptr
     */
    BankAccount* findById(const std::string& id);

    /**
     * Finds account by ID (read-only).
     * @param id account identifier
     * @return pointer to account or nullptr
     */
    const BankAccount* findById(const std::string& id) const;

    /**
     * Returns total number of accounts.
     * @return number of accounts
     */
    size_t getAccountCount() const;

private:
    /** Container storing all bank accounts */
    std::vector<BankAccount> accounts;
};