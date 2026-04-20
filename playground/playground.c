#include <stdio.h>
#include <sys/time.h>


long get_time_in_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
	printf("Secondes: %ld\n", tv.tv_sec);
	printf("microSecondes : %d\n", tv.tv_usec);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int main()
{
}
