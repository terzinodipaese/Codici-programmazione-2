#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int selectioSort(int *a, int len)
{
	int somma = 0;
	int min;
	
	for(int i=0; i<len; i++)
	{
		min = i;
		for(int j=i+1; j<len; j++)
			if(a[j] < a[min])
				min = j;
				
		somma += min - i;   //accumula le differenze tra l'indice del nuovo e del vecchio minimo
		
		int temp = a[i];
		a[i] = a[min];
		a[min] = temp;
	}
	
	return somma;
}

void swap(int *a, int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

int main()
{
	int N;
	
	for(int i=0; i<100; i++)
	{
		in >> N;
		int array[N];
		
		for(int i=0; i<N; i++)
			in >> array[i];
		
		out << selectioSort(array, N) << endl;
	}
	
	in.close();
	out.close();
}






