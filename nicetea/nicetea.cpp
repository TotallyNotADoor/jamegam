#include "nicetea.h"

/******** GameObject ********/
GameObject::GameObject() {
    Position = {0.0f, 0.0f};
}

/******** Sprite ********/
Sprite::Sprite(std::string path) {
    Asset = LoadImage(path.c_str());
}
Sprite::Sprite(Image image, bool copy) {
    if(copy) Asset = ImageCopy(image);
    else Asset = image;
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
AnimatedSprite::AnimatedSprite(std::string path, unsigned int frames, unsigned int fpf) : Sprite(path), Frames(frames), FpF(fpf) {
    AtlasPos.resize(frames);
    unsigned int Frame = 0;
    unsigned int Timer = 0;
}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf) : Sprite(image, false), Frames(frames), FpF(fpf) {
    AtlasPos.resize(frames);
    unsigned int Frame = 0;
    unsigned int Timer = 0;
}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf, bool copy) : Sprite(image, copy), Frames(frames), FpF(fpf) {
    AtlasPos.resize(frames);
    unsigned int Frame = 0;
    unsigned int Timer = 0;
}
void AnimatedSprite::Update() {
    Timer++;
    if(Timer >= FpF) {
        Frame++;
        if(Frame >= Frames) Frame = 0;
        Timer = 0;
    }
}
void AnimatedSprite::Draw() const {
    DrawTextureRec(Texture, AtlasPos[Frame], Position, WHITE);
}

/******** Entity ********/
Entity::Entity() {
    Velocity = {0.0f, 0.0f};
    Friction = 1.0f;
}
Entity::Entity(float friction) {
    Velocity = {0.0f, 0.0f};
    Friction = friction;
}
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

/******** PhysicsEntity ********/
PhysicsEntity::PhysicsEntity() {
    Gravity = {0.0f, 1.0f};
    GravityStrenght = 1.0f;
}
PhysicsEntity::PhysicsEntity(float gravity_strenght) {
    Gravity = {0.0f, 1.0f};
    GravityStrenght = gravity_strenght;
}
void PhysicsEntity::ApplyGravity() {
    ApplyForce(Vector2Multiply(Gravity, {GravityStrenght, GravityStrenght}));
}