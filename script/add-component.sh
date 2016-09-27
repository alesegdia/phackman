#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
	echo "Invalid number of arguments"
	exit 1
fi

COMPONENT_NAME=$1
COMPONENT_FILE=`echo "${COMPONENT_NAME,,}"`.h
COMPONENT_PATH=src/ecs/component/$COMPONENT_FILE

if [ -f $COMPONENT_PATH ]; then
	echo "There is an existing file, do you really want to overwrite? (type YeS)"
	read RESPONSE
	if [[ $RESPONSE != "YeS" ]]; then
		echo "OK, not doing nothing"
		exit 1
	fi
fi

echo NAME: $COMPONENT_NAME
echo FILE: $COMPONENT_FILE
echo PATH: $COMPONENT_PATH

FILE_CONTENTS=`cat > $COMPONENT_PATH << EOF
#pragma once

class $COMPONENT_NAME
{

};
EOF
`

echo FILE CONTENTS:

cat $COMPONENT_PATH
