#include "bird.h"

// Default constructor, initializes and places bird
Bird::Bird(){
    current_direction_ = DOWN;
    position.set(ofGetWindowWidth() / 4, ofGetWindowHeight() / 3);
    pipes_passed_ = 0;
    sound_effect_.load("passed 2.wav");
    sound_effect_.setVolume(0.40);
}

// Determines if the current state of the bird is dead
bool Bird::isDead(vector<Pipe> pipes_) {
    // Bird is dead if the body is off screen
    if (position.x < 0 || position.y < 0 || position.x > ofGetWindowWidth() - 70 || position.y > ofGetWindowHeight() - 70) {
        return true;
    }
    
    // If the bird is intersecting with any of the pipes it is dead
    return intersectsPipes(pipes_);
}

// Determines if the bird intersects any of the pipes
bool Bird::intersectsPipes(vector<Pipe> pipes_) {
    ofRectangle body_rect_(position.x + 30, position.y + 10, 10, 53);
    
    for (int i = 0; i < pipes_.size(); i++){
        if (body_rect_.intersects(pipes_.at(i).getPipeRect1()) || body_rect_.intersects(pipes_.at(i).getPipeRect2())){
            return true;
        }
      
        if (body_rect_.intersects(pipes_.at(i).getPipeRect3())){
            sound_effect_.play();
            pipes_passed_++;
        }
    }
    return false;
}

// Returns the amount of pipes passed successfully
int Bird::getPipesPassed(){
    return pipes_passed_;
}

// updates the Bird one body square in the current direction
void Bird::update(){
    // Move the bird body one square in the direction the bird is moving
    switch (current_direction_) {
        case UP:
            position.set(position.x, position.y - 70);
            break;
        case DOWN:
            position.set(position.x, position.y + 17);
            break;
    }
}

// Gets the Bird's current direction
BirdDirection Bird::getDirection() {
    return current_direction_;
}

// Sets the Bird's direction
void Bird::setDirection(BirdDirection new_direction){
    current_direction_ = new_direction;
}

// Gets the Bird's current position
ofVec2f Bird::getPosition(){
    return position;
}
