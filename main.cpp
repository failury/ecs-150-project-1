//
// Created by failury on 4/2/2020.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <string.h>
#include <iostream>


void ResetCanonicalMode(int fd, struct termios *savedattributes){
  tcsetattr(fd, TCSANOW, savedattributes);
}

void SetNonCanonicalMode(int fd, struct termios *savedattributes){
  struct termios TermAttributes;

  // Make sure stdin is a terminal. 
  if(!isatty(fd)){
    fprintf (stderr, "Not a terminal.\n");
    exit(0);
  }

  // Save the terminal attributes so we can restore them later. 
  tcgetattr(fd, savedattributes);

  // Set the funny terminal modes. 
  tcgetattr (fd, &TermAttributes);
  TermAttributes.c_lflag &= ~(ICANON | ECHO); // Clear ICANON and ECHO. 
  TermAttributes.c_cc[VMIN] = 1;
  TermAttributes.c_cc[VTIME] = 0;
  tcsetattr(fd, TCSAFLUSH, &TermAttributes);
}

void printPrompt(){
  char*WorkingDirectory;
  if((WorkingDirectory = getcwd(NULL, 0)) == NULL)
  {
    perror("Error getting working directory");
  }
  else
  {
    int count = 0;
    char *index;
    for(int i=0;i <= strlen(WorkingDirectory); i++){
      if(WorkingDirectory[i] == '/') count++;
      if(count >2)
      {
        index = strrchr(WorkingDirectory,'/');
      }
    }
    if(count > 2){
     std::cout<<"/..." << index << "%";
    }
      free(WorkingDirectory);
  }

}
void readCommand() {
  char RXChar;
  read(STDIN_FILENO, &RXChar, 1);
  if (0x04 == RXChar) { // Control-d
    return;
  } else {
    if (isprint(RXChar)) {
      printf("RX: '%c' 0x%02X\n", RXChar, RXChar);
    } else {
      printf("RX: ' ' 0x%02X\n", RXChar);
    }
  }
}
void executeCommand(){

}

int main(int argc, char *argv[]){
  //struct termios SavedTermAttributes;

  printPrompt();
  //SetNonCanonicalMode(STDIN_FILENO, &SavedTermAttributes);

//  while(1){
//    printPrompt();
//    readCommand();
//
//
//  }

  //ResetCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
  return 0;
}
