#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

class InputManager {
    std::string line;
    std::string command;
    std::vector<std::string> args;
    
public:
    // read a line of commands: command <args ... >
    // if fail return false
    bool readLine();

    std::string getLine() const;

    std::string getCommand() const;
    std::vector<std::string> getArgs() const;
    std::string getArg(unsigned int index) const;

    static std::vector<std::string> split(const std::string str);
};

#endif
