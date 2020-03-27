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
<!-- - shooting slower, slow enemy down -->
- change alien sprite
- add instructions on the start screen


## things to write about
- starts of slow with 1 asteroid and one enemy, a chance for the player to get a good understanding of the AI behaviour
- Alien can collide with asteroids and destroy them, the player can use this to their advantage
- the alien spaceship speed keeps accelerating if the player keeps on one specific side of them, this forces the player to keep moving, otherwise the enemy starts moving too fast.
  - *or the player could use this to their advantage, to destroy the asteroids using the enemy ship.*
  - to balance this out, I have made it so the alien ship does not collide with the player
- The bullet from the enemy fires every 2.5 seconds, to give enough time for the player to move
- Power-ups do not vanish after a level is completed, so they can strategically time their power pickups
- 


## Challenges I faced:
- I found it tricky to add new Power Up types after adding the first one, ad first I tried to add a variable inside of the first power up class that I had made that whould show what type of power up it is.
	- however this was not possible as the variable was not accessible when the collision between the power up and Player Ship happened, so I had to rely on the RTTI system created during one of the labs.
	- this was very useful.
- To hide the start menu and disable the pressing of the '1' key (which is one of the options in the start menu, and creates all the objects in the game) I figured out that the simplest and most elegant way to go about it was to create a boolean that is True when the Game 'starts' after pressing 1, and to not do anything if it has.
  - this boolean also came in handy for disabling the Spaceship control keys, as they would throw a null pointer when in the start menu(as the ship was not created yet). So now the keys do not do anything unless the 'isGameRunning' is true.



# Validation
- Add so that any game key does not take into effect unless the game has started
	- simple bool
