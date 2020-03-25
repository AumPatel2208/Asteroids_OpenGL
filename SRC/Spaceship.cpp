#include "GameUtil.h"
#include "GameWorld.h"
#include "Bullet.h"
#include "Spaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
Spaceship::Spaceship()
	: GameObject("Spaceship"), mThrust(0) {
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
Spaceship::Spaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mThrust(0) {
}

/** Copy constructor. */
Spaceship::Spaceship(const Spaceship& s)
	: GameObject(s), mThrust(0) {
}

/** Destructor. */
Spaceship::~Spaceship(void) {
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void Spaceship::Update(int t) {
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void Spaceship::Render(void) {
	if (mSpaceshipShape.get() != NULL) mSpaceshipShape->Render();

	// If ship is thrusting
	if ((mThrust > 0) && (mThrusterShape.get() != NULL)) {
		mThrusterShape->Render();
	}

	GameObject::Render();
}

/** Fire the rockets. */
void Spaceship::Thrust(float t) {
	mThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mThrust * cos(DEG2RAD * mAngle);
	mAcceleration.y = mThrust * sin(DEG2RAD * mAngle);
}

/** Set the rotation. */
void Spaceship::Rotate(float r) {
	mRotation = r;
}

/** Shoot a bullet. */
void Spaceship::Shoot(void) {
	// Check the world exists
	if (!mWorld) return;
	int count = 1;
	if (superShoot) {
		//maybe add the top one with a for loop that changes angle avoiding duplicate code.
		count = 3;
	}

	GLfloat tempAngle = mAngle;


	for (int i = 0; i < count; ++i) {
		// Construct a unit length vector in the direction the spaceship is headed
		switch (i) {
		case 0:

			tempAngle = mAngle;
			break;
		case 1:
			tempAngle = mAngle + 10;
			break;
		case 2:
			tempAngle = mAngle + 20;
			break;
		}

		GLVector3f spaceship_heading(cos(DEG2RAD * tempAngle), sin(DEG2RAD * tempAngle), 0);
		spaceship_heading.normalize();
		// Calculate the point at the node of the spaceship from position and heading
		GLVector3f bullet_position = mPosition + (spaceship_heading * 4);
		// Calculate how fast the bullet should travel
		float bullet_speed = 30;
		// Construct a vector for the bullet's velocity
		GLVector3f bullet_velocity = mVelocity + spaceship_heading * bullet_speed;
		// Construct a new bullet
		shared_ptr<GameObject> bullet
			(new Bullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
		bullet->SetBoundingShape(make_shared<BoundingSphere>(bullet->GetThisPtr(), 2.0f));
		bullet->SetShape(mBulletShape);
		// Add the new bullet to the game world
		mWorld->AddObject(bullet);
	}


}



bool Spaceship::CollisionTest(shared_ptr<GameObject> o) {
	if (o->GetType() != GameObjectType("Asteroid")) return false; //&& o->GetType() != GameObjectType("BulletPowerUp")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	if (o->GetType() == GameObjectType("Asteroid")) {
		isAsteroid = true;
	}
	// if (o->GetType() == GameObjectType("BulletPowerUp")) {
	// 	isPowerUp = true;
	// }
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void Spaceship::OnCollision(const GameObjectList& objects) {
	// if (isAsteroid) {
		//Remove Spaceship
		mWorld->FlagForRemoval(GetThisPtr());
		// Reset isAsteroid
		// isAsteroid = false;
	// }
	// else if (isPowerUp) {
	// 	//Implement Power Up condition
	// 	superShoot = true;
	// 	isPowerUp = false;
	// }
}
