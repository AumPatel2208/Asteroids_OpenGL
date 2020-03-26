#pragma once
#ifndef __BULLETALIEN_H__
#define __BULLETALIEN_H__

#include "GameUtil.h"
#include "GameObject.h"

class BulletAlien : public GameObject
{
public:
	BulletAlien();
	BulletAlien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	BulletAlien(const BulletAlien& b);
	virtual ~BulletAlien(void);

	virtual void Update(int t);

	void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	int GetTimeToLive(void) { return mTimeToLive; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

protected:
	int mTimeToLive;
};

#endif