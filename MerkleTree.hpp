#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Merkle Tree C++ Header File

template <typename T>
struct node
{
    // left child, right child, parent, children hash, state, sibling, level
    node<T> *lChild;
    node<T> *rChild;
    node<T> *parent;
    std::string hash;

    int state;
    int isFilled;
    size_t layer;
    int index;
};

template <typename T>
class MerkleTree
{
    private:
    void InOrderSetNull();

    public:
    #define LEAF 0;
    #define ROOT 2;
    #define MID 1;


    node<T> *rootNode;
    node<T> *rightMostChild;
    node<T> *currInsert; 

    size_t depth;
    size_t mSize;
    int currIndex; 
    char* pipeM;
    std::ofstream of; 


    MerkleTree();

    ~MerkleTree();

    void destroyMTree(node<T> *node);

    void addNode(std::string NodeValue);
    
    void postOrderInsertion(std::string hash, node<T> *s_node);

    void setLayers(node<T> *startNode); 

    void copy(node<T> *startNode);

    void setRightMostChild(); 

    void HashTree(node<T> *startNode);

    void setPipe(char* c);
    void openPipe(); 
    void closePipe(); 

    std::string hash(std::string unHashed);

    void PrettyPrint(node<T> *startNode);

    void GenerateReceipt(node<T> *startNode); 

    void printCurrentInsertHash();
};