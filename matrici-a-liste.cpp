#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class Node
{
private:
    Node<T> *pNext;
    T *pKey;
public:
    Node(T &key)
    {
        pKey = new T(key);
        pNext = NULL;
    }

    void setKey(T &key)
    {
        pKey = new T(key);
    }

    T& getKey()
    {
        return *pKey;
    }

    T *getKeyPtr()
    {
        return pKey;
    }


    void setNext(Node<T> *pNode)
    {
        pNext = pNode;
    }

    Node<T> *getNext()
    {
        return pNext;
    }

};

template<typename T>
class List
{
private:
    Node<T> *pHead, *pCurrent;
    size_t nSize;
public:
    List()
    {
        pHead = pCurrent = NULL;
        nSize = 0;
    }

    void insert(T &key)
    {
        Node<T> *pNode = new Node<T>(key);
        if(pHead == NULL)
            pHead = pNode;
        else
        {
            Node<T> *pTemp = pHead;
            while(pTemp->getNext())
                pTemp = pTemp->getNext();
            pTemp->setNext(pNode);
        }
        nSize++;
    }

    bool hasNext()
    {
        return (pCurrent && pCurrent->getNext() != NULL);
    }

    Node<T> *next()
    {
        Node<T> *pTemp = pCurrent;
        pCurrent = pCurrent->getNext();
        return pTemp;
    }

    void reset()
    {
        pCurrent = pHead;
    }

    size_t getSize() const
    {
        return nSize;
    }
};

class LMatrix
{
private:
    List<List<int> > *pRows;
    List<int> *pCurCol;
    size_t nRows, nCols;
public:

    LMatrix(size_t rows, size_t cols)
    {
        pRows = new List<List<int> >;
        pCurCol = NULL;
        nRows = rows;
        nCols = cols;
    }

    void insert(int iNumber)
    {
        if(pCurCol == NULL)
            pCurCol = new List<int>;

        pCurCol->insert(iNumber);
        
        if(pCurCol->getSize() >= nCols)
        {
            pRows->insert(*pCurCol);
            pCurCol = NULL;
        }
    }

    int **multiply(int **iMatrix, size_t iP)
    {
        int **iResult = new int*[nRows];
        
        for (size_t i = 0; i < nRows; i++)
            iResult[i] = new int[iP]();
        
        pRows->reset();
        for (size_t i = 0; i < nRows; i++)
        {
            List<int> *pCols = pRows->next()->getKeyPtr();
            
            for (size_t j = 0; j < iP; j++)
            {
                pCols->reset();
                int iValue = 0;
                for (size_t z = 0; z < nCols; z++)
                {
                    int iTemp = pCols->next()->getKey();
                    iValue += iTemp * iMatrix[z][j];
                }
                iResult[i][j] = iValue;
            }
        }
        return iResult;
    }
};



int main()
{
    ifstream ifFile("input.txt");
    ofstream ofFile("output.txt");

    size_t iN, iM, iP;
    while(ifFile >> iN)
    {
        ifFile >> iM;
        ifFile >> iP;

        LMatrix *pLM = new LMatrix(iN, iM);

        for (size_t i = 0; i < iN * iM; i++)
        {
            int iTemp;
            ifFile >> iTemp;
            pLM->insert(iTemp);
        }
        int **iMatrix = new int*[iM];

        for (size_t i = 0; i < iM; i++)
            iMatrix[i] = new int[iP]();
        
        for (size_t i = 0; i < iM; i++)
        {
            for (size_t j = 0; j < iP; j++)
            {
                ifFile >> iMatrix[i][j];
            }
        }
        int **iResult = pLM->multiply(iMatrix, iP);
        
        for (size_t i = 0; i < iN; i++)
        {
            for (size_t j = 0; j < iP; j++)
            {
                ofFile << iResult[i][j] << " ";
            }
        }
        
        ofFile << endl;
        
    }
    return 0;
}