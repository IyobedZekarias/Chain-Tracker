command -v pipenv >/dev/null 2>&1 || { echo "I require pipenv but it's not installed.  Aborting. Install pipenv by running command pip install pipenv" >&2; exit 1; }
pipenv run gunicorn --workers=16 --bind :5000 wsgi:app
