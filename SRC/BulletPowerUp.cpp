#include "GameWorld.h"
#include "BulletPowerUp.h"
#include "BoundingSphere.h"

BulletPowerUp::BulletPowerUp(void) : GameObject("BulletPowerUp")
{
	mRotation = 0; // rand() % 90;
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
	mPosition.z = 0.0;
}
BulletPowerUp::~BulletPowerUp(void)
{
}

bool BulletPowerUp::CollisionTest(shared_ptr<GameObject> o)
{
	if (GetType() == o->GetType()) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	// if (o->GetType() == GameObjectType("Spaceship")) isSpaceship = true;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void BulletPowerUp::Update(int t) {
}


void BulletPowerUp::OnCollision(const GameObjectList& objects)
{
	// if (isSpaceship) {
	// 	mWorld->FlagForRemoval(GetThisPtr());
	// 	isSpaceship = false;
	// }
}
