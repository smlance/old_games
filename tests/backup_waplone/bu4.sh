#!/bin/bash

PW="khvq2#Te^y^#"
UN="webaddrc"
SITE="https://bissel.webserversystems.com:2083"
COOK="cookies.txt"
WPW="4a421463"

backup () {
	curl -c $COOK --location -k --silent --user $UN:$PW "${SITE}/xfercpanel/$1" >/dev/null
	curl -b $COOK --location -k --silent --data "dest=scp&email_radio=0&server=waplone.webfactional.com&user=waplone&pass=$WPW&port=22&rdir=bak"  "${SITE}/frontend/x3/backup/dofullbackup.html"
}

lines=`curl -c $COOK --location -k --silent --user $UN:$PW "${SITE}/frontend/x3/index.html" -o temp_site.txt`

echo $lines

python3 rec.py

for i in $(cat temp_site.txt)
do
	echo $i
	backup $i
	wait
done

rm temp_site.txt

#--data "server=waplone.webfactional.com&user=waplone&password=$WPW&port=22&rdir=bak"
#--user $UN:$PW
