#pragma once
#ifndef __ALIENSPACESHIP_H__
#define __ALIENSPACESHIP_H__

#include "GameUtil.h"
#include "GameObject.h"
#include "Shape.h"

class AlienSpaceship : public GameObject {
public:
	AlienSpaceship();
	AlienSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r);
	AlienSpaceship(const AlienSpaceship& s);
	virtual ~AlienSpaceship(void);

	virtual void Update(int t);
	virtual void Render(void);

	virtual void Thrust(float t, const GLVector3f& playerPosition);
	virtual void Rotate(float r);
	virtual void Shoot(const GLVector3f& playerPosition);

	void SetAlienSpaceshipShape(shared_ptr<Shape> alienSpaceship_shape) { mAlienSpaceshipShape = alienSpaceship_shape; }
	void SetThrusterShape(shared_ptr<Shape> thruster_shape) { mThrusterShape = thruster_shape; }
	void SetBulletShape(shared_ptr<Shape> bullet_shape) { mBulletShape = bullet_shape; }

	void SetRandomPosition(){
		mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	}

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

	void toggleSuperShot() {
		superShoot = !superShoot;
	}

	void toggleUltraShoot() {
		ultraShoot = !ultraShoot;
	}

private:
	float mThrust;
	const double PI = atan(1) * 4;
	bool isAsteroid = false;
	bool isPowerUp = false;
	bool superShoot = false;
	bool ultraShoot = false;
	shared_ptr<Shape> mAlienSpaceshipShape;
	shared_ptr<Shape> mThrusterShape;
	shared_ptr<Shape> mBulletShape;
};

#endif
