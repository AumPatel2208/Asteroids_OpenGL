#pragma once
#pragma once
#ifndef __CIRCLEBULLETPOWERUP_H__
#define __CIRCLEBULLETPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class CircleBulletPowerUp : public GameObject {
public:
	CircleBulletPowerUp(void);

	virtual ~CircleBulletPowerUp(void);




	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

};


#endif
