/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-29 15:55:48 by sternero          #+#    #+#             */
/*   Updated: 2024-10-29 15:55:48 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_state
{
	DIE,						// Philosopher is dead
	EATING,						// Philosopher is eating
	FINISHED,					// Philosopher has finished eating
	FULL,						// Philosopher is full
	OFF,						// Philosopher is idle, is doing nothing
	SLEEPING,					// Philosopher is sleeping
	THINKING,					// Philosopher is thinking
}	t_state;

/*	This t_state enumeration represents the possible states of a philosopher in 
	the dining philosophers problem. It includes states like EATING, SLEEPING,
	and THINKING, as well as additional states like DIE, FINISHED, and FULL.

	Each state corresponds to a specific activity or condition of the philosopher
	during the simulation. For example, EATING indicates that the philosopher is
	currently eating, while THINKING indicates that the philosopher is thinking.

	The additional states DIE, FINISHED, and FULL may be used to represent
	special conditions, such as when a philosopher has died, finished eating all
	meals, or is full and no longer needs to eat.

	Overall, this enumeration provides a clear and concise way to represent the
	various states that a philosopher can be in during the simulation. It helps
	organize the logic of the program and makes it easier to understand the
	philosopher's behavior based on their current state.
*/

struct	s_data;

/*	Forward declaration of the t_data structure to allow the t_philo structure 
	to reference it. This is necessary because the t_philo structure contains a 
	pointer to the t_data structure, and the t_data structure is defined later 
	in the file. By using a forward declaration, we can inform the compiler that
	the t_data structure exists without providing the full definition at this 
	point. This allows us to define the t_philo structure with a pointer to the 
	t_data structure before the t_data structure is fully defined.	*/

typedef struct s_philo
{
	int				id;				// Philosopher's id
	int				meals;			// Number of meals eaten
	sem_t			*philo_sem;		// Semaphore for the philosopher	
	struct s_data	*data;			// Pointer to the main data structure
	t_state			state;			// Current state of the philosopher
	uint64_t		last_eat;		// Last time the philosopher ate
}	t_philo;

/*	This s_philo structure represents a philosopher in the dining philosophers 
	problem. It contains information about the philosopher's state, the number 
	of meals eaten, the forks they are holding, and synchronization mechanisms 
	to prevent problems with shared resources.	
	
	Let's break down each member of the structure:

	id: An integer representing the unique identifier of the philosopher.
	meals: An integer tracking the number of meals the philosopher has eaten.
	philo_sem: A semaphore used to synchronize access to shared resources.
	data: A pointer to the main data structure containing information about the 
		simulation.
	state: An enumeration representing the current state of the philosopher.
	last_eat: A 64-bit unsigned integer storing the timestamp of the last meal.

	Purpose of the Structure:

	This structure represents an individual philosopher in the simulation. 
	It stores information about the philosopher's state, the forks they need to 
	eat, and the necessary synchronization mechanisms to prevent race conditions 
	and deadlock.

	Key Points:

	Mutex Usage: The mutexes are crucial for ensuring that only one philosopher 
		can access a shared resource (like a fork or a state variable) at a 
		time. This prevents race conditions and ensures the correct execution 
		of the simulation.
	State Management: The state variable tracks the current activity of the 
		philosopher. This information is used to determine the next action, 
		such as picking up forks, eating, or thinking.
	Timestamping: The last_eat timestamp is used to implement a timeout 
		mechanism. If a philosopher hasn't eaten for a certain period, it can be 
		forced to release its forks to prevent deadlock.	*/

typedef struct s_data
{
	int				philos_num;		
	int				meals_num;
	pthread_t		watchdog;	
	sem_t			*forks_sem;
	sem_t			*print_sem;
	uint64_t		eat_time;
	uint64_t		die_time;				
	uint64_t		sleep_time;
	uint64_t		start_time;
	t_philo			philo;
}	t_data;

/*	This s_date structure is designed to hold various parameters and 
	synchronization mechanisms for a multi-threaded program like this.

	Breakdown of the Structure Members:

	nb_philos: An integer representing the number of philosophers in the 
		simulation.
	nb_meals: An integer specifying the number of meals each philosopher 
		should eat.
	watchdor: A thread responsible for monitoring the philosophers and
		ensuring they are alive and eating correctly.
	forks_sem: An array of semaphores representing the forks that the
		philosophers will use to eat.
	print_sem: A semaphore used to synchronize the output of the program.
	eat_time: The time it takes for a philosopher to eat a meal.
	die_time: The time it takes for a philosopher to die if they haven't
		eaten.
	sleep_time: The time it takes for a philosopher to sleep after eating.
	start_time: The timestamp when the simulation started.
	philos: An array of philosopher structures representing each philosopher
		in the simulation.

	Overall Function:

	This structure essentially acts as a container for all the necessary 
	information and synchronization mechanisms to implement a dining 
	philosophers problem. It provides a central location to store and access 
	shared data, ensuring that multiple threads can operate on it safely.

	Key Points:

	The mutex locks are used to protect shared resources like the number of 
	philosophers, the iteration flag, and the start time.
	The monitor threads are likely responsible for checking if all philosophers 
	are alive or have finished eating.
	The philosopher threads will use the forks to eat, and the synchronization 
	mechanisms will prevent deadlock and starvation.
	
	u_int64_t is used for time-related variables to ensure precision and 
	compatibility across different systems. This is important for accurately
	measuring time intervals in the simulation. The use of unsigned integers
	also ensures that time values are always positive, 64 bits provides a
	wide range of values to work with.

	The mutex are used to prevent the access of shared resources by multiple
	threads simultaneously, ensuring that only one thread can access a
	resource at a time. This is crucial. */

#endif