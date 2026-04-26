*This project has been created as part of the 42 curriculum by <llugez>*

# 1) Description 

## Summary
The goal of the philosophers project is to resolve the famous probem create by Djilkra :
The dining philosophers problem.

## Problem presentation
There are n philosophers around a table who want to eat some spaghettis obviously they each got a fork, hmm.. but philosophers can't eat with just one fork they need minimun 2 forks.
Philosophers are simple they just: eat, sleep, think and do that routine again.
Each philo shared some "comportement" :
- Time_to_die: If a philosopher has not started eating within time_to_die milliseconds since the start of their last meal or the start of the simulation, they die.
- Time_to_eat : The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- Time_to_sleep : The time a philosopher will spend sleeping.
Mumber_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten atleast number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

##  

# 2) Instruction

### Compilation

```bash
make
```

### Run 

```bash
./philo
```

### Clean

```bash
make clean      # Remove object files
make fclean     # Remove executable and object files
make re         # Clean + recompile
```

# 3) Resources
An article that explain how work multithreading: [link](https://www.geeksforgeeks.org/c/multithreading-in-c/)
Wikipedia page of the Dining philosophers problem: [link](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Usage of Ai
In this project, AI was used primarily to facilitate the understanding of extensive documentation and to help implement specific functions for which few examples were available online.  
All AI-generated responses were carefully reviewed, tested, and validated before being integrated into the project.

Example:
- Assistance in understanding parsing logic and edge cases (quotes, environment variables, pipes)
- Guidance on structuring the project and organizing the code
- Occasional help with debugging and identifying potential memory leaks
