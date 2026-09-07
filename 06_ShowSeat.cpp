#pragma once

#include <iostream>
#include <string>
#include "02_Seat.cpp"
using namespace std;

// Enum for seat status
enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    // Constructor - default status is AVAILABLE
    ShowSeat(Seat* seat) {
        this->seat = seat;
        this->status = SeatStatus::AVAILABLE;
    }

    // Getters
    Seat* getSeat() { return seat; }
    string getSeatNumber() { return seat->getSeatNumber(); }
    SeatType getType() { return seat->getType(); }
    SeatStatus getStatus() { return status; }

    // Set status
    void setStatus(SeatStatus status) {
        this->status = status;
    }

    // Check status
    bool isAvailable() {
        return status == SeatStatus::AVAILABLE;
    }

    bool isBooked() {
        return status == SeatStatus::BOOKED;
    }

    // Book this seat
    void book() {
        if (isAvailable()) {
            status = SeatStatus::BOOKED;
        }
    }

    // Release this seat
    void release() {
        if (isBooked()) {
            status = SeatStatus::AVAILABLE;
        }
    }

    // Get price (delegates to Seat)
    int getPrice() {
        return seat->getPrice();
    }
};