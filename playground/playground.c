#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

void	*routine(void *arg)
{
	pthread_t *thread = (pthread_t *)arg;
	while (1)
	{
		printf("je suis le thread_1\n");
		sleep(2);
		if (pthread_detach(*thread) != 0)
		{
			perror("detach"); 
		}
	}
	return (NULL);
}

int main()
{
	pthread_t thread_1;

	pthread_create(&thread_1, NULL, routine, &thread_1);
	pthread_join(thread_1, NULL);
}
