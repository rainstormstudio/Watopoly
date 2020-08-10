#include "inputManager.h"

bool InputManager::readLine() {
    args.resize(0);
    args.shrink_to_fit();
    if (!getline(std::cin, line)) {
        return false;
    }
    int count = 0;
    std::string word;
    int len = line.length();
    for (int i = 0; i <= len; ++i) {
        if (i == len || line[i] == ' ') {
            if (count == 0) {
                command = word;
            } else {
                args.emplace_back(word);
            }
            word = "";
            ++count;
        } else {
            word += line[i];
        }
    }
    return true;
}

std::string InputManager::getLine() const {
    return line;
}

std::string InputManager::getCommand() const {
    return command;
}

std::vector<std::string> InputManager::getArgs() const {
    return args;
}

std::string InputManager::getArg(unsigned int index) const {
    if (index >= args.size()) {
        return "";
    }
    return args[index];
}

std::vector<std::string> InputManager::split(const std::string str) {
    std::vector<std::string> result;
    int len = str.length();
    std::string token = "";
    for (int i = 0; i <= len; ++i) {
        if (i == len || str[i] == ' ') {
            result.push_back(token);
            token = "";
        } else {
            token += str[i];
        }
    }
    return result;
}
