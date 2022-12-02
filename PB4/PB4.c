#include <stdio.h>
#define MXN 505

int n, m, mt[MXN][MXN], fr_linie[MXN][MXN], fr_col[MXN][MXN];

void op1(int x, int ans1[])
{
	for (int i = 1; i <= n * n; ++i)
		if (fr_linie[x][i] == 0)
			ans1[i] = 1;
}

void op2(int y, int ans2[])
{
	for (int i = 1; i <= n * n; ++i)
		if (fr_col[y][i] == 0)
			ans2[i] = 1;
}

void op3(int z, int ans3[])
{
	int linie_start = (z % n != 0 ? n * (z / n) + 1 : n * (z / n - 1) + 1);
	int coloana_start = (z % n != 0 ? n * (z % n - 1) + 1 : n * (n - 1) + 1);
	int fr[MXN] = {0};
	for (int i = linie_start - 1; i < linie_start + n - 1; ++i)
		for (int j = coloana_start - 1; j < coloana_start + n - 1; ++j)
			fr[mt[i][j]] = 1;
	for (int i = 1; i <= n * n; ++i)
		ans3[i - 1] = !fr[i];
}

int invalid(void)
{
	for (int i = 0; i < n * n; ++i) { // check for columns
		int fr[MXN] = {0};
		for (int j = 0; j < n * n; ++j) {
			if (mt[i][j] != 0) {
				fr[mt[i][j]]++;
				if (fr[mt[i][j]] > 1)
					return 1;
			}
		}
	}
	for (int j = 0; j < n * n; ++j) { // check for linies
		int fr[MXN] = {0};
		for (int i = 0; i < n * n; ++i) {
			if (mt[i][j] != 0) {
				fr[mt[i][j]]++;
				if (fr[mt[i][j]] > 1)
					return 1;
			}
		}
	}
	for (int z = 1; z <= n * n; ++z) { // check for squares
		int linie_start = (z % n != 0 ? n * (z / n) + 1 : n * (z / n - 1) + 1);
		int col_start = (z % n != 0 ? n * (z % n - 1) + 1 : n * (n - 1) + 1);
		int fr[MXN] = {0};
		for (int i = linie_start - 1; i < linie_start + n - 1; ++i) {
			for (int j = col_start - 1; j < col_start + n - 1; ++j) {
				if (mt[i][j] != 0) {
					fr[mt[i][j]]++;
					if (fr[mt[i][j]] > 1)
						return 1;
				}
			}
		}
	}
	return 0;
}

int main(void)
{
	scanf("%d%d", &n, &m);
	int nr_elemente = 0;
	for (int i = 0; i < n * n; ++i) {
		for (int j = 0; j < n * n; ++j) {
			scanf("%d", &mt[i][j]);
			fr_linie[i][mt[i][j]]++;
			fr_col[j][mt[i][j]]++;
			nr_elemente += (mt[i][j] != 0);
		}
	}
	while (m--) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int x, ans1[MXN] = {0};
			scanf("%d", &x);
			x--;
			op1(x, ans1);
			for (int i = 1; i <= n * n; ++i)
				printf("%d ", ans1[i]);
			printf("\n");
		} else if (op == 2) {
			int y, ans2[MXN] = {0};
			scanf("%d", &y);
			y--;
			op2(y, ans2);
			for (int i = 1; i <= n * n; ++i)
				printf("%d ", ans2[i]);
			printf("\n");
		} else if (op == 3) {
			int z, ans3[MXN] = {0};
			scanf("%d", &z);
			op3(z, ans3);
			for (int i = 0; i < n * n; ++i)
				printf("%d ", ans3[i]);
			printf("\n");
		} else if (op == 4) {
			int x, y;
			scanf("%d%d", &x, &y);
			if (mt[x - 1][y - 1] != 0) {
				for (int i = 1; i <= n * n; ++i)
					printf("0 ");
				printf("\n");
				continue;
			}
			int ans1[MXN] = {0};
			op1(x - 1, ans1);
			int ans2[MXN] = {0};
			op2(y - 1, ans2);
			int line_start = (x % n == 0 ? x - (n - 1) : (x / n) * n + 1);
			int col_start = (y % n == 0 ? y - (n - 1) : (y / n) * n + 1);
			int ans3[MXN] = {0};
			for (int i = line_start - 1; i < line_start + n - 1; ++i)
				for (int j = col_start - 1; j < col_start + n - 1; ++j)
					ans3[mt[i][j]] = 1;
			for (int i = 1; i <= n * n; ++i)
				printf("%d ", (ans1[i] && ans2[i] && !ans3[i]));
			printf("\n");
		} else if (op == 5) {
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			x--, y--;
			if (mt[x][y] != 0)
				continue;
			mt[x][y] = c;
			fr_linie[x][mt[x][y]]++;
			fr_col[y][mt[x][y]]++;
			nr_elemente++;
		} else if (op == 6) {
			if (invalid())
				printf("1\n");
			else if (nr_elemente == n * n * n * n)
				printf("2\n");
			else
				printf("0\n");
		}
	}
	return 0;
}
