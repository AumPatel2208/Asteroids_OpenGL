#pragma once
#ifndef __ONEPOWERUP_H__
#define __ONEPOWERUP_H__
#include "GameUtil.h"
#include "GameObject.h"

class OnePowerUp : public GameObject {
public:
	OnePowerUp(void);

	virtual ~OnePowerUp(void);




	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

};


#endif
