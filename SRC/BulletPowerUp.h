#pragma once
#ifndef __BULLETPOWERUP_H__
#define __BULLETPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class BulletPowerUp : public GameObject {
public:
	BulletPowerUp(void);

	virtual ~BulletPowerUp(void);




	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);


};


#endif
