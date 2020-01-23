#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");



template <typename T> class Node
{
private:
	T key;
	Node<T> *parent, *left, *right;
	int mul;							//molteplicità
	
public:
	Node(T key)
	{
		mul = 1;
		this->key = key;
		parent = left = right = NULL;
	}
	
	void setMul(int mul) { this->mul = mul; }
	int getMul() { return mul; }
	
	T getKey() const { return key; }
	Node<T>* getParent() const { return parent; }
	Node<T>* getLeft() const { return left; }
	Node<T>* getRight() const { return right; }
	
	
	void setKey(T key) { this->key = key; }
	void setParent(Node<T> *parent) { this->parent = parent; }
	void setRight(Node<T> *right) { this->right = right; }
	void setLeft(Node<T> *left) { this->left = left; }
};


template <typename K> class BST
{
private:
	int n;
	Node<K> *root;
	
	void aux_inorder(Node<K> *node, ofstream &out)			//versione modificata per la molteplicità
	{
		if(node)
		{
			aux_inorder(node->getLeft(), out);
			for(int l=0; l<node->getMul(); l++)
				out << node->getKey() << " ";
			aux_inorder(node->getRight(), out);
		}
	}
	
	void aux_preorder(Node<K> *node, ofstream &out)			//versione modificata per la molteplicità
	{
		if(node)
		{
			for(int l=0; l<node->getMul(); l++)
				out << node->getKey() << " ";
			aux_preorder(node->getLeft(), out);
			aux_preorder(node->getRight(), out);
		}
	}
	
	void aux_postorder(Node<K> *node, ofstream &out)		//versione modificata per la molteplicità
	{
		if(node)
		{
			aux_postorder(node->getLeft(), out);
			aux_postorder(node->getRight(), out);
			
			for(int l=0; l<node->getMul(); l++)
				out << node->getKey() << " ";
		}
	}

public:
	BST()
	{
		n = 0;
		root = NULL;
	}
	
	Node<K>* getRoot() { return root; }
	
	void inorder(ofstream &out) { aux_inorder(root, out); }
	void preorder(ofstream &out) { aux_preorder(root, out); }
	void postorder(ofstream &out) { aux_postorder(root, out); }
	
	
	void insert(K key)
	{
		Node<K> *c = search(root, key);
		
		//ATTENZIONE, NOVITÀ
		if(c != NULL)
		{
			int inc = c->getMul();
			inc++;
			c->setMul(inc);
			return;
		}
			
		
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
	
	void canc(Node<K> *x, K key)
	{
		Node<K> *temp = search(x, key);
		if(temp == NULL)
			return;
			
		if(temp->getMul() > 1)
		{
			temp->setMul(temp->getMul() - 1);
			return;
		}
		
		Node<K> *parent = temp->getParent();
		if(!temp->getLeft() || !temp->getRight())
		{
			n--;
			temp->setMul(0);
			
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
			Node<K> *succ = this->getSuccessor(temp->getKey());
			temp->setKey(succ->getKey());
			canc(temp->getRight(), succ->getKey());
		}
		
	}
	
	Node<K>* getSuccessor(K key)
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
				return parent;
			else
				return NULL;
		}
		
		return NULL;
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
	
	
	Node<K>* minimo(Node<K> *node)
	{
		if(node)	
		{
			while(node->getLeft())
				node = node->getLeft();
		}
		
		if(node)
			return node;
		else
			return NULL;
	}
	
};


int main()
{
	string data_type, operation, visit_type;
	int N;
	
	for(int i=0; i<100; i++)
	{
		in >> data_type >> N >> visit_type;
		
		if(data_type == "int")
		{
			BST<int> myBST;
			
			for(int j=0; j<N; j++)			//ciclo sulle operazioni
			{
				in >> operation;
				if(operation[0] == 'i')
				{
					operation = operation.substr(4);
					myBST.insert(atoi(operation.c_str()));
				}
				
				else
				{
					operation = operation.substr(5);
					myBST.canc(myBST.getRoot(), atoi(operation.c_str()));
				}
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			
			if(visit_type == "preorder")
				myBST.preorder(out);
			
			if(visit_type == "postorder")
				myBST.postorder(out);
			
			out << endl;
		}
		
		
		
		
		
		
		if(data_type == "double")
		{
			BST<double> myBST;
			
			for(int j=0; j<N; j++)			//ciclo sulle operazioni
			{
				in >> operation;
				if(operation[0] == 'i')
				{
					operation = operation.substr(4);
					myBST.insert(atof(operation.c_str()));
				}
				
				else
				{
					operation = operation.substr(5);
					myBST.canc(myBST.getRoot(), atof(operation.c_str()));
				}
			}
			
			if(visit_type == "inorder")
				myBST.inorder(out);
			
			if(visit_type == "preorder")
				myBST.preorder(out);
			
			if(visit_type == "postorder")
				myBST.postorder(out);
				
			out << endl;
		}
		
	}
	
	in.close();
	out.close();
	
	return 0;
}
