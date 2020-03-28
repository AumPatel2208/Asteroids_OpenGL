#include "GameUtil.h"
#include "GameWorld.h"
#include "BulletAlien.h"
#include "AlienSpaceship.h"
#include "BoundingSphere.h"
#include <math.h>

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
AlienSpaceship::AlienSpaceship()
	: GameObject("AlienSpaceship"), mThrust(0) {
	mPosition.x = rand() / 2;
	mPosition.y = rand() / 2;
}

/** Construct a Alienspaceship with given position, velocity, acceleration, angle, and rotation. */
AlienSpaceship::AlienSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("AlienSpaceship", p, v, a, h, r), mThrust(0) {
}

/** Copy constructor. */
AlienSpaceship::AlienSpaceship(const AlienSpaceship& s)
	: GameObject(s), mThrust(0) {
}

/** Destructor. */
AlienSpaceship::~AlienSpaceship(void) {
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this Alienspaceship. */
void AlienSpaceship::Update(int t) {
	// Call parent update function
	GameObject::Update(t);
}

/** Render this Alienspaceship. */
void AlienSpaceship::Render(void) {
	if (mAlienSpaceshipShape.get() != NULL) mAlienSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}



/** Fire the rockets. */
void AlienSpaceship::Thrust(float t, const GLVector3f& playerPosition) {
	mThrust = t;

	/*some simple math to find the angle*/
	double angleRad = atan((playerPosition.y - GetPosition().y) / (playerPosition.x - GetPosition().x));
	if (playerPosition.x < GetPosition().x) {
		angleRad += PI;
	}
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust * cos(angleRad);
	mAcceleration.y = mThrust * sin(angleRad);
}

/** Set the rotation. */
void AlienSpaceship::Rotate(float r) {
	mRotation = r;
}

/** Shoot a bullet. */
void AlienSpaceship::Shoot(const GLVector3f& playerPosition) {

	///////////////////////
	// Check the world exists
	if (!mWorld) return;
	int count = 1;

	/*some simple math to find the angle*/
	double angleRad = atan((playerPosition.y - GetPosition().y) / (playerPosition.x - GetPosition().x));
	if (playerPosition.x < GetPosition().x) {
		angleRad += PI;
	}

	for (int i = 0; i < count; ++i) {
		GLVector3f alien_spaceship_heading(cos((angleRad + (10 * i))), sin((angleRad + (10 * i))), 0);
		alien_spaceship_heading.normalize();
		GLVector3f displacment(alien_spaceship_heading.x * 4 + 2, alien_spaceship_heading.y * 4, 0);
		// Calculate the point at the node of the Alien Spaceship from position and heading
		GLVector3f bullet_position = mPosition + displacment + (alien_spaceship_heading * 4);
		// Calculate how fast the bullet should travel
		float bullet_speed = 20;
		// Construct a vector for the bullet's velocity
		GLVector3f bullet_velocity = alien_spaceship_heading * bullet_speed;
		// Construct a new bullet
		shared_ptr<GameObject> bullet
			(new BulletAlien(bullet_position, bullet_velocity, mAcceleration, angleRad, 0, 2000));
		bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
		bullet->SetShape(mBulletShape);
		// Add the new bullet to the game world
		mWorld->AddObject(bullet);
	}

}


bool AlienSpaceship::CollisionTest(shared_ptr<GameObject> o) {
	if (o->GetType() != GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void AlienSpaceship::OnCollision(const GameObjectList& objects) {
	mWorld->FlagForRemoval(GetThisPtr());
}
