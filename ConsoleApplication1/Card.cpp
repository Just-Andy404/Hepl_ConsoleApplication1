#include "Card.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Card::~Card()
{
}

void Card::generateNumsOfCard()
{
    for (int i = 0; i < 16; ++i) {
        _NumsOfCard[i] = rand() % 9 + 1;
    }
}

void Card::printNumsOfCard() const
{
    for (int i = 0; i < 16; ++i) {
        if (_NumsOfCard[0] != 0)
        {
            cout << _NumsOfCard[i];
        }
    }
    cout << endl;
}

void Card::reportsExpensesCategories(const Account& acc)
{
    string filePath = "data/" + acc.getUserAccount() + ".txt";
    ifstream inFile(filePath);

    if (!inFile.is_open()) {
        cerr << "Unable to open file for reading." << endl;
        return;
    }

    struct Expense {
        double amount;
        string date;
        string category;
    };

    vector<Expense> expenses;
    string line;

    while (getline(inFile, line)) {
        if (line.find("Amount:") != string::npos) {
            Expense exp;
            size_t pos = line.find("Amount:") + 7;
            exp.amount = stod(line.substr(pos, line.find(",") - pos));

            pos = line.find("Date:") + 5;
            exp.date = line.substr(pos, line.find(",") - pos);

            pos = line.find("Category:") + 9;
            exp.category = line.substr(pos);

            expenses.push_back(exp);
        }
    }
    inFile.close();

    // Сортировка расходов по дате
    for (size_t i = 0; i < expenses.size(); ++i) {
        for (size_t j = i + 1; j < expenses.size(); ++j) {
            if (expenses[i].date > expenses[j].date) {
                swap(expenses[i], expenses[j]);
            }
        }
    }

    // Вывод отсортированных данных
    for (const auto& exp : expenses) {
        cout << "Amount: " << exp.amount << ", Date: " << exp.date << ", Category: " << exp.category << endl;
    }
}

bool Card::checkNumsOfCard(const int cardNumber[16]) const
{
    for (int i = 0; i < 16; ++i) {
        if (_NumsOfCard[i] != cardNumber[i]) {
            return false;
        }
    }
    return true;
}

const int* Card::getNumsOfCard() const {
    return _NumsOfCard;
}

double Card::getBalance() const
{
    return _balance;
}

void Card::logExpense(double amount, const string& date, const string& category, const string& userAccount)
{
    string filePath = "data/" + userAccount + ".txt";
    ofstream logFile(filePath, ios::app);
    if (logFile.is_open()) {
        logFile << "Amount: " << amount
            << ", Date: " << date
            << ", Category: " << category << endl;
        logFile.close();
    }
    else {
        cerr << "Unable to open log file for writing." << endl;
    }
}
