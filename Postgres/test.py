#-------------------------------------------------------------
# Developer ----- Bryce Martin
# Description --- This is where I will be testing a postgres
#                 Database that could be used for storage for
#                 the contents of our blockchain
#--------------------------------------------------------------

# we will need to install this package
# I have provided a file for windows user's in which they can run
# pip install "psycopg2-2.8.6-cp39-cp39-win_amd64.whl" in the corresponding filepath
import psycopg2

# Connect to our database/create a new table: preferable each company would have their own table

def createTable(tableName):
    connection = psycopg2.connect("dbname='chaintrackers-310119:us-central1:chaintracker-postgres' user = 'postgres' password = 'CTLunaticLabs' host = '34.70.129.72' port = '5432'")
    cursor = connection.cursor()
    cursor.execute("CREATE TABLE IF NOT EXISTS " + tableName + "(TimeStamp TEXT, Content TEXT, Hash TEXT)")

    connection.commit()
    connection.close()

# This function will be called when a user wants to insert something into the database
#store ts root hash
def insert(tableName, TimeStamp, Root, Hash):
    connection = psycopg2.connect("dbname='chaintrackers-310119:us-central1:chaintracker-postgres' user = 'postgres' password = 'CTLunaticLabs' host = '34.70.129.72' port = '5432'")

    #may need some string to binary input here later
    cursor = connection.cursor()
    cursor.execute("INSERT INTO " + tableName + " VALUES (%s,%s,%s)", (TimeStamp,Root,Hash))

    connection.commit()
    connection.close()

# this function will let us view the database in terminal
def view(tablename):
    connection = psycopg2.connect("dbname='chaintrackers-310119:us-central1:chaintracker-postgres' user = 'postgres' password = 'CTLunaticLabs' host = '34.70.129.72' port = '5432'")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM " + tablename)

    #this will fetch everything from our SQL command, store it in 'rows'
    rows = cursor.fetchall()
    connection.close()

    #returning the contents of the database to the terminal
    return rows

# Assuming if a whole company wants out of our service, we we just wipe the entire table and all of its contents
def deleteTable(tableName):
    connection = psycopg2.connect("dbname='chaintrackers-310119:us-central1:chaintracker-postgres' user = 'postgres' password = 'CTLunaticLabs' host = '34.70.129.72' port = '5432'")
    cursor = connection.cursor()
    cursor.execute("DROP TABLE " + tableName)

    connection.commit()
    connection.close()

# This is a function that can update table values where the hash equals a certain value. It is likely this will never be used.
# But update is apart of the REST API world.
def update(tableName, TimeStamp, Content, Hash):
    connection = psycopg2.connect("dbname='chaintrackers-310119:us-central1:chaintracker-postgres' user = 'postgres' password = 'bryce1jax' host = 'localhost' port = '5432'")
    cursor = connection.cursor()
    cursor.execute("UPDATE " + tableName + " SET TimeStamp=%s, Content=%s WHERE Hash=%s",(TimeStamp,Content,Hash))

    connection.commit()
    connection.close()


    #testing our functions so far.
print("got here")
createTable("test")
insert("test","2/22/2021","test", "hashvalue")

update("test", "2/22/2222", "content change", "hashvalue")
print(view("test"))
