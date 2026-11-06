#pragma once
#include <raylib.h>
#include <string>

class GameObject {
    private:
        std::string Name;
        Vector2 Position;
    public:
        std::string getName();
        Vector2 getPosition();
        void SetPosition(float x, float y);
        void ChangePosition(float x, float y);
};

class Sprite : public GameObject {      //A sprite. Will contain functions to assing it an image, manipulate it, and draw. Will preferably use a texture atlas.
    private:
        Image Texture;
    public:
        Sprite(std::string path);       //Will probably become deprecated when i implemet a texture atlas
        Sprite(Image image);            //For the texture atlas, although idk if Image is the right type
        void SetTexture();
        void Draw();                    //A challenge. Seriously. This will be the most complicated function untill surpassed
};

class Entity : public GameObject {      //An entity existing in the game world. Will be the parent of PhysicsEntity
    private:
        Vector2 Velocity;
        float Friction;
    public:
        Vector2 getVelocity();
        float getFriction();
        void SetVelocity(float x, float y);
        void SetFriction(float friction);
        void ChangeVelocity(float x,  float y);
        void ChangeFriction(float friction);

        void ApplyFriction();   //Apply friction to velocity (so that it does not just go forever, were not in space)
        void ApplyVelocity();   //Change position by velocity
        void Move();            //Both of the above combined, will potentially expand it to do more stuff
};