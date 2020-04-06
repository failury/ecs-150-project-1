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
#include <vector>
#include <list>
bool isExit = false;
std::list<std::string> commandHistory;
void tokenize(std::string const &str, const char* delim,std::list<std::string> &out)
{
  //source:https://www.techiedelight.com/split-string-cpp-using-delimiter/
  char *token = strtok(const_cast<char*>(str.c_str()), delim);
  while (token != nullptr)
  {
    out.push_back(std::string(token));
    token = strtok(nullptr, delim);
  }
}
void cd(std::string directory){

}
void ls(std::string directory){

}
void pwd(){

}
void ff(std::string filename,std::string directory){

}
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
    char output[5]  = "/...";
    char *index;
    if(strlen(WorkingDirectory) >= 16)
    {
      index = strrchr(WorkingDirectory,'/');
      strcat(index,"%");
      strcat(output,index);
      write(STDOUT_FILENO,output,strlen(output));
    }else {
      strcat(WorkingDirectory,"%");
      write(STDOUT_FILENO,WorkingDirectory,strlen(WorkingDirectory));
    }
  }
}
std::string readCommand() {
  std::string command;
  char c;
  do {
    if(c == '\004')
    {
      isExit = true;
      return command;
    } else {
      read(STDIN_FILENO, &c, 1);
      command += c;
    }
  } while (c != '\n');
  return command;
}
void addTohistory(std::string command){
  commandHistory.push_back(command);
  if(commandHistory.size() > 10){
    commandHistory.pop_front();
  }
}
std::list<std::string> processCommand(std::string command){
  command.pop_back();
  addTohistory(command);
  std::list<std::string> CommandandArgs;
  tokenize(command, " ", CommandandArgs);
  return CommandandArgs;
}

void executeCommand(std::list<std::string> processedCommand){
  if (processedCommand.front() == "exit") {
    isExit = true;
    return;
  }
  if (processedCommand.front() == "cd") {
    cd(*std::next(processedCommand.begin(),1));
  }else {
    write(STDOUT_FILENO, "Command: ",9);
    for (auto &s: processedCommand) {
      write(STDOUT_FILENO, s.c_str(),s.length());
      write(STDOUT_FILENO, " ",1);
    }
    write(STDOUT_FILENO, "\n",1);
  }
//  if (processedCommand.front() == "ls") ls(*std::next(processedCommand.begin(),1));
//  if (processedCommand.front() == "pwd") pwd();
//  if (processedCommand.front() == "ff") ff(*std::next(processedCommand.begin(),1), *std::next(processedCommand.begin(),2));
}

int main(int argc, char *argv[]){
  struct termios SavedTermAttributes;
  std::string command;
  std::list<std::string> processedCommand;
  while(isExit == false){
    printPrompt();
    command = readCommand();
    processedCommand = processCommand(command);
    executeCommand(processedCommand);
  }




  ResetCanonicalMode(0, &SavedTermAttributes);
  return 0;
}
