/**********************************************************************************
 *   CREATED BY IYOBED ZEKARIAS, IAN REITMAIER, ALEX NORDHOFF AND NATHAN MATHIES   *
 *                  IMPLEMENTATION OF MERKLE TREE TO BLOCKCHAIN                   *
 * CREATED TO SEND RECEIPT BACK TO CUSTOMER ON WHAT WAS SAVED INTO THE BLOCKCHAIN *
 **********************************************************************************/


// Merkle Tree C++ Implementation

#include "MerkleTree.hpp"
#include <cstring>
#include <openssl/sha.h>
#include <iomanip>

//constructor of the MerkleTree
template <typename T>
MerkleTree<T>::MerkleTree()
{
    rootNode = new node<T>;
    rightMostChild = new node<T>;
    rootNode -> state = ROOT;
    rootNode -> layer = 0;
    rootNode -> index = 0; 
    rightMostChild = nullptr;
    depth = 0;
    mSize = 0;
    currIndex = 1;
}

//destructor of the MerkleTree
template <typename T>
MerkleTree<T>::~MerkleTree()
{
    destroyMTree(rootNode);
}

template <typename T>
void MerkleTree<T>::destroyMTree(node<T> *node)
{
    if(node)
    {
        destroyMTree(node -> lChild);
        destroyMTree(node -> rChild);
        delete node;
    }
    else
    {
        return;
    }
}

template <typename T>
void MerkleTree<T>::addNode(std::string NodeValue)
{
    // If size is 0, special case... 
    if(mSize == 0)
    {
        
        node<T> *leafNode = new node<T>;
        node<T> *leafNodeR = new node<T>;

        rootNode -> lChild = leafNode;
        rootNode -> rChild = leafNodeR;
        rootNode -> hash = "";
        rootNode -> isFilled = 0; 

        leafNode -> parent = rootNode;
        leafNode -> hash = NodeValue;
        leafNode -> state = LEAF;
        leafNode -> layer = 1;
        leafNode -> isFilled = 1; 
        leafNode -> index = currIndex; 
        currIndex++; 

        leafNodeR -> parent = rootNode;
        leafNodeR -> state = LEAF;
        leafNodeR -> layer = 1;
        leafNodeR -> isFilled = 0; 
        leafNodeR -> index = currIndex; 
        currIndex++; 

        rightMostChild = leafNodeR;
        depth++;
        mSize += 3;
        HashTree(rootNode->lChild); 
        currInsert = rootNode -> lChild;
    }
    else{
        
        postOrderInsertion(NodeValue, rootNode -> rChild);
        HashTree(currInsert);

        // After the insertion if the rightmost child is filled then copy
        if(rightMostChild -> isFilled){
            node<T> *newRoot = new node<T>;
            newRoot -> lChild = rootNode; 
            rootNode -> parent = newRoot;
            newRoot -> index = currIndex; 
            currIndex++; 

            // need to set the layer of all elements in the tree on the left side to 
            // 1 + current layer
            newRoot -> layer = 0; 
            setLayers(rootNode);

            rootNode -> state = MID; 
            newRoot -> state = ROOT; 
            rootNode = newRoot; 

            node<T> *rightChild = new node<T>; 
            rootNode -> rChild = rightChild; 
            rightChild -> parent = rootNode; 
            rightChild -> layer = 1;
            rightChild -> hash = ""; 
            rightChild -> state = MID; 
            rightChild -> index = currIndex; 
            currIndex++;
            copy(rightChild);
            
            depth++;
            mSize = (mSize * 2) + 1; 
            setRightMostChild(); 
        }
    }
}

template <typename T>
std::string MerkleTree<T>::hash(std::string unHashed){
    unsigned char obuf[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)unHashed.c_str(), strlen(unHashed.c_str()), obuf);

    std::stringstream ss; 
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)obuf[i]; 
    }
    return ss.str();
}

