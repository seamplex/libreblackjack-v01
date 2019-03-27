#!/bin/bash

if [ ! -d soft_double ]; then
 echo "directory soft_double does not exist"
 exit 1
fi

cd soft_double

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
  result_double=`grep result_in ${player}-vs-${dealer}-double.yaml     | cut -d" " -f3`
   
  echo ${result_stand} ${result_double} | awk -f ../cell_choice.awk
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
