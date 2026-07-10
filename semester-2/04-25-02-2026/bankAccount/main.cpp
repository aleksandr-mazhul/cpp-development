#include <iostream>
#include "BankService.h"

using namespace std;

int main()
{
    cout << "=== TEST 1: Create accounts ===" << endl;

    BankService bank;

    string id1 = bank.openAccount("Alice", 1000.0);
    string id2 = bank.openAccount("Bob", 500.0);
    string id3 = bank.openAccount("Charlie");

    cout << "Alice ID: " << id1 << endl;
    cout << "Bob ID: " << id2 << endl;
    cout << "Charlie ID: " << id3 << endl;

    cout << "\n=== TEST 2: Deposit money ===" << endl;
    cout << "Alice balance before: " << bank.getBalance(id1) << endl;
    bank.deposit(id1, 500.0);
    cout << "Alice balance after +500: " << bank.getBalance(id1) << endl;

    cout << "\n=== TEST 3: Withdraw money ===" << endl;
    cout << "Bob balance before: " << bank.getBalance(id2) << endl;
    bank.withdraw(id2, 200.0);
    cout << "Bob balance after -200: " << bank.getBalance(id2) << endl;

    cout << "\n=== TEST 4: Transfer money ===" << endl;
    cout << "Before transfer:" << endl;
    cout << "Alice: " << bank.getBalance(id1) << endl;
    cout << "Bob: " << bank.getBalance(id2) << endl;

    bank.transfer(id1, id2, 300.0);

    cout << "After transfer 300 from Alice to Bob:" << endl;
    cout << "Alice: " << bank.getBalance(id1) << endl;
    cout << "Bob: " << bank.getBalance(id2) << endl;

    cout << "\n=== TEST 5: Error handling ===" << endl;

    cout << "Try to withdraw more than balance:" << endl;
    try
    {
        bank.withdraw(id2, 1000.0);
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nTry to transfer to yourself:" << endl;
    try
    {
        bank.transfer(id1, id1, 100.0);
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\n=== FINAL ACCOUNT STATUS ===" << endl;
    cout << "Total accounts: " << bank.getAccountCount() << endl;

    cout << "Alice: " << bank.getBalance(id1) << endl;
    cout << "Bob: " << bank.getBalance(id2) << endl;
    cout << "Charlie: " << bank.getBalance(id3) << endl;

    return 0;
}