#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include "08_Booking.cpp"
using namespace std;

class TicketPrinter {
public:
    // Print formatted ticket
    void printTicket(Booking* booking) {
        cout << "\n";
        cout << "=========================================" << endl;
        cout << "              MOVIE TICKET               " << endl;
        cout << "=========================================" << endl;
        cout << "Booking ID  : " << booking->getBookingId() << endl;
        cout << "Movie       : " << booking->getShow()->getMovie()->getTitle() << endl;
        cout << "Screen      : Screen-" << booking->getShow()->getScreen()->getScreenNumber() << endl;
        cout << "Show Time   : " << booking->getShow()->getStartTime() << endl;
        cout << "Seats       : " << booking->getSeatNumbers() << endl;
        cout << "Amount      :  " << booking->getTotalAmount() << endl;
        cout << "Payment     : " << booking->getPaymentMethod() << endl;
        cout << "Status      : " << booking->getStatusString() << endl;
        cout << "Booked on   : " << booking->getBookingTime() << endl;
        cout << "=========================================" << endl;
        cout << "          Thank you for booking!         " << endl;
        cout << "=========================================" << endl;
        cout << endl;
    }

    // Get formatted border
    string getFormattedBorder() {
        return "=========================================";
    }

    // Get current date/time
    string getCurrentDateTime() {
        time_t now = time(nullptr);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d-%b-%Y %I:%M %p", timeinfo);
        return string(buffer);
    }
};