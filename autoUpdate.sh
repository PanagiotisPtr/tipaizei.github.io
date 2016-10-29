#!/bin/bash  
echo "Parsing Data from the Internet"
python3 parse.py
echo "Updating index.html"
g++ update.cpp
./a.out
echo "Pushing update togithub"
