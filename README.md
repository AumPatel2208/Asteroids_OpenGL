# Knights Embers
> A 3D game created in Open-GL & C++ for Games Tech Coursework
## Aum Patel 


## Part 1
### Start Menu

I started creating this by:
  - making the ```CreateMenu()``` method inside of asteroids.
  - this sets the ```mGameDisplay``` Border
  - makes the 3 labels for the title, start game option and exit game option and align/place them appropriately into the world, and then adds them into the game display.  

Then I called this in the ```Start()``` method of Asteroids class after the animations are created. This correctly displayed the labels, however the all the other game objects were also created. 
To rectify this, I moved the code that created all the other objects into ```onKeyPressed()``` method, if the correct key was pressed to stat the game ('1'). Pressing '2' would call the ```Stop()``` method in the Asteroids class to end the game.
A problem I ran into here was that the Player could press 1 again and again and it would create the game objects multiple times, which is not ideal for normal functionality. There was also a null pointer error when any of the Spaceship controlling keys were pressed, this was due to the ```mSpaceship``` variable being null (as it was only created when '1' is pressed).

To fix both of these issues, I used a Boolean called ```isGameRunning```, this was initially set to false. 
- The spaceship controls would only work if it was true, therefore removing the null pointer invocation.
- and the '1' key would only function if ```isGameRunning``` was false, therefore avoiding any multiple presses.  

After implementing the menu, I went a step further and kept the '2) Exit Game' label still on the screen however moved into the top-right corner and kept the functionality of '2' key pressed. This would allow the players to exit the game from inside without having to click the X on the window.

<div style="page-break-after: always;"></div>

## Part 2
### Bonus/Power Ups System

I decided to make a power up the allows the spaceship to **shoot three bullets at once**.
To do this, I created a new CPP and Header file named ```BulletPowerUp``` and implemented the two collision methods. I did this with the help of Lab 2/3 documents.
Inside of the ```CollisionTest()``` method, I return false if the collision is with its own type or with a Spaceship.
I then created a ```CreateBulletPowerUps()``` method, which accepts an integer as the parameter which allows to say how many of that power up do you want to create.
- this allows for greater flexibility and expandability.

Inside of this method:
- I created a custom sprite for the power-up by using photoshop with dimensions 160x160, I feel it defines the power up accurately as it is an image of three bullets coming out from one point at different angles.
- I added a ```boundingShape``` on the object to allow collisions and added the it into the game world.

I then called that method when I create all the game objects for the start of the game (```OnKeyPressed()``` with case 1), and also when a new level is created.

After running the code, it worked and the spaceship was colliding with it. I now started working on adding the logic into the Spaceship's ```Shoot()``` method.
I added a Boolean to the Spaceship class called '```superShoot```' which is true if the power up is picked up.
- I added a '```toggleSuperShot()```' method which switched ```superShot```'s state from false to true and vice versa.

Then in the Shoot method:
- I created a local variable called ```count```, which is the number of bullets there are (this allows the code to be scalable if more bullet power ups wanted to be added).
- ```if superShot = true```, I turned ```count = 3```. 
- I then had a for loop that went from ```i=0 to count```, and I create the bullet in their. To change the position of each of the bullets, I add (```10 * i```) to the ```mAngle``` of the ```spaceship_heading``` vector, which increases the angle by 10 for every bullet implemented.
  - only minor issue with this solution is that the 3 bullets come out to the left of the ship.
  - to solve this issue, I would have to alternate between ```-10 * i``` and ```10 * i``` 

I then had to call the ```toggleSuperShot()``` method when the power up is picked up. I tried to implement this in ```CollisionTest``` by making a Boolean true which would tell me if it had collided with that object, however this did not work as collision test is run every 'frame' and checks every object in the scene, which ended up making that Boolean always true if the powerup merely existed in the scene.

