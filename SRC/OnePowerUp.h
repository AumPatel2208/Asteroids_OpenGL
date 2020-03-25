#pragma once
#ifndef __ONEPOWERUP_H__
#define __ONEPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class OnePowerUp : public GameObject {
public:
	OnePowerUp(void);
	// OnePowerUp(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	// OnePowerUp(const OnePowerUp& b);
	virtual ~OnePowerUp(void);

	// virtual void Update(int t);
	// virtual void Render();


	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

private:
	bool isSpaceship = false;
};


#endif
