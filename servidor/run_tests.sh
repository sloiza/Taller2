#!/usr/bin/env bash

rm -f info.log
rm -f debug.log
rm -f warn.log
rm -f trace.log
rm -f error.log

cd build/test
./tests

rm -r -f rocksDB/
rm -r -f  tmp/*
