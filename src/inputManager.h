#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

class InputManager {
    std::string command;
    std::vector<std::string> args;
    
public:
    // read a line of commands: command <args ... >
    // if fail return false
    bool readLine();

    std::string getCommand() const;
    std::vector<std::string> getArgs() const;
    std::string getArg(unsigned int index) const;
};

#endif
