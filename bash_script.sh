#!/bin/bash

FILE='../../Mes_projets/gitPassword.txt'

# assuming the file is in format:
# username
# password

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

(
  git status
  git pull
  sleep 1

  git add .
  sleep 1
  git commit -a -m "Update"
) &
wait

sleep 10
echo $USERNAME
sleep 1 # wait for 1 second
echo $PASSWORD

sleep 1
git push
