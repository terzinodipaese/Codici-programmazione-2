#include <iostream>
#include <fstream>

using namespace std;

void hanoi(int disks, int from, int to, int intermediate, fstream& out, int& moves, const int stop)
{
    if(disks == 1)     //caso base
    {
        moves++;
        if(moves == stop)
            out << from << " " << to << endl;
    } 
    
    else             //caso generale
    {
        hanoi(disks-1, from, intermediate, to, out, moves, stop);
        moves++;
        if(moves == stop)   //se si è raggiunti la mossa d'interesse, allora stampiamo from e to
            out << from << " " << to << endl;
        hanoi(disks-1, intermediate, to, from, out, moves, stop);
    }
}

int main()
{
    fstream input("input.txt", ios::in), output("output.txt", ios::out);
    
    for(int i = 0; i<100; i++)
    {
        int disks, stop;
        int moves = 0;
        input >> disks >> stop;
        hanoi(disks, 1, 3, 2, output, moves, stop);
    }
    
    return 0;
}
