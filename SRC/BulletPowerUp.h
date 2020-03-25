#pragma once
#ifndef __BULLETPOWERUP_H__
#define __BULLETPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class BulletPowerUp : public GameObject {
public:
	BulletPowerUp(void);
	// BulletPowerUp(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	// BulletPowerUp(const BulletPowerUp& b);
	virtual ~BulletPowerUp(void);

	// virtual void Update(int t);
	// virtual void Render();


	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

private:
	bool isSpaceship = false;
};


#endif
