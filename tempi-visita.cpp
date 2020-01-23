#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


#define WHITE 0
#define GRAY 1
#define BLACK 2

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
	
	Node<L>* getTrailer() { return trailer; }
	
	Node<L>* getHeader() { return header; }
	
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
	
	/*Node<L>* getFirstNode() 
	{ 
		if(header->getNext() != trailer)
			return header->getNext(); 
		else
			return NULL;
	}*/
	
	void reset() { current = header; }
	
	
};


template <typename G> class Graph
{
private:
	int n;
	int time;
	DLinkedList<G> *adjL;						//array delle liste di adiacenza
	G *keys;
	int indexK;
	int *color, *pred, *d, *f;					

public:
	Graph(int n)
	{
		this->n = n;							//numero di chiavi
		adjL = new DLinkedList<G>[n];			//inizializza un array con n liste singolarmente concatenate
		keys = new G[n];
		indexK = 0;
		
		color = new int[n];
		pred = new int[n];
		d = new int[n];
		f = new int[n];
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
	
	void DFS()
	{
		for(int i=0; i<n; i++)
		{
			color[i] = WHITE;
			pred[i] = -1;
		}
		
		time = 0;
		
		for(int i=0; i<n; i++)
			if(color[i] == WHITE)
				DFS_visit(i);
	}
	
	void DFS_visit(int i)
	{
		color[i] = GRAY;
		d[i] = time++;
		
		adjL[i].reset();
		Node<G> *l = adjL[i].getHeader();
		
		int j;
		/*while(l != NULL)*/for(int k=0; k<adjL[i].getNNodes(); k++)
		{
			l = l->getNext();
			if(l != NULL || l != adjL[i].getTrailer())
			{
				j = findIndex(l->getKey());
				if(color[j] == WHITE)
				{
					pred[j] = i;
					DFS_visit(j);
				}
			}
			
		}
		
		color[i] = BLACK;
		f[i] = time++;
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
			
			for(int k=0; k<number; k++)
			{
				node = adjL[i].next();
				out << "," << node->getKey();
			}
			
			out << ") ";
		}
		
	}
	
	void printDFS(ofstream &out)
	{
		for(int i=0; i<n; i++)
		{
			out << "(" << keys[i] << "," << d[i] << "," << f[i] << ") ";
		}
	}
	
	
};






int main()
{
	int N, M;
	string type, operazione;
	
	int aux_int1, aux_int2;
	double aux_double1, aux_double2;
	char aux_char1, aux_char2;
	
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
			
			myG.DFS();
			myG.printDFS(out);
			out << endl;
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
			
			myG.DFS();
			myG.printDFS(out);
			out << endl;
		}
		
		
		if(type == "char")
		{
			Graph<char> myG(N);
			
			for(int j=0; j<N; j++)				//inserimento chiavi
			{
				in >> aux_char1;
				myG.insertKey(aux_char1);	
			}
			
			myG.selectionSort();
			
			for(int k=0; k<M; k++)			//inserimento archi
			{
				in >> operazione;
				aux_char1 = operazione[1];
				
				
				in >> operazione;
				aux_char2 = operazione[0];
				
				myG.insertEdge(aux_char1, aux_char2);
			}
			
			myG.DFS();
			myG.printDFS(out);
			out << endl;
		}
		
		
	}
	
	in.close();
	out.close();
	
	return 0;
}
