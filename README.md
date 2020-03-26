# Games Tech Coursework


## Part 1
### Day 1
- Added simple start menu.
- works by not showing anything until they press 1.
- they can still press 2 to exit the Game.

## Part 2
### Day 1
- Bonus/Power up System
- started implementation
- Rushed Bullet Adding
	- Improve tommorow

### Day 2
- Used Lab 2/3 tutorial to implement a simple power up that collides with the spaceship only

- Need to add sprite (maybe animated) to it and make smaller

- Change Sprite maybe

- Temporarily removed asteroid damage on spaceship

- Power Up implemented, goes away in 10 seconds

- implementing Power up label
	- PowerKeeper.h
	- IPowerListener.h

- Add a bullet power up that is 360 bullets...
- Started Creating it
	- added toggle functionality, just need to create the H and CPP
- created H and CPP, Windows glitched on opening downloads folder, image should be donwloaded

### Day 3
- Stop asteroids collide with power up.

## Part 3
- Have alien spaceship on timer,
	- every some seconds the ai moves towards the player, and can shoot at the same time.
	- Create Alien Class and H, with thrust, and shoot
	- call thrust in OnTimerMethod

- Alien thrusts towards player, and shoots

### Improvements
- shooting slower, slow enemy down
- change alien sprite


## things to write about
- starts of slow with 1 asteroid and one enemy, a chance for the player to get a good understanding of the AI behaviour
- Alien can collide with asteroids and destroy them, the player can use this to their advantage
- Power-ups do not vanish, so they can strategically time their power pickups
- 

# Validation
- Add so that any game key does not take into effect unless the game has started
	- simple bool
