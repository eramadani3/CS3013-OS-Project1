# CS3013-OS-Project1
Part 1: Prolific has a parent process load in. We use srand in order to create a random number generator between 5 and 11.
We use fork() to create children from the original parent process. We use print statement within a loop where each child introduces itself.
After a short period of time we then terminate the child by exiting with an exit(0).

Part 2: Generations is very similar to prolific but in this case, after using srand to generate a random number we use the random number to determine the number of children/descendents each of the children will have.
We create a for loop containing a fork() and the code for each of the children. For each of the fork() calls we decrement the lifespan count which means each child that is created has one less descendent than its parent process.
To do this we use a helper function. Using print statements after each of the fork() calls we have the children print its process id and the number of descendents it will have.
Once the lifespan is 0 then we have reached the last descendent and each of the children exits with exit(0).
Each of the processes waits for its children to exit before exiting itself.

Part 3: Explorer uses srand to determine a random number value which is then used as an index in an array of directories. 
Once the randomly chosen directory is selected from the array, we use chdir() to change the directory. We then run the 'ls - tr' command in the directory
and get the ouput.

Part 4: Slug uses srand to select an amount of time between 4 and 9 seconds, we use print statements to indicate the randomly selected time and we set a timer to make the process wait that given time.

Part 5: Using the exec() call on ./slug we call 4 different slugs to race eachother. The exec call will make 4 slugs run in parallel and the parent process prints out a note of the state of the race every .2 seconds.
Because of the randomness of the slug process, the race outputs will vary from race to race.
