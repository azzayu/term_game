# term_game

Welcome to a small terminal game I made to pass the time.

## Getting started :

1. Download the repo
2. Get on LINUX (if on windows use WSL) 
3. Make use of the Makefile with the command "make" 
4. You can "make clean" if issues occur with compilation step
5. Then launch the game file (command "./game") to play on the default.txt savefile or enter your savefile name to play on that savefile

## Controls :
- Use z, q, s, d to move around (costs 1 stamina)
- Use w or space to rest for a turn (attacks still advance) (restores 3 stamina)
- Use a, e to change your aim to the left or right (ticks forward but does not cost or recover stamina)
- Use r to attack the current spot you are aiming at for 1 stamina
- Use f to charge a dash for your next move to be 3 tiles long for 5 stamina
- Use c to heal 2 health for 10 stamina and 3 turns advance
- All other characters on input are ignored
- Inbetween enemies you can choose to keep adventuring (c) or stop there and save your progress (q)
- You have to confirm an action by pressing the ENTER key on your keyboard

## How to play :

You will notice the screen is split in 2 halves, the top half is the heads up display where helpful information is available to you, the bottom half is the play area.

The heads up display contains the enemy type on the top left, your current exp progress to the next level, your health bar and stamina bar, and finally the enemy health, location, and which area you are targetting. the enemy is displayed by the small double rectangle asciii art, while where you are aiming is indicated by the colour of the frame (you're aiming at the yellow frame), to attack the enemy aim at it using 'a' or 'e' to align the yellow frame with the enemy location then attack with 'r'.

Now onto the play area, your character is represented by the single yellow square. your goal here is to dodge attacks (the red dots covering parts of the screen) by moving around with 'z', 'q', 's', 'd', and if necessary by first charging a dash (entering 'f' then another valid input such as the direction you want to dash in). you will notice 4 shades of red in the play area, only the brightest one means that if standing in the same tile you will take damage, the other shade are only to warn you of the inpending damage.

That is all you need to know to start playing, I suggest studying carefully each enemies different attack patterns and move chances in order to better eliminate them. That and to have tons of fun!
