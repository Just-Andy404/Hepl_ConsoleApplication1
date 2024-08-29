#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
//#include "Account.h"

using namespace std;

enum CardType { DEBIT, CREDIT };

// Базовый класс Card
class Card {
protected:
    int _NumsOfCard[17];
    double _balance;
    int _validity_period[6];
    CardType _cardType;

public:
    Card() : _balance(0.0) {
        for (int i = 0; i < 16; ++i) {
            _NumsOfCard[i] = 0;
        }
        for (int i = 0; i < 5; ++i) {
            _validity_period[i] = 0;
        }
    }

    virtual ~Card();

    void generateNumsOfCard();
    void printNumsOfCard() const;
    void reportsExpensesCategories();
    bool checkNumsOfCard(const int cardNumber[16]) const;
    const int* getNumsOfCard() const;
    double getBalance() const;
    CardType getCardType() const { return _cardType; }
    void setCardNumber(const int cardNumber[16]) {
        for (int i = 0; i < 16; ++i) {
            _NumsOfCard[i] = cardNumber[i];
        }
    }
    void logExpense(double amount, const string& date, const string& category, const string& userAccount);
};
