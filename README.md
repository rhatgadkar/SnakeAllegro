# SnakeAllegro

Classic snake game programmed in C++ using Allegro 5 library.

![snake1](https://user-images.githubusercontent.com/8902454/32877422-47255d72-ca56-11e7-9d70-b2f61c6ac180.jpeg)

Each snake body part contains a pointer to its parent body part, and the value of the previous
direction it was moving. In each tick, the body parts will move in the parent's direction from the previous tick.

Each time a food is collected, the score increments, and the food is spawned at a random location, which does not contain a snake body part or a wall.

When the snake head hits a wall or a snake body, the game is over.

The player controls the snake head using the arrow keys.
