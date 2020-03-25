#pragma once
#pragma once
#ifndef __CIRCLEBULLETPOWERUP_H__
#define __CIRCLEBULLETPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class CircleBulletPowerUp : public GameObject {
public:
	CircleBulletPowerUp(void);
	// CircleBulletPowerUp(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	// CircleBulletPowerUp(const CircleBulletPowerUp& b);
	virtual ~CircleBulletPowerUp(void);

	// virtual void Update(int t);
	// virtual void Render();


	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);
	void setType() {

	}
	// const static uint THREE_SHOT = 0;
	// const static uint CIRCLE_SHOT = 1;
private:
	int type;
	bool isSpaceship = false;
};


#endif
