#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MXN 1005

long n, mt[MXN][MXN], used[MXN][MXN];

long _ceil(long a, long b)
{
	return (a / b + (a % b == 0 ? 0 : 1));
}

void next_cell(long curr_x, long curr_y, long curr_dist)
{
	if (used[curr_x][curr_y] == 1) { // STOP
		printf("%ld\n%ld ", curr_dist, n - curr_x);
		if (curr_y <= 25) {
			printf("%c", (char)(curr_y + 'A'));
		} else if (curr_y < 27 * 26) {
			printf("%c", (char)(curr_y / 26 - 1 + 'A'));
			printf("%c", (char)(curr_y % 26 + 'A'));
		} else {
			printf("A");
			printf("%c", (char)(curr_y / 26 - 26 - 1 + 'A'));
			printf("%c", (char)(curr_y % 26 + 'A'));
		}
		return;
	}
	used[curr_x][curr_y] = 1;
	if (curr_x % 2 != curr_y % 2) { // patrat negru
		long next_x = (curr_x + mt[curr_x][curr_y] +
					   _ceil(labs(mt[curr_x][curr_y]), n) * n) % n;
		next_cell(next_x, curr_y, curr_dist + labs(mt[curr_x][curr_y]));
	} else { //patrat alb
		long next_y = (curr_y + mt[curr_x][curr_y] +
					   _ceil(labs(mt[curr_x][curr_y]), n) * n) % n;
		next_cell(curr_x, next_y, curr_dist + labs(mt[curr_x][curr_y]));
	}
}

int main(void)
{
	scanf("%ld", &n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%ld", &mt[i][j]);
	next_cell(0, 0, 0);
	printf("\n");
	return 0;
}
