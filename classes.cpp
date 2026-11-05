#include "classes.h"
#include <raylib.h>

GameObject::GameObject(std::string name, float x, float y) {
    Name = name;
    Position = {x, y};
}

GameObject::GameObject(float x, float y) {
    Name = "null";
    Position = {x, y};
}

void GameObject::SetPosition(float x, float y) {
    Position = {x, y};
}

void GameObject::ChangePosition(float x, float y) {
    Position.x += x;
    Position.y += y;
}