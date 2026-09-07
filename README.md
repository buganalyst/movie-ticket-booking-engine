# Movie Ticket Booking Engine

This is a modular, console-based movie ticket booking engine developed as a **B.Tech CSE 5th Semester System Design assignment**. The project demonstrates practical application of **Object-Oriented Programming, UML-based system modeling, SOLID principles, modular C++ design, abstraction, inheritance, polymorphism, composition, aggregation, and dependency inversion**.

The system models a cinema environment where customers can browse movies and shows, view seat availability, book seats, make payments, print tickets, and cancel bookings.

## Project Overview

This is designed around a modular object-oriented architecture. Each major responsibility is represented through a dedicated C++ class, with each class maintained in a separate source file as required by the assignment.

The project focuses on translating system requirements into:

- Functional and non-functional requirements
- Noun-verb analysis
- Class responsibilities
- Object relationships
- UML class diagrams
- UML sequence diagrams
- SOLID principles
- Modular source-code architecture
- Clean-code practices

## Features

- Display available movies
- Display shows for a selected movie
- Display seat layout and availability
- Book available seats
- Prevent booking of already-booked seats
- Support Silver, Gold, and Platinum seat types
- Automatic ticket price calculation
- Support UPI, Card, and Cash payments
- Handle failed payments without confirming the booking
- Release seats when payment fails
- Generate and display booking tickets
- Cancel existing bookings
- Make cancelled seats available again
- View customer bookings
- Validate user input and handle invalid selections

## Seat Pricing

| Seat Type | Price |
|---|---:|
| Silver | ₹150 |
| Gold | ₹250 |
| Platinum | ₹400 |

## Payment Methods

The system provides an abstract `Payment` class with multiple concrete implementations:

- `UpiPayment`
- `CardPayment`
- `CashPayment`

Payment processing uses runtime polymorphism through the `Payment` abstraction. A failed payment does not confirm the booking and the selected seats are released.

## System Architecture

The system is divided into independent classes based on their responsibilities.

```text
Movie
 └── Represents movie information

Seat
 └── Represents cinema seats and seat types

Screen
 └── Owns and manages seats

Cinema
 └── Owns movies and screens

Show
 └── Connects a movie with a screen and maintains show seats

ShowSeat
 └── Maintains seat availability for a particular show

Customer
 └── Stores customer information

Booking
 └── Represents a customer's booking

Payment
 ├── UpiPayment
 ├── CardPayment
 └── CashPayment

PriceCalculator
 └── Calculates booking price

TicketPrinter
 └── Displays booking ticket

BookingService
 └── Coordinates the booking and cancellation workflow
```

## Project Structure
```text
movie-ticket-booking-engine/
│
├── 01_Movie.cpp
├── 02_Seat.cpp
├── 03_Screen.cpp
├── 04_Cinema.cpp
├── 05_Show.cpp
├── 06_ShowSeat.cpp
├── 07_Customer.cpp
├── 08_Booking.cpp
├── 09_Payment.cpp
├── 10_PaymentTypes.cpp
├── 11_PriceCalculator.cpp
├── 12_TicketPrinter.cpp
├── 13_BookingService.cpp
├── main.cpp
└── README.md
```
Each class is implemented in a separate .cpp file. No header files are used, following the structure specified for the assignment.

## Compilation
Make sure a C++17-compatible compiler is installed.

Using g++:
```text
g++ -std=c++17 main.cpp 
```
Run the application:

On linux:
```text
./a.out
```
On Windows:
```text
./a.exe
```

## Sample Run
```text
=========================================
      WELCOME TO MOVIE TICKET SYSTEM
=========================================
  1. List Movies
  2. Book Tickets
  3. Cancel Booking
  4. My Tickets
  0. Exit
=========================================
Choose option: 1

===== MOVIES PLAYING =====
[1] 3 Idiots       | Hindi   | 170 min
[2] Interstellar   | English | 169 min

Choose movie: 1

===== SHOWS FOR: 3 Idiots =====
[1] Screen-1 | 06:00 PM
[2] Screen-2 | 09:00 PM

Choose show: 1

===== SEAT LAYOUT =====
PLATINUM (₹400): C1[ ] C2[ ] C3[X] C4[ ]
GOLD     (₹250): B1[ ] B2[ ] B3[X] B4[ ]
SILVER   (₹150): A1[ ] A2[X] A3[ ] A4[ ]

Enter seats to book (space-separated, e.g., A1 B2): A1 B2

=========================================
              BOOKING SUMMARY
=========================================
Movie       : 3 Idiots
Showtime    : Screen-1 (06:00 PM)
Seats       : A1 (Silver), B2 (Gold)
Total Due   : ₹400
=========================================
Select Payment Mode (1. UPI | 2. Card | 3. Cash): 1
Processing UPI payment... Success!

=========================================
               MOVIE TICKET
=========================================
Booking ID  : BK-1001
Movie       : 3 Idiots
Screen      : Screen-1
Show Time   : 06:00 PM
Seats       : A1, B2
Amount Paid : ₹400
Method      : UPI
Status      : CONFIRMED
=========================================
```

## Design Goals
The project was developed with the following goals:

- Translate system requirements into an object-oriented design
- Maintain clear separation of responsibilities
- Demonstrate UML-driven design
- Apply SOLID principles where appropriate
- Reduce coupling between system components
- Keep the code modular and maintainable
- Handle booking and payment failures safely
- Provide an interactive demonstration of the designed system

## Conclusion

Movie Ticket Booking Engine demonstrates the practical application of system design principles through a modular C++ implementation. The project integrates UML modeling, OOP, SOLID principles, clean code practices, and a complete movie booking workflow into a maintainable and extensible design.

## License

This project is open-source and available under the MIT License.
