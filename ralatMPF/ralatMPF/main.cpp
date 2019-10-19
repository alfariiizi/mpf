#include <iostream>
#include <conio.h>
#include <vector>
using namespace std;

//if needed
namespace al
{
	void print(const char* string, int max)
	{
		int n = 0;
		for (; *string != 0 && n + 1 < max; string++, n++)
		{
			_putch(*string);
		}
	}

	void read(char* s, int max)
	{
		for (char c = _getch(); *s != 13; s++, c = _getch())
		{
			*s = c;
			_putch(c);
		}
		*s = 0;
	}
}

//mpf
class Stat
{
private:
	class Var
	{
	public:
		Var() = default;
		Var(float& x, float& y)
			:
			x(x),
			y(y)
		{}
		const float xsq()const
		{
			return x * x;
		}
		const float ysq()const
		{
			return y * y;
		}
		const float xy()const
		{
			return x * y;
		}
		float GetX() const
		{
			return x;
		}
		float GetY() const
		{
			return y;
		}
	private:
		float x;
		float y;
	};
public:
	Stat() = default;
	Stat(int nData)
		:
		nData(nData)
	{
		variables = new Var[nData];
		cout << "X  |  Y" << endl;
		cout << "-------" << endl;
		float x, y;
		for (int i = 0; i < nData; i++)
		{
			cin >> x; cin >> y;
			variables[i] = Var(x, y);
		}
	}
	const float xZigma()
	{
		float zigma = 0.0f;
		for (int i = 0; i < nData; i++)
		{
			zigma += variables[i].GetX();
		}
		return zigma;
	}
	const float yZigma()
	{
		float zigma = 0.0f;
		for (int i = 0; i < nData; i++)
		{
			zigma += variables[i].GetY();
		}
		return zigma;
	}
	const float xsqZigma()
	{
		float zigma = 0.0f;
		for (int i = 0; i < nData; i++)
		{
			zigma += variables[i].xsq();
		}
		return zigma;
	}
	const float ysqZigma()
	{
		float zigma = 0.0f;
		for (int i = 0; i < nData; i++)
		{
			zigma += variables[i].ysq();
		}
		return zigma;
	}
	const float xyZigma()
	{
		float zigma = 0.0f;
		for (int i = 0; i < nData; i++)
		{
			zigma += variables[i].xy();
		}
		return zigma;
	}
	const float shit()
	{
		return (nData * xsqZigma()) - (xZigma() * xZigma());
	}
	const float longformShit()
	{
		const float holyshit = (xsqZigma() * yZigma() * yZigma()) - (2 * xZigma() * yZigma() * xyZigma()) + (float(nData) * xyZigma() * xyZigma());
		const float holyholyshit = (1.0f / (float(nData) - 2.0f)) * (ysqZigma() - (holyshit / shit()));
		return sqrt(holyholyshit);
	}
	const float A()
	{
		return ((xsqZigma() * yZigma()) - (xZigma() * xyZigma())) / shit();
	}
	const float B()
	{
		return ((float(nData) * xyZigma()) - (xZigma() * yZigma())) / shit();
	}
	const float Aralat()
	{
		const float fck = xsqZigma() / shit();
		return longformShit() * sqrt(fck);
	}
	const float Bralat()
	{
		const float fck = float(nData) / shit();
		return longformShit() * sqrt(fck);
	}
	void print()
	{
		cout << "\n   Tinggal rebahan lah ya" <<
				"\n----------------------------" << endl;
		cout << "zigma X   : " << xZigma() << endl;
		cout << "zigma Y   : " << yZigma() << endl;
		cout << "zigma Xsq : " << xsqZigma() << endl;
		cout << "zigma Ysq : " << ysqZigma() << endl;
		cout << "zigma XY  : " << xyZigma() << endl;
		cout << "segitiga  : " << shit() << endl;
		cout << "kotak     : " << longformShit() << endl;
		cout << "A         : " << A() << endl;
		cout << "B         : " << B() << endl;
		cout << "ralat A   : " << Aralat() << endl;
		cout << "ralat B   : " << Bralat() << endl;
		cout << "\nnote : 'kotak' merupakan hasil dari persamaan rumus yang panjang" << endl;
		delete[] variables;
	}
private:
	int nData;
	Var* variables;
};

int main()
{
	int nData;
	cout << "--v1.1" << endl << endl;
	cout << "Jumlah data : "; cin >> nData;
	cout << "\n--------------------------------------------------------------------------------------------" << endl;
	cout << "Cara memasukkan nilainya adalah masukkan nilai 'x' pada data pertama kemudian press 'space'"
		<< "\nkemudian masukkan nilai 'y' data pertama dan press 'enter'" << endl;
	cout << "contoh : 123.98 -45.56 || 123.98 merupakan nilai x1, -45.56 merupakan nilai y1" << endl;
	cout << "------------------------------------------------------------------------------------------\n" << endl;
	Stat stat = { nData };
	stat.print();

	while (!_kbhit());
	return 0;
}
