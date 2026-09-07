#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "03_Screen.cpp"
#include "01_Movie.cpp"
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen*> screens;
    vector<Movie*> movies;

public:
    // Constructor
    Cinema(string name) {
        this->name = name;
    }

    // Destructor - delete all screens and movies
    ~Cinema() {
        for (Screen* screen : screens) {
            delete screen;
        }
        screens.clear();
        for (Movie* movie : movies) {
            delete movie;
        }
        movies.clear();
    }

    // Add screen
    void addScreen(Screen* screen) {
        screens.push_back(screen);
    }

    // Add movie
    void addMovie(Movie* movie) {
        movies.push_back(movie);
    }

    // Getters
    string getName() { return name; }
    vector<Screen*>& getScreens() { return screens; }
    vector<Movie*>& getMovies() { return movies; }

    // Get movie by index
    Movie* getMovie(int index) {
        if (index >= 0 && index < (int)movies.size()) {
            return movies[index];
        }
        return nullptr;
    }

    // Get screen by index
    Screen* getScreen(int index) {
        if (index >= 0 && index < (int)screens.size()) {
            return screens[index];
        }
        return nullptr;
    }

    // List all movies
    void listMovies() {
        if (movies.empty()) {
            cout << "No movies currently playing." << endl;
            return;
        }
        cout << "\n===== MOVIES PLAYING =====" << endl;
        for (int i = 0; i < (int)movies.size(); i++) {
            cout << "[" << (i+1) << "] ";
            movies[i]->display();
            cout << endl;
        }
    }
};