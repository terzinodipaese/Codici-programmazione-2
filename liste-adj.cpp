#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


template <typename N> class Node
{
private:
	N key;
	Node<N> *next, *prev;
	
public:
	Node(N key)
	{
		this->key = key;
		prev = next = NULL;
	}
	
	Node()
	{
		prev = next = NULL;
	}
	
	void setNext(Node<N> *node) { next = node; }
	void setKey(N key) { this->key = key; }
	void setPrev(Node<N> *node) { prev = node; }
	
	N getKey() { return key; }
	Node<N>* getNext() { return next; }
	Node<N>* getPrev() { return prev; }
};

template <typename L> class DLinkedList
{
private:
	Node<L> *header, *trailer, *current;		//current è l'iteratore
	int nNodes;

public:
	DLinkedList()
	{
		nNodes = 0;
		
		header = new Node<L>;
		trailer = new Node<L>;
		
		header->setNext(trailer);
		header->setPrev(NULL);
		trailer->setPrev(header);
		trailer->setNext(NULL);
		
		current = header;
	}
	
	int getNNodes() { return nNodes; }
	
	void insert(L key)
	{
		nNodes++;
		Node<L> *node = new Node<L>(key);						//nodo con la chiave da inserire
		
		Node<L> *succ = header->getNext();						//serve a trovare il successore
		
		while((succ != trailer) && (succ->getKey() < node->getKey()))
			succ = succ->getNext();
		
		Node<L> *prev = succ->getPrev();
		
		node->setPrev(prev);
		node->setNext(succ);
		succ->setPrev(node);
		prev->setNext(node);
	}
	
	
	bool isEmpty() { return header->getNext() == trailer; }
	
	Node<L>* next()
	{
		if(current != NULL)
		{
			current = current->getNext();
			
			if(current != trailer)
				return current;
			
			return NULL;
		}
		
		return NULL;
	}
	
	
	void reset() { current = header; }
	

};


template <typename G> class Graph
{
private:
	int n;
	DLinkedList<G> *adjL;						//array delle liste di adiacenza
	G *keys;
	int indexK;

public:
	Graph(int n)
	{
		this->n = n;							//numero di chiavi
		adjL = new DLinkedList<G>[n];			//inizializza un array con n liste singolarmente concatenate
		keys = new G[n];
		indexK = 0;
	}
	
	void insertKey(G key)
	{
		if(indexK < n)
		{
			keys[indexK] = key;
			indexK++;
			return;
		}
		
		return;
	}
	
	int findIndex(G key)
	{
		for(int i=0; i<n; i++)
		{
			if(keys[i] == key)
				return i;
		}
		
		return -1;
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
			
			G temp = keys[i];
			keys[i] = keys[min];
			keys[min] = temp;
		}
	}

	
	void insertEdge(G key1, G key2)
	{
		int index1 = findIndex(key1);
		
		if(index1 == -1)
			return;
		else
			adjL[index1].insert(key2);
	}
	
	
	
	void printEdges(ofstream &out)
	{
		for(int i=0; i<n; i++)				//ciclo sul numero di liste di adiacenza
		{
			out << "(" << keys[i];
			
			adjL[i].reset();				//iteratore
			
			Node<G> *node = NULL;
			
			int number = adjL[i].getNNodes();
			
			//ciclo sulla lista di adiacenza
			for(int k=0; k<number; k++)
			{
				node = adjL[i].next();
				out << "," << node->getKey();
			}
			
			out << ") ";
		}
	}
};

int main()
{	
	string type, operation;
	
	int N, M;
	
	int aux_int1, aux_int2;
	char aux_char1, aux_char2;
	double aux_double1, aux_double2;
	
	
	for(int i=0; i<100; i++)
	{
		//leggiamo il numero di nodi e di archi e il tipo di dato
		in >> N >> M >> type;
		
		if(type == "int")
		{
			Graph<int> myG(N);
			
			for(int j=0; j<N; j++)			//ciclo sul numero delle chiavi
			{
				in >> aux_int1;
				myG.insertKey(aux_int1);
			}
			
			myG.selectionSort();				//ordiniamo le chiavi
			
			for(int y=0; y<M; y++)			//ciclo sul numero degli archi
			{
				in >> operation;
				operation = operation.substr(1);
				aux_int1 = atoi(operation.c_str());
				
				
				in >> operation;
				int len = operation.length();
				operation = operation.substr(0, len-1);
				aux_int2 = atoi(operation.c_str());
				
				myG.insertEdge(aux_int1, aux_int2);
			}
			
			myG.printEdges(out);
			out << endl;
		}
		
		
		
		
		
		
		if(type == "double")
		{
			Graph<double> myG(N);
			
			for(int j=0; j<N; j++)			//ciclo sul numero delle chiavi
			{
				in >> aux_double1;
				myG.insertKey(aux_double1);
			}
			
			myG.selectionSort();			//ordiniamo le chiavi
			
			for(int y=0; y<M; y++)			//ciclo sul numero degli archi
			{
				in >> operation;
				operation = operation.substr(1);
				aux_double1 = atof(operation.c_str());
				
				
				in >> operation;
				int len = operation.length();
				operation = operation.substr(0, len-1);
				aux_double2 = atof(operation.c_str());
				
				myG.insertEdge(aux_double1, aux_double2);
			}
			
			myG.printEdges(out);
			out << endl;
		}
		
		
		
		
		
		
		
		if(type == "char")
		{
			Graph<char> myG(N);
			
			for(int j=0; j<N; j++)			//ciclo sul numero delle chiavi
			{
				in >> aux_char1;
				myG.insertKey(aux_char1);
			}
			
			myG.selectionSort();				//ordiniamo le chiavi
			
			for(int y=0; y<M; y++)			//ciclo sul numero degli archi
			{
				in >> operation;
				aux_char1 = operation[1];
				
				
				in >> operation;
				aux_char2 = operation[0];
				
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
