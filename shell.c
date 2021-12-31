
#include "game.h"
#include "shell.h"

char hostbuffer[HOSTBUFFER_SIZE];
char bin[BIN_SIZE];
char* commands[] = {"cd", "help", "game", "exit"};
void* (*command_functions[])(char*) = {cd, help, game, quit};


void* cd(char* input) {
  if (input == NULL || strcmp(input, "~") == 0) {
    // Move to home directory
    chdir(getenv("HOME"));
  } else {
    // Move to given direcroty path
    chdir(input);
  }
}

void* help(char* input) {
  char* line = "-------------------------------";
  printf("\tBuilt In Commands:\n\n");
  printf("\tCommand\t|\tDescription\n");
  printf("\t%s%s%s\n",line, line, line);
  printf("\tcd\t|\tChanges current woking directory\n");
  printf("\t\t|\tTo move inside a sub directory ");
  printf("follow command with path [cd <path name>]\n");
  printf("\t\t|\tTo move to parent of current directory ");
  printf("follow command with two dots [cd ..]\n");
  printf("\t\t|\tTo move to home directory ");
  printf("write command by itself or followed by a ~ [cd ~]\n");
  printf("\t%s%s%s\n",line, line, line);
  printf("\tgame\t|\tExecutes a Guess a Number Game\n");
  printf("\t%s%s%s\n",line, line, line);
  printf("\texit\t|\tTerminates the current shell\n");
  printf("\t%s%s%s\n",line, line, line);
  printf("\thelp\t|\tPrint the built in commands and its description\n");
}

void* game(char* input) {
  // Executes a guessing game
  guess_the_number();
}

void* quit(char* input) {
  // Terminate shell
  printf("Exiting Shell...\n");
  exit(0);
}

// Wrapper of fork(). Checks for fork errors, quits on error.
pid_t Fork(void) {
  pid_t pid;
  if ((pid = fork()) < 0) {
    fprintf(stderr, "%s: %s\n", "fork error", strerror(errno));
    exit(0);
  }
  return pid;
}

// Wrapper of fgets. Checks and quits on Unix error.
char* Fgets(char *ptr, int n, FILE *stream) {
  char *rptr;
  if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
    fprintf(stderr, "%s\n", "fgets error");
    exit(0);
  }
  // remove "\n" new line 
  ptr[strcspn(ptr, "\n")] = '\0';
  return rptr;
}

// Check if the command is built into this shell
int builtin_command(char** argv) {
  int res = 0;
  int i;
  for (i=0; i<MAXARGS; i++) {
    // If command is found then exeute it
    if (strcmp(commands[i], argv[0]) == 0) {
    res = 1;  
    command_functions[i](argv[1]);
    break;
    }
  }
  return res;
}

// Parses and
void parser(char *buf, char** argv) {
  int i = 0;
  const char* delimiter = " ";
  char* token = strtok(buf, delimiter);  
  while (token != NULL) {
    argv[i] = token;
    token = strtok(NULL, delimiter);
    i++;
  }
}

void eval(char *cmdline) {
  char** argv = (char**)calloc(MAXARGS, sizeof(char*));
  char buf[BUFFER_SIZE];  // Holds modified command line
  pid_t pid;  // Process id
  const char* delimiter = " ";
  int i = 0;

  
  // Split buf into args
  strcpy(buf, cmdline);
  parser(buf, argv);

  // Ignore empty lines
  if (argv[0] == NULL) {
    return;  
  }

  if (builtin_command(argv) == 0) {
    // Concatenate "/bin/" path to the command
    strcpy(bin, "/bin/");
    strcat(bin, argv[0]);
    argv[0] = bin;

    // Executes command from child
    if (fork() == 0) {
      // Check that the command/program exists in Unix (/bin/)
      // If the command is not found then throw message
      execve(argv[0], argv, NULL);
      
      if (execve(argv[0], argv, NULL) < 0) {
        printf("\033[1;34mk-sea-shell-%s> \033[0m ", hostbuffer);
        printf("Command not found--Did you mean something else?\n");
      }
      // Terminates process
      exit(1);
    } else {
      wait(NULL);
    }
  } 
  free(argv);
  return;
}

int main() {
  char cmdline[BUFFER_SIZE];  // command line buffer
  int hostname;
  struct hostent *host_entry;

  // Retrieve host name
  hostname = gethostname(hostbuffer, sizeof(hostbuffer));

  while (1) {
    // Print command prompt with hostname
    printf("\033[1;34mk-sea-shell-%s> \033[0m", hostbuffer);

    // Read input from user
    Fgets(cmdline, BUFFER_SIZE, stdin);

    // If we get the eof, quit the program/shell
    if (feof(stdin)) {
      exit(0);
    }
    
    // Otherwise, evaluate the input and execute.
    eval(cmdline);
  }
}