#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <typename T> class Node
{
private:
	T key;
	Node<T> *parent, *left, *right;
	
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
	
	T getKey() const { return key; }
	Node<T>* getParent() const { return parent; }
	Node<T>* getLeft() const { return left; }
	Node<T>* getRight() const { return right; }
	
};




template <typename K> class BST
{
private:
	int n;
	Node<K> *root;
	
	void aux_inorder(Node<K> *node, ofstream &out)
	{
		aux_inorder(node->getLeft(), out);
		out << node->getKey() << " ";
		aux_inorder(node->getRight(), out);
	}
	
	void aux_preorder(Node<K> *node, ofstream &out)
	{
		out << node->getKey() << " ";
		aux_inorder(node->getLeft(), out);
		aux_inorder(node->getRight(), out);
	}
	
	
	void aux_postorder(Node<K> *node, ofstream &out)
	{
		aux_inorder(node->getLeft(), out);
		aux_inorder(node->getRight(), out);
		out << node->getKey() << " ";
	}
	

public:
	BST()
	{
		n = 0;
		root = NULL;
	}
	
	Node<K>* getRoot() { return root; }
	
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
	
	K getSuccessor(K key)
	{
		Node<K> *temp_node = search(root, key);
		if(temp_node)
		{
			if(temp_node->getRight())
				return minimo(temp_node->getRight());
			
			Node<K> *parent = temp_node->getParent();
			while(parent != NULL && temp_node == parent->getRight())
			{
				temp_node = parent;
				parent = parent->getParent();
			}
			
			if(parent)
				return parent->getKey();
			else
				return -1;
		}
	}
	
	
	K getPredecessor(K key)
	{
		Node<K> *temp_node = search(root, key);
		if(temp_node)
		{
			if(temp_node->getLeft())
				return massimo(temp_node->getLeft());
			
			Node<K> *parent = temp_node->getParent();
			while(parent != NULL && temp_node == parent->getLeft())
			{
				temp_node = parent;
				parent = parent->getParent();
			}
			
			if(parent)
				return parent->getKey();
			else
				return -1;
		}
	}
	
	
	
	void inorder(ofstream &out) { aux_inorder(root, out); }
	void preorder(ofstream &out) { aux_preorder(root, out); }
	void postorder(ofstream &out) { aux_postorder(root, out); }
	
	unsigned int getLeafNumber(Node<K> *node)
	{
		if(node == NULL)
			return 0;
		if(node->getLeft() == NULL && node->getRight() == NULL)
			return 1;
		else
			return getLeafNumber(node->getLeft()) + getLeafNumber(node->getRight());
	}
	
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
	
	Node<K>* search(Node<K> *node, K key)
	{
		if(node == NULL || node->getKey() == key)
			return node;
		if(key > node->getKey())
			search(node->getRight(), key);
		else
			search(node->getLeft(), key);
	}
	
	void canc(Node<K> *x, K key)
	{
		Node<K> *temp = search(x, key);
		if(temp == NULL)
			return;
		
		Node<K> *parent = temp->getParent();
		if(!temp->getLeft() || !temp->getRight())
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
		
		else
		{
			K next = this->getSuccessor(temp->getKey());
			Node<K> *succ = new Node<K>(next);
			temp->setKey(succ->getKey());
			canc(temp->getRight(), succ->getKey());
		}
		
	}
};

int main()
{
	string data_type, operation;
	int N, M;
	
	int aux_int;
	double aux_double;
	
	string appoggio;
	
	
	for(int i=0; i<100; i++)
	{
		in >> data_type >> N >> M;
		
		if(data_type == "int")
		{
			BST<int> myBST;
			int isucc[M];
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc") 
				{
					operation = operation.substr(5);
					aux_int = atoi(operation.c_str());
					myBST.canc(myBST.getRoot(), aux_int);
				}
				
				else
				{
					operation = operation.substr(4);
					aux_int = atoi(operation.c_str());
					myBST.insert(aux_int);
				}
			}
			
			for(int k=0; k<M; k++)		//leggiamo da file, lo mettiamo nell'array e ne stampiamo il successore
			{
				in >> appoggio;
				isucc[k] = atoi(appoggio.c_str());
				
				out << myBST.getSuccessor(isucc[k]) << " ";
			}
			
			out << endl;
		}
		
		
		
		if(data_type == "double")
		{
			BST<double> myBST;
			double dsucc[M];
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation.substr(0, 4) == "canc")
				{
					operation = operation.substr(5);
					aux_double = atof(operation.c_str());
					myBST.canc(myBST.getRoot(), aux_double);
				}
				
				else
				{
					operation = operation.substr(4);
					aux_double = atof(operation.c_str());
					myBST.insert(aux_double);
				}
			}
			
			for(int k=0; k<M; k++)		//leggiamo da file, lo mettiamo nell'array e ne stampiamo il successore
			{
				in >> appoggio;
				dsucc[k] = atof(appoggio.c_str());
				
				out << myBST.getSuccessor(dsucc[k]) << " ";
			}
			
			out << endl;
		}
		
		
	}
	

	
	return 0;
}
