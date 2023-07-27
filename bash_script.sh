#!/bin/bash

# assuming the file is in format:
# username
# password

FILE="C:/Users/Sandra/OneDrive_EPHEC_asbl/Bureau/gitPass.txt" # replace with the actual path to your file

USERNAME=$(sed -n '1p' < $FILE)
PASSWORD=$(sed -n '2p' < $FILE)

git status
git pull
git add .
git commit -a -m "Update"
git push
echo $USERNAME
sleep 1 # wait for 1 second
echo $PASSWORD

