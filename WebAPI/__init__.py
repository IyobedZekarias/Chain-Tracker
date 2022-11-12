from subprocess import Popen, PIPE, STDOUT
import flask  
#      ^^^^^ you will need to use pip install flask for this library
from flask import render_template

from flask_cors import CORS, cross_origin

######################################################################################################
# Purpose of python script:                                                                          #   
# The point here is to be able to set up an api that then runs blockchain process and pushes any api #
# json data to the blockchain                                                                        #
#                                                                                                    #
# Directison: (Must have python installed correctly and $PATH variables corrrectly implemented)      #
# Run 'pip3 install flask' and 'pip3 install requests'                                               #
# Also make sure that ./program works in current directory (if not run 'make clean' then 'make' in terminal)
#                                                                                                    #
# 1. Open two different terminal windows either in visual studio or external windows and make sure   #
#   both are in the directory of ChainTracker/Blockchain                                             #       
# 2. In the first terminal window run 'python3 Runner.py', this will start the python api on your    #
#   local machine on port 5000                                                                       #
# 3. In the second terminal window run 'python3 apiRunner.py' this will simmulate an outside program #                                        
#   sending a json file to the webAPI                                                                #
# 4. Lastly go to http://0.0.0.0:5000/break to see everything that is currently in the blockchain  #
#   (web-browsers don't always format things correctly so don't be suprised if it's completely jumbled up)
# 5. Ask Iyobed questions if directions unclear or if you're just curious on how things work         #
######################################################################################################




##
# POPEN: popen opens a child process, in this case the blockchain 
# and runs said child process whithout waiting
# by connececting stdout, stdin, and stderr to PIPE it makes it so that hte python program can continue
# and input information in as it goes
##


##
# Flask is going be used for the creation of the web api
# it will be able to run GET and POST, there will never be a delete or put option for our api
# A good video that explains a lot of this is https://www.youtube.com/watch?v=-gUyWoe_SKI
##
app = flask.Flask(__name__)
app.config["DEBUG"] = True
# CORS(app)
# cors = CORS(app, resources={
#     r"/*": {
#         "origins" : "*"
#     }
# })


useradded = [{                      # This could be the basic structure of the json file we accept for our api
    'hash' : 'not changed'          # If this format was used that would mean that the hashine would be done before hand. It would largely just depend
}]                                                                              ##


##
# This is GET it just returns what is currently in the useradded dictionary
##
@app.route('/', methods={'GET'})
@app.route('/About', methods={'GET'})
@app.route('/Software', methods={'GET'})
@app.route('/Account/', methods={'GET'})
@app.route('/Account/Sign Up', methods={'GET'})
@app.route('/Account/Login', methods={'GET'})
@app.route('/Account/Forgot Password', methods={'GET'})
@app.route('/Support/', methods={'GET'})
@app.route('/Support/Nonmember', methods={'GET'})
@app.route('/Contacts', methods={'GET'})
def get():
    return render_template("index.html", flask_token="Hello world")

##
# This POST method will input information sent to the api via JSON
# curl -i -H "Content-Type: Application/json" -X POST http://127.0.0.1:5000/    <--- Your url will probably be different
##
@app.route('/<uuid>', methods=['POST'])
def create(uuid):

    i = len(flask.request.json['hash'].encode('utf-8'))
    
    # files = []
    # pid = os.getpid()
    # j = 0
    # while(j < i):
    #     filename = str(pid) + "pi" + str(j); 
    #     path = 'pipefiles/' + filename
    #     os.mkfifo(path)
    #     #      p2.write(flask.request.json['hash'].encode('utf-8')[j:(j+63999)])
    #     files.append(path)
    #     filename = ""
    #     j += 1

    with open('pi', 'w') as p:
        p.write(uuid + " " + flask.request.json['hash'])
        p.close
        

    return flask.jsonify({'Created': flask.request.json['hash']})

##
# This break method is just for testing and will be removed for production it will show the blockchain in the borwser
##
@app.route('/block', methods=['GET'])
def Break():
    with open('pi', 'w') as pin:
        pin.write('block')
        pin.close
    with open('pob', 'r') as pout:
        stdout = pout.read()
        pout.close()
    #proc.stdin.write(b'1 This_is_Iyobed_Writing_to_YOU\nbreak\n')
    #proc.stdin.write(b'break')
    #proc.stdin.write(b'\n')
    stdout = stdout.replace('\n', '<br /><br />')

    return  stdout

@app.route('/merk', methods=['GET'])
def Merk():
    with open('pi', 'w') as pin:
        pin.write('merk')
        pin.close
    with open('pom', 'r') as pout:
        stdout = pout.read()
        pout.close()
    #proc.stdin.write(b'1 This_is_Iyobed_Writing_to_YOU\nbreak\n')
    #proc.stdin.write(b'break')
    #proc.stdin.write(b'\n')
    stdout = stdout.replace('\n', '<br />')

    return  stdout

if __name__ == "__main__":
    app.run(host='0.0.0.0')   # <----- this command ssl_context='adhoc' is for https instead of http you will need to run pip3 install pyopenssl




# while(True):
#     Uinput = input()
#     if(Uinput == 'break'):
#         proc.stdin.write(b'break\n')
#         stdout, stderr = proc.communicate()
#         print(stdout.decode('ascii'))
#         break
#     else:
#         Uinput_bytes = str.encode(Uinput)
#         proc.stdin.write(Uinput_bytes+b'\n')


# import requests
# res = requests.post('http://localhost:5000/api/add_message/1234', json={"mytext":"lalala"})
# if res.ok:
#     print res.json()

