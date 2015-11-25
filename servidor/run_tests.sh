#!/usr/bin/env bash

rm -f info.log
rm -f debug.log
rm -f warn.log
rm -f trace.log
rm -f error.log

cd /Taller2-master/servidor/build/test
./tests

rm -r -f rocksDB/
rm -r -f  tmp/*
