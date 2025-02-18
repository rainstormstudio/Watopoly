#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <map>
#include <string>
#include <memory>

struct Vec2 {
    int x = 0;
    int y = 0;

    Vec2() : x(0), y(0) {}
    Vec2(int x, int y) : x(x), y(y) {}

    Vec2 operator+(const Vec2 &v) {
        return Vec2(x + v.x, y + v.y);
    }

    Vec2 operator-(const Vec2 &v) {
        return Vec2(x - v.x, y - v.y);
    }

    Vec2 operator+=(const Vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2 operator-=(const Vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    bool operator==(const Vec2 &v) {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vec2 &v) {
        return !(x == v.x && y == v.y);
    }
};

enum GameState {
    NO_GAME,
    PRE_GAME,
    IN_GAME,
    WON_GAME
};

enum GameMode {
    NORMAL_GAMEMODE,
    TESTING_GAMEMODE
};

struct PlayerData {
    std::string name;
    char symbol;
    unsigned int timsCups;
    unsigned int money;
    unsigned int position;
    bool isInDCTims;
    unsigned int DCturns;
};

struct BuildingData {
    std::string name;
    std::string owner;
    int improvements;
};

struct SaveData {
    unsigned int numPlayers;
    std::vector<PlayerData> playerData;
    std::vector<BuildingData> buildingData;
};

#endif
