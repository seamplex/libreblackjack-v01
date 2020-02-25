if [ -z "`which pandoc`" ]; then 
 echo "error: pandoc not installed"
 exit 1
fi


rm -f players.md
for i in `cat players`; do
  echo $i
#   grep 'define(case_title' ../players/${i}/README.m4 >> players.md
#   awk '/> Difficulty.*/{t=1}t' ../players/${i}/README.m4 | grep -v Difficulty >> players.md
  sed s/\#/\#\#/ ../players/${i}/README.md | grep -v ':::' | grep -v 'Index' | grep -vw '\-\-\-\-\-\-\-' >> players.md
done

./reference.sh bjinit va > conf.md

m4 header.m4 blackjack.md | pandoc --toc --template template.texi -o blackjack.texi
