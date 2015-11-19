#!/usr/bin/env bash
echo "doxy serv"
doxygen ../servidor/Doxyconf
echo "doxy app"
doxygen ../app/Doxyconf
make html

xdg-open ../Documentation/_build/html/index.html