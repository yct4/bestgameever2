# pong

Goals: Make a very basic game and learn the basics of SDL2(https://www.libsdl.org/download-2.0.php) or SFML(https://www.sfml-dev.org/).

## Basic Mechanics of Pong

Video: https://www.ponggame.org/pong-no-flash.php
1 player game (vs the computer)
User 1 moves paddle back and forth as ball travels to other side of table. 
Game is over if ball travels past the paddle. 

## Tasks

1. Create SDL2 window and be able to close window. - X
2. Animate a moving ball on the screen. (One class.) - X
- Collision detection.
  - paddles - X
  - sides (top and bottom) // TODO(need to fix odd bouncing)
  - disappears/game stops if going past the end 
- Trajectory of ball. 
  - left to right - X 
  - angles of bounce (TODO: make this dependent on where the ball hits the paddle)
- How to speed up ball. 
2.5. Player class
- Parameterized initial position.
- Parameterized key bindings.
3. Animate a moving paddle on the screen. (One class.) - X
- Moving left and right - X
4. Create automatic paddle movement for computer player. 
5. Keeping score and displaying score. (Another class.)

## Sources

1. [How to Make Pong](https://www.instructables.com/id/Pong-With-Processing/)
2. [Basics of Game Development](https://www.gamedev.net/tutorials/_/technical/game-programming/your-first-step-to-game-development-starts-here-r2976/)
