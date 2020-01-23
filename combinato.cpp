#include <iostream>
#include <fstream>
#define STOP -1


using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");



int succ(int *array, int elem, int ind_lim)		//ritorna l'indice dell'immediato successore, cioè il più piccolo dei più grandi
{
	int index = -1;					//supponiamo che elem non abbia un successore
	int succ = 10001;
	int temp = 10001;
	
	for(int i=0; i<ind_lim; i++)
	{
		if(array[i] > elem)
		{
			temp = array[i];
			
			if(temp < succ)
			{
				succ = temp;
				index = i;
			}
		}
	}
	
	return index;
}


int pred(int *array, int elem, int ind_lim)			//ritorna il più grande dei più piccoli, ind_lim è indice dell'elemento inserito
{
	int index = -1;
	int pred = 0;
	int temp = 0;
	
	for(int i=0; i<ind_lim; i++)
	{
		if(array[i] <= elem)
		{
			temp = array[i];
			if(temp >= pred)
			{
				pred = temp;
				index = i;
			}
		}
	}
	
	return index;
}






class ArrayList
{
private:
	int *K, *N;
	int size, n;
	
public:
	ArrayList(int size = 200)
	{
		this->size = size;
		n = 0;
		K = new int[size];
		N = new int[size];
		
		
	}
	
	int findIndexK(int key)
	{
		for(int i=0; i<size; i++)
			if(K[i] == key)
				return i;
		
		return -1;
	}
	
	int findIndexN(int next)
	{
		for(int i=0; i<size; i++)
			if(N[i] == next)
				return i;
		
		return -1;
	}
	
	void insert(int x)
	{
		K[n] = x;
		N[n] = succ(K, x, n);
		
		if(pred(K, x, n) > -1)
			N[pred(K, x, n)] = n;
		
		n++;
	}
	
	
	void printIndexes(ofstream &out)
	{
		for(int i=0; i<size; i++)
			out << N[i] << " ";
		
		out << endl;
	}
};






int main()
{
	int N, number;
	
	for(int i=0; i<100; i++)
	{
		in >> N;
		ArrayList obj(N);
		
		for(int j=0; j<N; j++)
		{
			in >> number;
			obj.insert(number);
		}
		
		obj.printIndexes(out);
	}
	
	
	
	
	
	
}




