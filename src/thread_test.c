#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void	*herd_threads(void *ptr)
{
	// printf("in thread %d\n", *(int *)ptr);
	while (*(int *)ptr != -1)
		usleep(200000);
	return (NULL);
}

static void	*exec_thread(void *ptr)
{
	// printf("in thread %d\n", *(int *)ptr);
	// ++(*(int *)ptr);
	printf("sleeping thread %d\n", *(int *)ptr);
	sleep(5);
	printf("set dead thread %d\n", *(int *)ptr);
	*(int *)ptr = -1;
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[2];
	pthread_t	parent_thread;
	// int	ret = 0;
	// int	*ret_ptr = &ret;
	int	i;
	int var = 0;

	printf("var val (before thread): %d\n", var);
	if (pthread_create(&parent_thread, NULL, herd_threads, &var))
	{
		perror("pthread_create");
		return (-1);
	}
	i = 0;
	while (i < 1)
	{
		if (pthread_create(&threads[i], NULL, exec_thread, &var))
		{
			perror("pthread_create");
			return (-1);
		}
		if (pthread_detach(threads[i]))
		{
			perror("pthread_detach");
			return (-1);
		}
		++i;
	}
	if (pthread_join(parent_thread, NULL))
	{
		perror("pthread_join");
		return (-1);
	}
	// i = 0;
	// while (i < 2)
	// {
	// 	if ((errno = pthread_join(threads[i], NULL)))
	// 	{
	// 		perror("pthread_join");
	// 		// return (-1);
	// 	}
	// 	++i;
	// }
	// sleep(1);
	// if (pthread_join(threads[1], (void **)&ret_ptr))
	// 	return (-1);
	// printf("thread ret val: %d\n", ret);
	printf("var val (after thread): %d\n", var);
	return (0);
}
