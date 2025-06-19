#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	*exec_thread(void *ptr)
{
	// printf("in thread %d\n", *(int *)ptr);
	++(*(int *)ptr);
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[2];
	int	ret = 0;
	int	*ret_ptr = &ret;
	int	i;
	int var = 0;

	printf("var val (before thread): %d\n", var);
	i = 0;
	while (i < 2)
	{
		if (pthread_create(&threads[i], NULL, exec_thread, &var))
		{
			perror("pthread_create");
			return (-1);
		}
		++i;
	}
	i = 0;
	while (i < 2)
	{
		if (pthread_join(threads[i], (void **)&ret_ptr))
		{
			perror("pthread_join");
			return (-1);
		}
		++i;
	}
	// if (pthread_join(threads[1], (void **)&ret_ptr))
	// 	return (-1);
	printf("thread ret val: %d\n", ret);
	printf("var val (after thread): %d\n", var);
	return (0);
}
