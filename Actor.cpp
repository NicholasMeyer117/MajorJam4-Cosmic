#include "Actor.h"

void Actor::createActor(int Health, int Shields, float Speed, float Firerate, bool IsEnemy, int IFrames, 
float DamageMult, float FireRateMult, float BulletSpeedMult, float SpeedMult, float HealthMult)
{
    health = Health;
    maxHealth = Health;
    shields = Shields;
    speed = Speed;
    firerate = Firerate;
    isEnemy = IsEnemy;
    iFrames = IFrames;
    xPos = x;
    yPos = y;
    
    damageMult = DamageMult;
    fireRateMult = FireRateMult;
    bulletSpeedMult = BulletSpeedMult;
    speedMult = SpeedMult;
    healthMult = HealthMult;

}


