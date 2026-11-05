#pragma once
#include <raylib.h>
#include <string>

class GameObject {
private:
    // Pola klasy (atrybuty)
    std::string Name;
    Vector2 Position;

public:
    // Konstruktor
    GameObject(std::string name, float x, float y);

    GameObject(float x, float y);

    void SetPosition(float x, float y);

    void ChangePosition(float x, float y);

};