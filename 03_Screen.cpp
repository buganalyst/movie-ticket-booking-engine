#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "02_Seat.cpp"
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat*> seats;

public:
    // Constructor
    Screen(int screenNumber) {
        this->screenNumber = screenNumber;
    }

    // Destructor - delete all seats
    ~Screen() {
        for (Seat* seat : seats) {
            delete seat;
        }
        seats.clear();
    }

    // Add a seat to the screen
    void addSeat(string seatNumber, SeatType type) {
        seats.push_back(new Seat(seatNumber, type));
    }

    // Getters
    int getScreenNumber() { return screenNumber; }
    vector<Seat*>& getSeats() { return seats; }

    // Get seat by seat number
    Seat* getSeat(string seatNumber) {
        for (Seat* seat : seats) {
            if (seat->getSeatNumber() == seatNumber) {
                return seat;
            }
        }
        return nullptr;
    }

    // Display seat layout
    void displayLayout() {
        cout << "SEAT LAYOUT:" << endl;
        cout << "SILVER ( 150): ";
        for (Seat* seat : seats) {
            if (seat->getType() == SeatType::SILVER) {
                cout << seat->getSeatNumber() << " ";
            }
        }
        cout << endl;

        cout << "GOLD ( 250):   ";
        for (Seat* seat : seats) {
            if (seat->getType() == SeatType::GOLD) {
                cout << seat->getSeatNumber() << " ";
            }
        }
        cout << endl;

        cout << "PLATINUM ( 400): ";
        for (Seat* seat : seats) {
            if (seat->getType() == SeatType::PLATINUM) {
                cout << seat->getSeatNumber() << " ";
            }
        }
        cout << endl;
    }
};