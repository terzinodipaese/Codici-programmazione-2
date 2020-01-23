#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

template<class H>
class Nodo
{
private:
	Nodo<H>* padre;
	Nodo<H>* sinistro;
	Nodo<H>* destro;
	H* val;
public:
	Nodo(H v){
		val=new H(v);
		padre=sinistro=destro=NULL;
	}
	~Nodo(){
		if (val!=NULL) delete val;
	}

	Nodo<H>* getPadre(){return padre;}
	Nodo<H>* getSinistro(){return sinistro;}
	Nodo<H>* getDestro(){return destro;}
	H* getVal(){return val;}

	void setPadre(Nodo<H>* aux){padre=aux;}
	void setDestro(Nodo<H>* aux){destro=aux;}
	void setSinistro(Nodo<H>* aux){sinistro=aux;}
	void setVal(H x){*val=x;}  
};


template<class H>
class Albero
{
private:
	Nodo<H>* root;


	Nodo<H>* Successivo(Nodo<H>* aux){
		if (aux==NULL) return NULL;
		if(aux->getDestro()!=NULL)
			return Minimo(aux->getDestro());
		else {
			Nodo<H>* supp=aux->getPadre();
			while((supp!=NULL) &&(supp->getDestro()==aux)){
				aux=supp;
				supp=supp->getPadre();
			}
			return supp;
		}
	}

	Nodo<H>* Minimo(Nodo<H>* start){
		while((start!=NULL) && (start->getSinistro()!=NULL)){
			start=start->getSinistro();
		}
		return start;

	}
	/*void InOrder(){
		Nodo<H>* aux=Minimo(root);
		while(aux!=NULL){
			cout<<*aux->getVal()<<" ";
			aux=Successivo(aux);
		}
	}
	void InOrder(Nodo<H>* aux){
		if(aux!=NULL){
			InOrder(aux->getSinistro());
			cout<<*aux->getVal()<<" ";
			InOrder(aux->getDestro());
		}
	}*/
	void PostOrder(Nodo<H>* aux){
		if(aux!=NULL){
			PostOrder(aux->getSinistro());
			PostOrder(aux->getDestro());
			fout<<*aux->getVal()<<" ";
		}
	}
public:
	Albero():root(NULL){};
	//~Albero();
	
	Albero<H>* AddNode(H val){
	Nodo<H>* nuovo=new Nodo<H>(val);

	Nodo<H>* x=root;
	Nodo<H>* y=x;
	while(x!=NULL){
		y=x;
		if(val<*x->getVal())
			x=x->getSinistro();
		else 
			x=x->getDestro();
	}
	nuovo->setPadre(y);

	if(root==NULL)
		root=nuovo;
	else 
		if (val<*y->getVal())
			y->setSinistro(nuovo);
		else 
			y->setDestro(nuovo);

	return this;
}

	void stampa(){
		PostOrder(root);
		//InOrder(root);
		//cout<<endl;
		fout<<endl;
	}

	/*void Minimo(){
		cout<<*root->getVal()<<endl;
		Nodo<H>* x=Successivo(root);
		cout<<*x->getVal()<<endl;
	}*/

	void Naturalfill(H* arr)
	{
		Nodo<H>* aux=Minimo(root);			//cerchiamo il minimo, cioè quello più a sinistra
		int i=0;
		
		while(aux!=NULL)
		{
			aux->setVal(arr[i]);
			aux=Successivo(aux);
			i++;
		}
	}
};

//template<class H> 
//Albero<H>* Albero<H>::AddNode(H val)

template<class H>
void esegui(H t){
	int N;
	H supp;
	fin>>N;
	//cout<<N<<endl;

	Albero<H> Alb;

	for (int i = 0; i < N; ++i) {
		fin>>supp;
		//cout<<supp<<" ";
		Alb.AddNode(supp);
	}

	//Alb.stampa();

	H arr[N];
	for (int i = 0; i < N; ++i) /*{*/fin>>arr[i]; //cout<<arr[i]<<" ";}
	//Alb.Minimo();
	Alb.Naturalfill(arr);

	Alb.stampa();
	//cout<<endl;
}

int main()
{
	string s;
	int i=0;
	double d=0.0;

	for(int count =0;count<100;count++){
		fin>>s;
		
		if(s=="double")esegui(d);
		else esegui(i);
	}
	
	return 0;
}
