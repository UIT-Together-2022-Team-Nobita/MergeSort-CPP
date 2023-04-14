#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

bool Input(int[][1000], int&, int&, string);
void MergeSort(int[][1000], int, int, int, int);
void Merge(int[][1000], int, int, int, int, int);
bool Output(int[][1000], int, int, string);

int main()
{
	static int mat[1000][1000];
	int m, n;
	cout << "Project K04" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intmatrixdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(mat, m, n, filenameinp) == true)
		{
			MergeSort(mat, n, m, 0, n * m - 1);
			string filenameout = filename;
			filenameout += ".outp";
			Output(mat, m, n, filenameout);
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else
			cout << "\nCan't open the file" << filename << endl;
	}
	cout << endl;
	return 1;
}

bool Input(int mat[][1000], int& m, int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fi >> mat[i][j];
	return true;
}

void MergeSort(int mat[][1000], int n, int m, int Left, int Right)
{
	if (Left < Right) 
	{
		int Mid = Left + (Right - Left) / 2;
		MergeSort(mat, n, m, Left, Mid);		
		MergeSort(mat, n, m, Mid + 1, Right);	
		Merge(mat, n, m, Left, Mid, Right);		
	}
}

void Merge(int mat[][1000], int n, int m, int Left, int Mid, int Right)
{
	int* temp = new int[Right - Left + 1];
	int p = 0;
	int i = Left;		
	int j = Mid + 1;	
	while (!(i > Mid && j > Right))
	{
		if ((i <= Mid && j <= Right && mat[i / m][i % m] < mat[j / m][j % m]) || j > Right)
		{
			temp[p++] = mat[i / m][i % m];
			i++;
		}
		else
		{
			temp[p++] = mat[j / m][j % m];
			j++;
		}
	}
	for (i = 0; i < p; i++)
		mat[(Left + i) / m][(Left + i) % m] = temp[i];
	delete[]temp;
}

bool Output(int mat[][1000], int m, int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << m << setw(5) << n << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			fo << setw(5) << mat[i][j];
		fo << endl;
	}
	return true;
}