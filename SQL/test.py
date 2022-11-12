#-------------------------------------------------------------
# Developer ----- Bryce Martin
# Description --- This is where I will be testing a relational
#                 Database that could be used for storage for
#                 the contents of our blockchain
#--------------------------------------------------------------

# instead of installing these packages - run this file using the virtual environment using these commands:
# 1.) install venv - pip install venv or pip3 install venv
# 2.) tap into the venv "pyenv" by using this command: source pyenv/bin/activate
# 3.) then execute the python command to run: python test.py or python3 test.py
# 4.) to exit the venv - just type deactivate

import sqlite3
from google.api_core.protobuf_helpers import get_messages
from google.cloud import storage
from datetime import datetime
import mysql.connector
import sys

# Connect to our database/create a new table: preferable each company would have their own table

def createTable(companyName):
    try:
        connection = mysql.connector.connect(user='root', password='CTLunaticLabs', host='34.66.88.75', database='chaintracker')
        cursor = connection.cursor()
        cursor.execute("CREATE TABLE IF NOT EXISTS " + companyName + "(TimeStamp TEXT, Root TEXT, Hash TEXT)")
        connection.commit()
        connection.close()
    except:
        print("Unable to connect to the server and/or execute commands. {createTable function}")

# This function will be called when a user wants to insert something into the database
#store ts root hash
def insert(companyName, Root, Hash):
    Timestamp = datetime.now()
    time = Timestamp.strftime("%m/%d/%Y/, %H:%M:%S")
    try:
        connection = mysql.connector.connect(user='root', password='CTLunaticLabs', host='34.66.88.75', database='chaintracker')
        cursor = connection.cursor()
        cursor.execute("INSERT INTO " + companyName + " VALUES (%s,%s,%s)", (time,Root,Hash))
        connection.commit()
        connection.close()
    except:
        print("Unable to connect to the server and/or execute commands. {insert function}")

# this function will let us view the database in terminal
def view(companyName):
    try:
        connection = mysql.connector.connect(user='root', password='CTLunaticLabs', host='34.66.88.75', database='chaintracker')
        cursor = connection.cursor()
        cursor.execute("SELECT * FROM " + companyName)
        rows = cursor.fetchall()
        connection.close()
        return rows
    except:
        print("Unable to connect to the server and/or execute commands. {view function}")

# Assuming if a whole company wants out of our service, we we just wipe the entire table and all of its contents
def deleteTable(companyName):
    try:
        connection = mysql.connector.connect(user='root', password='CTLunaticLabs', host='34.66.88.75', database='chaintracker')
        cursor = connection.cursor()
        cursor.execute("DROP TABLE " + companyName)
        connection.commit()
        connection.close()
    except:
        print("Unable to connect to the server and execute commands. {deleteTable function}")

# This is a function that can update table values where the hash equals a certain value. It is likely this will never be used.
# But update is apart of the REST API world.
def update(companyName, Root, Hash):
    try:
        connection = mysql.connector.connect(user='root', password='CTLunaticLabs', host='34.66.88.75', database='chaintracker')
        cursor = connection.cursor()
        cursor.execute("UPDATE " + companyName + " SET Hash=%s WHERE Root=%s",(Hash,Root))
        connection.commit()
        connection.close()
    except:
        print("Unable to connect to the server and/or execute commands. {update function}")


#testing our functions so far.
#print("got here")
#createTable("test")
#insert("test","test", "hashvalue")
update("test", "test", "changed")
#deleteTable("test")
print(view("test"))

