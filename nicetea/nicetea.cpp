#include "nicetea.h"

vector<LevelHitbox> LevelHitboxes;

/******** LevelLoader ********/
bool LoadLevel(const string &path) {
	return false;
}
bool SaveLevel(const string &path) {
	return false;
}

/******** GameObject ********/
GameObject::GameObject() {
	Position = {0.0f, 0.0f};
}

/******** Sprite ********/
Sprite::Sprite(){
	Texture = { 0, 0, 0, 0, 0 };
	Asset = {nullptr, 0, 0, 0, 0};
}
Sprite::Sprite(const string& path) {
	Texture = { 0, 0, 0, 0, 0 };
	Asset = LoadImage(path.c_str());
	MakeTexture();
}
Sprite::Sprite(Image image) {
	Texture = { 0, 0, 0, 0, 0 };
	Asset = image;
	MakeTexture();
}
Sprite::Sprite(Sprite&& other) noexcept : Texture(other.Texture), Asset(other.Asset) {
	other.Texture = {0, 0, 0, 0, 0};
	other.Asset = {nullptr, 0, 0, 0, 0};
}
Sprite& Sprite::operator=(Sprite&& other) noexcept {
	if (this != &other) {
		if (Asset.data != nullptr) UnloadImage(Asset);
		if (Texture.id > 0) UnloadTexture(Texture);
		Texture = other.Texture;
		Asset = other.Asset;
		other.Texture = {0, 0, 0, 0, 0};
		other.Asset = {nullptr, 0, 0, 0, 0};
	}
	return *this;
}
void Sprite::MakeTexture() {
		if(Texture.id > 0) UpdateTexture(Texture, Asset.data);
		else if(Asset.data != nullptr) Texture = LoadTextureFromImage(Asset);
}
void Sprite::Draw() const {
	if(Texture.id >0) DrawTexture(Texture, lround(Position.x), lround(Position.y), WHITE);
}
Sprite::~Sprite() {
	if(Asset.data != nullptr) UnloadImage(Asset);
	if(Texture.id > 0) UnloadTexture(Texture);
}

/******** AtlasSprite ********/
AtlasSprite::AtlasSprite() : Sprite(), Frame(UINT_NAN), Frames(UINT_NAN) {}
AtlasSprite::AtlasSprite(const string& path, unsigned int frames) : Sprite(path), Frames(frames), Frame(0) {
	AtlasPos.resize(frames);
}
AtlasSprite::AtlasSprite(Image image, unsigned int frames) : Sprite(image), Frames(frames), Frame(0) {
	AtlasPos.resize(frames);
}
void AtlasSprite::SetFrame(unsigned int frame) {
	Frame = frame%Frames;
}
void AtlasSprite::ChangeFrame(unsigned int change) {
	Frame += change;
	Frame = Frame%Frames;
}
void AtlasSprite::Draw() const {
	if(Texture.id > 0 && Frame != UINT_NAN) DrawTextureRec(Texture, AtlasPos[Frame], Position, WHITE);
}

/******** AnimatedSprite ********/
AnimatedSprite::AnimatedSprite() : AtlasSprite(), Timer(0), FramesPerFrame(UINT_NAN) {}
AnimatedSprite::AnimatedSprite(const string& path, unsigned int frames, unsigned int fpf) : AtlasSprite(path, frames), FramesPerFrame(fpf), Timer(0) {}
AnimatedSprite::AnimatedSprite(Image image, unsigned int frames, unsigned int fpf) : AtlasSprite(image, frames), FramesPerFrame(fpf), Timer(0) {}
void AnimatedSprite::SetTimer(unsigned int timer) {
	Timer = timer%FramesPerFrame;
}
void AnimatedSprite::ChangeTimer(unsigned int change) {
	Timer += change;
	Timer = Timer%FramesPerFrame;
}
void AnimatedSprite::UpdateAnimation() {
	if(Frame != UINT_NAN && Frames != UINT_NAN && FramesPerFrame != UINT_NAN) {
		Timer++;
		if(Timer >= FramesPerFrame) {
			Frame++;
			if(Frame >= Frames) Frame = 0;
			Timer = 0;
		}
	}
}

/******** AnimatedSpriteEx ********/

//ToDo

