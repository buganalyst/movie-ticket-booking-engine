#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

// Enum for booking status
enum class BookingStatus {
    CONFIRMED,
    FAILED,
    CANCELLED
};

class Booking {
private:
    string bookingId;
    Show* show;
    Customer* customer;
    vector<ShowSeat*> bookedSeats;
    int totalAmount;
    BookingStatus status;
    string paymentMethod;
    string bookingTime;

public:
    // Constructor
    Booking(Show* show, Customer* customer, vector<ShowSeat*> seats, int amount) {
        this->show = show;
        this->customer = customer;
        this->bookedSeats = seats;
        this->totalAmount = amount;
        this->status = BookingStatus::FAILED;  // Default until payment succeeds
        this->paymentMethod = "";
        this->bookingTime = getCurrentDateTime();
        this->bookingId = "";  // Will be set by BookingService
    }

    // Get current date/time as string
    string getCurrentDateTime() {
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d-%b-%Y %I:%M %p", timeinfo);
        return string(buffer);
    }

    // Setters
    void setBookingId(string id) { bookingId = id; }
    void setStatus(BookingStatus status) { this->status = status; }
    void setPaymentMethod(string method) { paymentMethod = method; }

    // Convenience methods
    void confirm() { status = BookingStatus::CONFIRMED; }
    void cancel() { status = BookingStatus::CANCELLED; }
    void fail() { status = BookingStatus::FAILED; }

    // Getters
    string getBookingId() { return bookingId; }
    Show* getShow() { return show; }
    Customer* getCustomer() { return customer; }
    vector<ShowSeat*>& getBookedSeats() { return bookedSeats; }
    int getTotalAmount() { return totalAmount; }
    BookingStatus getStatus() { return status; }
    string getPaymentMethod() { return paymentMethod; }
    string getBookingTime() { return bookingTime; }

    // Get seat numbers as comma-separated string
    string getSeatNumbers() {
        string result = "";
        for (int i = 0; i < (int)bookedSeats.size(); i++) {
            result += bookedSeats[i]->getSeatNumber();
            if (i < (int)bookedSeats.size() - 1) {
                result += ", ";
            }
        }
        return result;
    }

    // Get status as string
    string getStatusString() {
        if (status == BookingStatus::CONFIRMED) return "CONFIRMED";
        else if (status == BookingStatus::FAILED) return "FAILED";
        else return "CANCELLED";
    }

    // Display booking details
    void display() {
        cout << "\n===== BOOKING DETAILS =====" << endl;
        cout << "Booking ID: " << bookingId << endl;
        cout << "Movie: " << show->getMovie()->getTitle() << endl;
        cout << "Screen: " << show->getScreen()->getScreenNumber() << endl;
        cout << "Time: " << show->getStartTime() << endl;
        cout << "Seats: " << getSeatNumbers() << endl;
        cout << "Amount:  " << totalAmount << endl;
        cout << "Status: " << getStatusString() << endl;
        cout << "Payment: " << paymentMethod << endl;
        cout << "Booked on: " << bookingTime << endl;
    }
};