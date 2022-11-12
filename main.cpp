/* https://medium.com/@timmykko/using-openssl-library-with-macos-sierra-7807cfd47892
/////////////////////////////////////////
//               BLOCKCHAIN:
//
//
//        Created by: Ian Reitmaier
//   Alex Nordhoff, Nathan Matheis, Bryce Martin, 
//            and Iyobed Zekarias
//
//
//    This is the main program for testing purposes
//    for the blockchain functions.
//
//////////////////////////////////////////////
*/


#include "blockchain.hpp"
#include "blockchain.cpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int, char** argv)
{

/*****************************************************
 *            COMMANDS TO RUN BLOCKCHAIN:            *
 *               1. RM PIPEIN PIPEOUT                *
 *             2. MKFIFO PIPEIN PIPEOUT              *
 *                  3. CAT PIPEIN &                  *
 *         4. ECHO <UUID> <MESSAGE> > PIPEIN         *
 * {DO THIS COMMAND AS MANY TIMES AS YOU WOULD LIKE} *
 *              5. ECHO BLOCK > PIPEIN               *
 *                 6. CAT < PIPEOUT                  *
 *****************************************************/


    // std::ifstream f;
    // f.open(argv[1]);
    // std::string line;
    // std::getline(f, line);
    // f.close();
    // unsigned char obuf[SHA256_DIGEST_LENGTH];

    // SHA256((unsigned char*)line.c_str(), strlen(line.c_str()), obuf);

    // std::ofstream fO;
    // fO.open(argv[2]);
    
    // int i;
    // for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    //     fO <<std::hex << std::setfill('0') << std::setw(2) << (unsigned int)obuf[i]; 
    // }
    // fO << '\n';
    // fO.close();

    // return 0;


    blockchain<int> newBlockChain;
    newBlockChain.setPipes(argv[2], argv[3]);

    while(true){
        std::ifstream f;
        f.open(argv[1]);
        std::string line;
        std::getline(f, line);
        f.close();

        if(line == "block"){
            newBlockChain.prettyPrint();
            continue;
        }
        else if(line == "merk"){
            newBlockChain.prettyPrintM();
            continue;
        }
        else if(line == "exit"){
            return 0; 
        }
        else if(line == "receipt"){
            newBlockChain.GenerateReceipt(); 
            continue;
        }
        size_t space = line.find(" ");

        std::string uid = line.substr(0, space);
        std::string file = line.substr(space+1);
        if(uid == "0" && file == "init") continue;

        std::string combined = uid+file;
        

        newBlockChain.addTransaction(combined);
    }
    return 0; 
}