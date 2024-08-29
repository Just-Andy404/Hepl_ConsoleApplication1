#pragma once
#include "Card.h"
#include "Account.h"
#include <iostream>

class CreditCard : public Card {
private:
    double _creditLimit;  

public:
    CreditCard(double creditLimit = 0.0) : _creditLimit(creditLimit) {
        _cardType = CREDIT;
    }
    void addMoney(const Account& acc);
    void payment(const Account& acc);
    double getCreditLimit() const { return _creditLimit; }
    void setCreditLimit(double limit) { _creditLimit = limit; }
};
