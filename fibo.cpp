/*
 * 		Codice che risolve l'esercizio fibonacci del Coding contest
 */

#include <iostream>
#include <fstream>

static long long int FIB[1000] = {0};

using namespace std;



//recursive technique with memoization, best way to compute the Fibonacci series
long long int fibonacci(int n)      
{
    if((n == 0) || (n == 1)) return n;
    if(FIB[n]) return FIB[n];
    
    FIB[n] = fibonacci(n-1) + fibonacci(n-2);
    
    return FIB[n];
}




int main(int argc, char** argv)
{
    int n;
    ofstream out("output.txt");
    ifstream in("input.txt");
    
    for(int i=0; i<100; i++)
    {
        in >> n;                        //read from file and memorise the value into our variable n
        out << fibonacci(n) << endl;    //compute the value of fibonacci(n) and memorise it in the output file
    }
    
    out.close();
    in.close();
        
    return 0;
}






