#ifndef __ASTEROIDS_H__
#define __ASTEROIDS_H__

#include "GameUtil.h"
#include "GameSession.h"
#include "IKeyboardListener.h"
#include "IGameWorldListener.h"
#include "IScoreListener.h"
#include "ScoreKeeper.h"
#include "Player.h"
#include "IPlayerListener.h"

class GameObject;
class Spaceship;
class AlienSpaceship;
class GUILabel;

class Asteroids : public GameSession, public IKeyboardListener, public IGameWorldListener, public IScoreListener,
                  public IPlayerListener {
public:
	Asteroids(int argc, char* argv[]);
	virtual ~Asteroids(void);

	virtual void Start(void);
	virtual void Stop(void);

	// Declaration of IKeyboardListener interface ////////////////////////////////

	void OnKeyPressed(uchar key, int x, int y);
	void OnKeyReleased(uchar key, int x, int y);
	void OnSpecialKeyPressed(int key, int x, int y);
	void OnSpecialKeyReleased(int key, int x, int y);

	// Declaration of IScoreListener interface //////////////////////////////////

	void OnScoreChanged(int score);

	// Declaration of the IPlayerLister interface //////////////////////////////

	void OnPlayerKilled(int lives_left);

	// Declaration of IGameWorldListener interface //////////////////////////////

	void OnWorldUpdated(GameWorld* world) {
	}

	void OnObjectAdded(GameWorld* world, shared_ptr<GameObject> object) {
	}

	void OnObjectRemoved(GameWorld* world, shared_ptr<GameObject> object);

	// Override the default implementation of ITimerListener ////////////////////
	void OnTimer(int value);

private:
	shared_ptr<Asteroids> thisPtr;
	shared_ptr<Spaceship> mSpaceship;
	shared_ptr<AlienSpaceship> mAlienSpaceship;
	shared_ptr<GUILabel> mScoreLabel;
	shared_ptr<GUILabel> mLivesLabel;
	shared_ptr<GUILabel> mGameOverLabel;

	shared_ptr<GUILabel> aBulletPowerTime;
	shared_ptr<GUILabel> aGameTitle;
	shared_ptr<GUILabel> aStartGameOption;
	shared_ptr<GUILabel> aExitGameOption;
	shared_ptr<GUILabel> aInstructions;

	bool isGameRunning = false;
	bool isAlienAlive = false;

	uint mLevel;
	uint mAsteroidCount;

	void ResetSpaceship();
	shared_ptr<GameObject> CreateSpaceship();
	shared_ptr<GameObject> CreateAlienSpaceship();
	void CreateGUI();
	void CreateMenu();
	void CreateAsteroids(const uint num_asteroids);
	void CreateBulletPowerUps(const uint num_powerUps);
	void CreateCircleBulletPowerUps(const uint num_powerUps);
	void CreateOnePowerUps(const uint num_powerUps);

	shared_ptr<GameObject> CreateExplosion(const int& type);

	const static uint SHOW_GAME_OVER = 0;
	const static uint START_NEXT_LEVEL = 1;
	const static uint CREATE_NEW_PLAYER = 2;
	const static uint RESET_BULLET_POWER_UP = 3;
	const static uint INCREASE_POWER_UP_COUNTER = 4;
	const static uint RESET_CIRCLE_BULLET_POWER_UP = 5;
	const static uint UPDATE_ALIEN_SHIP = 6;
	const static uint SHOOT_ALIEN_SHIP = 7;


	const static int EXPLOSION_ASTEROID = 0;
	const static int EXPLOSION_SPACESHIP = 1;

	int bulletPowerTime;
	ScoreKeeper mScoreKeeper;
	Player mPlayer;
};

#endif
