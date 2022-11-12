#-------------------------------------------------------------
# Developer ----- Bryce Martin
# Description --- this code will be used as interaction between
#                 our project and a NoSQL database                 
#--------------------------------------------------------------

# this is the library that we need to install to run tests
# cmds: win - pip install pyrebase4, unix/linux - pip3 install pyrebase4
import pyrebase
from datetime import date
import os
from flask import Flask, render_template, redirect, request, url_for, session


#connecting to test db
firebaseConfig = {"apiKey": "AIzaSyDxui7WG4KJp6b6Gbof5l3jJh44DTQwGHg",
  "authDomain": "chaintrackerdb.firebaseapp.com",
  "databaseURL": "https://chaintrackerdb-default-rtdb.firebaseio.com/",
  "projectId": "chaintrackerdb",
  "storageBucket": "chaintrackerdb.appspot.com",
  "messagingSenderId": "259838780730",
  "appId": "1:259838780730:web:92a8f0e1eaed42216b1c03",
  "measurementId": "G-36HQ9GQ7SY"}

firebase = pyrebase.initialize_app(firebaseConfig)

db = firebase.database()        # connection to the db
auth = firebase.auth()          # setting up an authentification
storage = firebase.storage()    # interacting with storage

app = Flask(__name__)

# @app.route('/')
# def index():
#     return "hi"

#--------------------------------------------------------------
# Authentification functions 
#--------------------------------------------------------------\
def login(email, password):
    try:
        authattempt = auth.sign_in_with_email_and_password(email,password)
        print("login worked")
        return authattempt
    except:
        print("Username/password was incorrect or not found. Try again.")

def signup(email, password, confirmation):
    try:
        if password == confirmation:
            auth.create_user_with_email_and_password(email,password)
        else:
            print("password does not match confirmation")
    except:
        print("email already exists")

#--------------------------------------------------------------
# google storage functions
#--------------------------------------------------------------
def uploadFile(filename, dbname):
    try:
        storage.child(dbname).put(filename)
    except:
        print("Unable to upload file")

def downloadFile(dbname, path, name):
    try:
        storage.child(dbname).download(path, name)
    except:
        print("download failed")

#--------------------------------------------------------------
# google real-time database functions - CRUD OPS
#--------------------------------------------------------------

# this function will be used to create tables per company/user
def create(company, key, hashlist):
    #year-month-day
    timestamp = date.today()

    date_time = timestamp.strftime("%m-%d-%Y")
    data = {"name": company, "date" : date_time, "hashlist" : hashlist}
    try:
        db.child("company").child(company).child(date_time).child(key).set(hashlist)
    except:
        print("Unable to create node entry. Please try again")

# This function will clear an entire table
def delete(company):
    try:
        db.child("company").child(company).remove()
    except:
        print("Failed to delete company table")

# This will return all the hashvalues if the user have a known key

def readHashes(company, date, key):
    hlist = []
    try:
        var = db.child("company").child(company).child(date).child(key).get()
        print(var.val())
        return var.val()
    except:
        print("Failed to retrieve values")


###########
# TESTING #
###########

#hashlist = [123, 345, 673, 2456]

#create("Lipscomb", 48928924, [123, 234, 2344,23])
#delete("Lipscomb")

readHashes("Lipscomb","03-23-2021", 48928924)


#Flask app.run
# if __name__ == "__main__":
#    app.run(debug = True)


