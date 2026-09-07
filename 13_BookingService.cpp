#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
using namespace std;

class BookingService {
private:
    Cinema* cinema;
    static int nextBookingId;
    PriceCalculator* priceCalculator;
    TicketPrinter* ticketPrinter;
    vector<Booking*> bookings;

public:
    // Constructor
    BookingService(Cinema* cinema) {
        this->cinema = cinema;
        this->priceCalculator = new PriceCalculator();
        this->ticketPrinter = new TicketPrinter();
    }

    // Destructor
    ~BookingService() {
        for (Booking* b : bookings) {
            delete b;
        }
        bookings.clear();
        delete priceCalculator;
        delete ticketPrinter;
    }

    // Static member initialization
    static int getNextBookingId() {
        return ++nextBookingId;
    }

    // Generate booking ID
    string generateBookingId() {
        return "BK" + to_string(getNextBookingId());
    }

    // Start booking process
    Booking* startBooking(Customer* customer, Show* show, vector<string> seatNumbers) {
        // Validate seats
        if (!show->areSeatsAvailable(seatNumbers)) {
            cout << "ERROR: One or more seats are already booked!" << endl;
            return nullptr;
        }

        // Get ShowSeat objects
        vector<ShowSeat*> selectedSeats;
        for (string seatNum : seatNumbers) {
            ShowSeat* ss = show->getShowSeat(seatNum);
            if (ss) {
                selectedSeats.push_back(ss);
            }
        }

        // Calculate total
        int total = priceCalculator->calculateTotal(selectedSeats);

        // Create booking (status defaults to FAILED)
        Booking* booking = new Booking(show, customer, selectedSeats, total);
        booking->setBookingId(generateBookingId());

        return booking;
    }

    // Process payment
    bool processPayment(Booking* booking, string method) {
        int amount = booking->getTotalAmount();
        Payment* payment = nullptr;

        // Create appropriate payment object
        if (method == "UPI") {
            payment = new UpiPayment();
        } else if (method == "Card") {
            payment = new CardPayment();
        } else if (method == "Cash") {
            payment = new CashPayment();
        } else {
            cout << "ERROR: Invalid payment method!" << endl;
            return false;
        }

        // Process payment
        bool success = payment->pay(amount);

        if (success) {
            booking->setPaymentMethod(method);
            booking->confirm();
            // Book the seats in the show
            vector<string> seatNumbers;
            for (ShowSeat* ss : booking->getBookedSeats()) {
                seatNumbers.push_back(ss->getSeatNumber());
            }
            booking->getShow()->bookSeats(seatNumbers);
        } else {
            booking->fail();
            // Release seats
            vector<string> seatNumbers;
            for (ShowSeat* ss : booking->getBookedSeats()) {
                seatNumbers.push_back(ss->getSeatNumber());
            }
            booking->getShow()->releaseSeats(seatNumbers);
        }

        delete payment;
        return success;
    }

    // Complete booking flow
    bool bookSeats(Customer* customer, Show* show, vector<string> seatNumbers, string paymentMethod) {
        // Start booking
        Booking* booking = startBooking(customer, show, seatNumbers);
        if (booking == nullptr) {
            return false;
        }

        // Show price breakdown
        priceCalculator->displayBreakdown(booking->getBookedSeats());

        // Process payment
        bool success = processPayment(booking, paymentMethod);

        if (success) {
            // Store booking
            bookings.push_back(booking);

            // Print ticket
            ticketPrinter->printTicket(booking);

            cout << "Booking confirmed! Booking ID: " << booking->getBookingId() << endl;
            return true;
        } else {
            cout << "Payment failed. Booking not confirmed. Seats released." << endl;
            delete booking;
            return false;
        }
    }

    // Cancel booking
    bool cancelBooking(string bookingId) {
        Booking* booking = findBooking(bookingId);

        if (booking == nullptr) {
            cout << "ERROR: Booking ID not found!" << endl;
            return false;
        }

        if (booking->getStatus() == BookingStatus::CANCELLED) {
            cout << "ERROR: Booking already cancelled!" << endl;
            return false;
        }

        if (booking->getStatus() == BookingStatus::FAILED) {
            cout << "ERROR: Cannot cancel a failed booking!" << endl;
            return false;
        }

        // Cancel the booking
        booking->cancel();

        // Release seats
        vector<string> seatNumbers;
        for (ShowSeat* ss : booking->getBookedSeats()) {
            seatNumbers.push_back(ss->getSeatNumber());
        }
        booking->getShow()->releaseSeats(seatNumbers);

        cout << "✓ Booking " << bookingId << " cancelled successfully. Seats released." << endl;
        return true;
    }

    // Find booking by ID
    Booking* findBooking(string bookingId) {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) {
                return b;
            }
        }
        return nullptr;
    }

    // Getters
    Cinema* getCinema() { return cinema; }
    vector<Booking*>& getBookings() { return bookings; }

    // List all bookings for a customer (simplified)
    void listMyTickets(string customerName) {
        bool found = false;
        cout << "\n===== MY TICKETS =====" << endl;
        for (Booking* b : bookings) {
            if (b->getCustomer()->getName() == customerName &&
                b->getStatus() == BookingStatus::CONFIRMED) {
                cout << "[" << b->getBookingId() << "] ";
                cout << b->getShow()->getMovie()->getTitle() << " | ";
                cout << b->getShow()->getShowDisplay() << " | ";
                cout << "Seats: " << b->getSeatNumbers() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No confirmed bookings found for " << customerName << endl;
        }
    }
};

// Initialize static member
int BookingService::nextBookingId = 1000;