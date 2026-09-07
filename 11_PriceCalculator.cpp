#pragma once

#include <iostream>
#include <vector>
#include "06_ShowSeat.cpp"
using namespace std;

class PriceCalculator {
private:
    static const int SILVER_PRICE = 150;
    static const int GOLD_PRICE = 250;
    static const int PLATINUM_PRICE = 400;

public:
    // Calculate total for selected seats
    int calculateTotal(vector<ShowSeat*> seats) {
        int total = 0;
        for (ShowSeat* ss : seats) {
            total += ss->getPrice();
        }
        return total;
    }

    // Get price for a seat type
    int getPriceForType(SeatType type) {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        else if (type == SeatType::GOLD) return GOLD_PRICE;
        else return PLATINUM_PRICE;
    }

    // Display price breakdown
    void displayBreakdown(vector<ShowSeat*> seats) {
        cout << "\n===== PRICE BREAKDOWN =====" << endl;
        int total = 0;
        for (ShowSeat* ss : seats) {
            string typeStr;
            if (ss->getType() == SeatType::SILVER) typeStr = "SILVER";
            else if (ss->getType() == SeatType::GOLD) typeStr = "GOLD";
            else typeStr = "PLATINUM";

            cout << ss->getSeatNumber() << " " << typeStr;
            cout << "  " << ss->getPrice() << endl;
            total += ss->getPrice();
        }
        cout << "----------------------------" << endl;
        cout << "TOTAL:  " << total << endl;
    }
};