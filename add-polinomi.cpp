#include <iostream>
#include <fstream>

using namespace std;

class Monomio
{
private:
    int iCoeff;
    int iExp;
    Monomio *pNext;
public:
    Monomio(int iCoeff, int iExp)
    {
        this->iCoeff = iCoeff;
        this->iExp = iExp;
        this->pNext = NULL;
    }

    Monomio *getNext() const
    {
        return this->pNext;
    }

    void setNext(Monomio *pNext)
    {
        this->pNext = pNext;
    }

    int getCoeff() const
    {
        return this->iCoeff;
    }

    int getExp() const
    {
        return this->iExp;
    }

    void add(int iValue)
    {
        this->iCoeff += iValue;
    }

};

class Polinomio
{
private:
    Monomio *pMonoHead, *pMonoCurrent;		//pMonoCurrent è l'iteratore
public:
    Polinomio()
    {
        pMonoHead = pMonoCurrent = NULL;
    }

    void add(Monomio *pMonomio)
    {
        if(pMonoHead == NULL)		//in questo caso la lista era vuota
        {
            pMonoHead = pMonomio;
            return;
        }

	//se gli esponenti sono uguali, somma i coefficienti
        if(pMonomio->getExp() == pMonoHead->getExp())
        {
            pMonoHead->add(pMonomio->getCoeff());
            return;
        }
	
	//il monomio con coefficiente inferiore deve 
	//seguire quello di grado superiore
	else if(pMonomio->getExp() > pMonoHead->getExp())
        {
            pMonomio->setNext(pMonoHead);
            pMonoHead = pMonomio; 
            return;
        }
        

        pMonoCurrent = pMonoHead;
        while(pMonoCurrent->getNext() != NULL
                && pMonomio->getExp() <= pMonoCurrent->getNext()->getExp())
        {
            if(pMonomio->getExp() == pMonoCurrent->getNext()->getExp())
            {
                pMonoCurrent->getNext()->add(pMonomio->getCoeff());
                return;
            }
	    
            pMonoCurrent = pMonoCurrent->getNext();
        }
	
        pMonomio->setNext(pMonoCurrent->getNext());
        pMonoCurrent->setNext(pMonomio);        
    }

    void print(ofstream &ofs)
    {
        pMonoCurrent = pMonoHead;
	
        while(pMonoCurrent != NULL)
        {
            int iCoeff = pMonoCurrent->getCoeff();
            int iExp = pMonoCurrent->getExp();
            
            if(iCoeff == 0)
            {
                if(pMonoCurrent->getNext())
                {
                    if(pMonoCurrent->getNext()->getCoeff() > 0)
                        ofs << "+";
                }
                pMonoCurrent = pMonoCurrent->getNext();
                continue;
            }

            if(!((iCoeff == 1 || iCoeff == -1) && iExp > 0))
                ofs << pMonoCurrent->getCoeff();
            
            if(iCoeff == -1 && iExp > 0)
                ofs << "-";

            if(iExp > 0)
            {
                ofs << "x";

                if(iExp != 1)
                    ofs << "^" << iExp;
            }
	    
            if(pMonoCurrent->getNext())
            {
                if(pMonoCurrent->getNext()->getCoeff() > 0)
                    ofs << "+";
            }
            pMonoCurrent = pMonoCurrent->getNext();
        }
    }
    
    
};


int main()
{
    ifstream ifFile("input.txt");
    ofstream ofFile("output.txt");
    size_t nSize;
	
    while(ifFile >> nSize)	//finchè viene letto qualcosa
    {
        Polinomio *pPolinomio = new Polinomio();
        int iLastSign = 1;
        char chLastSign = '+';
        for (size_t i = 0; i < nSize; i++)	//ciclo sul numero di monomi
        {         
            char chMonomio;
            ifFile >> chMonomio; // (
            while(chMonomio != ')')
            {
                int iCoeff = 0, iExp = 0, iSign = 1;
                ifFile >> chMonomio;

                if(chMonomio == ')')
                    break;

                if(chMonomio == '-' || chMonomio == '+')
                {
                    iSign = (chMonomio == '-') ? -1 : 1;
                    ifFile >> chMonomio;
                }

                while(chMonomio >= '0' && chMonomio <= '9')
                {
                    iCoeff = (iCoeff * 10) + (chMonomio - '0');
                    ifFile >> chMonomio;
                }
                
                if(iCoeff == 0)
			iCoeff = 1;

                if(chMonomio == 'x')
                {
			ifFile >> chMonomio;
			if(chMonomio == '^')
			{
				ifFile >> iExp;
			}
		    
			else
			{
				iExp = 1;
				int iCurrIndex = ifFile.tellg();
				ifFile.seekg(iCurrIndex - 2);
				ifFile >> chMonomio;
			}
                }
                //cout << iCoeff * iSign * iLastSign << " " << iExp  << endl;
                pPolinomio->add(new Monomio(iCoeff * iSign * iLastSign, iExp));
	     }

            if(i != nSize - 1)
            {
                ifFile >> chLastSign;
                iLastSign = (chLastSign == '-') ? -1 : 1;
            }
            //pPolinomio->print(ofFile);                            
        }
        pPolinomio->print(ofFile);
        ofFile << endl;
    }

    
    //pPolinomio->print();
    return 0;
}
