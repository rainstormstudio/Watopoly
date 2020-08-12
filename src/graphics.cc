#include "graphics.h"

/*
    coordinate orientation:
    0 -> x
    |
    y
*/

Graphics::Graphics(int width, int height) {
    screenWidth = width;
    screenHeight = height;
    theDisplay = std::vector<std::vector<char>>(screenHeight);
    for (int i = 0; i < screenHeight; ++i) {
        theDisplay[i] = std::vector<char>(screenWidth);
        for (int j = 0; j < screenWidth; ++j) {
            theDisplay[i][j] = ' ';
        }
    }
}

int Graphics::getWidth() const { return screenWidth; }

int Graphics::getHeight() const { return screenHeight; }

void Graphics::clear() {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            theDisplay[i][j] = ' ';
        }
    }
    msg = "";
}

void Graphics::render() {
    for (int i = 0; i < screenHeight; ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            std::cout << theDisplay[i][j];
        }
        std::cout << std::endl;
    }
    if (msg != "") {
        std::cout << msg << std::endl;
    }
}

void Graphics::render(unsigned int height) {
    for (int i = 0; i < screenHeight && i < static_cast<int>(height); ++i) {
        for (int j = 0; j < screenWidth; ++j) {
            std::cout << theDisplay[i][j];
        }
        std::cout << std::endl;
    }
}

void Graphics::draw(char value, int x, int y) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        theDisplay[y][x] = value;
    }
}

void Graphics::drawImage(std::string filename) {
    std::string line;
    std::ifstream infile {filename};
    if (infile.is_open()) {
        int row = 0;
        while (std::getline(infile, line)) {
            int len = line.length();
            for (int i = 0; i < len && i < screenWidth; ++i) {
                theDisplay[row][i] = line[i];
            }
            ++row;
        }
        infile.close();
    }
}

void Graphics::write(std::string content, int x, int y, int width) {
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        theDisplay[y][x + j] = content[i];
        ++j;
        if (j == screenWidth || j == width) {
            ++ y;
            j = 0;
        }
    }
}

void Graphics::addMsg(std::string str) {
    msg += str;
}