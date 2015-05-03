#!/bin/bash

BINARY=./build/manalgo
LIST=`$BINARY -l`

mkdir outputs

for i in $LIST
do
        echo "Generating: $i"
	TIMESTAMP=`date +%s`
        $BINARY --painting $i --output ./outputs/$TIMESTAMP-$i.jpg
done
