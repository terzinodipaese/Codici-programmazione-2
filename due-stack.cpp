/* Implementazione di una coda 
 * con due pile: esercizio due-stack
 */


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>


using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class Stack
{
private:
	T *array;
	int top, size;		//top: puntatore all'elemento più in alto
							//size: massimo numero di elementi inseribili
							//n: numero di elementi effettivamente presenti nella pila

public:
	Stack(int size = 200)
	{
		this->size = size;
		array = new T[size];
		top = -1;
	}
	
	T pop()
	{
		if(top == -1)		//se la pila è vuota
			return -1;
		
		else
		{
			top--;
			return array[top+1];
		}
	}
	
	
	
	void push(T element)
	{
		if(top < size-1)
		{
			top++;
			array[top] = element;
		}
		
		else
			return;
	}
	
	
	bool isEmpty() { return top == -1; }
	
};





template <typename K> class Queue
{
private:
	Stack<K> *stack1, *stack2;
	
	void moveStack1toStack2()				//sposta tutto il contenuto dello 1o stack nel 2o stack
	{
		while(!stack1->isEmpty())
			stack2->push(stack1->pop());
	}
	
public:
	Queue(int len = 200)
	{
		stack1 = new Stack<K>(len);
		stack2 = new Stack<K>(len);
	}
	
	bool isEmpty() { return stack1->isEmpty() && stack2->isEmpty(); }
	
	
	void enqueue(K element) { stack1->push(element); }
	
	K dequeue()
	{
		if(isEmpty()) return -1;
		
		if(stack2->isEmpty()) moveStack1toStack2();
		
		return stack2->pop();
	}
};




int main()
{
	string data_type, operation;
	int N;
	
	
	int aux_int;
	double aux_double;
	char aux_char;
	bool aux_bool;
	
	
	for(int i=0; i<100; i++)
	{
		in >> data_type >> N;
		
		
		if(data_type == "int")
		{
			Queue<int> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				
				else
				{
					operation = operation.substr(1);
					aux_int = atoi(operation.c_str());
					myQ.enqueue(aux_int);
				}
			}
			
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
		}
		
		
		if(data_type == "double")
		{
			Queue<double> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				
				else
				{
					operation = operation.substr(1);
					aux_double = atof(operation.c_str());
					myQ.enqueue(aux_double);
				}
			}
			
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
		}
		
		
		if(data_type == "bool")
		{
			Queue<bool> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				
				else
				{
					operation = operation.substr(1);
					aux_bool = atoi(operation.c_str());
					myQ.enqueue(aux_bool);
				}
			}
			
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
		}
		
		
		if(data_type == "char")
		{
			Queue<char> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				
				else
				{
					aux_char = operation[1];
					myQ.enqueue(aux_char);
				}
			}
			
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
		}
		
		
		
		out << endl;
		
	}
	
	in.close();
	out.close();
	
	return 0;
}
