#!/bin/sh

gcc -I${JAVA_HOME}/include -luuid -I${JAVA_HOME}/include/linux -fPIC -shared SysInfo.c -o libSysInfo.so
${JAVA_HOME}/bin/javac ./systools/SysInfo.java
