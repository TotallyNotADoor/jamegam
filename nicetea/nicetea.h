#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>
#include <cmath>

class GameObject {										//An object that exists in the game world
	public:
		Vector2 Position;
		GameObject();
};

class Sprite : public GameObject {						//A base class for objects that are rendered to the screen
														//It's very complicated and important, a literal backbone of rendering
	protected:
		Texture2D Texture;
	public:
		Image Asset;
		Sprite();
		explicit Sprite(const std::string& path);
		Sprite(Image image);
		Sprite(Image image, bool copy);
		Sprite(Sprite&& other) noexcept;
		Sprite& operator=(Sprite&& other) noexcept;

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void MakeTexture();
		virtual void Draw() const;

		virtual ~Sprite();
};

class AtlasSprite : public Sprite {						//A sprite, but it uses an atlas instead of an image for easy sprite swapping (for animations use AnimatedSprite or AnimatedSpriteEx tho)
	protected:
		unsigned int Frame;					//What frame (sprite) rn
		unsigned int Frames;				//How many frames
	public:
		std::vector<Rectangle> AtlasPos;	//The set of atlas positions. Automatically initialized by constructor
		AtlasSprite(std::string path, unsigned int frames);
		AtlasSprite(Image image, unsigned int frames);
		AtlasSprite(Image image, unsigned int frames, bool copy);
		void SetFrame(unsigned int frame);
		virtual void Draw() const override;
};

class AnimatedSprite : public AtlasSprite {				//An animated sprite using an atlas and a set of rectanges
	protected:
		unsigned int Timer;
	public:
		unsigned int FramesPerFrame;		//Frames per Frame (Game frames per 1 Animation frame)
		AnimatedSprite(std::string path, unsigned int frames, unsigned int fpf);
		AnimatedSprite(Image image, unsigned int frames, unsigned int fpf);
		AnimatedSprite(Image image, unsigned int frames, unsigned int fpf, bool copy);
		void Update();
};

class AnimatedSpriteEx : public AnimatedSprite {		//AnimatedSprite with muliple animations
	//ToDo
};

class Entity : public GameObject {				//An entity existing in the game world. Will be the parent of PhysicsEntity
	public:
		Vector2 Velocity;
		float Friction;							//!!!Important!!! this is a multiplier for velocity, so it should be  ALWAYS  Friction ∈ (0, 1)
		Entity();
		explicit Entity(float friction);
		void ApplyFriction();					//Apply friction to velocity (so that it does not just go forever, were not in space)
		void ApplyVelocity();					//Change position by velocity
		void ApplyForce(Vector2 force);			//Apply a force to velocity (change velocity by Vector2)
		void Move();							//Both ApplyFriction and ApplyVelocity combined, will be potentially expanded it to do more stuff
};

class PhysicsEntity : public Entity {					//Entity with Gravity methods
	public:
		Vector2 Gravity;
		float GravityStrength;
		PhysicsEntity();
		PhysicsEntity(float gravity_strength);
		void ApplyGravity();
};
