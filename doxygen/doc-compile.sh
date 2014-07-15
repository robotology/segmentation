#!/bin/bash

DESTINATIONXML=generated-from-xml

# clean-up
rm doc -rf
rm $DESTINATIONXML -rf

# generate doxy from xml
mkdir $DESTINATIONXML
list=`find ../ -iname *.xml | xargs`
for i in $list
do
   filename=`basename $i`
   doxyfile=${filename%%.*}
   xsltproc --output $DESTINATIONXML/$doxyfile.dox $YARP_SOURCE_DIR/scripts/yarp-module.xsl $i
done

doxygen ./generate.txt
