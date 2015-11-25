#!/usr/bin/env bash
cd /Taller2-master/servidor/build
make
make test
coveralls --exclude lib --exclude tests --gcov-options '\-lp'