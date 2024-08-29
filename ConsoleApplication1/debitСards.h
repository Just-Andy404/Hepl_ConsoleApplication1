#pragma once
#include "Account.h"
#include "Card.h"

class DebitCard : public Card {
public:
    DebitCard() { _cardType = DEBIT; }  // ������������� ��� ��� ��������� �����
    void addMoney(const Account& account);
    void payment(const Account& acc);
    double getHowMuchMoney(const string& filename);
private:
};
