if [ -z "`which pandoc`" ]; then 
 echo "error: pandoc not installed"
 exit 1
fi
m4 header.m4 blackjack.md | pandoc --toc --template template.texi -o blackjack.texi
