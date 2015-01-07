#!/bin/bash

PROJECT=$2

echo "pre_apk_build:"

#cp icons
if [ -f icons/$PROJECT.png ]; then
	echo "    overridding "icons/$PROJECT.png
	mkdir -p res/drawable/;
	cp icons/$PROJECT.png res/drawable/icon.png
fi

#mv weixin callback 
WXPATH=src/`cat packagename.xml | sed 's/\./\//g'`
mkdir -p $WXPATH
mv inc-modules/umengsocial/src/com/gamed9/platform/umengsocial/wxapi $WXPATH
echo "moving wxapi => "$WXPATH;
sleep 2;

#app replace
if [ -f config/$PROJECT/app_replace/ ]; then
	echo "    overridding  "config/$PROJECT/app_replace/
	cp -rf config/$PROJECT/app_replace/* .
fi

#cpp defines
ANDROID_DEFINE_FILE=`pwd`/config/$PROJECT/android_platform_defines.h
if [ -f $ANDROID_DEFINE_FILE ]; then
	cp $ANDROID_DEFINE_FILE ../gamenative/android_platform_defines.h
else
	echo "//" > ../gamenative/android_platform_defines.h
fi

#build native cpp
pushd ../pet2;
./_build_native.sh ;
BUILD_NATIVE_RESULT=$?
popd;
cp -rf ../pet2/libs/armeabi libs/
if [ $BUILD_NATIVE_RESULT != 0 ]; then
	echo "BuildNative failed";
	exit 1;
fi


#app overlay

# app config
if [ -f config/$PROJECT/app_config.sh ]; then
	pushd config/$PROJECT/>/dev/null;
	./app_config.sh;
	popd >/dev/null;
fi

#cp resources
./_cp_resource.sh $*;

sleep 2;

