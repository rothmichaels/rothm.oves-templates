#!/bin/bash -x

# ARGUMENTS
#
# $1 = project type
# $2 = Max class name
# $3 = function prefix
# $4 = destination directory

projType=$1
maxClass=$2
funcPrefix=$3
dest=$4

templateDir=`dirname "$0"`
templateDir="$templateDir/rm.template.$projType"
echo $templateDir
newProjDir="$dest/$maxClass"

mkdir "$newProjDir"



cp "$templateDir/Info.plist" "$templateDir/maxmspsdk.xcconfig" "$newProjDir/."

sed -e "s/rm\.template\.max/$maxClass/g" "$templateDir/rm.template.max.c" | \
    sed -e "s/rm_template_max/$funcPrefix/g" > "$newProjDir/$maxClass.c"

newXCodeProjFile="$newProjDir/$maxClass.xcodeproj"
mkdir $newXCodeProjFile
cp -R "$templateDir/rm.template.max.xcodeproj/project.xcworkspace" "$newXCodeProjFile/."

sed -e "s/rm.template.max.c/$maxClass\.c/g" "$templateDir/rm.template.max.xcodeproj/project.pbxproj" \
    > "$newXCodeProjFile/project.pbxproj"
