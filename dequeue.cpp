#include <iostream>
#include <fstream>
#include <cstdlib>			//per la funzione atoi
#include <string>			//per la funzione substr
			

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <typename T> class Queue
{
/* Implementazione della coda: - head: indice dell'elemento inserito meno recentemente
 * 							   - tail: indice della prima POSIZIONE LIBERA
 * 							   - array: dove si memorizza fisicamente la roba
 * 							   - max_size: numero massimo di elementi inseribili
 */

private:
	int tail, head;
	T *array;
	int max_size;
	
public:
	Queue(int max_size = 200)
	{
		this->max_size = max_size;
		array = new T[max_size];
		
		tail = head = 0;
	}
	
	bool isEmpty() { return tail == head; }

	
	bool isFull() 
	{
		return (head == 0 && tail == max_size) || (head == tail+1);
	}	
	
	T dequeue()
	{
		if(isEmpty() == true)
		{
			cout << "Empty queue" << endl;
			return -1;
		}
		
		T temp = array[head];
		
		if(head == max_size)
			head = 0;
		else
			head++;
			
		return temp;
	}
	
	void enqueue(T x)
	{
		if(isFull() == true)
		{
			cout << "Full queue" << endl;
			return;
		}
		
		if(tail == max_size)
			tail = 0;
		
		array[tail] = x;
		
		if(tail == max_size)
			tail = 0;
		else if(head != tail+1)
			tail++;
	}
};




int main()
{
	string type;
	int N;
	string operation;	
	
	string aux;
	

	for(int i=0; i<100; i++)
	{	
		in >> type >> N;
		
		int count = 0;
		
		if(type == "int")
		{
			Queue<int> myQ(N);
			
			for(int i=0; i<N; i++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				else
				{
					aux = operation.substr(1);		//estrazione valore
					myQ.enqueue(atoi(aux.c_str()));	//trasformiamo la stringa in array di char, trasformiamo questo in intero, 
													//poi lo incodiamo
					count++;
				}	
			}	
			
			for(int j=0; j<count; j++)		//ciclo di stampa su file
				out << myQ.dequeue() << " ";
		}
		
		
		if(type == "double")
		{
			Queue<double> myQ(N);
			
			for(int i=0; i<N; i++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				else
				{
					aux = operation.substr(1);		//estrazione valore
					myQ.enqueue(atof(aux.c_str()));	//trasformiamo la stringa in array di char, trasformiamo questo in double, 
													//poi lo incodiamo
													
					count++;
				}
			}
			
			for(int j=0; j<count; j++)		//ciclo di stampa su file
				out << myQ.dequeue() << " ";
		}
		
		
		
		if(type == "bool")
		{
			Queue<bool> myQ(N);
			
			for(int i=0; i<N; i++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				else
				{
					aux = operation.substr(1);		//estrazione valore
					myQ.enqueue(atoi(aux.c_str()));	//trasformiamo la stringa in array di char, trasformiamo questo in intero, 
													//poi lo incodiamo
					count++;
				}
			}
			
			for(int j=0; j<count; j++)		//ciclo di stampa su file
				out << myQ.dequeue() << " ";	
		}
		
		
		if(type == "char")
		{
			Queue<char> myQ(N);
			
			for(int i=0; i<N; i++)
			{
				in >> operation;
				if(operation == "dequeue")
					myQ.dequeue();
				else
				{
					char carattere = operation[1];		//estrazione valore
					myQ.enqueue(carattere);	
					
					count++;	 
				}	
			}	
			
			for(int j=0; j<count; j++)		//ciclo di stampa su file
				out << myQ.dequeue() << " ";
		}
		
		out << endl;
		
	}
	
	in.close();
	out.close();
	
	
	return 0;
}
