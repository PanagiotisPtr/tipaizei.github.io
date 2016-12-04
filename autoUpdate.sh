#!/bin/bash
echo "Enter commit message:"
read message
echo "Parsing Data from the Internet"
python3 parse_updated.py
echo "Updating index.html"
g++ update.cpp -std=c++11
./a.out
echo "Pushing update to GitHub"
git add .
git commit -m "	$message"
git push -f
echo "Pushed Changes on GitHub"
echo "Enjoy"
sensible-browser https://github.com/PanagiotisPtr/tipaizei.github.io
sensible-browser http://www.tipaizei.tk