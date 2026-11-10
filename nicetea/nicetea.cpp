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
Sprite::Sprite(Sprite&& other) noexcept
    : Texture(other.Texture), Asset(other.Asset) {
    other.Texture = {0, 0, 0, 0, 0}; // Reset source so it doesn't delete them
    other.Asset = {nullptr, 0, 0, 0, 0};
}
void Sprite::MakeTexture() {
    if(Texture.id > 0) UnloadTexture(Texture);
    Texture = LoadTextureFromImage(Asset);
}
void Sprite::Draw() const {
    if(Texture.id >0) DrawTexture(Texture, lround(Position.x), lround(Position.y), WHITE);
}
Sprite::~Sprite() {
    if(Asset.data != nullptr)  UnloadImage(Asset);
    if(Texture.id > 0) UnloadTexture(Texture);
}

/******** AtlasSprite ********/
void AtlasSprite::Draw() const {
    if(Texture.id > 0) DrawTextureRec(Texture, AtlasPos, Position, WHITE);
}

/******** AnimatedSprite ********/
AnimatedSprite::AnimatedSprite(std::string path, unsigned int frames, unsigned int fpf) : Sprite(path), Frames(frames), FpF(fpf), Frame(0), Timer(0) {
    AtlasPos.resize(frames);
}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf) : Sprite(image, false), Frames(frames), FpF(fpf), Frame(0), Timer(0) {
    AtlasPos.resize(frames);
}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf, bool copy) : Sprite(image, copy), Frames(frames), FpF(fpf), Frame(0), Timer(0) {
    AtlasPos.resize(frames);
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