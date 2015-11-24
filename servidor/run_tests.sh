#!bin/bash

rm info.log
rm debug.log
rm warn.log
rm trace.log
rm error.log

cd test
./tests

rm -r rocksDB/
rm tmp/*