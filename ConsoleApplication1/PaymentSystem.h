#pragma once
#include <iostream>
#include <vector>
using namespace std;

class PaymentSystem {
private:
    struct Payment {
        double _amount;
        string _date;
        string _category;

        Payment(double amt, const string& dt, const string& cat)
            : _amount(amt), _date(dt), _category(cat) {}
    };

    vector<Payment> payments;

public:
    // ����� ��� ���������� ������ �������
    void addPayment(double amount, const string& date, const string& category) {
        payments.emplace_back(amount, date, category);
    }

    // ����� ��� ������ ���� ��������
    void printPayments() const {
        for (const auto& payment : payments) {
            cout << "Amount: " << payment._amount
                << ", Date: " << payment._date
                << ", Category: " << payment._category << endl;
        }
    }

    // ����� ��� ��������� ���������� ��������
    int getPaymentCount() const {
        return payments.size();
    }

};
