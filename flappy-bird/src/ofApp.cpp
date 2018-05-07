#include "ofApp.h"

// Game Setup method
void flappyBird::setup(){
    ofSetBackgroundColor(ofColor(205, 255, 255));
    ofSetWindowTitle("Flappy Bird 🐤");
    pipes_.push_back(Pipe());
    
    // Fonts for display screens loaded in
    myfont.loadFont("joystix monospace.ttf", 70);
    mymediumfont.loadFont("joystix monospace.ttf", 25);
    mysmallerfont.loadFont("joystix monospace.ttf", 18);
    
    // Images that are displayed during gameplay loaded in
    bird_pic_loader.load("bird.png");
    back_pic_loader.load("background.jpg");
    
    // Main background music loaded in
    main_.load("flappy bird.wav");
    main_.play();
}

// Update function called before every draw that updates bird position and score
void flappyBird::update(){
    if (current_state == IN_PROGRESS) {
        game_bird_.update();
        score_ = game_bird_.getPipesPassed();

        if (game_bird_.isDead(pipes_)) {
            main_.load("died.wav");
            main_.setVolume(0.70);
            main_.play();
            scores_.push_back(score_);
            current_state = FINISHED;
        }
    }
}

// Updates all the pipes in the pipe vector
void flappyBird::updateAllPipes(){
    frames_passed++;
    if ((frames_passed % 24) == 0){
        pipes_.push_back(Pipe());
        pipes_made++;
    }
    
    int prev_level_ = level_;
    level_ = floor(pipes_made / 7);
    
    if (prev_level_ < level_){
        level_up_.load("level up.wav");
        level_up_.setVolume(0.50);
        level_up_.play();
    }
    
    for (int i = 0; i < pipes_.size(); i++) {
        pipes_.at(i).update(level_);
        if (pipes_.at(i).getPipeRect1().x < 0 - 90){
            pipes_.erase(pipes_.begin() + i);
        }
    }
}

// Function called on every frame
void flappyBird::draw(){
    if (current_state == PAUSED){
        if (!started_){
            drawGameStart();
        } else {
            if (show_scores){
                drawGamePausedWScores();
            } else {
                drawGamePaused();
            }
        }
    } else if (current_state == FINISHED){
        drawGameFinished();
    } else {
        updateAllPipes();
        drawBird();
        drawAllPipes();
        drawScoreAndLevel();
    }
}

// Function that handles actions based on user key presses
void flappyBird::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case
    
    if (upper_key == 'S' && current_state != FINISHED) {
        // Starts the game
        started_ = true;
        current_state = IN_PROGRESS;
    } else if (upper_key == 'P' && current_state != FINISHED) {
        show_scores = false;
        // Pause or unpause
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
        if (current_state == PAUSED){
            main_.setPaused(true);
        } else {
            main_.setPaused(false);
        }
    } else if (upper_key == 'T' && current_state != FINISHED) {
        show_scores = true;
        // Pause or unpause
        current_state = (current_state == IN_PROGRESS) ? PAUSED : IN_PROGRESS;
        if (current_state == PAUSED){
            main_.setPaused(true);
        } else {
            main_.setPaused(false);
        }
    } else if (current_state == IN_PROGRESS) {
        BirdDirection current_direction = game_bird_.getDirection();
        if (upper_key == ' ' && current_direction != UP) {
            sound_effects_.load("boop.wav");
            sound_effects_.setVolume(0.25);
            sound_effects_.play();
            game_bird_.setDirection(UP);
            update();
            game_bird_.setDirection(DOWN);
        }
    } else if (upper_key == 'R' && current_state == FINISHED) {
        reset();
    }
}

// Resets the game
void flappyBird::reset() {
    main_.load("flappy bird.wav");
    main_.setVolume(1.0);
    main_.play();
    current_state = IN_PROGRESS;
    game_bird_ = Bird();
    frames_passed = 0;
    pipes_made = 0;
    pipes_.clear();
    pipes_.push_back(Pipe());
}

// Draws Bird
void flappyBird::drawBird(){
    ofVec2f bird_pos = game_bird_.getPosition();
    ofSetColor(255, 255, 255);
    back_pic_loader.draw(0, 0, 1024, 768);
    bird_pic_loader.draw(bird_pos.x, bird_pos.y, 70, 70);
}

// Draws all of the pipes in the pipe vector
void flappyBird::drawAllPipes(){
    for (int i = 0; i < pipes_.size(); i++){
        ofSetColor(pipes_.at(i).getColor());
        ofDrawRectangle(pipes_.at(i).getPipeRect1());
        
        // Draws a portion of bottom rectangle so that it looks well with background image
        ofRectangle bottom_ = pipes_.at(i).getPipeRect2();
        bottom_.setSize(bottom_.width, bottom_.height - 50);
        ofDrawRectangle(bottom_);
    }
}

// Draws Score
void flappyBird::drawScoreAndLevel(){
    ofSetColor(255, 204, 217);
    ofDrawRectRounded(ofGetWindowWidth() / 4, 3, ofGetWindowWidth() / 2, 50, 10);
    
    ofSetColor(0, 0, 0);
    mymediumfont.drawString("SCORE:", ofGetWindowWidth() / 4 + 23, 40);
    mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 4 + 180.5, 40);
    mymediumfont.drawString("LEVEL:", ofGetWindowWidth() / 2 + 40, 40);
    mymediumfont.drawString(std::to_string(level_ + 1), ofGetWindowWidth() / 2 + 196, 40);
}