I later found that I could implement the code into the ```OnObjectRemoved()``` method.
  - So if the object removed was a ```BulletPowerUp```, I would call ```toggleSuperShot()``` in the ```mSpaceship``` variable.`

I decided it would be a nice idea to create a label for the Bullet power up so I did that
  - the label value would initially be 0, but when power up is picked up it would make it 10 and call an ```OnTimer()``` method that would control the changing of the label value to count down from 10 to 0.

After implementing this power up, I decided to implement a **One-Up** power up that would give the player an extra life.
The implementation was mostly similar with some differences:
- I added a method inside of the Player method called ```addLives()``` that takes an integer as a variable.
- I then call that ````OnObjectRemoved()```` if the ```GameObjectType``` is 'OnePowerUp'
- I also update the ```mLivesLabel``` to display the now changed number of lives.


I decided to add another bullet power up, however this one would be more powerful, and spawn bullets from all around the player. It would be rarer and spawn every other level, balancing it out. This would be a Circle shot which would **fire bullets 360 degrees**

I had to implement this by creating another game object class and implementation was very similar to the 3 shot power up, however the only difference was I toggled ```ultraShot``` Boolean when this object was removed. this would be used in the if statement inside the Shoot method.
- I spawned all power ups inside the ```OnKeyPressed()``` case 1,
- and then I spawned them inside of ```OnTimer``` when it is a start of a new level.
- I created the circle bullet power ups by doing ```if (mLevel % 2 == 0)``` which would make sure that it would spawn it every other level.

An issue I had with the way the engine detected what object type had are detected:
- At first I tried to have one power up class that works for all powerups with only a variable that would define what power up it is. However, I could not figure out how I would go about doing that within this engine as when OnObjectRemoved is called I can not access any PowerUp methods but only the GameObject methods, so I have to stick with the RTTI created to do that, and the only way to initialise the GameObjectType is by creating a new class to do it. I think this lead to unnecessary duplication of code. EG. there is no difference between BulletPowerUp and CircleBulletPowerUp in their code (other than the GameObjectType), but only on what assets are put on them and what 'toggleShot' method is called OnObjectRemoved (which all happens outside the two power up methods and inside the Asteroids method). 
This is mainly an issue with how the Engine is designed. I found ways around it, but I feel there is a more code-efficient way of going about distinguishing small differences between 2 things inside of one object rather than having to create 2. 


## Part 3
### Alien Spaceship 

Initially when I started thinking about moving the Alien spaceship around, I thought I would need some sort of path finding algorithm, however I thought it would be much more interesting if the alien ship would interact with the Asteroids and destroy them. Then the player can use this to their advantage to destroy the asteroids around the game. This could be done by finding the angle between the Alien ship and the Player's ship.
I started with creating an ```AlienSpaceship``` class, very similar to the Spaceship class with some differences on the shooting mechanics:
- I added a ```SetRandom()``` position method which I can use to set position to anywhere in the world when creating it
- I also made it so that the player's position needs to be passed through into the Shoot and Thrust methods, from there I will use Maths to calculate the trajectory angle for the bullet.
  - I get the angle by doing an arctan to the difference in the y of the playerPosition and alien position divided by the difference in the x of the playerPosition and alien position.
  - if the x position of the player is less than the x position of the alien, I add PI to the angle.
  - this correctly finds the angle, in radians, from where the alien is positioned to where the player is.

Next inside the Asteroids Class, I created a Boolean to check whether the alien is alive or not, and I created a ```shared_ptr<AlienSpaceship> mAlienSpaceship;``` which stores the instance of the alien in the game. I also created a ```CreateAlienSpaceship()``` method which is mostly similar to ```CreateSpaceship()```:
  - I created a different bullet.shape which is a red colour to help the player easily see it.
  - I also created a different sprite for the alien so that it fits in with the style of the current sprites while being easily distinguishable to the Player.
    - I had issues with this, I was following every guideline in the labs and by duplicating the current code for creating a new Animation.
    - However I got a greybox most of the time, even after checking the path to be correct.
    - to fix this, I had to do alot of trial and error in what file was working and wasn't (all 128x128 png files)
    - in the end I took the ```spaceship_fs.png``` and imported it into photoshop, placed the image I wanted on it and removed the old spaceship and saved it as a new png.

I call this method after creating the player spaceship, and turn ```isAlienAlive``` into true,
- I then also create the alien again in the ```START_NEXT_LEVEL``` case inside ```OnTimer```, but only if ```isAlienAlive=false```.

I now had an alien space ship with a nice sprite spawning into the scene, I now had to call the shoot and thrust functions periodically, to do this:
- I created 2 new cases in the ```OnTimer``` function:
- ```UPDATE_ALIEN_SHIP```, which calls the ```Thrust()``` method inside the ship with a speed of 5 and then Set_Timer every 10th of a second which calls ```UPDATE_ALIEN_SPACESHIP``` case recursively, &
- ```SHOOT_ALIEN_SHIP```, which calls the ```Shoot()``` method inside the ship and then Set_Timer every two and a half seconds which calls ```SHOOT_ALIEN_SHIP``` case recursively
- These two methods only do something if the alien ship is alive.
- I experimented around with the thrust speed and the frequency of shooting a bit before coming to these numbers, to provide some sort of fair gameplay balance.
  
I decided not to make the Alien Ship try and avoid the bullets. This is because the game has a feeling of low gravity, it is already hard enough to control the Player, and to aim and shoot at a moving enemy at the same time having to deal with colliding into asteroids. Having the enemy spaceship dodge the bullets, in addition to all of these obstacles, would make the game extremely difficulty.

Given that, I had a good idea on how I would make the enemy ship dodge the Player's bullets:
- Rather than the thrust type movement I have currently implemented, I would have the game change the Velocity of the alien ship; this makes the movement much more responsive.
- Rather than just spawning the Player's bullets into the world, I would have to add the bullets spawned by the player into a list, which makes them accessible, and then I would have to check through the list during the movement of the alien ship to see if any of the bullets are moving in the same trajectory as the alien ship's own movement.
- then if it was, it would change velocity to move to a random direction *away* from the bullet to dodge it.
- Downsides to this method would be that it could be very inefficient checking through every bullet in the list every time I update the enemy's movement.
  - a way around this problem is to have a pseudo-grid in the game and only check the bullets that are in a certain proximity of the alien ship (relative to the grid).
    - eg. partitioning the world using a quadtree.
  - another solution is to limit the number of bullets possible in the scene.
- Another way I could go about doing this is by having predetermined multiple paths the enemy follows.
  - this would make it simpler to calculate future possible collisions.
  - I could then switch the path the enemy is travelling in, slow the enemy down to avoid the collision, or reverse its moving direction.
  -   This method could detract from the freedom that the enmey has to move in, however, this could be 'faked' by having paths be auto created, or change during the game, giving the illusion that the enemy is not on a predetermined path.

## General notes
- I decided to start the game off slow, with only one asteroid and an alien ship spawning; I did this so that it gives the player a chance to get a good understanding of the AI behaviour, how to control the player, and what the power-ups do.
- I decided to not make the alien ship get destroyed on collision with an Asteroid, but the asteroid gets destroyed. Same with the Alien's bullets
  - I did this so that once learnt, the Player can use this to their advantage to get a higher score.
- The alien spaceship speed keeps accelerating if the player keeps on one specific side of them, this forces the player to keep moving, otherwise the enemy starts moving very fast.
  - again, the Player can use this to their advantage to use the invulnerability of the Alien to destroy the asteroids.
  - however this makes the Alien much more difficult to shoot down.
- Power-ups once spawned, do not vanish at the end of a level or after a certain period of time
  - This allows the player to strategically time their power pickups and get an edge over the game.
  - Removing power ups could be simply done by using the ```OnTimer``` member to remove the placed power up after a certain period of time, maybe by also adding a flashing animation to notify the Player that the power up will vanish.

### Bugs
- Bullet time counter goes into negative, -1 is the most common, however can go into -4 at times.
  - Happens when the shoot button is pressed down during the Circle Power up.
  - may be due to the lag the use of the power up comes with.

### Possible Improvements
- Play around with the respawn mechanic so that the Player is invulnerable for a second or two so that the player does not unfairly get destroyed
  - Can also make the spaceship spawn in a safe space and not the centre.
- Make the asteroids not spawn in the centre of the screen where the player spawns at the beginning of the game.
