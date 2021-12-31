#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void clear_input(void){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        continue;
    }
}

void guess_the_number() {
    int num;
    int rand_number;
    int user_guess; 
    int attempts = 1;
    char* line = "--------------";
    
  
    printf("\t\033[1;92m%s Welcome to Guess the Number Game %s\033[0m\n",
             line, line);
    printf("\tInput a number greater or equal to 10 --> ");
    scanf("%d", &num);
    clear_input();

    while (num < 10) {
        printf("\tYour input is below 10\n");
        printf("\tInput a number greater of equal to 10 --> ");
        scanf("%d", &num);
        clear_input();
    }

    printf("\n\tYou have 5 attempts to guess a number between 1 and %d\n", num);
    
    // Generate a random number
    rand_number = rand() % num;

    // Loop until user wins or game over
    while (1) {
  
        if (attempts > 5) {
            printf("\n\tGame Over!, you used all of your attempts\n");
            printf("\t\033[1;92m%s Input \"game\" to play again %s\033[0m\n",
                     line, line);
            break;
        }
  
        // Scan guess of user
        printf("\tEnter your guess--> ");
        scanf("%d", &user_guess);
        clear_input();
  
        // If guess is correct print number of attempts and exit game
        if (user_guess == rand_number) {
           printf("\n\tCongratulation! ");
           printf("You guessed the number(%d) in %d attempts!\n",
                     rand_number, attempts);
           printf("\t\033[1;92m%s Input \"game\" to play again %s\033[0m\n",
                     line, line);
           break;
        } else if (user_guess > rand_number) {
            // When the guess is higher than the answer
            printf("\t\033[1;91mYour guess is to high, Guess again!\033[0m\n");
            attempts++;
        } else {
            // When the guess is lower than the answer
            printf("\t\033[1;91mYour guess is too low, Guess again!\033[0m\n");
            attempts++;
        }
    }
}
