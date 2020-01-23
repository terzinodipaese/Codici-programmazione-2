#include <iostream>
#include <fstream>
#include <string>

using namespace std;


template <typename T> class Stack
{
private:
	int top, size;
	T *arrayStack;
	
public:
	Stack(int len = 200)
	{
		size = len;
		arrayStack = new T[size];
		top = -1;
	}
	
	~Stack()
	{
		delete[] arrayStack;
	}
	
	T pop()
	{
		if(top == -1)
			return -1;
		
		else
		{
			top--;
			return arrayStack[top+1];
		}
	}
	
	void push(T element)
	{
		if(top < size-1)
		{
			top++;
			arrayStack[top] = element;
		}
		
		else
			return;
	}
	
	
};

int main()
{
	//lettura e scrittura da e su file
	ofstream out("output.txt");
	ifstream in("input.txt");
	
	
	//variabili ausiliarie
	int intero = 0;
	bool booleano = false;
	char carattere = '0';
	double virgola = 0.00;
	
	
	
	string type, operazione; //immagazzina il tipo di dato e l'operazione da compiere, rispettivamente
	int N;
	
	int count;			//conta il numero di valori immessi nello stack
	
	
	
	
	for(int task=0; task<100; task++)		//scorre le 100 righe 
	{
		count = 0;
		in >> type >> N;
		
		if(type == "int")
		{
			Stack<int> pila(N);
			
			for(int i=0; i<N; i++)	//scorre la singola riga e legge tutti gli elementi
			{
				in >> operazione;
			
				if(operazione == "pop")
					pila.pop();
				
				else
				{
					intero = stoi(operazione.substr(1)); //estrae la sottostringa a partire dalla posizione 1 fino alla fine, la converte in intero
					pila.push(intero);
					count++;							 //incrementiamo quando inseriamo qualcosa
				}
			}
			
			for(int i=0; i<count; i++)	
				out << pila.pop() << " ";
		}	//fine if del tipo int
			
			
			
			
		if(type == "char")
		{
			Stack<char> pila(N);
			
			for(int i=0; i<N; i++)	//scorre la singola riga e legge tutti gli elementi
			{
				in >> operazione;
			
				if(operazione == "pop")
					pila.pop();
				
				else
				{
					carattere = operazione[1]; 		  //prende il secondo carattere di operazione
					pila.push(carattere);
					count++;						  //incrementiamo quando inseriamo qualcosa
				}
			}
			
			for(int i=0; i<count; i++)	
				out << pila.pop() << " ";
			
		}	//fine if del tipo char
			
			
			
			
			
		if(type == "bool")
		{
			Stack<bool> pila(N);
			
			for(int i=0; i<N; i++)	//scorre la singola riga e legge tutti gli elementi
			{
				in >> operazione;
			
				if(operazione == "pop")
					pila.pop();
				
				else
				{
					booleano = stoi(operazione.substr(1)); //estrae la sottostringa a partire dalla posizione 1 fino alla fine, la converte in intero
					pila.push(booleano);
					count++;							   //incrementiamo quando inseriamo qualcosa
				}
			}
			
			for(int i=0; i<count; i++)	
				out << pila.pop() << " ";
			
		}	//fine if del tipo bool
			
			
			
			
		if(type == "double")
		{
			Stack<double> pila(N);
			
			for(int i=0; i<N; i++)	//scorre la singola riga e legge tutti gli elementi
			{
				in >> operazione;
			
				if(operazione == "pop")
					pila.pop();
				
				else
				{
					virgola = stod(operazione.substr(1)); //estrae la sottostringa a partire dalla posizione 1 fino alla fine, la converte in double
					pila.push(virgola);
					count++;							  //incrementiamo quando inseriamo qualcosa
				}
			}
			
			for(int i=0; i<count; i++)	
				out << pila.pop() << " ";
			
		}	//fine if del tipo double
		
		out << endl;	
		
	}	//fine ciclo for principale
	
	

	return 0;
}



