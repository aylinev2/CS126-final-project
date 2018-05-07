# CS 126 FinalProject
* For my final project, I decided to create an Open Frameworks implementation of Flappy Bird.
* In this project, I used the [ofxGui](http://openframeworks.cc/documentation/ofxGui/) library and other significant tools in OpenFrameworks such as [ofSoundPlayer](http://openframeworks.cc/documentation/sound/ofSoundPlayer/), [ofTrueTypeFront](http://openframeworks.cc/documentation/graphics/ofTrueTypeFont/), and [ofImage](http://openframeworks.cc/documentation/graphics/ofImage/). 

# Rules
* In this game, the player must navigate the bird through a series of openings between pipes. Colliding with a pipe or moving the bird out of the screen results in a game over.
* The height that the bird rises when the space bar is pressed is fixed. The player can press the spacebar repeatedly to gain altitude. When the player does not press the spacebar, the bird loses altitude.
* The score is determined by the amount of pipes passed successfully.
* After successfuly passing 7 pipes, the player levels up and the speed at which the pipes move increases.
* The player has the option to pause the game at any time by pressing 'P' or 'T'.
  * Pressing 'T' will pause the game and display the top 10 scores since the game was opened along with the current score.
  * Pressing 'P' will simply pause the game and display the current score.
* When the player loses, he or she has the option to restart by pressing 'R'.

# How to run Flappy Bird
* In order to run the flappy bird game, you must first have an IDE such as [xcode](https://developer.apple.com/xcode/) or [visual studio](https://www.visualstudio.com/vs/). 
* After properly setting up your IDE, download [OpenFrameworks](http://openframeworks.cc/download/). 
* After downloading OpenFrameworks, open the OpenFrameworks project generator.
* Download this project as a ZIP and extract it.
* In the OpenFrameworks project generator, choose import and select the extracted ZIP file of this project.
* Once imported, the program is able to be run.
