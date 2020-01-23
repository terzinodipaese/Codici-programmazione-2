#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class Graph
{
private:
	bool **adjM;
	T *keys;
	int n;
	int indexK;
	
public:
	Graph(int n)
	{
		indexK = 0;
		
		this->n = n;
		keys = new T[n];
		
		adjM = new bool*[n];
		
		for(int i=0; i<n; i++)
			adjM[i] = new bool[n];
			
		for(int i=0; i<n; i++)
			for(int g=0; g<n; g++)
				adjM[i][g] = false;
	}
	
	void insertKey(T key)
	{
		if(indexK < n)
		{
			keys[indexK] = key;
			indexK++;
			return;
		}
		
		return;
	}
	
	int findIndex(T key)
	{
		for(int i=0; i<n; i++)
			if(keys[i] == key)
				return i;
		
		return -1;
	}
	
	void insertEdge(T key1, T key2)
	{
		int index1 = findIndex(key1);
		int index2 = findIndex(key2);
		
		if(index1 == -1 || index2 == -1)
			return;
		
		else
			adjM[index1][index2] = true;
	}
	
	T* getKeysArray() { return keys; }
	
	void printEdges(ofstream &out)
	{
		for(int row=0; row<n; row++)
		{
			out << "(" << keys[row];
			for(int col=0; col<n; col++)
			{
				if(adjM[row][col] == true)
					out << "," << keys[col];
			}
			
			out << ") ";
		}
	}
	
	
	void selectionSort()
	{
		for(int i=0; i<n; i++)
		{
			int min = i;
			for(int j=i+1; j<n; j++)
			{
				if(keys[j] < keys[min])
					min = j;
			}
			
			T temp = keys[min];
			keys[min] = keys[i];
			keys[i] = temp;
		}
	}
	
};





int main()
{
	char c;
	string data_type, operation1, operation2;
	int N, M;
	
	int aux_int1, aux_int2;
	double aux_double1;
	char aux_char1, aux_char2;
	

	for(int i=0; i<100; i++)				//ciclo sulle righe
	{
		in >> N >> M >> data_type;
		
		if(data_type == "int")
		{
			Graph<int> myG(N);
			
			for(int i=0; i<N; i++)			//ciclo sugli inserimenti delle chiavi
			{
				in >> aux_int1;
				myG.insertKey(aux_int1);
			}
			
			myG.selectionSort();			//ordina l'array delle chiavi
			
			for(int i=0; i<M; i++)			//ciclo sugli inserimenti degli archi
			{
				in >> c;
				in >> aux_int1;
				
				in >> operation1;
				int length = operation1.length();
				operation1 = operation1.substr(0, length-1);
				aux_int2 = atoi(operation1.c_str());
				
				myG.insertEdge(aux_int1, aux_int2);
			}
			
			myG.printEdges(out);
			out << endl;
		}
		
		
		
		
		
		if(data_type == "double")
		{
			Graph<double> myG(N);
			
			for(int i=0; i<N; i++)			//ciclo sugli inserimenti delle chiavi
			{
				in >> aux_double1;
				myG.insertKey(aux_double1);
			}
			
			myG.selectionSort();			//ordina l'array delle chiavi
			
			for(int i=0; i<M; i++)			//ciclo sugli inserimenti degli archi
			{
				in >> c;
				in >> aux_double1;
				
				
				in >> operation2;
				int len = operation2.length();
				operation2 = operation2.substr(0, len-1);
				
				myG.insertEdge(aux_double1, atof(operation2.c_str()));
			}
			
			myG.printEdges(out);
			out << endl;
		}
		
		
		
		
		
		if(data_type == "char")
		{
			Graph<char> myG(N);
			
			for(int i=0; i<N; i++)			//ciclo sugli inserimenti delle chiavi
			{
				in >> aux_char1;
				myG.insertKey(aux_char1);
			}
			
			myG.selectionSort();			//ordina l'array delle chiavi
			
			for(int i=0; i<M; i++)			//ciclo sugli inserimenti degli archi
			{
				in >> operation1;
				aux_char1 = operation1[1];
				
				in >> operation1;
				aux_char2 = operation1[0];
				
				myG.insertEdge(aux_char1, aux_char2);
			}
			
			myG.printEdges(out);
			out << endl;
		}
		
	}
	
	
	in.close();
	out.close();
	
	return 0;
}
