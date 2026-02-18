This project has been created as part of the 42 curriculum by xalves

# Philosophers
Philosophers doing Philosophers things

## “Description”
### A section that clearly presents the project, including its goal and a brief overview.
**Philosophers** is a project where we simulate x amount of philosophers, on a process where they eat, sleep and think.
With each philosopher having _only 1 'fork'_ each, and they can only eat when they have 2 forks. (their fork on the fork of the other philosopher in the oposite side of their fork) 
If the other fork is being used by other philosopher, the philosopher must wait until he has that fork available for use.

## “Instructions”
### An section containing any relevant information about compilation,installation, and/or execution

- `n_philos` -> The number of philosophers and also the number of forks.
- `time_to_die (in milliseconds)` -> if a philosopher has not started eating within `time_to_die milliseconds` since the start of their last meal or the start of the simulation, they die.
- `time_to_eat (in milliseconds)` -> The time it takes for a philosopher to eat.
- `time_to_sleep (in milliseconds)` -> The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat (optional argument)` -> If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## “Resources”
### A section listing classic references related to the topic (documen-tation, articles, tutorials, etc.), as well as a description of how AI was used —specifying for which tasks and which parts of the project.
