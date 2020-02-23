if [ -z "`which pandoc`" ]; then 
 echo "error: pandoc not installed"
 exit 1
fi
pandoc blackjack.md --toc --template template.texi -o blackjack.texi