template <typename T> 
void MerkleTree<T>::copy(node<T> *startNode){
    node<T> *leftChild = new node<T>; 
    node<T> *rightChild = new node<T>; 

    leftChild -> rChild = nullptr;
    leftChild -> lChild = nullptr; 
    leftChild -> hash = "";
    leftChild -> layer = startNode -> layer + 1; 
    leftChild -> isFilled = 0; 
    leftChild -> index = currIndex; 
    currIndex++;

    rightChild -> rChild = nullptr;
    rightChild -> lChild = nullptr; 
    rightChild -> hash = "";
    rightChild -> layer = startNode -> layer + 1; 
    rightChild -> isFilled = 0;
    rightChild -> index = currIndex; 
    currIndex++;

    startNode -> lChild = leftChild;
    startNode -> rChild = rightChild; 
    leftChild -> parent = startNode; 
    rightChild -> parent = startNode; 

    if(startNode -> layer == depth){
        leftChild -> state = LEAF; 
        rightChild -> state = LEAF;
    }
    else{
        leftChild -> state = MID; 
        copy(leftChild); 
        rightChild -> state = MID;
        copy(rightChild); 
    }
    
}

template <typename T> 
void MerkleTree<T>::setLayers(node<T> *startNode){
    startNode -> layer = startNode -> parent -> layer + 1; 
    if(startNode -> state){
        setLayers(startNode->lChild); 
        setLayers(startNode->rChild); 
    }
}

template <typename T>
void MerkleTree<T>::setRightMostChild(){
    node<T> *start = rootNode;
    while(true){
        if(!start->state){
            rightMostChild = start;
            break; 
        }
        start = start -> rChild; 
    }
}

// recursive function to do a post order insertion of the hash on the Merkle Tree.
template <typename T>
void MerkleTree<T>::postOrderInsertion(std::string hash, node<T> *s_node)
{
    //If what is passed in is a leaf then insert the hash and leave
    //This should only happen once and that is when we are inserting the second element
    if(!s_node->state){
        s_node -> hash = hash;
        s_node -> isFilled = 1; 
        currInsert = s_node;
        return;
    }

    if(!s_node->lChild->isFilled){
        if(!s_node->rChild->isFilled){
            if(!s_node->lChild->state){
                s_node -> lChild -> hash = hash; 
                s_node -> lChild -> isFilled = 1; 
                currInsert = s_node -> lChild; 
                return; 
            }else{
                postOrderInsertion(hash, s_node->lChild); 
                return; 
            }
        }

    }else{
        if(!s_node -> rChild -> state){
            s_node -> rChild -> hash = hash; 
            s_node -> rChild -> isFilled = 1; 
            currInsert = s_node -> rChild; 
            return; 
        }else{
            postOrderInsertion(hash, s_node->rChild); 
            return;
        }
        
    }

    // // Left, Right, Root
    // if(!s_node -> lChild -> state && s_node -> lChild -> hash == "")
    // {
    //     s_node -> lChild -> hash = hash;
    //     s_node -> lChild -> isFilled = 1; 
    //     currInsert = s_node -> lChild;
    //     return;
    // }
    // else if(!s_node -> lChild -> state && s_node -> lChild -> hash != "")
    // {
    //     if(s_node -> rChild -> hash == "")
    //     {
    //         s_node -> rChild -> hash = hash; 
    //         s_node -> rChild -> isFilled = 1; 
    //         currInsert = s_node -> rChild;
    //         return;
    //     }
    // }
    // else
    // {
    //     postOrderInsertion(hash, s_node -> lChild);
    // }
    

    

    // if(!s_node -> rChild -> state && s_node -> rChild -> hash == "")
    // {
    //     s_node -> rChild -> hash = hash;
    //     s_node -> rChild -> isFilled = 1; 
    //     currInsert = s_node -> rChild;
    //     return;
    // }
    // else if(!s_node -> rChild -> state && s_node -> rChild -> hash != "")
    // {
    //     return;
    // }
    // else
    // {
    //     postOrderInsertion(hash, s_node -> rChild);
    // }
}

