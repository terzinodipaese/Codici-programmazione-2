/* NELL'ESERCIZIO C'È SCRITTO CHE I TIPI DI DATO SONO 
 * int, double, bool e char, ma in realtà ci sono solo int e double
 */

#include <iostream>
#include <fstream>
#include <string>			//per le funzione substr
#include <cstdlib>			//per le funzioni atoi, atof e c_str

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");



template <typename T> class Node
{
private:
	T key;
	Node<T> *parent, *right, *left;

public:
	Node(T key)
	{
		this->key = key;
		parent = left = right = NULL;
	}
	
	void setKey(T key) { this->key = key; }
	void setParent(Node<T> *parent) { this->parent = parent; }
	void setLeft(Node<T> *left) { this->left = left; }
	void setRight(Node<T> *right) { this->right = right; }
	
	
	T getKey() { return key; }
	Node<T>* getParent() { return parent; }
	Node<T>* getLeft() { return left; }
	Node<T>* getRight() { return right; }
	
};


template <typename K> class BST
{
private:
	int n;
	Node<K> *root;
	
	
	void aux_inorder(Node<K> *x, ofstream &out)
	{
		if(x)
		{
			aux_inorder(x->getLeft(), out);
			out << x->getKey() << " ";
			aux_inorder(x->getRight(), out);	
		}
	}
	
	void aux_postorder(Node<K> *x, ofstream &out)
	{
		if(x)
		{
			aux_postorder(x->getLeft(), out);
			aux_postorder(x->getRight(), out);
			out << x->getKey() << " ";
		}
	}
	
	void aux_preorder(Node<K> *x, ofstream &out)
	{
		if(x)
		{
			out << x->getKey() << " ";
			aux_preorder(x->getLeft(), out);
			aux_preorder(x->getRight(), out);
		}
	}

public:
	BST()
	{
		n = 0;
		root = NULL;
	}
	
	void inorder(ofstream &out) { aux_inorder(root, out); }
	void preorder(ofstream &out) { aux_preorder(root, out); }
	void postorder(ofstream &out) { aux_postorder(root, out); }	
	
	Node<K>* getRoot() { return root; }
	
	void insert(K key)
	{
		Node<K> *node = root;
		Node<K> *parent = NULL;
		
		while(node != NULL)
		{
			parent = node;
			if(key > node->getKey())
				node = node->getRight();
			else
				node = node->getLeft();
		}
		
		Node<K> *newnode = new Node<K>(key);
		n++;
		
		if(parent == NULL)
		{
			root = newnode;
			return;
		}
		
		newnode->setParent(parent);
		
		if(key <= parent->getKey())
			parent->setLeft(newnode);
		else
			parent->setRight(newnode);
	}
	
	unsigned int getLeafNumber(Node<K> *node)
	{
		if(node == NULL)
			return 0;
		
		if(node->getLeft() == NULL && node->getRight() == NULL)		//caso base
			return 1;
		else
			return getLeafNumber(node->getLeft()) + getLeafNumber(node->getRight());
	}
	
	Node<K>* search(Node<K> *y, K key)
	{
		if(y == NULL || y->getKey() == key)
			return y;
		
		if(key < y->getKey())
			search(y->getLeft(), key);
		else
			search(y->getRight(), key);
	}
	
	K getPredecessor(K key)
	{
		Node<K> *temp_node = search(root, key);
		
		if(temp_node)
		{
			if(temp_node->getLeft())
				return massimo(temp_node->getLeft());
			
			Node<K> *y = temp_node->getParent();
			
			while(y != NULL && temp_node == y->getLeft())
			{
				temp_node = y;
				y = y->getParent();
			}
			
			if(y)
				return y->getKey();
			else
				return -1;
		}
		
		else
			return -1;
	}
	
	K getSuccessor(K key)
	{
		Node<K> *temp_node = search(root, key);
		
		if(temp_node)
		{
			if(temp_node->getRight())					//caso 1, esiste un sottoalbero destro
				return minimo(temp_node->getRight());
			
			//caso 2, non c'è un sottoalbero destro
			Node<K> *y = temp_node->getParent();
			while(y != NULL && temp_node == y->getRight())
			{
				temp_node = y;
				y = y->getParent();
			}
		
			if(y)
				return y->getKey();
			else
				return -1;
		}
		
		else
			return -1;
	}
	
	
	K massimo(Node<K> *node)
	{
		if(node)
		{
			while(node->getRight())
				node = node->getRight();
		}
		
		if(node)
			return node->getKey();
		else
			return -1;
	}
	
	K minimo(Node<K> *node)
	{
		if(node)
		{
			while(node->getLeft())
				node = node->getLeft();
		}
		
		if(node)
			return node->getKey();
		else
			return -1;
	}
	
	
	void canc(Node<K> *x, K key)
	{
		Node<K> *temp = search(x, key);
		if(temp == NULL)
			return;
		
		Node<K> *parent = temp->getParent();
		
		if(!temp->getLeft() || !temp->getRight())		//caso 1 & caso 2: 0 o 1 figlio
		{
			n--;
			Node<K> *son = temp->getRight();
			if(temp->getLeft())
				son = temp->getLeft();
			
			if(!parent)						
				root = son;
			else
			{
				if(temp == parent->getLeft())
					parent->setLeft(son);
				else
					parent->setRight(son);
			}
			
			if(son)
				son->setParent(parent);
		}
		
		else 											//caso 3: 2 figli
		{			
			K next = this->getSuccessor(temp->getKey());				//otteniamo la chiave del successore
			Node<K> *succ = new Node<K>(next);			//creiamo il successore
			temp->setKey(succ->getKey());				//assegnamo al nodo da cancellare la chiave del successore
			canc(temp->getRight(), succ->getKey());		//cancelliamo il nodo che conteneva il successore
		}
	}
	
};