// Draws Game Start screen
void flappyBird::drawGameStart(){
    ofSetColor(255, 255, 255, 255);
    back_pic_loader.draw(0, 0, 1024, 768);
    
    ofSetColor(255, 204, 217);
    ofDrawRectRounded(ofGetWindowWidth() / 4, ofGetWindowHeight() / 4, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 10);
    
    ofSetColor(66, 197, 244);
    myfont.drawString("FLAPPY", ofGetWindowWidth() / 3.6, ofGetWindowHeight() / 2.2);
    myfont.drawString("BIRD", ofGetWindowWidth() / 2.9, ofGetWindowHeight()  / 1.6);
    
    ofSetColor(128, 128, 128);
    mysmallerfont.drawString("Press S to start!", ofGetWindowWidth() / 3, ofGetWindowHeight() / 1.4);
}

// Draws Game Paused screen
void flappyBird::drawGamePaused(){
    ofSetColor(255, 255, 255, 255);
    back_pic_loader.draw(0, 0, 1024, 768);
    
    ofSetColor(255, 204, 217);
    ofDrawRectRounded(ofGetWindowWidth() / 4, ofGetWindowHeight() / 4, ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 10);
    
    ofSetColor(0, 0, 255);
    myfont.drawString("GAME", ofGetWindowWidth() / 2.9, ofGetWindowHeight() / 2.6);
    myfont.drawString("PAUSED", ofGetWindowWidth() / 3.6, ofGetWindowHeight()  / 2);
    
    ofSetColor(128, 128, 128);
    mymediumfont.drawString("SCORE", ofGetWindowWidth() / 2.3, ofGetWindowHeight()  / 1.75);
    
    if (score_ < 10){
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.05, ofGetWindowHeight()  / 1.6);
    } else {
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.1, ofGetWindowHeight()  / 1.6);
    }
    mysmallerfont.drawString("Press P to unpause!", ofGetWindowWidth() / 3.1, ofGetWindowHeight() / 1.4);
}

// Draws Game Paused screen with top ten scores
void flappyBird::drawGamePausedWScores(){
    ofSetColor(255, 255, 255, 255);
    back_pic_loader.draw(0, 0, 1024, 768);
    
    ofSetColor(255, 204, 217);
    ofDrawRectRounded(ofGetWindowWidth() / 4, ofGetWindowHeight() / 7, ofGetWindowWidth() / 2, ofGetWindowHeight() / 1.25, 10);
    
    ofSetColor(0, 0, 255);
    myfont.drawString("GAME", ofGetWindowWidth() / 2.9, ofGetWindowHeight() / 3.5);
    myfont.drawString("PAUSED", ofGetWindowWidth() / 3.6, ofGetWindowHeight()  / 2.5);
    
    ofSetColor(128, 128, 128);
    mymediumfont.drawString("SCORE", ofGetWindowWidth() / 2.3, ofGetWindowHeight()  / 2.2);
    
    if (score_ < 10){
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.05, ofGetWindowHeight()  / 2.0);
    } else {
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.1, ofGetWindowHeight()  / 2.0);
    }
    
    mysmallerfont.drawString("Press T to unpause!", ofGetWindowWidth() / 3.1, ofGetWindowHeight() / 1.1);
    displayTopTen();
}

// Draws Game Over screen with top ten scores
void flappyBird::drawGameFinished(){
    ofSetColor(255, 255, 255, 255);
    back_pic_loader.draw(0, 0, 1024, 768);
    
    ofSetColor(255, 204, 217);
    ofDrawRectRounded(ofGetWindowWidth() / 4, ofGetWindowHeight() / 7, ofGetWindowWidth() / 2, ofGetWindowHeight() / 1.25, 10);
    
    ofSetColor(255, 64, 0);
    myfont.drawString("GAME", ofGetWindowWidth() / 2.9, ofGetWindowHeight() / 3.5);
    myfont.drawString("OVER!", ofGetWindowWidth() / 3.1, ofGetWindowHeight()  / 2.5);
    
    ofSetColor(128, 128, 128);
    mymediumfont.drawString("FINAL SCORE", ofGetWindowWidth() / 2.8, ofGetWindowHeight()  / 2.2);
    
    if (score_ < 10){
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.05, ofGetWindowHeight()  / 2.0);
    } else {
        mymediumfont.drawString(std::to_string(score_), ofGetWindowWidth() / 2.1, ofGetWindowHeight()  / 2.0);
    }
    
    mysmallerfont.drawString("Press R to restart!", ofGetWindowWidth() / 3.1, ofGetWindowHeight() / 1.1);
    displayTopTen();
}

// Draws top 10 scores since game started in descending order
void flappyBird::displayTopTen(){
    ofSetColor(66, 197, 244);
    mysmallerfont.drawString("TOP TEN SCORES", ofGetWindowWidth() / 2.75, ofGetWindowHeight() / 1.85);
    
    scores_.sort(std::greater<int>());
    
    int i = 0;
    double spacing_ = 1.75;
    for (list<int>::const_iterator it = scores_.begin(); it != scores_.end() && i < 10; ++it, i++) {
        if (*it < 10){
            mysmallerfont.drawString(to_string(*it), ofGetWindowWidth() / 2.05, (ofGetWindowHeight() / (spacing_)) + (25 * i));
        } else {
            mysmallerfont.drawString(to_string(*it), ofGetWindowWidth() / 2.1, (ofGetWindowHeight() / (spacing_)) + (25 * i));
        }
    }
}
