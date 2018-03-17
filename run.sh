#!/bin/sh

LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH java -classpath ./common.jar systools.SysInfo
# LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH java -classpath ./ systools.SysInfo
