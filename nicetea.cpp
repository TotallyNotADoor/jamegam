#include "nicetea.h"

/******** GameObject ********/
GameObject::GameObject() {
    Position = {0.0f, 0.0f};
}

/******** Entity ********/
void Entity::ApplyFriction() {
    Velocity = Vector2AddValue(Velocity, Friction);
}
void Entity::ApplyVelocity() {
    Position =  Vector2Add(Position, Velocity);
}
void Entity::Move() {
    ApplyFriction();
    ApplyVelocity();
}

/******** Sprite ********/
Sprite::Sprite(std::string path) {
    Asset = LoadImage(path.c_str());
}
Sprite::Sprite(const Image& image) {
    Asset = image;
}
void Sprite::MakeTexture() {
    Texture = LoadTextureFromImage(Asset);
}
void Sprite::Draw() const {
    DrawTexture(Texture, lround(Position.x), lround(Position.y), WHITE);
}
Sprite::~Sprite() {
    UnloadImage(Asset);
    UnloadTexture(Texture);
}

/******** AtlasSprite ********/
void AtlasSprite::Draw() const {
    DrawTextureRec(Texture, AtlasPos, Position, WHITE);
}