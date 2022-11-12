from subprocess import Popen, PIPE, STDOUT
import os

# with open(FIFO, 'w') as f:
#         f.write('1 hello')
#         f.close()



# res = Popen(['mkfifo pipein pipeout', 
#         'cat pipein &', 
#         './program < pipein >> pipeout',
#         './startAPI.sh'],
#     cwd="/Users/nbstr/Documents/2021 Spring/SENG350V Software Studio/ChainTracker/Blockchain",   ## THIS WILL NEED TO BE CHANGED TO YOUR SPECIFIC LOCATION OF YOUR FILE
#       
#     shell=True)

#loc="/home/nbstrong161/ChainTracker/Blockchain"
#loc="/Users/nbstr/Documents/2021 Spring/SENG350V Software Studio/ChainTracker/Blockchain"
loc = os.path.dirname(os.path.realpath(__file__))


Popen("./program pi pob pom", 
        cwd=loc,
        shell=True)

Popen("./startWorkers.sh", 
        cwd=loc,
        shell=True)


