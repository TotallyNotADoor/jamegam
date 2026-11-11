#include "nicetea.h"

/******** GameObject ********/
GameObject::GameObject() {
    Position = {0.0f, 0.0f};
}

/******** Sprite ********/
Sprite::Sprite() : Texture{0, 0, 0, 0, 0},  Asset{nullptr, 0, 0, 0, 0} {
}
Sprite::Sprite(const std::string& path) {
    Asset = LoadImage(path.c_str());
    MakeTexture();
}
Sprite::Sprite(Image image) {
    Asset = image;
    MakeTexture();
}
Sprite::Sprite(Image image, bool copy) {
    if(copy) Asset = ImageCopy(image);
    else Asset = image;
    MakeTexture();
}
Sprite::Sprite(Sprite&& other) noexcept : Texture(other.Texture), Asset(other.Asset) {
    other.Texture = {0, 0, 0, 0, 0}; // Reset source so it doesn't delete them
    other.Asset = {nullptr, 0, 0, 0, 0};
}
void Sprite::MakeTexture() {
    if(Texture.id > 0) UpdateTexture(Texture, Asset.data);
    else Texture = LoadTextureFromImage(Asset);
}
void Sprite::Draw() const {
    if(Texture.id >0) DrawTexture(Texture, lround(Position.x), lround(Position.y), WHITE);
}
Sprite::~Sprite() {
    if(Asset.data != nullptr)  UnloadImage(Asset);
    if(Texture.id > 0) UnloadTexture(Texture);
}

/******** AtlasSprite ********/
AtlasSprite::AtlasSprite(std::string path, unsigned int frames) : Sprite(path), Frames(frames), Frame(0) {
    AtlasPos.resize(frames);
}
AtlasSprite::AtlasSprite(Image image, unsigned int frames) : Sprite(image, false), Frames(frames), Frame(0) {
    AtlasPos.resize(frames);
}
AtlasSprite::AtlasSprite(Image image, unsigned int frames, bool copy) : Sprite(image, copy), Frames(frames), Frame(0) {
    AtlasPos.resize(frames);
}
void AtlasSprite::SetFrame(unsigned int frame) {
    if(frame <= Frames) Frame = frame;
    else Frame = frame%Frames;
}
void AtlasSprite::Draw() const {
    if(Texture.id > 0) DrawTextureRec(Texture, AtlasPos[Frame], Position, WHITE);
}

/******** AnimatedSprite ********/
AnimatedSprite::AnimatedSprite(std::string path, unsigned int frames, unsigned int fpf) : AtlasSprite(path, frames), FramesPerFrame(fpf), Timer(0) {}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf) : AtlasSprite(image, frames), FramesPerFrame(fpf), Timer(0) {}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf, bool copy) : AtlasSprite(image, copy), FramesPerFrame(fpf), Timer(0) {}
void AnimatedSprite::Update() {
    Timer++;
    if(Timer >= FramesPerFrame) {
        Frame++;
        if(Frame >= Frames) Frame = 0;
        Timer = 0;
    }
}

/******** Entity ********/
Entity::Entity() {
    Velocity = {0.0f, 0.0f};
    Friction = 0.9f;
}
Entity::Entity(float friction) {
    Velocity = {0.0f, 0.0f};
    Friction = friction;
}
void Entity::ApplyFriction() {
    Velocity = Vector2Scale(Velocity, Friction);
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
    GravityStrength = 1.0f;
}
PhysicsEntity::PhysicsEntity(float gravity_strenght) {
    Gravity = {0.0f, 1.0f};
    GravityStrength = gravity_strenght;
}
void PhysicsEntity::ApplyGravity() {
    ApplyForce(Vector2Multiply(Gravity, {GravityStrength, GravityStrength}));
}