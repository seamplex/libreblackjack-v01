#!/bin/bash

src=$1
tag=$2
dir=$3

if [ -z "${tag}" ]; then
  echo "usage: $0 src tag [dir]";
  exit
fi

if [ -z "${dir}" ]; then
  dir=../src
fi  

kws=`grep "///${tag}+" ${dir}/${src}.c | awk '{print $1}' | awk -F+ '{print $2}' | sort | uniq` 

for kw in ${kws}; do

  # keyword como definition list
  echo "\`${kw}\`"
  echo
  echo -n ':    '
  grep "///${tag}+${kw}+desc" ${dir}/${src}.c | cut -d" " -f2-
  echo  

  # detailed description
  # el cut saca los tags especiales
  # el segundo se es para poder poner links como https:/\/ (sin la barra del medio gcc piensa que es un comentario)
  echo -n ':    '
  grep "///${tag}+${kw}+detail" ${dir}/${src}.c | cut -d" " -f2- | sed 's_/\\/_//_'
  echo  

  # default
  echo -n ':    **Default:** '
  grep "///${tag}+${kw}+default" ${dir}/${src}.c | cut -d" " -f2- | sed 's_/\\/_//_'
  echo  
  echo  
  
done

echo 
