#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <vector>
#include <string>

class InputManager {
    std::string command;
    std::vector<std::string> args;
    
public:
    void readLine();

    std::string getCommand() const;
    std::vector<std::string> getArgs() const;
    std::string getArg(int index) const;
};

#endif
