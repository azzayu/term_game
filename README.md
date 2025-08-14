# term_game

Welcome to a small terminal game I made to pass the time.

## Getting started:

1. Download the repo
2. Get on LINUX (if on windows use WSL) 
3. Make use of the Makefile with the command "make" 
4. You can "make clean" if issues occur with compilation step
5. then launch the game file (command "./game") to play on the default.txt savefile or enter your savefile name to play on that savefile

## Controls :
- Use z, q, s, d to move around (costs 1 stamina)
- Use w or space to rest turn (attacks still advance) (restores 3 stamina)
- Use a, e to change your aim to the left or right (ticks forward but does not cost or recover stamina)
- Use r to attack the current spot you are aiming at for 1 stamina
- Use f to charge a dash for your next move to be 3 tiles long for 5 stamina
- Use c to heal 2 health for 10 stamina and 3 turns advance
- All other characters on input are ignored
- inbetween enemies you can choose to keep adventuring (c) or stop there and save your progress (q)
