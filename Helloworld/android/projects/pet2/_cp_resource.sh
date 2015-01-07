#!/bin/bash
PWD="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

GLOBAL_RESOURCE_DIR=$PWD/../../../../../../../resource/
APP_DIR=$PWD
#########################################################

echo "APP_RESOURCE_DIR	= $APP_RESOURCE_DIR"
echo "GLOBAL_RESOURCE_DIR	= $GLOBAL_RESOURCE_DIR"

echo $GLOBAL_RESOURCE_DIR

# make sure assets is exist
mkdir -p $APP_DIR/assets


echo "coping $GLOBAL_RESOURCE_DIR => $APP_DIR/assets/"
cp -rf $GLOBAL_RESOURCE_DIR/* $APP_DIR/assets/



