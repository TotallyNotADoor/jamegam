#include "classes.h"
#include <raylib.h>

//******** GameObject ********
std::string GameObject::getName() {
    return Name;
}
Vector2 GameObject::getPosition() {
    return Position;
}
void GameObject::SetPosition(float x, float y) {
    Position = {x, y};
}
void GameObject::ChangePosition(float x, float y) {
    Position.x += x;
    Position.y += y;
}

//******** Entity ********
Vector2 Entity::getVelocity() {
        return Velocity;
}
void Entity::SetVelocity(float x, float y) {
    Velocity = {x, y};
}
float Entity::getFriction() {
    return Friction;
}
void Entity::ChangeVelocity(float x, float y) {
    Velocity.x += x;
    Velocity.y += y;
}
void Entity::SetFriction(float friction) {
    Friction = friction;
}
void Entity::ChangeFriction(float friction) {
    Friction += friction;
}
void Entity::ApplyFriction() {
    ChangeVelocity(-Friction, -Friction);
}
void Entity::ApplyVelocity() {
    ChangePosition(Velocity.x, Velocity.y);
}
void Entity::Move() {
    ApplyFriction();
    ApplyVelocity();
}