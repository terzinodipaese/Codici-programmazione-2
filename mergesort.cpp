#include <iostream>
#include <fstream>

using namespace std;


ifstream fin("input.txt");
ofstream fout("output.txt");


void Merge(int* a, int left, int center, int right)
{
	int i = left, j = center+1, k = 0;
	int b[right+1];

	while((i<=center) && (j<=right))
	{
		if(a[i] <= a[j])
		{
			b[k] = a[i];
			i++;
		}
		
		else 
		{
			b[k] = a[j];
			j++;
		}
		
		k++;
	}


	while(i <= center)
	{
		b[k] = a[i];
		i++; 
		k++;
	}
	
	
	while(j <= right)
	{
		b[k] = a[j];
		j++; 
		k++;
	}

	for (int t=left; t<=right; ++t, k++)
		a[t] = b[t-left];
}

void MergeSort(int* a, int left, int right, int& s)
{
	int center = (left + right)/2;
	
	if (left<right)
	{
		s += a[left];

		MergeSort(a,left,center,s);
		MergeSort(a,center+1,right,s);
		Merge(a,left,center,right);
	}
}

void MergeSort(int* a, int n, int& s)
{ 
	MergeSort(a, 0, n-1, s);
}

int main()
{
	int N;
	int* a;
	int somma;
	
	for (int count = 0; count < 100; ++count)
	{
		fin >> N;
		//cout<<N<<endl;
		a = new int[N];
		for (int i = 0; i < N; ++i) 
		{
			fin >> a[i];
			//cout<<a[i]<<" ";
		}
		//cout<<endl;
		somma = 0;
		MergeSort(a,N,somma);
		fout << somma << endl;
		//for (int i = 0; i < N; ++i) cout<<a[i]<<" ";
		//cout<<endl<<endl;
		delete[] a;
	}
	
	return 0;
}
