#!/bin/bash

if [ ! -d hard_hit ]; then
 echo "directory hard_hit does not exist"
 exit 1
fi

cd hard_hit

echo "<table>"
echo " <tr>"
echo " <th></th>"
for dealer in 2 3 4 5 6 7 8 9 T A; do
 echo "  <th>${dealer}</th>"
done
echo " </tr>"


for player in `seq 5 20`; do
 echo " <tr>"
 echo "  <th>${player}</th>"
 playerpadded=`printf %02d ${player}`
 
 for dealer in 2 3 4 5 6 7 8 9 T A; do
  result_stand=`grep result_in ${playerpadded}-vs-${dealer}-stand.yaml | cut -d" " -f3`
  result_hit=`grep result_in ${playerpadded}-vs-${dealer}-hit.yaml     | cut -d" " -f3`
   
  echo ${result_stand} ${result_hit} | awk -f ../cell_choice.awk
 done
 echo " </tr>"
done
echo "</table>"



echo "<table>"
echo " <tr>"
echo " <th></th>"
for dealer in 2 3 4 5 6 7 8 9 T A; do
 echo "  <th>${dealer}</th>"
done
echo " </tr>"


for player in `seq 5 20`; do
 echo " <tr>"
 echo "  <th>${player}</th>"
 playerpadded=`printf %02d ${player}`
 
 for dealer in 2 3 4 5 6 7 8 9 T A; do
  result=`grep result_in ${playerpadded}-vs-${dealer}-*.yaml | awk '{print $2}' | sort -rg | head -n1`
  error=`grep error_in ${playerpadded}-vs-${dealer}-*.yaml | awk '{print $2}' | sort -rg | head -n1`
  
#   echo ${result} ${error}
  echo ${result} ${error} | awk -f ../cell_result.awk
 done
 echo " </tr>"
done
echo "</table>"


cd ..
