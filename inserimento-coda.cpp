#include <iostream>
#include <fstream>

using namespace std;


ifstream in("input.txt");
ofstream out("output.txt");


template <typename T> class Queue
{
private:
	T *array;
	int tail, head;
	int n, max_size;
	
public:
	Queue(int max_size = 200)
	{
		this->max_size = max_size;
		array = new T[max_size];
		
		n = 0;
		
		tail = head = 0;
	}
	
	bool isEmpty()
	{
		return tail == head;
	}
	
	bool isFull()
	{
		return (head == 0 && tail == max_size) || (head == tail + 1); 
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
		else if(head != tail+1)			//ATTENZIONE, IMPORTANTISSIMO
			tail++;
			
		n++;
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
			
		n--;	
		
		return temp;
	}
};


int main()
{
	string tipo;
	int N;
	
	bool aux_bool;
	int aux_int;
	double aux_double;
	char aux_char;
	
	
	for(int i=0; i<100; i++)
	{
		in >> tipo >> N;
		
		if(tipo == "int")
		{
			Queue<int> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_int;
				myQ.enqueue(aux_int);
			}
				
			for(int k=0; k<N; k++)
				out << myQ.dequeue() << " ";
		}
		
		
		
		if(tipo == "double")
		{
			Queue<double> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_double;
				myQ.enqueue(aux_double);
			}
				
			for(int k=0; k<N; k++)
				out << myQ.dequeue() << " ";
		}
		
		
		if(tipo == "bool")
		{
			Queue<bool> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_bool;
				myQ.enqueue(aux_bool);
			}
				
			for(int k=0; k<N; k++)
				out << myQ.dequeue() << " ";
		}
		
		
		if(tipo == "char")
		{
			Queue<char> myQ(N);
			
			for(int j=0; j<N; j++)
			{
				in >> aux_char;
				myQ.enqueue(aux_char);
			}
				
			for(int k=0; k<N; k++)
				out << myQ.dequeue() << " ";
		}
		
		out << endl;
	}
	
	
	in.close();
	out.close();
	
	return 0;
}
