/*
    Created by Maitiu Morton 2/1/2017
        Edited by DericM 3/8/2017
*/
#ifndef WEAPON_H
#define WEAPON_H
#include <SDL2/SDL.h>
#include "../LTexture.h"
#include <string>

class Marine;

class Weapon {
public:

    Weapon(std::string type = "no type", int range = 0, int damage = 0, int clip = 0, int clipMax = 0,
            int ammo = 0, int rAOE = 0, int reloadSpeed = 0);
    Weapon(const Weapon& w);
    ~Weapon() = default;

    std::string getType();//returns weapon type
    int getClip(); //returns bullets in clip
    int getClipMax(); //returns max amount clip can hold
    int getDamage(); //returns damage of weapon
    int getRange(); //returns range of weapon
    int getReloadSpeed();//returns weapon reload speed
    int getAmmo();//returns ammo amount
    int getRAOE(); //returns radius of effect
    void reloadClip();//resets clip to max amount
    bool reduceAmmo(int rounds);
    virtual void fire(Marine &marine);

protected:
    std::string type;
    int range; //range of weapon
    int damage;//damage per bullet
    int clip;//bullets in clip
    int clipMax;//max amount clip can hold
    int ammo; //amount of bullets total
    int rAOE; //radius of area of effect
    int reloadSpeed;
    LTexture inGameTexture;
    LTexture UiTexture;
    int reloadTick;
    int reloadDelay;

};

#endif
