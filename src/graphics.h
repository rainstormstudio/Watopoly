#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Graphics {
    std::vector<std::vector<char>> theDisplay;
    int screenWidth;
    int screenHeight;
    std::string msg;

public:
    Graphics(int width, int height);

    int getWidth() const;
    int getHeight() const;

    void clear();
    void render();
    void render(unsigned int height);

    void draw(char value, int x, int y);
    void drawImage(std::string filename);
    void write(std::string content, int x, int y, int width);

    void addMsg(std::string str);
    void resetMsg();
};

#endif
