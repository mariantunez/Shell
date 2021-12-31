#ifndef GAME_H

#define GAME_H

// Implements a Guess the Number game
// Loops to receive user input until the game is won or a game over ocurrs
// The user have 5 attempts to guess the right answer of the number
// If the attempts are exceed then it's game over
void guess_the_number();

// Clears the input stream after using scanf discarding any characters
// that remain in the input stream
void clear_input(void);

#endif