T04_G02

GROUP MEMBERS:
- Pedro Miguel Magalhães Nunes
- Lourenço Alexandre Correia Gonçalves

PROGRAM DEVELOPMENT STATE:
- All objectives asked for in the project specification were accomplished;
- When a robot collides with an electrified post, the post loses it's ability to electrocute, this wasn't explicitly asked in the specification (there is nothing against it too) but was asked in the first project and we believe it made even more sense in the second one, taking in consideration the updated rules of the game
- The purpose of the Winners option of the menu is very vague in the specification so here's how we decided to do it: this option displays the contents of a winners.txt file that stores the winners (with time and map) at the same time that those informations are stored in the MAZE_XX_WINNERS.txt files; we added an option to reset the leaderboard displayed, by deleting winners.txt; information is only added to winners.txt when a player beats the game, so if a MAZE_XX_WINNERS.txt file exists previously and winners.txt does not exist yet, for example, the maze specific leaderboard's contents do not get added to winners.txt; to sum it up winners.txt is more of a temporary leaderboard and all-time winners of each map are store in the other files
- We choose exits to be an object of type Post (both exits and other posts work very similarly)
- When building a Game object, the variable corresponding to the time played is set to -1, this way (and since after calling Game::play() that variable is >0) we check at the beginning of Game::updateLeaderboards() if the Game object has been played, and if it hasn't then the leaderboards can't be update (not really a problem for this project in specific, but in terms of designing the class Game could be important)
- Both Player and Robot classes are derivated from an Entity class, because this two objects are very similar
- We considered stuck and dead states for robots as the same, since they have the same behaviour in-game
- Robot id is not explicitly used, but has a correlation to the robots moving order, just as asked


MAIN DIFFICULTIES:
- Initially we add a couple of issues working with multiple files and headers
- Learning the concepts of OOP during the development of the project
- Finding an optimized way to check for collisions while moving the player and robots (avoid an exagerated amount of iterations)

