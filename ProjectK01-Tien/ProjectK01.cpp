#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

bool Input(int[], int&, string);
void MergeSort(int[], int, int);
void Merge(int[], int, int, int);
bool Output(int[], int, string);

int main()
{
	static int a[1000000];
	int n;
	cout << "Project K01" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(a, n, filenameinp) == true)
		{
			MergeSort(a, 0, n - 1);
			string filenameout = filename;
			filenameout += ".outp";
			Output(a, n, filenameout);
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else
			cout << "\nCan't open the file" << filename << endl;
	}
	cout << endl;
	return 1;
}

bool Input(int a[], int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> n;
	for (int i = 0; i < n; i++)
		fi >> a[i];
	return true;
}

void MergeSort(int a[], int Left, int Right)
{
	if (Left < Right) 
	{
		int Mid = Left + (Right - Left) / 2;
		MergeSort(a, Left, Mid);		
		MergeSort(a, Mid + 1, Right);	
		Merge(a, Left, Mid, Right);
	}
}
void Merge(int a[], int Left, int Mid, int Right)
{
	int* temp_arr = new int[Right - Left + 1];
	int p = 0;
	int i = Left;		
	int j = Mid + 1;	
	while (!(i > Mid && j > Right))
	{
		if ((i <= Mid && j <= Right && a[i] < a[j]) || j > Right)
			temp_arr[p++] = a[i++];
		else
			temp_arr[p++] = a[j++];
	}
	for (i = 0; i < p; i++)
		a[Left + i] = temp_arr[i];
	delete[]temp_arr;
}

bool Output(int a[], int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << n << endl;
	for (int i = 0; i < n; i++)
		fo << setw(5) << a[i];
	return true;
}