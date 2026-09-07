#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "09_Payment.cpp"
using namespace std;

// ===== UPI PAYMENT =====
class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment() {
        // Generate a random UPI ID for demo
        upiId = "user" + to_string(rand() % 10000) + "@upi";
    }

    bool pay(int amount) override {
        cout << "[UPI] Processing payment of  " << amount << " via " << upiId << "... ";
        // Simulate payment processing
        // 90% success rate for demo
        bool success = (rand() % 10) != 0;  // 9 out of 10 succeed
        if (success) {
            cout << "SUCCESS" << endl;
        } else {
            cout << "FAILED" << endl;
        }
        return success;
    }

    string getMethodName() override {
        return "UPI";
    }
};

// ===== CARD PAYMENT =====
class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment() {
        // Generate a random card number for demo
        cardNumber = "XXXX-XXXX-XXXX-" + to_string(1000 + rand() % 9000);
    }

    bool pay(int amount) override {
        cout << "[CARD] Processing payment of  " << amount << " via Card " << cardNumber << "... ";
        // 85% success rate for demo
        bool success = (rand() % 100) < 85;
        if (success) {
            cout << "SUCCESS" << endl;
        } else {
            cout << "FAILED" << endl;
        }
        return success;
    }

    string getMethodName() override {
        return "Card";
    }
};

// ===== CASH PAYMENT =====
class CashPayment : public Payment {
public:
    CashPayment() {
        // No data needed
    }

    bool pay(int amount) override {
        cout << "[CASH] Processing cash payment of  " << amount << "... ";
        // Cash always succeeds (assuming customer has cash)
        cout << "SUCCESS" << endl;
        return true;
    }

    string getMethodName() override {
        return "Cash";
    }
};