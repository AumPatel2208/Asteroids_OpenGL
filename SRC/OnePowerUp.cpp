#include "GameWorld.h"
#include "OnePowerUp.h"
#include "BoundingSphere.h"

OnePowerUp::OnePowerUp(void) : GameObject("OnePowerUp")
{

	mRotation = rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;

}
OnePowerUp::~OnePowerUp(void)
{
}

bool OnePowerUp::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	if (o->GetType() != GameObjectType("Spaceship")) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void OnePowerUp::OnCollision(const GameObjectList& objects)
{
		mWorld->FlagForRemoval(GetThisPtr());

}
