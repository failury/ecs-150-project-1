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
std::vector<std::string> commandHistory;
int historyIndex = 0;
void clearField(int size){
  for (unsigned int i = 0; i < size; i++) {// clear the field
    write(STDOUT_FILENO, "\b \b", 3);
  }
}
void tokenize(std::string const &str, const char *delim, std::list<std::string> &out) {
  //source:https://www.techiedelight.com/split-string-cpp-using-delimiter/
  char *token = strtok(const_cast<char *>(str.c_str()), delim);
  while (token != nullptr) {
    out.push_back(token);
    token = strtok(nullptr, delim);
  }
  out.push_back("noargs");
  }
void cd(std::string directory) {
  std::string destination;
  std::string currentDirecoty= getcwd(NULL, 0);
  if(directory == "noargs")
  {
  chdir(getenv("HOME"));
  }else if(directory == "..") {
  auto index = currentDirecoty.find_last_of("/");
    destination = currentDirecoty.substr(0,index);
    if (chdir(destination.c_str()) == -1){
      write(STDOUT_FILENO, "Error Changing Directory\n", 25);
    }
  } else {
    destination = currentDirecoty + "/" + directory;
    if(chdir(destination.c_str()) == -1){
      write(STDOUT_FILENO, "Error Changing Directory\n", 25);
    }
  }
}
void ls(std::string directory) {

}
void pwd() {

}
void ff(std::string filename, std::string directory) {

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
void printPrompt() {
  clearField(128);
  std::string WorkingDirectory;
  WorkingDirectory = getcwd(NULL, 0);
  std::string output = "/.../";
  int index;
    if (WorkingDirectory.length() >= 16) {
      index = WorkingDirectory.find_last_of("/");
      WorkingDirectory = WorkingDirectory.substr(index+1);
      WorkingDirectory +="% ";
      output+= WorkingDirectory;
      write(STDOUT_FILENO, output.c_str(), output.length());
    } else {
      WorkingDirectory +="% ";
      write(STDOUT_FILENO, WorkingDirectory.c_str(), WorkingDirectory.length());
    }

}
std::string readCommand() {
  std::string command;
  char c;
  do {
    read(STDIN_FILENO, &c, 1);
    if (c == '\004') // control D detect
    {
      isExit = true;
      return command;
    } else if (c == 0x7F)// backspace
    {
      if (command.length() == 0) {//cant delete anymore
        write(STDOUT_FILENO, "\a", 1);
      } else {
        write(STDOUT_FILENO, "\b \b", 3);//**
        command.pop_back();
      }
    } else if (c== 0x1B) { //the up arrow is represented as three ASCII character, 0x1B, 0x5B and 0x41, down arrow is x1B, 0x5B and 0x42.
      read(STDIN_FILENO, &c, 1);
      if (c == 0x5B) {
        read(STDIN_FILENO, &c, 1);
        if (c == 0x41) {
          clearField(128);
          historyIndex--;
          if (historyIndex <= 0) {
            historyIndex = 0;
            write(STDOUT_FILENO, "\a", 1);
            clearField(128);
            auto displayCommand = commandHistory[historyIndex];
            printPrompt();
            command = displayCommand;
            write(STDOUT_FILENO, command.c_str(), command.length());
            continue;
          } else {
            auto displayCommand = commandHistory[historyIndex];

            printPrompt();
            command = displayCommand;
            write(STDOUT_FILENO, command.c_str(), command.length());
          }
        } if (c == 0x42)// down arrow
        {
          clearField(128);
          historyIndex++;
           if(historyIndex >= int(commandHistory.size()) || historyIndex >=10){
            historyIndex = int(commandHistory.size());
             clearField(128);
            write(STDOUT_FILENO, "\a", 1);
            printPrompt();
            continue;
          } else
            {
            auto displayCommand = std::next(commandHistory.begin(),historyIndex);
            command = *displayCommand;
            printPrompt();
            write(STDOUT_FILENO, command.c_str(), command.length());
          }
        }
      }
    }
    else {
      command += c;
      write(STDOUT_FILENO, &c, 1);
    }
  } while (c != 0x0A);
  return command;
}
void addTohistory(std::string command) {
  commandHistory.push_back(command);
  historyIndex++;
  if (commandHistory.size() > 10) {
    commandHistory.erase(commandHistory.begin());
  }
}
std::list<std::string> processCommand(std::string command) {
  command.pop_back();
  addTohistory(command);
  std::list<std::string> CommandandArgs;
  tokenize(command, " ", CommandandArgs);
  return CommandandArgs;
}

void executeCommand(std::list<std::string> processedCommand) {
  if (processedCommand.front() == "exit") {
    isExit = true;
    return;
  }
  if (processedCommand.front() == "cd") {
    cd(*std::next(processedCommand.begin(), 1));
  } else {
    write(STDOUT_FILENO, "Command: ", 9);
    for (auto &s: processedCommand) {
      if (s == "noargs") {
        break;
      }
      write(STDOUT_FILENO, s.c_str(), s.length());
      write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);
  }
//  if (processedCommand.front() == "ls") ls(*std::next(processedCommand.begin(),1));
//  if (processedCommand.front() == "pwd") pwd();
//  if (processedCommand.front() == "ff") ff(*std::next(processedCommand.begin(),1), *std::next(processedCommand.begin(),2));
}

int main(int argc, char *argv[]) {
  struct termios SavedTermAttributes;
  std::string command;
  SetNonCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
  std::list<std::string> processedCommand;
  while (isExit == false) {
    printPrompt();
    command = readCommand();
    processedCommand = processCommand(command);
    executeCommand(processedCommand);
  }

  ResetCanonicalMode(0, &SavedTermAttributes);
  return 0;
}
