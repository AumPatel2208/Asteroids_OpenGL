# Games Tech Coursework


## Part 1
### Day 1
- Added simple start menu.
- works by not showing anything until they press 1.
- they can still press 2 to exit the Game.

////////////////////////////////////////////////////
- At first
  - created the 'CreateMenu()' method inside of asteroids.
  - this sets the mGameDisplay Border
  - makes the 3 labels for the title, start game option and exit game option and align/place them appropriately into the world, and then adds them into the game display
- then I called this in the Start method of Asteroids class after the animations are created.
- this correctly displayed the labels, however the all the other game objects were also created
- to rectify that, I moved the code that created all the other objects into onKeyPressed method, if the correct key was pressed to stat the game ('1')
- pressing 2 would call the Stop method in the Asteroids class to end the game.
- A problem I ran into here was that the Player could press 1 again and again and it would create the game objects multiple times, which is not ideal for normal functionality :).
- There was also a null pointer error when any of the Spaceship controlling keys were pressed, this was due to the mSpaceship variable being null (as it was only created when '1' is pressed).
- To fix both of these issues, I used a Boolean called 'isGameRunning', this was initially set to false. 
  - The spaceship controls would only work if it was true, therefore removing the null pointer invocation.
  - and the '1' key would only function if 'isGameRunning' was false, therefore avoiding any multiple presses.
- after implementing the menu, I went a step further and kept the '2) Exit Game' label still on the screen however moved into the top-right corner and kept the functionality of '2' key pressed. This would allow the players to exit the game from inside without having to click the X on the window.

////////////////////////////////////////////////////



## Part 2
### Day 1
- Bonus/Power up System
- started implementation
- Rushed Bullet Adding
	- Improve tomorrow

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
- created H and CPP, Windows glitched on opening downloads folder, image should be downloaded



////////////////////////////////////////////////////////////////
- I decided to make a power up the allows the spaceship to shoot three bullets at once.
- I created a new CPP and Header file named ```BulletPowerUp``` and implemented the two collision methods.
  - Inside of the collision test method, I return false if the collision is with its own type or with a Spaceship.
- I then created a ```CreateBulletPowerUps``` method, which accepts an integer as the parameter which allows to say how many of that power up do you want to create.
- I created a custom sprite for this by using photoshop with dimensions 160x160, I feel it defines the power up accurately as it is an image of three bullets coming out from one point at different angles.
- I added a ```boundingShape``` on it to allow collisions and added the object into the game world.
- I then called that method when I create all the game objects for the start of the game ('```OnKeyPressed```' with case 1), and also when a new level is created.
- after running the code, it worked and the spaceship was colliding with it. I then started working on adding the logic into the Spaceship's shoot method.
- I added a Boolean to the Spaceship class called '```superShoot```' which is true if the power up is picked up.
- I added a '```toggleSuperShot()```' method which switched ```superShot```'s state from false to true and vice versa.
- Then in the Shoot method I created a local variable called ```count```, which is the number of bullets there are (this allows the code to be scalable if more bullet power ups wanted to be added).
- ```if superShot = true```, I turned ```count = 3```. 
- I then had a for loop that went from i=0 to count, and I create the bullet in their. To change the position of each of the bullets, I add (```10 * i```) to the mAngle of the spaceship_heading vector, which increases the angle by 10 for every bullet implemented.
  - only minor issue with this solution is that the 3 bullets come out to the left of the ship.
  - to solve this issue, I would have to alternate between ```-10 * i``` and ```10 * i``` 
