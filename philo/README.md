*This project has been created as part of the 42 curriculum by xalves*

# Philosophers
Simulation of the classic Dining Philosophers problem.

## “Description”
Simulates a configurable number of philosophers, each running in a concurrent process where they eat, sleep, and think.
With each philosopher having _only 1 'fork'_ each, and they can only eat when they have 2 forks. (their fork on the fork of the other philosopher in the opposite side of their fork) 
If the other fork is being used by another philosopher, the philosopher must wait until he has that fork available for use.

## “Instructions”

### Compilation
To compile the projet simply run:
```bash
make
```
To recompile everything run:
```bash
make re
```


### Argumets

```bash
./philo n_philos time_to_die time_to_eat time_to_sleep [count_eat]
```

- `n_philos` -> The number of philosophers and also the number of forks.
- `time_to_die (in milliseconds)` -> if a philosopher has not started eating within `time_to_die milliseconds` since the start of their last meal or the start of the simulation, they die.
- `time_to_eat (in milliseconds)` -> The time it takes for a philosopher to eat.
- `time_to_sleep (in milliseconds)` -> The time a philosopher will spend sleeping.
- `count_eat (optional argument)` -> If all philosophers have eaten at least `count_eat`, the simulation stops.(If not specified, the simulation stops when a philosopher dies).

### Examples
Basic philosopher simulation:
```bash
./philo 5 800 200 200
```
This will create a simulation with 5 philosophers which have 800ms `time_to_die`, 200ms `time_to_eat`, 200ms `time_to_sleep`.
```bash
./philo 5 800 200 200 8
```
Same as above, but now `count_eat` is 8, so they will only stop after 8 repeats(eating 8 times).

### Cleanup
Remove object files:
```bash
make clean
```
Remove object files and executable:
```bash
make fclean
```

## Resources
- [Youtube Code Vault -> Unix Threads in C](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Dining philosophers problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [pthread_mutex_init(3) — Linux manual page](https://www.man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html)
- 42 Philosophers en.subject.pdf
