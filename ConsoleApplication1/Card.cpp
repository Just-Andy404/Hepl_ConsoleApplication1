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

void Card::reportsExpensesCategories()
{
    //// Получаем 3D массив всех трат пользователя
    //    std::vector<std::vector<std::vector<std::string>>> expenses = analyzeExpensesFile(fileName);

    //// Выводим данные о тратах
    //std::cout << "User Expenses Categories Report:" << std::endl;
    //for (const auto& expense : expenses) {
    //    for (const auto& detail : expense) {
    //        std::cout << "Amount: " << detail[0] << ", Date: " << detail[1] << ", Category: " << detail[2] << std::endl;
    //    }
    //}

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

