#ifndef SHELL_H
#define SHELL_H

#define MAXARGS 5
#define BUFFER_SIZE 80
#define HOSTBUFFER_SIZE 256
#define BIN_SIZE 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>


/*
 * Changes current directory
 * Implements the function chdir() to move to directories
 * To reach the home directory name the getenv() is used
 */
void* cd(char* input);


/*
 * Prints helpful descriptions of the in built commands
 */
void* help(char* input);


/*
 * Executes a guessing game
 * When the guessing game program ends it return the k-shell prompt
 */
void* game(char* input);


/*
 * Call exit(0) to terminate the shell program
 */
void* quit(char* input);


/*
 * Checks if a command exist in the in built commands
 * If command exist the its executed
 * If command is not found it return 0
 */
int builtin_command(char** argv);


/*
 * Splits the the command lne inputs into tokens
 * Stores token into the given array
 */
void parser(char *buf, char** argv);


/*
 * Evaluates the command line arguments
 * Parses the arguments and check if it's an in built in command
 * If it's not an in built command then invoke a child and 
 * execute the unix command that matches
 * If a command was not found prints and error
 */
void eval(char *cmdline);

#endif