/******** PhysicsObject ********/
PhysicsObject::PhysicsObject() {
	Velocity = {0.0f, 0.0f};
	MaxVelocity = {10.0f, 10.0f};
	Gravity = {0.0f, 1.0f};
	GravityStrength = 1.0f;
	Friction = 0.5f;
	CurrentCollisionID = UINT_NAN;
}
PhysicsObject::PhysicsObject(float gravity_strength, float friction) {
	Velocity = {0.0f, 0.0f};
	MaxVelocity = {10.0f, 10.0f};
	Gravity = {0.0f, 1.0f};
	GravityStrength = gravity_strength;
	Friction = friction;
	CurrentCollisionID = UINT_NAN;
}
PhysicsObject::PhysicsObject(float gravity_strength, float friction, Vector2 max_velocity) {
	Velocity = {0.0f, 0.0f};
	MaxVelocity = max_velocity;
	Gravity = {0.0f, 1.0f};
	GravityStrength = gravity_strength;
	Friction = friction;
	CurrentCollisionID = UINT_NAN;
}
void PhysicsObject::ApplyFriction(bool affect_y) {
	if(affect_y) Velocity = Vector2Scale(Velocity, Friction);
	else Velocity.x = Velocity.x * Friction;
}
void PhysicsObject::ApplyForce(Vector2 force) {
	Velocity = Vector2Add(Velocity, force);
	Velocity = Vector2Clamp(Velocity, Vector2Negate(MaxVelocity), MaxVelocity);
}
void PhysicsObject::ApplyGravity() {
	if(!Grounded) ApplyForce(Vector2Scale(Gravity, GravityStrength));
}
bool PhysicsObject::IsCollidingWithLevel() {
	for(size_t i = 0; i < LevelHitboxes.size(); ++i) {
		if(LevelHitboxes[i].Active && CheckCollisionRecs(Hitbox, LevelHitboxes[i].Hitbox)) {
				CurrentCollisionID = static_cast<unsigned int>(i);
				return true;
		}
	}
	return false;
}
bool PhysicsObject::IsCollidingWithCurrentCollider() {
	if(CurrentCollisionID != UINT_NAN && CurrentCollisionID < LevelHitboxes.size()) {
		return CheckCollisionRecs(LevelHitboxes[CurrentCollisionID].Hitbox, Hitbox);
	}
	return false;
}
void PhysicsObject::MoveAndCollide() {
	Position.x += Velocity.x;
	Hitbox.x = Position.x;
	if(IsCollidingWithLevel()) {
		Grounded = true;
		short direction = Sign(Velocity.x);;
		if(direction != 0) {
			while(IsCollidingWithCurrentCollider()) {
				Position.x -= direction;
				Hitbox.x = Position.x;
			}
		}
		Velocity.x = 0.0f;
		CurrentCollisionID = UINT_NAN;
	}

	Position.y += Velocity.y;
	Hitbox.y = Position.y;
	if(IsCollidingWithLevel()) {
		Grounded = true;
		short direction = Sign(Velocity.y);
		if(direction != 0) {
			while(IsCollidingWithCurrentCollider()) {
				Position.y -= direction;
				Hitbox.y = Position.y;
			}
		}
		Velocity.y = 0.0f;
		CurrentCollisionID = UINT_NAN;
	}
	else Grounded = false;
}
void PhysicsObject::TickPhysics() {
	ApplyFriction(false);
	ApplyGravity();
	MoveAndCollide();
}

/******** PhysicsEntity ********/
	PhysicsEntity::PhysicsEntity(const string& path, unsigned int frames, unsigned int fpf)
	: PhysicsObject(), AnimatedSprite(path, frames, fpf) {}

	PhysicsEntity::PhysicsEntity(Image image, unsigned int frames, unsigned int fpf)
	: PhysicsObject(), AnimatedSprite(image, frames, fpf) {}

	PhysicsEntity::PhysicsEntity(float gravity_strength, float friction, const string& path, unsigned int frames, unsigned int fpf)
	: PhysicsObject(gravity_strength, friction), AnimatedSprite(path, frames, fpf) {}

	PhysicsEntity::PhysicsEntity(float gravity_strength, float friction, Image image, unsigned int frames, unsigned int fpf)
	: PhysicsObject(gravity_strength, friction), AnimatedSprite(image, frames, fpf) {}

	PhysicsEntity::PhysicsEntity(float gravity_strength, float friction, Vector2 max_velocity, const string& path, unsigned int frames, unsigned int fpf)
	: PhysicsObject(gravity_strength, friction, max_velocity), AnimatedSprite(path, frames, fpf) {}

	PhysicsEntity::PhysicsEntity(float gravity_strength, float friction, Vector2 max_velocity, Image image, unsigned int frames, unsigned int fpf)
	: PhysicsObject(gravity_strength, friction, max_velocity), AnimatedSprite(image, frames, fpf) {}
