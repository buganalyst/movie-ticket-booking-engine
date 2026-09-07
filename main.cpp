#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "13_BookingService.cpp"
using namespace std;

// Function to clear input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to get integer input with validation
int getIntInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number." << endl;
            clearInput();
        } else {
            clearInput();
            return value;
        }
    }
}

// Function to get string input
string getStringInput(string prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// Display main menu
void showMainMenu() {
    cout << "\n=========================================" << endl;
    cout << "      WELCOME TO MOVIE TICKET SYSTEM      " << endl;
    cout << "=========================================" << endl;
    cout << "  1. List Movies" << endl;
    cout << "  2. Book Tickets" << endl;
    cout << "  3. Cancel Booking" << endl;
    cout << "  4. My Tickets" << endl;
    cout << "  0. Exit" << endl;
    cout << "=========================================" << endl;
    cout << "Choose an option: ";
}

int main() {
    // Seed random number generator for payment simulation
    srand(time(nullptr));

    // ===== SETUP PHASE =====

    // Create Cinema
    Cinema* cinema = new Cinema("PVR Cinemas");

    // Create Movies
    Movie* movie1 = new Movie("The Shawshank Redemption", "English", 142);
    Movie* movie2 = new Movie("The Prestige", "English", 130);
    Movie* movie3 = new Movie("Shutter Island", "English", 138);
    cinema->addMovie(movie1);
    cinema->addMovie(movie2);
    cinema->addMovie(movie3);

    // Create Screens and Seats
    // Screen 1
    Screen* screen1 = new Screen(1);
    // Silver seats
    screen1->addSeat("A1", SeatType::SILVER);
    screen1->addSeat("A2", SeatType::SILVER);
    screen1->addSeat("A3", SeatType::SILVER);
    screen1->addSeat("A4", SeatType::SILVER);
    // Gold seats
    screen1->addSeat("B1", SeatType::GOLD);
    screen1->addSeat("B2", SeatType::GOLD);
    screen1->addSeat("B3", SeatType::GOLD);
    screen1->addSeat("B4", SeatType::GOLD);
    // Platinum seats
    screen1->addSeat("C1", SeatType::PLATINUM);
    screen1->addSeat("C2", SeatType::PLATINUM);
    screen1->addSeat("C3", SeatType::PLATINUM);
    cinema->addScreen(screen1);

    // Screen 2
    Screen* screen2 = new Screen(2);
    // Silver seats
    screen2->addSeat("A1", SeatType::SILVER);
    screen2->addSeat("A2", SeatType::SILVER);
    screen2->addSeat("A3", SeatType::SILVER);
    screen2->addSeat("A4", SeatType::SILVER);
    // Gold seats
    screen2->addSeat("B1", SeatType::GOLD);
    screen2->addSeat("B2", SeatType::GOLD);
    screen2->addSeat("B3", SeatType::GOLD);
    // Platinum seats
    screen2->addSeat("C1", SeatType::PLATINUM);
    screen2->addSeat("C2", SeatType::PLATINUM);
    screen2->addSeat("C3", SeatType::PLATINUM);
    cinema->addScreen(screen2);

    // Create Shows
    vector<Show*> shows;

    Show* show1 = new Show(movie1, screen1, "06:00 PM");
    shows.push_back(show1);

    Show* show2 = new Show(movie1, screen2, "09:00 PM");
    shows.push_back(show2);

    Show* show3 = new Show(movie2, screen1, "07:00 PM");
    shows.push_back(show3);

    Show* show4 = new Show(movie3, screen2, "08:00 PM");
    shows.push_back(show4);

    // Create BookingService
    BookingService* bookingService = new BookingService(cinema);

    // ===== APPLICATION LOOP =====

    int choice;
    Customer* currentCustomer = nullptr;

    do {
        showMainMenu();
        choice = getIntInput("");

        switch (choice) {
            case 1: {
                // F1: List Movies
                cinema->listMovies();
                break;
            }

            case 2: {
                // F2-F7: Book Tickets
                cout << "\n===== BOOK TICKETS =====" << endl;

                // Get customer details
                string name = getStringInput("Enter your name: ");
                string phone = getStringInput("Enter your phone: ");
                Customer* customer = new Customer(name, phone);

                // List movies
                cinema->listMovies();
                int movieChoice = getIntInput("Choose movie (enter number): ");
                Movie* selectedMovie = cinema->getMovie(movieChoice - 1);

                if (selectedMovie == nullptr) {
                    cout << "Invalid movie selection!" << endl;
                    delete customer;
                    break;
                }

                // List shows for selected movie
                cout << "\n===== SHOWS FOR " << selectedMovie->getTitle() << " =====" << endl;
                vector<Show*> availableShows;
                int showIndex = 1;
                for (Show* s : shows) {
                    if (s->getMovie() == selectedMovie) {
                        cout << "[" << showIndex << "] " << s->getShowDisplay() << endl;
                        availableShows.push_back(s);
                        showIndex++;
                    }
                }

                if (availableShows.empty()) {
                    cout << "No shows available for this movie." << endl;
                    delete customer;
                    break;
                }

                int showChoice = getIntInput("Choose show (enter number): ");
                Show* selectedShow = availableShows[showChoice - 1];

                if (selectedShow == nullptr) {
                    cout << "Invalid show selection!" << endl;
                    delete customer;
                    break;
                }

                // Display seat layout
                selectedShow->displaySeatLayout();

                // Get seat selection
                string seatInput = getStringInput("\nEnter seat numbers: ");

                // Parse seat numbers
                vector<string> seatNumbers;
                string current = "";
                for (char c : seatInput) {
                    if (c == ',' || c == ' ') {
                        if (!current.empty()) {
                            seatNumbers.push_back(current);
                            current = "";
                        }
                    } else {
                        current += c;
                    }
                }
                if (!current.empty()) {
                    seatNumbers.push_back(current);
                }

                if (seatNumbers.empty()) {
                    cout << "No seats selected!" << endl;
                    delete customer;
                    break;
                }

                // Get payment method
                cout << "\n===== PAYMENT =====" << endl;
                cout << "1. UPI" << endl;
                cout << "2. Card" << endl;
                cout << "3. Cash" << endl;
                int paymentChoice = getIntInput("Choose payment method: ");

                string paymentMethod;
                if (paymentChoice == 1) paymentMethod = "UPI";
                else if (paymentChoice == 2) paymentMethod = "Card";
                else if (paymentChoice == 3) paymentMethod = "Cash";
                else {
                    cout << "Invalid payment method!" << endl;
                    delete customer;
                    break;
                }

                // Book seats
                bool success = bookingService->bookSeats(customer, selectedShow, seatNumbers, paymentMethod);

                if (!success) {
                    // Booking failed
                    delete customer;
                } else {
                    // Store customer for My Tickets
                    currentCustomer = customer;
                }
                break;
            }

            case 3: {
                // F8: Cancel Booking
                cout << "\n===== CANCEL BOOKING =====" << endl;
                string bookingId = getStringInput("Enter Booking ID to cancel (e.g., BK1001): ");
                bookingService->cancelBooking(bookingId);
                break;
            }

            case 4: {
                // My Tickets
                cout << "\n===== MY TICKETS =====" << endl;
                if (currentCustomer == nullptr) {
                    string name = getStringInput("Enter your name: ");
                    bookingService->listMyTickets(name);
                } else {
                    bookingService->listMyTickets(currentCustomer->getName());
                }
                break;
            }

            case 0: {
                cout << "\nThank you for using Movie Ticket System!" << endl;
                break;
            }

            default: {
                cout << "Invalid choice! Please try again." << endl;
                break;
            }
        }

    } while (choice != 0);

    // ===== CLEANUP =====

    // Delete shows
    for (Show* s : shows) {
        delete s;
    }
    shows.clear();

    // Delete booking service (will delete bookings)
    delete bookingService;

    // Delete cinema (will delete screens, seats, movies)
    delete cinema;

    // Delete current customer if exists
    if (currentCustomer) {
        delete currentCustomer;
    }

    return 0;
}