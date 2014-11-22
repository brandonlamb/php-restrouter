#!/bin/bash

TEST=$1".php"

clear

for i in {1..20}
do
   /usr/bin/php -f $TEST
done

