# Makefile for the Blockchain Folder...
#Iyobed: /opt/homebrew/opt/openssl@1.1/lib/libcrypto.a


PROG = program
CC = clang++

CPPFLAGS = -g -Wall
OBJS = main.o blockchain.o MerkleTree.o
$(PROG) : $(OBJS)
	$(CC) /opt/homebrew/opt/openssl@1.1/lib/libcrypto.a -o $(PROG) $(CPPFLAGS) $(OBJS)
	#$(CC) -o $(PROG) $(CPPFLAGS) $(OBJS) -lcrypto #<-----For the cloud server 

main.o : main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

blockchain.o : blockchain.cpp 
	$(CC) $(CPPFLAGS) -c blockchain.cpp

MerkleTree.o : MerkleTree.cpp
	$(CC) $(CPPFLAGS) -c MerkleTree.cpp

clean:
	rm -f core $(PROG) $(OBJS)

run: $(PROG)
	./$(PROG) pi pob pom
