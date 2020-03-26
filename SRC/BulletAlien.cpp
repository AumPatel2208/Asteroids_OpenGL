#include "GameWorld.h"
#include "BulletAlien.h"
#include "BoundingSphere.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. BulletAliens live for 2s by default. */
BulletAlien::BulletAlien()
	: GameObject("BulletAlien"), mTimeToLive(2000) {
}

/** Construct a new bulletAlien with given position, velocity, acceleration, angle, rotation and lifespan. */
BulletAlien::BulletAlien(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl)
	: GameObject("BulletAlien", p, v, a, h, r), mTimeToLive(ttl) {
}

/** Copy constructor. */
BulletAlien::BulletAlien(const BulletAlien& b)
	: GameObject(b),
	  mTimeToLive(b.mTimeToLive) {
}

/** Destructor. */
BulletAlien::~BulletAlien(void) {
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update bulletAlien, removing it from game world if necessary. */
void BulletAlien::Update(int t) {
	// Update position/velocity
	GameObject::Update(t);
	// Reduce time to live
	mTimeToLive = mTimeToLive - t;
	// Ensure time to live isn't negative
	if (mTimeToLive < 0) { mTimeToLive = 0; }
	// If time to live is zero then remove bulletAlien from world
	if (mTimeToLive == 0) {
		if (mWorld) mWorld->FlagForRemoval(GetThisPtr());
	}

}

bool BulletAlien::CollisionTest(shared_ptr<GameObject> o) {
	if (o->GetType() != GameObjectType("Asteroid")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void BulletAlien::OnCollision(const GameObjectList& objects) {
	mWorld->FlagForRemoval(GetThisPtr());
}
