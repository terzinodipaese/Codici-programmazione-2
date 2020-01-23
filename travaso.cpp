#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");



template <typename B> class Queue
{
private:
	B *array;
	int head, tail, size;
	
public:
	
	Queue(int size = 200)
	{
		this->size = size;
		array = new B[size];
		
		head = tail = 0;
	}
	
	
	bool isEmpty() { return tail == head; }
	
	bool isFull() { return (head == 0 && tail == size) || (head == tail+1); }
	
	void enqueue(B element)
	{
		if(isFull() == true)
			return;
		
		if(tail == size)
			tail = 0;
		
		array[tail] = element;
		
		if(tail == size)
			tail = 0;
		else if(head != tail+1)
			tail++;
	}
	
	
	B dequeue()
	{
		if(isEmpty() == true)
			return -1;
		
		B temp = array[head];
		
		if(head == size)
			head = 0;
		else
			head++;
		
		return temp;
	}
	
};






template <typename T> class Stack
{
private:
	T *array;
	int top, size;

public:
	Stack(int size = 200)
	{
		this->size = size;
		array = new T[size];
		top = -1;
	}
	
	bool isEmpty() { return top == -1; }
	
	void push(T element)
	{
		if(top < size-1)			//condizione che segnala se la pila è piena o meno
		{
			top++;
			array[top] = element;
		}
		
		else
			return;			
	}

	T pop()
	{
		if(top == -1)		//serve a controllare se la pila è vuota o meno
			return -1;
		
		else
		{
			top--;
			return array[top+1];
		}
	}	
	
	
	void travaso(Queue<T> *myQ)
	{
		while(this->isEmpty() == false)
			myQ->enqueue(this->pop());
	}
};



int main()
{
	string data_type, operation;
	int N;
	
	int aux_int;
	double aux_double;
	bool aux_bool;
	char aux_char;
	
	
	for(int i=0; i<100; i++)
	{
		in >> data_type >> N;
		
		if(data_type == "int")
		{
			Queue<int> myQ;
			Stack<int> myS;
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation == "travasa")
					myS.travaso(&myQ);
				
				if(operation == "dequeue")
					myQ.dequeue();
				
				if(operation == "pop")
					myS.pop();
				
				if(operation[0] == 'e')
				{
					operation = operation.substr(2);
					aux_int = atoi(operation.c_str());
					myQ.enqueue(aux_int);
				}
				
				if(operation.substr(0, 2) == "p:")
				{
					operation = operation.substr(2);
					aux_int = atoi(operation.c_str());
					myS.push(aux_int);
				}
			}
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
			
			out << endl;
		}
		
		
		
		
		if(data_type == "double")
		{
			Queue<double> myQ;
			Stack<double> myS;
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation == "travasa")
					myS.travaso(&myQ);
				
				if(operation == "dequeue")
					myQ.dequeue();
				
				if(operation == "pop")
					myS.pop();
				
				if(operation[0] == 'e')
				{
					operation = operation.substr(2);
					aux_double = atof(operation.c_str());
					myQ.enqueue(aux_double);
				}
				
				if(operation.substr(0, 2) == "p:")
				{
					operation = operation.substr(2);
					aux_double = atof(operation.c_str());
					myS.push(aux_double);
				}
			}
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
			
			out << endl;
		}
		
		
		
		
		
		if(data_type == "bool")
		{
			Queue<bool> myQ;
			Stack<bool> myS;
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation == "travasa")
					myS.travaso(&myQ);
				
				if(operation == "dequeue")
					myQ.dequeue();
				
				if(operation == "pop")
					myS.pop();
				
				if(operation[0] == 'e')
				{
					operation = operation.substr(2);
					aux_bool = atoi(operation.c_str());
					myQ.enqueue(aux_bool);
				}
				
				if(operation.substr(0, 2) == "p:")
				{
					operation = operation.substr(2);
					aux_bool = atoi(operation.c_str());
					myS.push(aux_bool);
				}
			}
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
			
			out << endl;
		}
		
		
		
		
		if(data_type == "char")
		{
			Queue<char> myQ;
			Stack<char> myS;
			
			for(int j=0; j<N; j++)
			{
				in >> operation;
				
				if(operation == "travasa")
					myS.travaso(&myQ);
				
				if(operation == "dequeue")
					myQ.dequeue();
				
				if(operation == "pop")
					myS.pop();
				
				if(operation[0] == 'e')
				{
					aux_char = operation[2];
					myQ.enqueue(aux_char);
				}
				
				if(operation.substr(0, 2) == "p:")
				{
					aux_char = operation[2];
					myS.push(aux_char);
				}
			}
			
			while(!myQ.isEmpty())
				out << myQ.dequeue() << " ";
			
			out << endl;
		}
	}
	
	
	
	in.close();
	out.close();
	
	
	
	return 0;
}



