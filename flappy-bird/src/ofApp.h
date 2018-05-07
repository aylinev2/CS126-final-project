#pragma once
#include "ofMain.h"
#include "bird.h"
#include "pipe.h"
using namespace std;

class flappyBird : public ofBaseApp{
    
// Enum to represent the current state of the game
enum GameState {
    IN_PROGRESS = 0,
    PAUSED,
    FINISHED
};
    
private :
    int pipes_made = 0; // Number of pipes created since game started
    int level_ = 0; // The current level
    long int frames_passed = 0; // Number of frames passed, used for timing between each pipe's creation
    GameState current_state = PAUSED; // Represents the current state of the game, used to determine possible actions
    Bird game_bird_; // The object that represents the user controlled bird
    bool started_ = false; // Represents whether or not the game has started.
    bool show_scores = false; // Represents whether or not top ten scores should be displayed.
    int score_; // Current score
    list<int> scores_; // List containing all scores since game was opened
    vector<Pipe> pipes_; // List containing all the current pipe obstacles
    
    // Fonts needed for start, pause, and title screens.
    ofTrueTypeFont myfont;
    ofTrueTypeFont mysmallerfont;
    ofTrueTypeFont mymediumfont;
    
    // Image loaders needed for game
    ofImage bird_pic_loader;
    ofImage back_pic_loader;
    
    // Sound Players needed to play background music and other sound effects
    ofSoundPlayer main_;
    ofSoundPlayer sound_effects_;
    ofSoundPlayer level_up_;
    
    // Helper methods to draw various states of the game on the screen.
    void drawBird();
    void drawAllPipes();
    void drawScoreAndLevel();
    void drawGameStart();
    void drawGamePaused();
    void drawGamePausedWScores();
    void drawGameFinished();
    void displayTopTen();
    
    // Resets the game
    void reset();
    
public:
    // Sets the game up
    void setup();
    
    // Functions that are called on every frame
    void updateAllPipes();
    void update();
    void draw();

    // Function that handles user interaction
    void keyPressed(int key);
};
