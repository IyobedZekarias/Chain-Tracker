# Run pip3 install pipenv
# Run pipenv shell
# Run pipenv install flask gunicorn flask-cors
# Command to serve wsgi is gunicorn --certfile=selfSigned.cert --keyfile=selfSigned.key --workers=15 --bind 0.0.0.0:5001 wsgi:app

from WebAPI import app

if __name__ == "__main__":
    app.run(host='0.0.0.0')