#pragma once
/*


BIG DEAL BUGS: 

- Write better collision detection for when the player rams the ball against the y axis on the side of the paddle
- dt is the wrong number. It is 1 in 2nd frame and then 0 in 3rd. m_current and m_previous are getting incorrect values



THINGS TO BE DONE:
- Measure frame rate and get it to 60
- Clean up code and anything that is not being used <-- YES!!!
- Add an entity system to the game to manage entities   <------  This is not entirely necessary because the game only 
contains three game objects and an entity system would over-complicate the game more than it needed to be. As more game
objects are added, I feel like some sort of Enity-component system would be better suitable. Maybe I will come back to
this and add one in the future.
 






3) Stop using frame rate as a measurement in the update loop (refer to Jamie King's YouTube video)


*/