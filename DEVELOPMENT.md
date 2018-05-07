## Progress - Before Code Review 4/18
* Began writing game setup functions.
* Wrote functions for displaying start menu, paused menu, and game over menu
  * To get these functions to work properly I had to:
    * load in fonts and set font sizes
    * draw rounded rectangles
    * draw text
    * set specific colors (r, g, b) before drawing text or shapes
    * calculate the x and y positions for each shape/line of text
* Wrote function for displaying top 10 scores
* Added implementation for playing background music

## Progress - Before Code Review 4/25
* Created Pipe and Bird classes
* Wrote functions for creating, displaying, and updating pipes
  * To get these functions to work properly I had to:
    * Create a vector containing pipe objects
    * Keep track of how many frames have passed before creating another pipe
    * Generate random colors and heights for each pipe
    * Calculate rate that pipes should move by each time they are updated
    * Calculate dimensions for bottom pipe rectangle by looking at space that should be between each pipe and top rectangle dimensions
    * Draw rectangles based off of pipe position, dimensions, and color
    * Remove pipes from pipe vector once they were no longer within the screen in order to free some space
* Wrote functions for creating, displaying, and updating bird
  * To get these functions to work properly I had to:
    * Load in, draw, and set proper dimensions for bird image
    * Calculate fair starting position for bird
    * Calculate rate that bird should move by each time it is updated
    * Determine whether or not the bird intersects any pipe each time its position is updated
      * To do this I had to create another rectangle that was an accurate representation of the bird's body or else I wouldn't be able to use the handy intersects() function 
    * Determine whether or not the bird successfully passed any pipe each time its position is updated
      * To do this I had to check if the bird's x position past or at a pipes right corner x position
* Added implementation for playing sound effects when bird is jumping up and when bird dies; also made it possible for music to pause when user pauses game
* Wrote function for displaying current score during gameplay

## Progress - Before Code Review 5/2
* Added implementation for leveling up and playing sound when leveling up
  * To get this implentation to work correctly I had to:
    * Edit the update() function in the pipe class since the amount of squares that a pipe is shifted by had to be changed each time the level increased.
    * Add more variables in the ofApp such as pipes_made and level_ to keep track of important info
    * Specify when to increase a level and play a sound (I decided to go up a level and play the sound after another 7 pipes are made)
* Added implementation for playing sound each time pipe is passed
  * To get this implentation to work correctly I had to:
    * Edit the way I was checking if a bird had passed a pipe. I decided to create a third rectangle for each pipe and this third rectangle represents the space in between a pipe's two rectangles. After creating this third rectangle, I decided to use the intersects() function with the bird's body and the third rectangle to determine if a pipe was successfully passed.
    * Add a sound player to the bird class and load in and play this sound whenever the bird body intersects the pipe's 3rd rectangle.
* Added implementation for displaying level
   * To get this implentation to work correctly I had to:
     * Edit the drawScore() function by rearranging the position of the background rectangle and drawing the level in addition to drawing the current score.
* Added implementation for displaying a background image
   * To get this implentation to work correctly I had to:
     * Decide when to call draw() for the background image. I found out that calling it right before the first shapes for each state (rectangles in the case for start, pause and end screens, and bird for during gameplay) were drawn was the best time since calling draw() before or after would cause the background to be completely black.
     * Change the way the bottom rectangle of each pipe was drawn since I didn't want the pipe to look like it was going into the entire dirt portion of the grass.
