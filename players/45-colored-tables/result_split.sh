#!/bin/bash

if [ ! -d split ]; then
 echo "directory split does not exist"
 exit 1
fi

cd split

echo "<table>"
echo " <tr>"
echo " <th></th>"
for dealer in `seq 2 9` T A; do
 echo "  <th>${dealer}</th>"
done
echo " </tr>"


for firstcard in `seq 2 9` T A; do
 player="${firstcard},${firstcard}"
 echo " <tr>"
 echo "  <th>${player}</th>"
 
 for dealer in `seq 2 9` T A; do
  result_stand=`grep result_in ${player}-vs-${dealer}-nosplit.yaml | cut -d" " -f3`
  result_split=`grep result_in ${player}-vs-${dealer}-split.yaml     | cut -d" " -f3`
   
  echo ${result_stand} ${result_split} | awk -f ../cell_choice.awk
 done
 echo " </tr>"
done
echo "</table>"



echo "<table>"
echo " <tr>"
echo " <th></th>"
for dealer in `seq 2 9` T A; do
 echo "  <th>${dealer}</th>"
done
echo " </tr>"


for firstcard in `seq 2 9` T A; do
 player="${firstcard},${firstcard}"
 echo " <tr>"
 echo "  <th>${player}</th>"
 
 for dealer in `seq 2 9` T A; do
  result=`grep result_in ${player}-vs-${dealer}-*.yaml | awk '{print $2}' | sort -rg | head -n1`
  error=`grep error_in ${player}-vs-${dealer}-*.yaml | awk '{print $2}' | sort -rg | head -n1`
  
  echo ${result} ${error} | awk -f ../cell_result.awk
 done
 echo " </tr>"
done
echo "</table>"


cd ..
