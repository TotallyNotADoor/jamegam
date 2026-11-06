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

class Entity : public GameObject {
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

        void ApplyFriction();
        void ApplyVelocity();
        void Move();
};