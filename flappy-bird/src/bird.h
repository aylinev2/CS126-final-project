#include "ofMain.h"
#include "pipe.h"
#pragma once

// Enum that represents all possible directions that the bird can be moving
typedef enum {
    UP = 0,
    DOWN
} BirdDirection;

class Bird {
private:
    ofVec2f position; // The current position of the bird
    BirdDirection current_direction_; // The current direction of the bird
    int pipes_passed_; // The amount of pipes successfully passed
    
public:
    Bird(); // Default constructor, initializes and places bird
    bool isDead(vector<Pipe> pipes_); // Determines if the current state of the bird is dead
    void update(); // updates the Bird one body square in the current direction
    BirdDirection getDirection(); // Gets the Bird's current direction
    void setDirection(BirdDirection new_direction); // Sets the Bird's direction
    ofVec2f getPosition(); // Gets the Bird's current position
    bool intersectsPipes(vector<Pipe> pipes_); // Determines if a bird intersects any of the pipes
    int getPipesPassed(); // Returns the number of pipes passed
    ofSoundPlayer sound_effect_; // Sound Player needed to play pipe passed sound;
};
