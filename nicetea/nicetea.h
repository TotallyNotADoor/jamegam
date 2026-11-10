#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>

class GameObject {
    public:
        Vector2 Position;
        GameObject();
};

class Sprite : public GameObject {      //A sprite
    protected:
        Texture2D Texture;
    public:
        Image Asset;
        Sprite() = default;
        Sprite(std::string path);
        Sprite(Image image, bool copy);
        void MakeTexture();
        virtual void Draw() const;

        virtual ~Sprite();

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
};

class AtlasSprite : public Sprite {     //A sprite, but it uses an atlas instead of an image
    public:
        Rectangle AtlasPos;
        AtlasSprite(std::string path, Rectangle position) : Sprite(path), AtlasPos(position){};
        AtlasSprite(Image image, Rectangle position) : Sprite(image, false) , AtlasPos(position){};
        AtlasSprite(Image image, Rectangle position, bool copy) : Sprite(image, copy) , AtlasPos(position){}    //with this you can use an image thats already loaded (Image = Image only passes a pointer reference)
        void Draw() const override;
};

class AnimatedSprite : public Sprite {      //An animated sprite using an atlas and a set of rectangles (as positions in the atlas)
    protected:
        unsigned int Frame;                 //What frame rn
        unsigned int Timer;
        unsigned int Frames;                //How many frames
    public:
        unsigned int FpF;                   //Frames per Frame (Game frames  per  1 Animation frame )
        std::vector<Rectangle> AtlasPos;    //The set of atlas positions. Automatically initialized with constructor
        AnimatedSprite(std::string path, unsigned int frames, unsigned int fpf);
        AnimatedSprite(Image image, unsigned int frames, unsigned int fpf);
        AnimatedSprite(Image image, unsigned int frames, unsigned int fpf, bool copy);
        void Update();
        void Draw() const override;
};

class AnimatedSpriteEx : public AnimatedSprite {
    //ToDo
};

class Entity : public GameObject {      //An entity existing in the game world. Will be the parent of PhysicsEntity
    public:
        Vector2 Velocity;
        float Friction;
        Entity();
        Entity(float friction);
        void ApplyFriction();   //Apply friction to velocity (so that it does not just go forever, were not in space)
        void ApplyVelocity();   //Change position by velocity
        void ApplyForce(Vector2 force);
        void Move();            //Both of the above combined, will potentially expand it to do more stuff
};

class PhysicsEntity : public Entity {
    public:
        Vector2 Gravity;
        float GravityStrenght;
        PhysicsEntity();
        PhysicsEntity(float gravity_strenght);
        void ApplyGravity();
};