template <typename T>
void MerkleTree<T>::HashTree(node<T> *startNode){
    if(startNode == rootNode -> lChild && mSize == 3){
        rootNode -> hash = hash(startNode->hash);
        rootNode -> isFilled = 1; 
        return; 
    }


    node<T> *parent = startNode -> parent; 
    if(startNode == parent -> lChild){
        parent -> hash = startNode -> hash; 
        parent -> isFilled = 0; 
    }else{
        parent -> hash = hash(parent->lChild->hash + parent->rChild->hash); 
        parent -> isFilled = 1; 
    }

    if(startNode->parent != rootNode){
        HashTree(parent); 
    }else{
        rootNode -> hash = hash(rootNode->lChild->hash + rootNode->rChild->hash); 
    }
    // else if(parent == rootNode -> rChild){
    //     rootNode -> hash = hash(parent->lChild->hash + parent->rChild->hash); 
    // }
}

template <typename T>
void MerkleTree<T>::PrettyPrint(node<T> *startNode){
    //if the the node we are at is the root just print root for ease of use
    if(startNode == rootNode){
        of << "root" << rootNode -> hash.substr(0,3); 
        of << "--";
    }
    else{
        if(startNode -> hash == ""){
            of << "empty" << startNode->index << "--";
        }
        else{
            if(startNode -> isFilled) of << "node";
            else of << "copy" << startNode -> layer;
            of << startNode -> hash.substr(0,3); 
            of << "--";
        }
    }

    //if the node is empty then print empty instead of what is actually there  
    if(startNode -> lChild -> hash == ""){
        of << "empty" << startNode->lChild->index << std::endl;
    }
    else{
        if(startNode -> lChild -> isFilled) of << "node";
        else of << "copy" << startNode -> lChild -> layer;
        of << startNode -> lChild -> hash.substr(0,3); 
        of << std::endl;
    }
    

    if(startNode == rootNode){
        of << "root" << rootNode -> hash.substr(0,3); 
        of << "--";
    }
    else{
        if(startNode -> hash == ""){
            of << "empty" << startNode -> index << "--";
        }
        else{
            if(startNode -> isFilled) of << "node";
            else of << "copy" << startNode -> layer;
            of << startNode -> hash.substr(0,3); 
            of << "--";
        }
    }
    
    if(startNode -> rChild -> hash == ""){
        of << "empty" << startNode -> rChild -> index << std::endl;
    } 
    else{
        if(startNode -> rChild -> isFilled) of << "node";
        else of << "copy" << startNode -> lChild -> layer;
        of << startNode -> rChild -> hash.substr(0,3); 
        of << std::endl;
    }
    

    if(startNode -> lChild -> state){
        PrettyPrint(startNode->lChild);
        PrettyPrint(startNode->rChild);
    }
}

template <typename T>
void MerkleTree<T>::GenerateReceipt(node<T> *startNode){

    if(startNode == rootNode){
        of<< "root: "; 
        of << startNode -> hash; 
        of << std::endl;
        return; 
    }

    node<T> *sibling; 
    if(startNode->parent->lChild == startNode) sibling = startNode->parent->rChild; 
    else sibling = startNode->parent->lChild;

    if(startNode == rootNode->lChild){
        of<< "root: "; 
        if(mSize == 3) of << startNode -> parent -> hash; 
        else of << startNode -> hash; 
        of << std::endl;
        return; 
    }

    if(sibling->isFilled){
        of << sibling -> hash; 
        of << std::endl;
        GenerateReceipt(startNode->parent); 
    }else{
        GenerateReceipt(startNode->parent); 
    }
}

template <typename T>
void MerkleTree<T>::printCurrentInsertHash(){
    of << "current: ";
    of << currInsert -> hash; 
    of << std::endl;
}

template <typename T> 
void MerkleTree<T>::setPipe(char* c){
    pipeM = c; 
}

template <typename T>
void MerkleTree<T>::openPipe(){
    of.open(pipeM); 
}

template <typename T>
void MerkleTree<T>::closePipe(){
    of.close();
}