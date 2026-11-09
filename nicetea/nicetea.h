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
        Sprite(const Image& image);
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
        AtlasSprite(Image image, Rectangle position) : Sprite(image) , AtlasPos(position){};
        void Draw() const override;
};

class AnimatedSprite : public Sprite {      //An animated sprite using an atlas and a set of rectangles
    protected:
        unsigned int Frame;
        unsigned int Timer;
        unsigned int Frames;
    public:
        unsigned int FpF;
        std::vector<Rectangle> AtlasPos;
        AnimatedSprite(std::string path, unsigned int frames) : Sprite(path), Frames(frames){};
        AnimatedSprite(Image image, unsigned int frames) : Sprite(image), Frames(frames){};
        void ChangeSize(unsigned int new_frames);
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
        void ApplyFriction();   //Apply friction to velocity (so that it does not just go forever, were not in space)
        void ApplyVelocity();   //Change position by velocity
        void ApplyForce(Vector2 force);
        void Move();            //Both of the above combined, will potentially expand it to do more stuff
};