command lsof >/dev/null 2>&1 || { echo "I require lsof but it's not installed. Aborting. Install lsof by running command sudo apt-get install lsof" >&2; exit 1; }
kill -9 $(lsof -i tcp:5000 | egrep -v "COMMAND PID USER" | awk '{print $2}' | sort -n | uniq)
rm pi pob pom