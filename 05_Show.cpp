#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"
using namespace std;

class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat*> showSeats;

public:
    // Constructor
    Show(Movie* movie, Screen* screen, string startTime) {
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        initializeShowSeats();
    }

    // Destructor - delete all showSeats
    ~Show() {
        for (ShowSeat* ss : showSeats) {
            delete ss;
        }
        showSeats.clear();
    }

    // Initialize show seats from physical seats
    void initializeShowSeats() {
        vector<Seat*>& seats = screen->getSeats();
        for (Seat* seat : seats) {
            showSeats.push_back(new ShowSeat(seat));
        }
    }

    // Getters
    Movie* getMovie() { return movie; }
    Screen* getScreen() { return screen; }
    string getStartTime() { return startTime; }
    vector<ShowSeat*>& getShowSeats() { return showSeats; }

    // Get ShowSeat by seat number
    ShowSeat* getShowSeat(string seatNumber) {
        for (ShowSeat* ss : showSeats) {
            if (ss->getSeatNumber() == seatNumber) {
                return ss;
            }
        }
        return nullptr;
    }

    // Display seat layout with status
    void displaySeatLayout() {
        cout << "\n===== SEAT LAYOUT =====" << endl;
        cout << "Screen: " << screen->getScreenNumber() << " | Time: " << startTime << endl;
        cout << "(" << " [ ] = AVAILABLE  [X] = BOOKED )" << endl << endl;

        // Display by seat type
        cout << "SILVER ( 150): ";
        for (ShowSeat* ss : showSeats) {
            if (ss->getType() == SeatType::SILVER) {
                cout << ss->getSeatNumber();
                cout << (ss->isAvailable() ? "[ ] " : "[X] ");
            }
        }
        cout << endl;

        cout << "GOLD ( 250):   ";
        for (ShowSeat* ss : showSeats) {
            if (ss->getType() == SeatType::GOLD) {
                cout << ss->getSeatNumber();
                cout << (ss->isAvailable() ? "[ ] " : "[X] ");
            }
        }
        cout << endl;

        cout << "PLATINUM ( 400): ";
        for (ShowSeat* ss : showSeats) {
            if (ss->getType() == SeatType::PLATINUM) {
                cout << ss->getSeatNumber();
                cout << (ss->isAvailable() ? "[ ] " : "[X] ");
            }
        }
        cout << endl;
    }

    // Check if all requested seats are available
    bool areSeatsAvailable(vector<string> seatNumbers) {
        for (string seatNum : seatNumbers) {
            ShowSeat* ss = getShowSeat(seatNum);
            if (ss == nullptr || ss->isBooked()) {
                return false;  // Reject whole booking
            }
        }
        return true;  // All seats available
    }

    // Book seats (mark as BOOKED)
    bool bookSeats(vector<string> seatNumbers) {
        if (!areSeatsAvailable(seatNumbers)) {
            return false;
        }
        for (string seatNum : seatNumbers) {
            ShowSeat* ss = getShowSeat(seatNum);
            if (ss) {
                ss->book();
            }
        }
        return true;
    }

    // Release seats (mark as AVAILABLE)
    bool releaseSeats(vector<string> seatNumbers) {
        for (string seatNum : seatNumbers) {
            ShowSeat* ss = getShowSeat(seatNum);
            if (ss) {
                ss->release();
            }
        }
        return true;
    }

    // Get show display string
    string getShowDisplay() {
        return "Screen-" + to_string(screen->getScreenNumber()) + " " + startTime;
    }
};