//
// Created by failury on 4/2/2020.
//

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <termios.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
#include <dirent.h>
bool isExit = false;
std::vector<std::string> commandHistory;
int historyIndex = 0;
std::string parentDirecoty;
void clearField(int size){
  for (unsigned int i = 0; i < size; i++) {// clear the field
    write(STDOUT_FILENO, "\b \b", 3);
  }
}

std::string tokenize(std::string string) {
  // adapted from https://www.geeksforgeeks.org/remove-extra-spaces-string/
  std::string str = string;
  // n is length of the original string
  int n = str.length();
  // i points to next position to be filled in
  // output string/ j points to next character
  // in the original string
  int i = 0, j = -1;
  // flag that sets to true is space is found
  bool spaceFound = false;
  // Handles leading spaces
  while (++j < n && str[j] == ' ');
  // read all characters of original string
  while (j < n)
  {
    // if current characters is non-space
    if (str[j] != ' ')
    {
        // copy current character at index i
        // and increment both i and j
        str[i++] = str[j++];
      // set space flag to false when any
      // non-space character is found
      spaceFound = false;
    }
      // if current character is a space
    else if (str[j++] == ' ')
    {
      // If space is encountered for the first
      // time after a word, put one space in the
      // output and set space flag to true
      if (!spaceFound)
      {
        str[i++] = ' ';
        spaceFound = true;
      }
    }
  }

  // Remove trailing spaces
  if (i <= 1)
    str.erase(str.begin() + i, str.end());
  else
    str.erase(str.begin() + i - 1, str.end());
  return str;
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
  //https://stackoverflow.com/a/612176
  //https://stackoverflow.com/a/10323131
  std::string currentDirecoty= getcwd(NULL, 0);
  if(directory == "noargs")
  {
    directory = currentDirecoty;
  }
  DIR *dir;
  struct dirent *ent;
  struct stat filestatus;
  if ((dir = opendir (directory.c_str())) != NULL) {
    while((ent = readdir (dir)) != NULL){
      stat(directory.c_str(), &filestatus);
      if(S_ISDIR(filestatus.st_mode)){write(STDOUT_FILENO, "d", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IRUSR){write(STDOUT_FILENO, "r", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IWUSR){write(STDOUT_FILENO, "w", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IXUSR){write(STDOUT_FILENO, "x", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IRGRP){write(STDOUT_FILENO, "r", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IWGRP){write(STDOUT_FILENO, "w", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IXGRP){write(STDOUT_FILENO, "x", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IROTH){write(STDOUT_FILENO, "r", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IWOTH){write(STDOUT_FILENO, "w", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      if(filestatus.st_mode & S_IXOTH){write(STDOUT_FILENO, "x", 1);} else{write(STDOUT_FILENO, "-", 1);	}
      write(STDOUT_FILENO, " ", 1);
      write(STDOUT_FILENO,ent->d_name,strlen(ent->d_name));
      write(STDOUT_FILENO, "\n", 1);
    }
    closedir (dir);
    } else {
    write(STDOUT_FILENO, ("Failed to open directory \"" + directory + "\"").c_str(), directory.length()+ 27);
    write(STDOUT_FILENO, "\n", 1);
  }
}
void pwd() {
  std::string currentDirecoty= getcwd(NULL, 0);
  write(STDOUT_FILENO,currentDirecoty.c_str(),currentDirecoty.length());
  write(STDOUT_FILENO, "\n", 1);
}
void ff(std::string filename, std::string directory) {
  DIR *dir;
  struct dirent *ent;
  struct stat filestatus;
  std::string currentDirecoty= getcwd(NULL, 0);
  int firsTime = 0;
  if(directory == "noargs")
  {
    directory = currentDirecoty;
  }
  if(firsTime == 0) {
    parentDirecoty = currentDirecoty;
    auto index = parentDirecoty.find_last_of("/");
    parentDirecoty = parentDirecoty.substr(index+1);
  }
  if ((dir = opendir (directory.c_str())) != NULL) {
    while((ent = readdir (dir)) != NULL){
      if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
      {
        std::string file = std::string(ent->d_name);
        if (file == filename){
          auto index = directory.find(parentDirecoty);
          auto display = directory.substr(index);
          write(STDOUT_FILENO,display.c_str(),display.length());
          write(STDOUT_FILENO, "/", 1);
          write(STDOUT_FILENO,ent->d_name,strlen(ent->d_name));
          write(STDOUT_FILENO, "\n", 1);
        }
        std:: string subpath = directory + "/" + ent->d_name;
        firsTime++;
        ff(filename,subpath);
      }
    }
  }
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
          historyIndex-=1;
          if (historyIndex <= 0) {
            historyIndex = 0;
            write(STDOUT_FILENO, "\a", 1);
            clearField(128);
            std::string displayCommand = commandHistory[historyIndex];
            printPrompt();
            command = displayCommand;
            write(STDOUT_FILENO, command.c_str(), command.length());
            continue;
          } else {
            std:: string displayCommand = commandHistory[historyIndex];
            printPrompt();
            command = displayCommand;
            write(STDOUT_FILENO, displayCommand.c_str(), displayCommand.length());
          }
        } if (c == 0x42)// down arrow
        {
          clearField(128);
          historyIndex+=1;
           if(historyIndex >= int(commandHistory.size()) || historyIndex >=10){
            historyIndex = int(commandHistory.size());
            clearField(128);
            command = "";
            write(STDOUT_FILENO, "\a", 1);
            printPrompt();
            continue;
          } else
            {
            std:: string displayCommand = commandHistory[historyIndex];
            printPrompt();
            command = displayCommand;
            write(STDOUT_FILENO, displayCommand.c_str(), displayCommand.length());
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
  if (command !="")
  {
    command.pop_back();
    historyIndex = commandHistory.size()+1;
    commandHistory.push_back(command);
    if (commandHistory.size() > 10) {
      commandHistory.erase(commandHistory.begin());
    }
  }

}
std::vector<std::vector<std::string>> processCommand(std::string command) {
  addTohistory(command);
  command = tokenize(command);
  std::vector<std::string> CommandandArgs;
  char temp[command.length()];
  strcpy(temp, command.c_str());
  char *token;
  token = strtok(temp, "|");
  while ( token != NULL){
    CommandandArgs.push_back(token);
    token = strtok(NULL, "|");
  }
  char* minitoken;
  std::vector<std::vector<std::string>> AllCommands(CommandandArgs.size());
  for(int i =0; i < CommandandArgs.size();i++){
    char temp[CommandandArgs[i].length()];
    strcpy(temp, CommandandArgs[i].c_str());
    minitoken = strtok(temp, " ");
    while ( minitoken != NULL){
      AllCommands[i].push_back(minitoken);
      minitoken = strtok(NULL, " ");
    }
  }
  return AllCommands;
}
void runCommand(std::string command, std::vector<std::string> args){
  args.push_back("noargs");
  if(command == "cd")
    cd(args[0]);
  else if (command == "ls")
    ls(args[0]);
  else if (command == "ff")
    ff(args[0], args[1]);
  else if (command == "pwd")
    pwd();
  else if (command == "exit")
    exit(0);
  else{

  }

}
void executeCommand(std::vector<std::vector<std::string>> processedCommands) {
  if(processedCommands.size() == 0)
  {
    return;
  } else if (processedCommands.size() == 1){
    auto command = processedCommands[0][0];
    processedCommands[0].erase(processedCommands[0].begin());
    runCommand(command,processedCommands[0]);
  } else {

    return;
  }
}

int main(int argc, char *argv[]) {
  struct termios SavedTermAttributes;
  std::string command;
  SetNonCanonicalMode(STDIN_FILENO, &SavedTermAttributes);
  std::vector<std::vector<std::string>> processedCommand;
  while (isExit == false) {
    printPrompt();
    command = readCommand();
    processedCommand = processCommand(command);
    executeCommand(processedCommand);
  }

  ResetCanonicalMode(0, &SavedTermAttributes);
  return 0;
}
