T04_G02

GROUP MEMBERS:
- Pedro Miguel Magalhães Nunes
- Lourenço Alexandre Correia Gonçalves

PROGRAM DEVELOPMENT STATE:
- All objectives asked for in the project specification were accomplished;
- We kept the data from the leaderboard file generated in previous runs, added the new entries and reorganized them all;
- We didn't use an explicit id variable to store the robots sequential order,
instead the robots (represented as structs) are stored in a vector, which size and order do not change at any point in the program, and so the vector indexation is used as the sequential identifier.

MAIN DIFFICULTIES:
- The most challenging part of the code was reorganizing the leaderboard when running the program after data had already been written into the leaderboard file. To do this, we created a function to read the old leaderboard entries from the respective file, store them in a vector, add the new entries to that vector, sort it according to time (ascending order) and finally overwriting the contents of the file with the new organized entries from the vector.