- I then had to call the ```toggleSuperShot()``` method when the power up is picked up. I tried to implement this in ```CollisionTest``` by making a Boolean true which would tell me if it had collided with that object, however this did not work as collision test is run every 'frame' and checks every object in the scene, which ended up making that Boolean always true if the powerup merely existed in the scene.
- I later found that I could implement the code into the OnObjectRemoved method.
  - So if the object removed was a ```BulletPowerUp```, I would call ```toggleSuperShot()``` in the ```mSpaceship``` variable.`

- After implementing this power up, I decided to implement a 1up power up that would give the player an extra life.
- the implementation was mostly similar with some differences
  - I added a method inside of the Player method called ```addLives()``` that takes an integer as a variable
  - I then call that if ObjectRemoved is OnePowerUp
  - I also update the mLivesLabel to display the now changed number of lives.

- I also decided it would be a nice idea to create a label for the Bullet power up so I did that
  - it would be 0, up when power up is picked up, count down from 10 to 0.

- I decided to add another bullet power up, however this one would be more powerful, and spawn bullets from all around the player. It would be rarer and spawn every other level, balancing it out.
- I had to implement this by creating another game object class and implementation was very similar to the 3 shot power up, however the only difference was I toggled ```ultraShot``` Boolean. this would be used in the if statement inside the Shoot method.
- I spawned all power ups inside the ```OnKeyPressed``` case 1,
- and then I spawned them inside of ```OnTimer``` when it is a start of a new level.
- I created the circle bullet power ups by doing ```if (mLevel % 2 == 0)``` which would make sure that it would spawn it every other level.

- Issue
- At first I tried to have one power up class that works for all powerups with only a variable that would define what power up it is. However, I could not figure out how I would go about doing that within this engine as when OnObjectRemoved is called I can not access any PowerUp methods but only the GameObject methods, so I have to stick with the RTTI created to do that, and the only way to initialise the GameObjectType is by creating a new class to do it. I think this lead to unnecessary duplication of code. EG. there is no difference between BulletPowerUp and CircleBulletPowerUp in their code (other than the GameObjectType), but only on what assets are put on them and what 'toggleShot' method is called OnObjectRemoved (which all happens outside the two power up methods and inside the Asteroids method). 
This is mainly an issue with how the Engine is designed. I found ways around it, but I feel there is a more code-efficient way of going about distinguishing small differences between 2 things inside of one object rather than having to create 2. 


### Day 3
- Stop asteroids collide with power up.

## Part 3
- Have alien spaceship on timer,
	- every some ```seconds()``` the ai moves towards the player, and can shoot at the same time.
	- Create Alien Class and H, with thrust, and shoot
	- call thrust in OnTimerMethod

- Alien thrusts towards player, and shoots
- Thought about changing the shoot interval to a random number between 1 and 4 seconds, however I thought adding randomness would retract from skilful learning of the timing and getting into a rhythm.
- `

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

- Explain why I didn't make the Alien ship avoid bullets
  - because the Game has a feeling of low gravity, it is already hard enough to control the player, and to aim and shoot at a moving enemy at the same time having to deal with colliding into asteroids
  - having the enemy spaceship dodge the bullets would make the game extremely difficulty.
    - given that, I had a good idea on how I would make the enemy ship dodge bullets:
    - Rather than the thrust type movement it currently has, it would change into changing the Velocity of the alien ship, so it is more responsive movement
    - Rather than spawning all the bullets into the world, I would add the bullets spawned by the player into a list and check through the list during the movement of the alien ship to see if any of the bullets were in the same trajectory as its own movement.
    - then if it was, it would change velocity to move to a random direction away from the bullet to dodge it.
    - Downsides to this method would be that it could be inefficient checking through every bullet.
      - a way around this problem is to have a pseudo-grid in the game and only check the bullets that are in a certain proximity of the alien ship (relative to the grid).
      - eg. partitioning the world using a quadtree.

- 


## Challenges I faced:
- I found it tricky to add new Power Up types after adding the first one, ad first I tried to add a variable inside of the first power up class that I had made that would show what type of power up it is.
	- however this was not possible as the variable was not accessible when the collision between the power up and Player Ship happened, so I had to rely on the RTTI system created during one of the labs.
	- this was very useful.
- To hide the start menu and disable the pressing of the '1' key (which is one of the options in the start menu, and creates all the objects in the game) I figured out that the simplest and most elegant way to go about it was to create a boolean that is True when the Game 'starts' after pressing 1, and to not do anything if it has.
  - this Boolean also came in handy for disabling the Spaceship control keys, as they would throw a null pointer when in the start menu(as the ship was not created yet). So now the keys do not do anything unless the 'isGameRunning' is true.



# Validation
- Add so that any game key does not take into effect unless the game has started
	- simple bool

## Bugs
- bullet time counter goes into negative, -1 is the most common, however can go into -4 at times.