#include "nicetea.h"

/******** GameObject ********/
GameObject::GameObject() {
    Position = {0.0f, 0.0f};
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

/******** AnimatedSprite ********/
void AnimatedSprite::ChangeSize(unsigned int new_frames) {
    Frames = new_frames;
    AtlasPos.resize(new_frames);
}
void AnimatedSprite::Update() {
    Timer++;
    if(Timer>FpF) {
        Frame++;
        if(Frame>Frames) Frame = 1;
        Timer = 0;
    }
}
void AnimatedSprite::Draw() const {
    DrawTextureRec(Texture, AtlasPos[Frame], Position, WHITE);
}

/******** Entity ********/
void Entity::ApplyFriction() {
    Velocity = Vector2AddValue(Velocity, Friction);
}
void Entity::ApplyVelocity() {
    Position =  Vector2Add(Position, Velocity);
}
void Entity::ApplyForce(Vector2 force) {
    Velocity = Vector2Add(Velocity, force);
}
void Entity::Move() {
    ApplyFriction();
    ApplyVelocity();
}
