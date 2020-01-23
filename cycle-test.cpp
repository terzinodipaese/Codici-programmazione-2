#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


#define WHITE 0
#define GRAY 1
#define BLACK 2


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
	int time;
	
	int *color, *pred, *d, *f;

public:
	Graph(int n)
	{
		this->n = n;
		keys = new T[n];
		adjM = new bool*[n];
		
		color = new int[n];
		pred = new int[n];
		d = new int[n];
		f = new int[n];
		
		indexK = 0;
		
		for(int i=0; i<n; i++)
			adjM[i] = new bool[n];
			
		for(int j=0; j<n; j++)
			for(int l=0; l<n; l++)
				adjM[j][l] = false;
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
		
		adjM[index1][index2] = true;
	}
	
	void selectionSort()
	{
		int min; 
		
		for(int i=0; i<n; i++)
		{
			min = i;
			for(int j=i+1; j<n; j++)
				if(keys[j] < keys[min])
					min = j;
			
			T temp = keys[i];
			keys[i] = keys[min];
			keys[min] = temp;
		}
	}
	
	int DFS()
	{
		time = 0;
		int cycle = 0;
		
		for(int i=0; i<n; i++)
		{
			color[i] = WHITE;
			pred[i] = -1;
		}
		
		for(int i=0; i<n; i++)
			if(color[i] == WHITE)
				cycle += DFS_visit(i);
				
		return cycle;
	}
	
	
	int DFS_visit(int v)
	{
		int cycle = 0;
		color[v] = GRAY;
		d[v] = time++;
		
		for(int u=0; u<n; u++)
		{
			if(adjM[v][u] == true)
			{
				if(color[u] == WHITE)
					cycle += DFS_visit(u);
				else if(color[u] == GRAY)
					cycle++;		
			}
		}
		
		f[v] = time++;
		color[v] = BLACK;
		return cycle;
	}
	
	
};




int main()
{
	int N, M;
	string type, operazione;
	
	int aux_int1, aux_int2;
	char aux_char1, aux_char2;
	double aux_double2, aux_double1;
	
	
	
	for(int i=0; i<100; i++)
	{
		in >> N >> M >> type;
		
		if(type == "int")
		{
			Graph<int> myG(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_int1;
				myG.insertKey(aux_int1);
			}
			
			myG.selectionSort();
			
			for(int k=0; k<M; k++)
			{
				in >> operazione;
				operazione = operazione.substr(1);
				aux_int1 = atoi(operazione.c_str());
				
				in >> operazione;
				int len = operazione.length();
				operazione = operazione.substr(0, len-1);
				aux_int2 = atoi(operazione.c_str());
				
				myG.insertEdge(aux_int1, aux_int2);
			}
			
			out << myG.DFS() << endl;
		}
		
		
		
		
		if(type == "double")
		{
			Graph<double> myG(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_double1;
				myG.insertKey(aux_double1);
			}
			
			myG.selectionSort();
			
			for(int k=0; k<M; k++)
			{
				in >> operazione;
				operazione = operazione.substr(1);
				aux_double1 = atof(operazione.c_str());
				
				in >> operazione;
				int len = operazione.length();
				operazione = operazione.substr(0, len-1);
				aux_double2 = atof(operazione.c_str());
				
				myG.insertEdge(aux_double1, aux_double2);
			}
			
			out << myG.DFS() << endl;
		}
		
		
		
		if(type == "char")
		{
			Graph<char> myG(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_char1;
				myG.insertKey(aux_char1);
			}
			
			myG.selectionSort();
			
			for(int k=0; k<M; k++)
			{
				in >> operazione;
				aux_char1 = operazione[1];
				
				
				in >> operazione;
				aux_char2 = operazione[0];
				
				myG.insertEdge(aux_char1, aux_char2);
			}
			
			out << myG.DFS() << endl;
		}
		
	}
	
	
	
	in.close();
	out.close();
	
	
	return 0;
}









