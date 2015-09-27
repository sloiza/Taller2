#!bin/bash

curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!" 
curl -s "http://localhost:8080/page{1,2}/[1-1000]" &
pidlist="$pidlist $!"  

for job in $pidlist do 
  echo $job     
  wait $job || let "FAIL+=1" 
done  

if [ "$FAIL" == "0" ]; then 
  echo "OK!" 
else 
  echo "FAIL! Hubieron ($FAIL) fallas." 
fi