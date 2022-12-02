#include <stdio.h>

void sort(int n, int v[])
{
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (v[j] > v[i]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

long __gcd(long a, long b)
{
	if (a == 0)
		return b;
	while (b != 0) {
		long r = a % b;
		a = b;
		b = r;
	}
	return a;
}

long _ceil(long a, long b)
{
	return (a / b + (a % b == 0 ? 0 : 1));
}

int main(void)
{
	long fr[26] = {0};
	char x;
	scanf("%c", &x);
	getchar();
	long read_letters = 0, distinct_letters = 0, last_allert = 0, in_queue = 0;
	while ((x >= 'a' && x <= 'z') || x == 'Q' || x == 'T' || x == 'E') {
		//alerte
		if (x == 'Q') {
			char y;
			scanf("%c", &y);
			getchar();
			printf("%c %ld\n", y, fr[(int)(y - 'a')]);
		} else if (x == 'T') {
			int k;
			scanf("%d", &k); //primele k : s
			getchar();
			int most_frequent[26];
			for (int i = 0; i < 26; ++i)
				most_frequent[i] = fr[i];
			sort(26, most_frequent);
			int first_found = 0;
			for (int i = 0; i < 26 && k != 0; ++i) {
				if (i != 0 && most_frequent[i] == most_frequent[i - 1])
					continue;
				for (int j = 0; j < 26 && k != 0; ++j) {
					if (fr[j] == most_frequent[i] && first_found == 0) {
						printf("%c", (char)('a' + j));
						first_found = 1;
						k--;
					} else if (fr[j] == most_frequent[i] && first_found == 1) {
						printf(" %c", (char)('a' + j));
						k--;
					}
				}
			}
			printf("\n");
		} else if (x == 'E') {
			char y;
			scanf("%c", &y);
			getchar();
			in_queue -= fr[(int)(y - 'a')];
			if (fr[(int)(y - 'a')] != 0)
				distinct_letters--;
			fr[(int)(y - 'a')] = 0;
		} else { // ALERTE
			if (fr[(int)(x - 'a')] == 0)
				distinct_letters++;
			read_letters++;
			in_queue++;
			fr[(int)(x - 'a')]++;
			//printf("%c-%ld\n", x, read_letters);
			for (char z = 'a'; z <= 'z'; ++z) {
				if (fr[(int)(z - 'a')] >= _ceil(in_queue, 2) &&
					distinct_letters >= 2 && read_letters >= 5 &&
					(read_letters - last_allert + 1) > 5) {
					printf("%c ", z);
					long gcd = __gcd(fr[(int)(z - 'a')], in_queue);
					printf("%ld", fr[(int)(z - 'a')] / gcd);
					printf("/%ld\n", in_queue / gcd);
					last_allert = read_letters;
				}
			}
		}
		scanf("%c", &x);
		getchar();
	}
	return 0;
}
