#!/bin/bash  
echo "Parsing Data from the Internet"
python3 parse.py
echo "Updating index.html"
g++ update.cpp
./a.out
echo "Pushing update to GitHub"
git add .
git commit -m "Daily Update"
git push -f
echo "Pushed Changes on GitHub"
echo "Enjoy"
sensible-browser http://www.tipaizei.tk
exit
