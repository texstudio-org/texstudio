#!/bin/bash

readarray -t arr < <(curl -u $1  https://api.bintray.com/packages/sunderme/texstudio/texstudio-osx|jq -c '.versions[5:]') 

a=( $(echo $arr|sed 's/[]["]//g'))

IFS=',' read -ra ADDR <<< "$a"
for i in "${ADDR[@]}"; do 
echo "$i"; 
curl -u $1 -X DELETE  https://api.bintray.com/packages/sunderme/texstudio/texstudio-osx/versions/$i
done

readarray -t arr < <(curl -u $1  https://api.bintray.com/packages/sunderme/texstudio/texstudio-win|jq -c '.versions[5:]') 

a=( $(echo $arr|sed 's/[]["]//g'))

IFS=',' read -ra ADDR <<< "$a"
for i in "${ADDR[@]}"; do 
echo "$i"; 
curl -u $1 -X DELETE  https://api.bintray.com/packages/sunderme/texstudio/texstudio-win/versions/$i
done

readarray -t arr < <(curl -u $1  https://api.bintray.com/packages/sunderme/texstudio/texstudio-linux|jq -c '.versions[5:]') 

a=( $(echo $arr|sed 's/[]["]//g'))

IFS=',' read -ra ADDR <<< "$a"
for i in "${ADDR[@]}"; do 
echo "$i"; 
curl -u $1 -X DELETE  https://api.bintray.com/packages/sunderme/texstudio/texstudio-linux/versions/$i
done
