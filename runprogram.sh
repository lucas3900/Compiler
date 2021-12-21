#!/usr/bin/bash

f=`basename $1 .decaf`
./decafc "${f}.decaf"
java -jar ~acampbel/jasmin.jar *.j > /dev/null 2> /dev/null
java "${f}_"
