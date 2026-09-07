#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Movie {
private:
    string title;
    string language;
    int duration;  // in minutes

public:
    // Constructor
    Movie(string title, string language, int duration) {
        this->title = title;
        this->language = language;
        this->duration = duration;
    }

    // Getters
    string getTitle() { return title; }
    string getLanguage() { return language; }
    int getDuration() { return duration; }

    // Display movie details
    void display() {
        cout << title << " " << language << " " << duration << " min";
    }
};