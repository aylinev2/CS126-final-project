#pragma once
#include <random>
#include "ofMain.h"

class Pipe {
private:
    std::mt19937 generator_; // Generator used for pseudorandom number generation for pipe color and position
    std::uniform_int_distribution<> dist_y_; // Generates valid y positions in current window dimension
    std::uniform_int_distribution<> dist_color_; // Generates valid rgb values
    
    ofVec2f pipe_space_; // Amount of space that should be left between the pipe top and bottom
    ofRectangle pipe_rect_1; // The rectangle which represents the pipe top
    ofRectangle pipe_rect_2; // The rectangle which represents the pipe bottom
    ofRectangle pipe_rect_3; // The rectangle which represents the pipe's empty space
    ofColor color_; // The color of the pipe
    
public:
    Pipe(); // Default constructor, sets up generator devices and rarndomly places pipe space at a valid location
    Pipe& operator=(const Pipe& other); // Copy consturctor
    ofRectangle getPipeRect1(); // Gets the rectangle that represents the pipe top
    ofRectangle getPipeRect2(); // Gets the rectangle that represents the pipe bottom
    ofRectangle getPipeRect3(); // Gets the rectangle that represents the pipe's empty space
    ofColor getColor(); // Gets the color of the current pipe object
    void setPipe(); // Sets the pipe's size
    void update(int level); // updates the pipe by moving it a certain amount of squares in the current direction
};
