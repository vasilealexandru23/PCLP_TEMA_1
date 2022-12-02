#include <stdio.h>
#include <math.h>

const long MIN = -(1e18) + 5;

long long convert_8_10(long long n)
{
	long long p = 1;
	long long converted = 0;
	while (n) {
		converted += (n % 10) * p;
		p *= 8;
		n /= 10;
	}
	return converted;
}

int main(void)
{
	int N;
	scanf("%d", &N);
	unsigned long long ps = 0;
	double n_a = 0, n_b = 0;
	long long a_max_1 = -1, a_max_2 = -1, b_max_1 = -1, b_max_2 = -1;
	while (N--) {
		long long a, b; // baza 8
		scanf("%lld%lld", &a, &b);
		a = convert_8_10(a);
		b = convert_8_10(b);
		if (a > a_max_1) {
			a_max_2 = a_max_1;
			a_max_1 = a;
		} else if (a > a_max_2 && a != a_max_1) {
			a_max_2 = a;
		}
		if (b > b_max_1) {
			b_max_2 = b_max_1;
			b_max_1 = b;
		} else if (b > b_max_2 && b != b_max_1) {
			b_max_2 = b;
		}
		ps += a * b;
		n_a += (double)a * (double)a;
		n_b += (double)b * (double)b;
	}
	printf("%lld\n%lld %lld\n", ps, a_max_2, b_max_2);
	printf("%.7F %.7F\n", sqrt((double)n_a), sqrt((double)n_b));
	return 0;
}
