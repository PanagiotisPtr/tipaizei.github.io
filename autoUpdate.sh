#!/bin/bash
echo "Enter commit message:"
read message
#echo "Parsing Data from the Internet"
#python3 parse_updated.py
#echo "Updating index.html"
#g++ update.cpp -std=c++11
#./a.out
echo "Pushing update to GitHub"
git add .
git commit -m "Daily Update $message"
git push -f
echo "Pushed Changes on GitHub"
echo "Enjoy"
sensible-browser http://www.tipaizei.tk
