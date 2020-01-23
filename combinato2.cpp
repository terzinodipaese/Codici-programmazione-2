#include <iostream>
#include <fstream>
using namespace std;

class List
{
    private:
        int *keys, *indexes;
        int size, head;
    public:
        List(int dim)
        {
            keys = new int[dim];                //array delle chiavi
            indexes = new int[dim];             //array degli indici/successori
            size = 0;                           //tiene il conteggio del numero di elementi attualmente nella struttura dati
            head = -1;                          //"punta" alla testa, all'inizio è uguale a -1, vuol dire che la lista è vuota
        }

        void insert(int key)
        {
            keys[size] = key;               //inseriamo la chiave
            int prev = -1;                  //supponiamo che il predecessore non ci sia
            int cursor = head;              //è come se chiamassimo begin()/reset()
            
            //finchè cursor non vale -1(saremmo arrivati all'elemento più grande) e 
            //contemporaneamente la chiave visitata è <= di quella inserita
            while(cursor != -1 && keys[cursor] <= key)
            {
                prev = cursor;
                cursor = indexes[cursor];
            }
            
            //se non c'è predecessore, l'elemento inserito è il più piccolo, allora è la testa
            if(prev==-1)
            {
                indexes[size] = head;
                head = size;
            } 
            
            //altrimenti colleghiamo il predecessore a lui, e lui al successore
            else
            {
                indexes[prev] = size;
                indexes[size] = cursor;
            }
            
            //puntiamo alla prima posizione vuota
            size++;
        }

        void canc(int key)
        {
            int prev = -1;
            int cursor = head;
            while(cursor != -1 && keys[cursor]<key)
            {
                prev = cursor;
                cursor = indexes[cursor];
            }
            
            //se non ha predecessore, allora è la testa
            if(prev==-1)
                head = indexes[cursor];
            else
                indexes[prev] = indexes[cursor];        //altrimenti colleghiamo il predecessore al successore
            
            if(head == size-1)
                head = cursor;
               
            //trasferiamo la chiave e il successore dell'ultimo elemento inserito nella posizione liberatasi
            keys[cursor] = keys[size-1];
            indexes[cursor] = indexes[size-1];
            
            //a questo punto adeguiamo gli indici, cioè, se c'è qualche elemento che puntava a size-1
            //lo facciamo puntare a cursor, cioè la posizione dove si trova adesso l'ultimo elemento inserito(size-1)
            for(int i = 0; i<size; i++)
                if(indexes[i] == (size-1))
                    indexes[i] = cursor;
            
            //adesso abbiamo un elemento in meno
            size--;
        }

        void printIndexes(ofstream& out)
        {
            for(int i = 0; i<size; i++)
                out << indexes[i] << " ";
            out << endl;
        }
};

int main()
{
    ifstream in("input.txt"); 
    ofstream out("output.txt");
    
    for(int i = 0; i<100; i++)
    {
        string command;
        int N;
        in >> N;
        List *l = new List(N);
        
        for(int j=0; j<N; j++)
        {
            in >> command;
            if(command[0] == 'i')
                l->insert(atoi(command.substr(1).c_str()));
            else
                l->canc(atoi(command.substr(1).c_str()));
        }
        
        l->printIndexes(out);
    }
    
    return 0;
}
