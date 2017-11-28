//
#include<conio.h>
#include <iostream>
#include <iomanip>

using namespace std;

bool promising(int* s, int n, int limit)//s array of position , n number of queens
{
	if (limit == 0)
	{
		return true;
	}
	for (int i = 0; i <= limit - 1; i++)
	{
		for (int j = i + 1; j <= limit; j++)
		{
			if ((s[i] >= n) || (s[j] >= n) || (s[i] == s[j] || i - j == s[i] - s[j] || i - j == s[j] - s[i]))
			{
				return false;
			}
		}
	}
	return true;
}


void n_queen(int *s, int n, int limit)
{
	static int counter = 0;
	if (promising(s, n, limit))
	{
		if (limit == n - 1)
		{
			int row = 0;
			counter++;
			cout << setw(3) << counter << ": ";
			for (int i = 0; i < n; i++)
			{
				cout << setw(2) << "(" << row << "," << s[i] << ")";
				row++;
			}
			cout << endl;
		}
		else
		{
			for (int j = 0; j < n; j++)
			{
				s[limit + 1] = j;
				n_queen(s, n, limit + 1);
			}
		}
	}
}

//open-mind.ir
void solve_n_qeen(int n)
{
	int *s;
	s = new int[n];

	for (int i = 0; i < n; i++)
	{
		s[0] = i;
		n_queen(s, n, 0);
	}
}


int main()
{
	int n;
	cout << "Enter n(number of queens in n*n board) ::";
	cin >> n;
	solve_n_qeen(n);
	_getch();
}