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

typedef enum s_state
{
	EATING = 0,						// Philosopher is eating
	SLEEPING = 1,					// Philosopher is sleeping
	THINKING = 2,					// Philosopher is thinking
	DIE = 3,						// Philosopher is dead
	FULL = 4,						// Philosopher is full
	OFF = 5							// Philosopher is idle, is doing nothing
}	t_state;

/*	This t_state enumeration represents the possible states of a philosopher in 
	the dining philosophers problem. It includes states like eating, sleeping, 
	thinking, and dead.	It is used to track the current state of a philosopher
	and determine their behavior in the simulation. 
	
	This code defines an enumeration type named t_state that represents the 
	different possible states a philosopher can be in during the Dining 
	Philosophers problem simulation. Let's break down each state:

	EATING: The philosopher is currently eating.
	SLEEPING: The philosopher is currently sleeping.
	THINKING: The philosopher is currently thinking.
	DIE: The philosopher has finished eating all their meals and is considered 
		dead.
	FULL: The philosopher has finished eating the current meal and is waiting 
		for the next one.
	OFF: The philosopher is idle and not doing anything.

	This enumeration is used to track the current state of each philosopher and 
	to determine the next action they should take. For example, a philosopher in 
	the "EATING" state will eventually transition to the "SLEEPING" state, and 
	so on. The enumeration provides a clear and concise way to represent the
	possible states of a philosopher in the simulation. */

typedef struct s_philo
{
	int				id;				// Philosopher's id
	int				meals;			// Number of meals eaten
	pthread_mutex_t	*fork_l;		// Left fork
	pthread_mutex_t	*fork_r;		// Right fork
	pthread_mutex_t mut_last_eat;	// Mutex for the last time the philos ate
	pthread_mutex_t	mut_num_meals;	// Mutex for the number of meals	
	pthread_mutex_t mut_state;		// Mutex for the state
	struct s_data	*data;			// Pointer to the main data structure
	t_state			state;			// Current state of the philosopher
	uint64_t		last_eat;		// Last time the philosopher ate
}	t_philo;

/*	This s_philo structure represents a philosopher in the dining philosophers 
	problem. It contains information about the philosopher's state, the number 
	of meals eaten, the forks they are holding, and synchronization mechanisms 
	to prevent problems with shared resources.	
	
	Let's break down each member of the structure:

	id: A unique identifier for each philosopher.
	meals: A counter to track the number of meals a philosopher has eaten.
	fork_l and fork_r: Pointers to mutexes representing the left and right 
		forks, respectively. These mutexes are used to synchronize access 
		to the forks.
	mut_last_eat: A mutex to protect the last_eat variable. This is likely used 
		to implement a timeout mechanism to prevent deadlock.
	mut_num_meals: A mutex to protect the meals variable. This ensures that the 
		meal count is updated atomically.
	mut_state: A mutex to protect the state variable. This is used to ensure 
		that the philosopher's state is updated atomically.
	data: A pointer to the main data structure, which likely contains global 
		information about the simulation, such as the total number of 
		philosophers and the simulation time.
	state: The current state of the philosopher. This could be one of the 
		following: THINKING, EATING, or SLEEPING.
	last_eat: A timestamp indicating the last time the philosopher finished 
		eating.

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
	int				nb_philos;			
	int				nb_meals;			
	int				nb_full_p;			
	bool			keep_iterating;
	uint64_t		eat_time;
	uint64_t		die_time;				
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	mut_eat_t;
	pthread_mutex_t	mut_die_t;				
	pthread_mutex_t	mut_sleep_t;
	pthread_mutex_t	mut_print;
	pthread_mutex_t	mut_nb_philos;
	pthread_mutex_t	mut_keep_iter;
	pthread_mutex_t	mut_start_time;
	pthread_t		monit_all_alive;
	pthread_t		monit_all_full;
	pthread_t		*philo_ths;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;

/*	This s_date structure is designed to hold various parameters and 
	synchronization mechanisms for a multi-threaded program like this.

	Breakdown of the Structure Members:

	nb_philos: An integer representing the number of philosophers in the 
		simulation.
	nb_meals: An integer specifying the number of meals each philosopher 
		should eat.
	nb_full_p: An integer to track the number of philosophers who have 
		finished eating.
	keep_iterating: A boolean flag to control the overall iteration of the 
		simulation.
	eat_time: A 64-bit unsigned integer representing the time a philosopher 
		spends eating.
	die_time: A 64-bit unsigned integer representing the time a philosopher 
		spends dying.
	sleep_time: A 64-bit unsigned integer representing the time a philosopher 
		spends sleeping.
	start_time: A 64-bit unsigned integer to store the start time of the 
		simulation.
	mut_eat_t, mut_die_t, mut_sleep_t, mut_print, mut_nb_philos, mut_keep_iter,
		mut_start_time: These are mutex locks used to synchronize access to 
		shared resources, preventing race conditions.
	monit_all_alive, monit_all_full: These are thread handles for threads 
		responsible for monitoring the state of the philosophers.
	philo_ths: An array of thread handles for the philosopher threads.
	forks: An array of mutex locks, representing the forks used by the 
		philosophers.
	philos: An array of structures, each representing a philosopher with its 
		own state and thread handle.

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