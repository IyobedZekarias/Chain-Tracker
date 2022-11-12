/*
/////////////////////////////////////////
//               BLOCKCHAIN:
//
//
//        Created by: Ian Reitmaier
//   Alex Nordhoff, Nathan Matheis, Bryce Martin, 
//            and Iyobed Zekarias
//
//
//    This is the header file for the blockchain
//    functions.
//
//////////////////////////////////////////////
*/

#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include <openssl/sha.h>
#include <string>
#include <iostream>
#include "MerkleTree.cpp"

template <typename T>
struct block
{
    block<T> *prevB;
    std::string hash; 
    //std::string hasharr[50];
    size_t arrSize;
    block<T> *nextB;
};

template <typename T>
class blockchain
{
    private:

    public:
    block<T> *head;
    block<T> *tail;
    size_t chainSize;
    MerkleTree<T> mTree;
    char* pipeB;  
    char* pipeM;
    
    //constructor
    blockchain();

    //destuctor 
    ~blockchain();

    //copy constructor
    blockchain(const blockchain<T> &bChain);

    //adding block
    block<T> * addBlock(std::string hash);

    //printing the blockchain
    void prettyPrint();

    //Print Merkle Tree
    void prettyPrintM();

    //Make Receipt for user
    void GenerateReceipt();

    //update the blocks from legure
    void update(std::string password);

    //delete block from blockchain
    void deleteBlock(std::string blockHash);

    //Setting pipes for use in blockchain and Merkle Tree
    void setPipes(char* pipeoutBlock, char* pipeoutMerkle);

    void addTransaction(std::string combined);



};

#endif