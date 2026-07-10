#pragma once

#include <string>


/**
 * Types of operations that can occur on a bank account.
 */
enum class OperationType
{
    /** Deposit money to the account */
    Deposit,

    /** Withdraw money from the account */
    Withdraw,

    /** Transfer money from this account to another account */
    TransferOut,

    /** Transfer money from another account to this account */
    TransferIn
};

/**
 * Represents a single operation in the account history.
 * Stores information about the type of operation,
 * the amount involved, the related account (for transfers),
 * and the time when the operation occurred.
 */
struct Operation
{
    /** Type of the operation */
    OperationType type;

    /** Amount of money involved in the operation */
    double amount;

    /** Related account (used for transfer operations) */
    std::string accountNumber;

    /** Time when the operation happened */
    std::time_t date;
};

class BankAccount
{
public:
    /**
     * Constructs an account with the given owner name and initial deposit.
     * @param ownerName non-empty owner name
     * @param initialDeposit initial balance (must be >= 0)
     * @throws std::invalid_argument if ownerName is empty or initialDeposit is negative
     */
    BankAccount(const std::string& ownerName, double initialDeposit);

    /**
     * Constructs an account with the given owner name and zero initial balance.
     */
    BankAccount(const std::string& ownerName);

    /**
     * Returns the total number of accounts created so far.
     */
    static int getAccountCount();

    /**
     * Returns the owner name.
     */
    const std::string& getOwnerName() const;

    /**
     * Returns the unique account number.
     */
    const std::string& getAccountNumber() const;

    /**
     * Deposit money to the account.
     */
    void deposit(double amount);

    /**
     * Withdraw money from the account.
     */
    void withdraw(double amount);

    /**
     * Transfer money to another account.
     */
    void transfer(BankAccount& targetAccount, double amount);

    /**
     * Returns the current balance.
     */
    double getBalance() const;

private:
    /** Name of the account owner */
    std::string ownerName;

    /** Unique account identifier */
    std::string accountNumber;

    /** Current balance of the account */
    double balance;

    /** Total number of BankAccount objects that have been created */
    static int accountCount;

    /** Base value for generating account numbers */
    static constexpr long BankId = 4000;

    /** Maximum number of operations stored in the account history */
    static constexpr size_t maxOperations = 100;

    /** Fixed-size array storing the history of operations for this account */
    Operation history[maxOperations];

    /** Current number of stored operations in the history array */
    size_t historySize = 0;

    /**
     * Adds a new operation to the account history.
     * The operation is appended to the internal history array if there is space available.
     * @param type type of the operation being recorded
     * @param amount amount of money involved in the operation
     * @param accountNumber related account (used for transfer operations)
     */
    void addToHistory(OperationType type, double amount, const std::string& accountNumber);

    /**
     * Returns the number of operations currently stored in the account history.
     * @return number of stored operations
     */
    size_t getHistorySize() const;

    /**
     * Returns a pointer to the operation at the given index in the history.
     * If the index is out of range, the method should return nullptr.
     * @param i index of the operation in the history
     * @return pointer to the operation or nullptr if index is invalid
     */
    const Operation* getOperation(size_t i) const;

    /**
     * Generates a unique account number.
     * @return generated account number string
     */
    static std::string generateAccountNumber();

    /**
     * Validates that a string is not empty.
     * @param name string to validate
     * @param message error message thrown if validation fails
     * @throws std::invalid_argument if the string is empty
     */
    static void ValidateEmptyString(const std::string& name, const std::string& message);

    /**
     * Validates that a monetary amount is positive.
     * @param value amount to validate
     * @param message error message thrown if validation fails
     * @throws std::invalid_argument if the amount is not positive
     */
    static void validateAmountPositive(double value, const std::string& message);

    /**
     * Validates that a monetary amount is finite (not NaN or infinity).
     * @param amount amount to validate
     * @param message error message thrown if validation fails
     * @throws std::invalid_argument if the value is not finite
     */
    static void validateAmountFinite(double amount, const std::string& message);
};