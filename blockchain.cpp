/*
////////////////////////////////////////////
//               BLOCKCHAIN:
//
//
//        Created by: Ian Reitmaier
//   Alex Nordhoff, Nathan Matheis, Bryce Martin, 
//            and Iyobed Zekarias
//
//
//      This code is a doubly linked Blockchain
//
//////////////////////////////////////////////
*/
#include "blockchain.hpp"
#include <iomanip>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <typeinfo>
/*
This function was developed by Ian Reitmaier & Alex Nordhoff
This function will create the blockchain itself
*/

//constructor
template <typename T>
blockchain<T>::blockchain()
{
    head = nullptr;
    tail = nullptr;
    chainSize = 0;
}

template <typename T>
void blockchain<T>::setPipes(char* pipeoutBlock, char* pipeoutMerkle){ 
    pipeB = pipeoutBlock; 
    pipeM = pipeoutMerkle; 
    mTree.setPipe(pipeoutMerkle); 
}
/*
This function was developed by Ian Reitmaier & Alex Nordhoff
This function will destroy the blockchain if needed.
*/

//destructor
template <typename T>
blockchain<T>::~blockchain()
{
    block<T> *blockOne = head;
    block<T> *blockTwo = head;
    while(blockOne != nullptr)
    {
        blockTwo = blockOne -> nextB;
        delete blockOne;
        blockOne = blockTwo;
    }
}

/*
This function was developed by Ian Reitmaier & Alex Nordhoff
This function will copy a certain blockchain into another blockchian
*/

//copy constructor
template <typename T>
blockchain<T>::blockchain(const blockchain<T> &bChain)
{
    int i = 0;
    block<T> *blockOne = bChain.head;
    block<T> *prevBlock = nullptr;

    while(blockOne != nullptr)
    {
        block<T> *n = new block<T>;

        n -> hash = blockOne -> hash;

        n -> prevB = prevBlock;
        n -> nextB = nullptr;
        if(prevBlock != nullptr)
        {
            prevBlock -> nextB = n;
        }
        tail = n;
        if(i == 0)
        {
            head = n;
        }
        blockOne = blockOne -> nextB;
        prevBlock = n;
        i++;

    }
}
/*
This function was developed by Ian Reitmaier & Alex Nordhoff
This function will add a new block to the end of the BC if there is already one 
block in the chain. If the size = 0 then we will create a new block make it the head and tail.
*/

//add function
template <typename T>
block<T> * blockchain<T>::addBlock(std::string hash)
{
    //Instatiating a blockchain
    if(chainSize == 0)
    {
        block<T> *newBlock = new block<T>;

        newBlock -> nextB = head;
        newBlock->hash = hash;
        if(head != nullptr)
        {
            head -> prevB = newBlock; 
        }
        else
        {
            tail = newBlock;
        }

        newBlock -> prevB = nullptr;
        head = newBlock;
        chainSize++;
        return newBlock;
    }
    //inserting at the end
    else
    {
        block<T> *newBlock = new block<T>;
        newBlock->hash = hash;
        newBlock -> nextB = nullptr;
        tail -> nextB = newBlock;
        newBlock -> prevB = tail;
        tail = newBlock;
        chainSize++;
        return newBlock;
    }
}

/*
This function was developed by Bryce Martin
This simple function will display all the blocks within our blockchain for testing.
*/

template <typename T>
void blockchain<T>::prettyPrint()
{
    std::ofstream fo;
    fo.open(pipeB);
    //reassign a pointer to be the first block
    block<T> *first = head;
    
    while(first != nullptr)
    {
        fo << " \n\n=======================\n " << "BLOCK: ";
        fo << first -> hash; 
        fo << '\n';
        fo << " ======================= \n";
        
        // for(size_t i = 0; i < first->arrSize; i = i + 2)
        // {
        //      fo << first -> hasharr[i] << " " << first->hasharr[i+1].substr(0,100) << "\n";
        // }

        first = first -> nextB;
    }
    fo << "\n";
    fo.close();
}

template <typename T>
void blockchain<T>::prettyPrintM(){ 
    mTree.openPipe();
    mTree.PrettyPrint(mTree.rootNode); 
    mTree.closePipe();
}

template <typename T>
void blockchain<T>::GenerateReceipt(){
    mTree.openPipe(); 
    mTree.printCurrentInsertHash(); 
    mTree.GenerateReceipt(mTree.currInsert); 
    mTree.closePipe();
}

template <typename T>
void blockchain<T>::update(std::string password)
{

}

template <typename T>
void blockchain<T>::deleteBlock(std::string blockHash)
{
    block<T> *current = head;
    
    while(current != nullptr)
    {
        if(current->hash == blockHash)
        {
            current -> prevB -> nextB = current -> nextB;
            current -> nextB -> prevB = current -> prevB;
            current -> nextB = nullptr;
            current -> prevB = nullptr;
            delete current; 
            chainSize--;
        }
        current = current -> nextB;
    }
}


/*
This function was developed by Bryce Martin
The addTransaction function will allow someone to input contents into a block's
array containing hash values for each transaction
*/
template <typename T>
void blockchain<T>::addTransaction(std::string combined)
{
    // block<T> *current = head;

    // while(current != nullptr)
    // {
    //     if(hashID == current -> hash)
    //     {
    //         current->hasharr[current->arrSize] = contents;
    //         current->arrSize++;
    //         return;
    //     }

    //     else
    //     {
    //         current = current -> nextB;
    //         continue;
    //     }

    // }


    unsigned char obuf[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)combined.c_str(), strlen(combined.c_str()), obuf);

    std::stringstream ss; 
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)obuf[i]; 
    }

    addBlock(ss.str());
    mTree.addNode(ss.str());
    // current->hasharr[current->arrSize] = uid;
    // current->arrSize++;
    // current->hasharr[current->arrSize] = contents; 
    // current->arrSize++;
}