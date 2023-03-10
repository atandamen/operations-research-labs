#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename T>
class Solver 
{
	// Summary:
	//	Количество состояний
	int _n;

	// Summary:
	//	Матрица переходных вероятностей
    vector<vector<T>> _P; 
public:
    Solver(int n): _n(n)
    {
        _P.resize(n);
        for (auto& row : _P)
            row.resize(n);
    }

	// Summary:
	//	Устанавливает значение i-ой строки и j-ого столбца в значение v
    void Set(int i, int j, T v)
    {
        _P[i][j] = v;
    }

	// Summary
	//	Возвращает i-ую строку
	vector<T> GetRow(int i) 
	{
		return _P[i];
	}
	
	// Summary:
	//	Печатает содержимое таблицы в консоль
    void Print()
    {
        for(auto& row : _P) {
            for (auto v : row)
                cout << setw(4) << v;
            cout << endl; 
        }

        cout << endl;
    }
	
	
	// Summary:
	//	Рассчитывает шаг на основе предыдущих данных
	vector<T> SingleStep(vector<T>& p) 
	{
		assert(p.size() == _n);

		vector<T> v;
		for (int i = 0; i != _n; i++) 
		{
			T m = T(0);
			for (int j = 0; j != _n; j++) 
			{
				m += p[j] * _P[j][i];
			}

			v.push_back(m);
		}

		return v;
	}
};

template<typename T>
void printRow(vector<T>& row, int w = 4)
{
	for (auto v : row)
		cout << v << " ";
	cout << endl;
}

int main()
{
    int n = 0;
    cin >> n;

    Solver<float> solver(n);
    for (int i = 0; i != n; i++) 
    {
		for (int j = 0; j != n; j++) 
		{
			float v{ 0 };
			cin >> v;

			solver.Set(i, j, v);
		}
    }

	int m{ 0 };
	cin >> m;
	
	vector<float> p { 1, 0, 0, 0 };
	
	for (int i = 0; i != m+1; i++) {
		cout << "  Шаг #" << i << endl;
		
		printRow(p);
		
		p = solver.SingleStep(p);	
	}
}
