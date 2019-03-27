#!/bin/bash

if [ ! -d soft_hit ]; then
 echo "directory soft_hit does not exist"
 exit 1
fi

cd soft_hit

echo "<table>"
echo " <tr>"
echo " <th></th>"
for dealer in `seq 2 9` T A; do
 echo "  <th>${dealer}</th>"
done
echo " </tr>"


for secondcard in A `seq 2 9`; do
 player="A,${secondcard}"
 echo " <tr>"
 echo "  <th>${player}</th>"
 
 for dealer in `seq 2 9` T A; do
  result_stand=`grep result_in ${player}-vs-${dealer}-stand.yaml | cut -d" " -f3`
  result_hit=`grep result_in ${player}-vs-${dealer}-hit.yaml     | cut -d" " -f3`
   
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


for secondcard in A `seq 2 9`; do
 player="A,${secondcard}"
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