int main()
{
	int N;
	string data_type, visit_type, operation;
	
	char aux_char;
	int aux_int;
	double aux_double;
	bool aux_bool;
	
	for(int i=0; i<100; i++)
	{
		in >> data_type >> N >> visit_type;
		
		if(data_type == "int")
		{
			BST<int> myBST;
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc")
				{
					operation = operation.substr(5);			//estrai la sottostringa che contiene il valore
					aux_int = atoi(operation.c_str());		//trasforma la stringa C++ in stringa C, cioè array di caratteri
															//poi trasforma la stringa in intero
					myBST.canc(myBST.getRoot(), aux_int);					//cancellazione
				}
				
				else
				{
					operation = operation.substr(4);
					aux_int = atoi(operation.c_str());
					myBST.insert(aux_int);
				}	
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			if(visit_type == "preorder")
				myBST.preorder(out);
			if(visit_type == "postorder")
				myBST.postorder(out);
		}
		
		
		if(data_type == "double")
		{
			BST<double> myBST;
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc")
				{
					operation = operation.substr(5);			//estrai la sottostringa che contiene il valore
					aux_double = atof(operation.c_str());		//trasforma la stringa C++ in stringa C, cioè array di caratteri
																//poi trasforma la stringa in double
					myBST.canc(myBST.getRoot(), aux_double);					//cancellazione
				}
				
				else
				{
					operation = operation.substr(4);
					aux_double = atof(operation.c_str());
					myBST.insert(aux_double);
				}	
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			if(visit_type == "preorder")
				myBST.preorder(out);
			if(visit_type == "postorder")
				myBST.postorder(out);
		}
		
		if(data_type == "bool")
		{
			BST<bool> myBST;
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc")
				{
					operation = operation.substr(5);			//estrai la sottostringa che contiene il valore
					aux_bool = atoi(operation.c_str());		//trasforma la stringa C++ in stringa C, cioè array di caratteri
															//poi trasforma la stringa in bool/intero
					myBST.canc(myBST.getRoot(), aux_bool);					//cancellazione
				}
				
				else
				{
					operation = operation.substr(4);
					aux_bool = atoi(operation.c_str());
					myBST.insert(aux_bool);
				}	
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			if(visit_type == "preorder")
				myBST.preorder(out);
			if(visit_type == "postorder")
				myBST.postorder(out);
		}
		
		
		if(data_type == "char")
		{
			BST<char> myBST;
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc")
				{
					aux_char = operation[5];				//estrai la carattere che contiene il valore		
					myBST.canc(myBST.getRoot(), aux_char);					//cancellazione
				}
				
				else
				{
					aux_char = operation[4];
					myBST.insert(aux_char);
				}	
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			if(visit_type == "preorder")
				myBST.preorder(out);
			if(visit_type == "postorder")
				myBST.postorder(out);
		}
		
		
		out << endl;
		
	}
	
	in.close();
	out.close();
	
	return 0;
}







