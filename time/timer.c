#include <time.h>
#include <stdio.h>

int main(){

	time_t *t;

        *t = ( time_t ) 0 ;

	*t = time(t);

	struct tm *timer;

        timer = localtime(t);

	int i = (*t - (56 * 60 * 60 * 24 * 365)  );
	printf("\n%ld %d %d/%d %d:%d\n", ((*t/60/60/24/365) + 1970 ),i, timer->tm_mday, (1 + timer->tm_mon), timer->tm_hour, timer->tm_min );

	return 0;
}
