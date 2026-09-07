#pragma once

#include <iostream>
#include <string>
using namespace std;

class Customer {
private:
    string name;
    string phone;

public:
    // Constructor
    Customer(string name, string phone) {
        this->name = name;
        this->phone = phone;
    }

    // Getters
    string getName() { return name; }
    string getPhone() { return phone; }

    // Display customer info
    void display() {
        cout << "Name: " << name << " | Phone: " << phone;
    }
};