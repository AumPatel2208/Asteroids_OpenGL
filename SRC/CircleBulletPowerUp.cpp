#include "GameWorld.h"
#include "CircleBulletPowerUp.h"
#include "BoundingSphere.h"

CircleBulletPowerUp::CircleBulletPowerUp(void) : GameObject("CircleBulletPowerUp")
{
	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
}
CircleBulletPowerUp::~CircleBulletPowerUp(void)
{
}

bool CircleBulletPowerUp::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	if (o->GetType() != GameObjectType("Spaceship")) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void CircleBulletPowerUp::OnCollision(const GameObjectList& objects)
{
		mWorld->FlagForRemoval(GetThisPtr());
}
