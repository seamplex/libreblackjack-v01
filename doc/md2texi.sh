if [ -e ../.hg ]; then
  cat << EOF > version.texi
@set UPDATED `hg log -r tip --template="{date|shortdate}"`
@set UPDATED-MONTH `hg log -r tip --template="{date|shortdate}"`
@set EDITION 
@set VERSION 0.1.`hg log -r tip --template="{rev}"`
EOF
fi
pandoc README.md -o libreblackjack.texi --template template.texi
