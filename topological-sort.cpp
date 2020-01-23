#include <fstream>
#include <iostream>

using namespace std;

ifstream infile("input.txt");
ofstream ofile("output.txt");

template <class H> class Grafo
{
private:
	int n,m,len;
	int t,radice_attuale;
	int **M;
	H** K;
	int *d,*f,*c,*r,*p;
	
	int trovaIndice(H v)
	{
		for(int i=0;i<n;i++)
			if(*K[i]==v) return i;
		return -1;
	}
	
public:
	Grafo(int l)
	{
		len=l;
		n=m=0;
		
		M=new int*[len];
		K=new H*[len];
		
		for(int i=0;i<len;i++)
		{
			K[i]=NULL;
			M[i]=new int[len];
			for(int j=0;j<len;j++) M[i][j]=0;
		}
		
		d=new int[len];
		f=new int[len];
		c=new int[len];
		r=new int[len];
		p=new int[len];
		
	}
	
	Grafo<H>* addNodo(H x)
	{
		
		if(n==len || trovaIndice(x)>=0) return this;
		K[n]=new H(x);
		n++;
		return this;
	}
	
	Grafo<H>* addArco(H x,H y)
	{
		
		int i=trovaIndice(x);
		int j=trovaIndice(y);
		if(i<0 || j<0) return this;
		if(M[i][j]==0)
		{
			M[i][j]=1;
			m++;
		}
		return this;
	}
	
	void DFSVisit(int v)
	{
		c[v]++;
		d[v]=t++;
		r[v]=radice_attuale;
		for(int u=0;u<n;u++)
		{
			if(M[v][u]==1)
				if(c[u]==0)
				{
					p[u]=v;
					DFSVisit(u);
				}
		}
		
		c[v]++;
		f[v]=t++;
	}
	
	void DFS()
	{
		t=0;
		for(int i=0;i<n;i++)
		{
			c[i]=0;
			p[i]=-1;
		}
		
		for(int i=0;i<n;i++)
		{
			if(c[i]==0)
			{
				radice_attuale=i;
				DFSVisit(i);
			}
		}
	}
	
	void sort(int *a, int n, int *k) 
	{
		for(int i=1; i<n; i++) 
		{
			int j = i-1;
			while(j>=0 && k[a[j+1]]>k[a[j]]) 
			{
				int t = a[j+1];
				a[j+1] = a[j];
				a[j] = t;
				j--;
			}
		}
	}
	
	void topsort()
	{
		DFS();
		int *s=new int[n];
		
		for(int i=0;i<n;i++) 
			s[i]=i;
		
		sort(s,n,f);
		
		for(int i=0;i<n;i++) 
			ofile<< *K[s[i]] << " ";
		
		ofile << endl;
	}
};

template <class H> void metodo(int n,int m)
{

    char a;
    H el;
    Grafo<H>* g=new Grafo<H>(n);
	
    for(int i=0;i<n;i++)
    {
        infile>>el;
        g->addNodo(el);
    }
    
    for(int j=0;j<m;j++)
    {
        H x,y;
        infile>>a;

        infile>>el;
        x=el;

	//infile>>a;

        infile>>el;
        y=el;

        g->addArco(x,y);
        infile>>a;

    }
   g->topsort();


}

int main()
{
    string type;
    int n;
    if(infile.is_open())
        while(infile>>n)
        {
            int N=n;
            infile>>n;
            int M=n;
            infile>>type;
            if(type=="int") metodo<int>(N,M);
            if(type=="char") metodo<char>(N,M);
            if(type=="bool") metodo<bool>(N,M);
            if(type=="double") metodo<double>(N,M);
        }
    else cout<<"HO ROTTUTO TUTTO"<<endl;
    infile.close();
    ofile.close();
    return 0;
}