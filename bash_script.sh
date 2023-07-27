#!/bin/bash

FILE='../../Mes_projets/gitPassword.txt'

# assuming the file is in format:
# username
# password
#C:\Users\Sandra\OneDrive_EPHEC_asbl\Bureau\Polytech\Mes_projets\gitP
while IFS= read -r line
do
  if [ -z "$USERNAME" ]
  then
    USERNAME="$line"
  else
    PASSWORD="$line"
  fi
done < "$FILE"


USERNAME=$(sed -n '1p' < $FILE)
PASSWORD=$(sed -n '2p' < $FILE)

git status
git pull
sleep 1

git add .
git commit -a -m "Update"
git push
sleep 1

echo $USERNAME
sleep 1 # wait for 1 second
echo $PASSWORD

