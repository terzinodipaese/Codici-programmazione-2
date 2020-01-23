#include <iostream>
#include <fstream>

using namespace std;


template <typename T> class Node
{
	private:
		T key;                           //chiave
		Node<T> *left, *right, *parent;  //puntatori a sottoalbero sinistro, destro e genitore, rispettivamente
	
	public:
		Node(T key)
		{
			this->key = key;
			left = parent = right = NULL;	
		}
		
		void setKey(T key) { this->key = key; }
		void setLeft(Node<T> *left) { this->left = left; }
		void setRight(Node<T> *right) { this->right = right; }
		void setParent(Node<T> *parent) { this->parent = parent; } 
		
		T getKey() { return key; }
		Node<T>* getLeft() { return left; }
		Node<T>* getRight() { return right; }
		Node<T>* getParent() { return parent; }
};



template <typename H> class BST
{
	private:
		int n; //numero di nodi
		Node<H>* root;
		
		//funzioni di visita ausiliarie
		
		void aux_inorder(Node<H> *x, ofstream &out)    		//variante per stampare direttamente su file
		{
			if(x)
			{
				aux_inorder(x->getLeft(), out);
				out << x->getKey() << " ";
				aux_inorder(x->getRight(), out);
			}
		}
		
		void aux_preorder(Node<H> *x, ofstream &out)		//variante per stampare direttamente su file
		{
			if(x)
			{
				out << x->getKey() << " ";
				aux_preorder(x->getLeft(), out);
				aux_preorder(x->getRight(), out);
			}
		}
		
		void aux_postorder(Node<H> *x, ofstream &out)	//variante per stampare direttamente su file
		{
			if(x)
			{
				aux_postorder(x->getLeft(), out);
				aux_postorder(x->getRight(), out);
				out << x->getKey() << " ";
			}
		}
	
	public:
		BST()
		{
			n = 0;      	//all'inizio ha 0 nodi
			root = NULL;    //la radice è uguale a NULL, infatti non c'è nessun nodo
		}
		
		void insert(H element)
		{
			/* Nella prima parte della funzione si cerca il parent in base alla chiave, dopo se parent è NULL allora il nuovo nodo
			 * è la radice, in ogn caso verrà settato setLeft o setRight in base alla chiave del nuovo nodo
			 * e del parent, dopodicchè si crea il collegamento setParent, che tra l'altro è unico 
			 * in un BST.
			 */
			
			
			Node<H>* node = root;   //node punta alla radice, contiene l'indirizzo di memoria della radice
			Node<H>* parent = NULL;
			
			while(node != NULL)    			//finchè node punta a qualcosa
			{
				parent = node;      		//imposta il parent
				if(element > node->getKey())
					node = node->getRight();
				else
					node = node->getLeft();
			}
			
			Node<H>* newnode = new Node<H>(element);    //crea il nuovo nodo
			n++;     //tiene il conto dei nodi
			
			if(parent == NULL)   //in questo caso l'albero era vuoto
			{
				root = newnode;
				return;			//questo è quello che evita segmentation fault, IMPORTANTE!!!
			}
			
			if(element <= parent->getKey())
				parent->setLeft(newnode);
			else
				parent->setRight(newnode);
			
			newnode->setParent(parent);
		}
		
		void inorder(ofstream &out)
		{
			aux_inorder(root, out);
		}
		
		void postorder(ofstream &out)
		{
			aux_postorder(root, out);
		}
		
		void preorder(ofstream &out)
		{
			aux_preorder(root, out);
		}
};


int main()
{
	string data_type, visit_type;       //tipo di dato può essere bool, int, char, double
	int N;								//numero di elementi da inserire
	//variabili d'appoggio
	int intero;
	char carattere;
	bool booleano;
	double virgola;			
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	for(int i=0; i<100; i++)  //ciclo per le righe
	{
		in >> data_type >> N >> visit_type;
		
		if(data_type == "int")
		{
			BST<int> albero;
			for(int j=0; j<N; j++)    //inserimento nodi
			{
				in >> intero;
				albero.insert(intero);
			}
			
			if(visit_type == "inorder")
				albero.inorder(out);
			if(visit_type == "preorder")
				albero.preorder(out);
			if(visit_type == "postorder")
				albero.postorder(out);	
		}
		
		if(data_type == "char")
		{
			BST<char> albero;
			for(int j=0; j<N; j++)
			{
				in >> carattere;
				albero.insert(carattere);
			}
			
			if(visit_type == "inorder")
				albero.inorder(out);
			if(visit_type == "preorder")
				albero.preorder(out);
			if(visit_type == "postorder")
				albero.postorder(out);
		}
		
		if(data_type == "double")
		{
			BST<double> albero;
			for(int j=0; j<N; j++)
			{
				in >> virgola;
				albero.insert(virgola);
			}
			
			if(visit_type == "inorder")
				albero.inorder(out);
			if(visit_type == "preorder")
				albero.preorder(out);
			if(visit_type == "postorder")
				albero.postorder(out);
		}
		
		if(data_type == "bool")
		{
			BST<bool> albero;
			for(int j=0; j<N; j++)
			{
				in >> booleano;
				albero.insert(booleano);
			}
			
			if(visit_type == "inorder")
				albero.inorder(out);
			if(visit_type == "preorder")
				albero.preorder(out);
			if(visit_type == "postorder")
				albero.postorder(out);
		}
		
		out << endl;
		
	}
	
	in.close();
	out.close();
	
	return 0;
}









