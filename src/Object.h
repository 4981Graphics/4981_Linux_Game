#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include "Entity.h"
#include "LTexture.h"
#include <SDL2/SDL.h>
#include "HitBox.h"
class Object : public Entity {
public:

    Object();
    virtual ~Object();

    void setHeight(int);
    void setWidth(int);
    int getHeight();
    int getWidth();
    void onCollision();
    void collidingProjectile(int damage);

private:
    int height; // Height of object
    int width; // Width of object
};

#endif
