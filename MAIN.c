#include <stdio.h>
#define MAXN 10000
#include "QCOUNT.c"
#include "mysub_wip_4:29.c"

main(){
	int N[1] = {2000};
	int n,ct,loop,round,answer,total,biggest, num_incorrect=0, num_correct=0;

	for (round = 0; round<1; round++) {
		n = N[round];
		total = 0;
		biggest = -1;
		for (loop=1; loop<=10000; loop++) {
			printf("Start: \n");
			QCOUNT(0,n);
			answer = mysub( n );
			if (answer<0) {
				printf(" *** flagged error %d at round=%d, loop=%d\n",answer,round,loop);
				return(0);
			}
			ct = QCOUNT(2,answer);

			// printf("Compares: %d\n", ct);

			if (ct<=0) {
				printf(" *** ERROR at round=%d, loop=%d\n",round,loop);
				num_incorrect += 1;
				// return(0);
			} else {
				num_correct += 1;
				total += ct;
			}
			if (ct>biggest) biggest=ct;
			// total += ct;

			// printf("\n\n");
		}

		printf("n=%5d,   max=%6d,   avg=%8.2f\n",n,biggest,total/(float)num_correct);
		printf("num_correct=%d, num_incorrect=%d\n", num_correct, num_incorrect);
		fflush(stdout);
	}
}
