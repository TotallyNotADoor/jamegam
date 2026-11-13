#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>
#include <cmath>
#include <climits>
using namespace std;

constexpr unsigned int UINT_NAN = UINT_MAX;

struct LevelHitbox{
	Rectangle Hitbox;
	bool Active;
};

extern vector<LevelHitbox> LevelHitboxes;

bool LoadLevel(const string& path);
bool SaveLevel(const string& path);

template<typename Type>
short Sign(Type val) noexcept {
    return (Type(0) < val) - (val < Type(0));
}

class GameObject {
	public:
		Vector2 Position;

		GameObject();
};

class Sprite : public virtual GameObject {
	protected:
		Texture2D Texture;
	public:
		Image Asset;

		Sprite();
		explicit Sprite(const string& path);
		Sprite(Image image);

		Sprite(Sprite&& other) noexcept;
		Sprite& operator=(Sprite&& other) noexcept;

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void MakeTexture();
		virtual void Draw() const;

		virtual ~Sprite();
};

class AtlasSprite : public Sprite {
	protected:
		unsigned int Frame;
		unsigned int Frames;
	public:
		vector<Rectangle> AtlasPos;

		AtlasSprite();
		AtlasSprite(const string& path, unsigned int frames);
		AtlasSprite(Image image, unsigned int frames);

		void SetFrame(unsigned int frame);
		void ChangeFrame(unsigned int change);

		virtual void Draw() const override;
};

class AnimatedSprite : public AtlasSprite {
	protected:
		unsigned int Timer;
	public:
		unsigned int FramesPerFrame;

		AnimatedSprite();
		AnimatedSprite(const string& path, unsigned int frames, unsigned int fpf);
		AnimatedSprite(Image image, unsigned int frames, unsigned int fpf);

		void SetTimer(unsigned int timer);
		void ChangeTimer(unsigned int change);
		void UpdateAnimation();
};

class AnimatedSpriteEx : public AnimatedSprite {
	//ToDo
};

class PhysicsObject : public virtual GameObject {
	public:
		Rectangle Hitbox;
		Vector2 Velocity;
		Vector2 MaxVelocity;
		Vector2 Gravity;
		float Friction;
		float GravityStrength;
		unsigned int CurrentCollisionID;
		bool Grounded;
		PhysicsObject();
		PhysicsObject(float gravity_strength, float friction);
		PhysicsObject(float gravity_strength, float friction, Vector2 max_velocity);

		void ApplyFriction(bool affect_y);
		void ApplyGravity();
		void ApplyForce(Vector2 force);

		bool IsCollidingWithLevel();
	protected:
		bool IsCollidingWithCurrentCollider();
	public:
		void MoveAndCollide();
		void TickPhysics();
};

class PhysicsEntity : public PhysicsObject, public AnimatedSprite {
	public:
		PhysicsEntity(const string& path, unsigned int frames, unsigned int fpf);
		PhysicsEntity(Image image, unsigned int frames, unsigned int fpf);
		PhysicsEntity(float gravity_strength, float friction, const string& path, unsigned int frames, unsigned int fpf);
		PhysicsEntity(float gravity_strength, float friction, Image image, unsigned int frames, unsigned int fpf);
		PhysicsEntity(float gravity_strength, float friction, Vector2 max_velocity, const string& path, unsigned int frames, unsigned int fpf);
		PhysicsEntity(float gravity_strength, float friction, Vector2 max_velocity, Image image, unsigned int frames, unsigned int fpf);


};
