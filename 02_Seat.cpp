#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Enum for seat types
enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

class Seat {
private:
    string seatNumber;
    SeatType type;

public:
    // Constructor
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;
        this->type = type;
    }

    // Getters
    string getSeatNumber() { return seatNumber; }
    SeatType getType() { return type; }

    // Get price based on seat type
    int getPrice() {
        if (type == SeatType::SILVER) return 150;
        else if (type == SeatType::GOLD) return 250;
        else return 400;  // PLATINUM
    }

    // Convert enum to string
    string getTypeString() {
        if (type == SeatType::SILVER) return "SILVER";
        else if (type == SeatType::GOLD) return "GOLD";
        else return "PLATINUM";
    }
};