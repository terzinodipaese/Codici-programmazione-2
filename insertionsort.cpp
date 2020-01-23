#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


int insertionSort(int *a, int len)
{
	int spostamenti = 0;	//accumulatore degli spostamenti
	int key;				//variabile d'appoggio
	int j;
	
	for(int i=1; i<len; i++)
	{
		key = a[i];
		j = i-1;
		
		while(j >=0 && key < a[j])
		{
			a[j+1] = a[j];
			j--;
			spostamenti++;
		}
		
		a[j+1] = key;
	}
	
	return spostamenti;
}


int main()
{
	int N;
	
	for(int i=0; i<100; i++)		//ciclo per le righe
	{
		in >> N;
		int array[N];
		
		for(int j=0; j<N; j++)
			in >> array[j];
			
		out << insertionSort(array, N) << endl;
	}
	
	in.close();
	out.close();
	
	return 0;
}
