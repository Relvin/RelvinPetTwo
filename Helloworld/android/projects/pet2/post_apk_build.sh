#!/bin/bash

PROJECT=$2

echo "post_apk_build:"

DEST_PATH=/home/work/projects/apks/pet2/
mkdir -p $DEST_PATH
if [ -d $DEST_PATH ]; then
	mv ../*.apk ../*.obb $DEST_PATH
	echo "apks at $DEST_PATH"
fi

