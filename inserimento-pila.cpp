/*
 * 		Codice che risolve l'esercizio inserimento-pila del Coding contest
 * 
 */

#include <iostream>
#include <fstream>


using namespace std;


template <typename T> class Stack
{
private:
	int top;			//tiene traccia dell'indice dell'elemento più in alto
	T *arrayStack;		//serve a memorizzare fisicamente gli elementi
	int size;			//indica il numero di elementi
	
public:
	Stack(int len = 200)	//argomento standard
	{
		arrayStack = new T[len];	//questo è l'errore che provocava "corrupted top size". ATTENZIONE!! mettere [] e non ()
		top = -1;				
		size = len;
	}
	
	
	~Stack()
	{
		delete[] arrayStack;
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
	
};









int main()
{	
	int intero = 0;				//variabile d'appoggio
	char carattere = '0';		//variabile d'appoggio
	bool booleano = true;		//variabile d'appoggio
	double virgola = 0.00;		//variabile d'appoggio
	
	
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n;						//memorizza il numero di elementi in una riga
	string tipo;				//memorizza il tipo di dato
	
	
	
	for(int i=0; i<100; i++)		//ciclo che scorre le 100 righe
	{
		in >> tipo;
		in >> n;
		
		if(tipo == "int")
		{
			Stack<int> pila(n);
			
			for(int i=0; i<n; i++) 		//ciclo che scorre gli n elementi e li legge
			{
				in >> intero;
				pila.push(intero);
			}
			
			for(int i=0; i<n; i++)
				out << pila.pop() << " ";
				
			pila.~Stack();					//serve a deallocare l'array allocato dinamicamente
				
		}
		
		else if(tipo == "char")
		{
			Stack<char> pila(n);
			
			for(int i=0; i<n; i++)			//ciclo che scorre gli n elementi e li legge
			{
				in >> carattere;
				pila.push(carattere);
			}
			
			for(int i=0; i<n; i++)
				out << pila.pop() << " ";
				
			pila.~Stack();					//serve a deallocare l'array allocato dinamicamente
					
		}
		
		else if(tipo == "bool")
		{
			Stack<bool> pila(n);
			
			for(int i=0; i<n; i++)			//ciclo che scorre gli n elementi e li legge
			{
				in >> booleano;
				pila.push(booleano);
			}
			
			for(int i=0; i<n; i++)
				out << pila.pop() << " ";
				
			pila.~Stack();					//serve a deallocare l'array allocato dinamicamente
				
		}
		
		else if(tipo == "double")
		{
			Stack<double> pila(n);
			
			for(int i=0; i<n; i++)			//ciclo che scorre gli n elementi e li legge
			{
				in >> virgola;
				pila.push(virgola);
			}
			
			for(int i=0; i<n; i++)
				out << pila.pop() << " ";
				
			pila.~Stack();					//serve a deallocare l'array allocato dinamicamente
					
		}
		
		
		
		out << endl;
	}
	
	return 0;
}




