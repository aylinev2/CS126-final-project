#include "pipe.h"

// Default constructor
Pipe::Pipe() {
    pipe_space_.set(90, 185);
    generator_ = std::mt19937(rand());
    dist_y_ = std::uniform_int_distribution<>(pipe_space_.y / 2, ofGetWindowHeight() - (pipe_space_.y * 2));
    dist_color_ = std::uniform_int_distribution<>(0, 255);
    setPipe();
}

// Copy constructor
Pipe& Pipe::operator=(const Pipe& other) {
    pipe_rect_1 = other.pipe_rect_1;
    pipe_rect_2 = other.pipe_rect_2;
    pipe_rect_3 = other.pipe_rect_3;
    pipe_space_.set(other.pipe_space_);
    color_.set(other.color_);
    
    return *this;
}

// Gets the rectangle that represents the pipe top
ofRectangle Pipe::getPipeRect1() {
    return pipe_rect_1;
}

// Gets the rectangle that represents the pipe bottom
ofRectangle Pipe::getPipeRect2(){
    return pipe_rect_2;
}

// Gets the rectangle that represents the pipe's empty space
ofRectangle Pipe::getPipeRect3(){
    return pipe_rect_3;
}

// Gets the color of the current pipe object
ofColor Pipe::getColor(){
    return color_;
}

// Sets pipe dimensions and color
void Pipe::setPipe(){
    auto y = dist_y_(generator_);
    pipe_rect_1.setPosition(ofGetWindowWidth() - pipe_space_.x, 0);
    pipe_rect_1.setSize(90, y);
    
    pipe_rect_2.setPosition(ofGetWindowWidth() - pipe_space_.x, y + pipe_space_.y);
    pipe_rect_2.setSize(90, ofGetWindowHeight() - pipe_space_.y - y);
    
    pipe_rect_3.setPosition(pipe_rect_1.getBottomRight().x, pipe_rect_1.getBottomRight().y);
    pipe_rect_3.setSize(10, 185);
    
    color_.r = dist_color_(generator_);
    color_.g = dist_color_(generator_);
    color_.b = dist_color_(generator_);
}

// updates the pipe by moving it a certain amound of squares in the current direction
void Pipe::update(int level) {
    pipe_rect_1.setPosition(pipe_rect_1.getTopLeft().x - 15 - (level * 2), pipe_rect_1.getTopLeft().y);
    pipe_rect_2.setPosition(pipe_rect_2.getTopLeft().x - 15 - (level * 2), pipe_rect_2.getTopLeft().y);
    pipe_rect_3.setPosition(pipe_rect_3.getTopLeft().x - 15 - (level * 2), pipe_rect_3.getTopLeft().y);
}
