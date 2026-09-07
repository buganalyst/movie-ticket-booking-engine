#pragma once

#include <iostream>
#include <string>
using namespace std;

// Abstract Payment class
class Payment {
public:
    // Constructor
    Payment() {}

    // Virtual destructor
    virtual ~Payment() {}

    // Pure virtual methods
    virtual bool pay(int amount) = 0;
    virtual string getMethodName() = 0;
};