
$DESTINATIONXML="generated-from-xml"

if (test-path doc) {
    rm doc -Recurse
}

if (test-path $DESTINATIONXML) {
    rm $DESTINATIONXML -Recurse
}

if (!(test-path $DESTINATIONXML)) {
    mkdir $DESTINATIONXML
}

ls -Path ../ -Filter *.xml -Recurse | `
foreach-object {xsltproc --output "$DESTINATIONXML/$($_.basename).dox" `
$env:YARP_SOURCE_DIR\scripts\yarp-module.xsl $_.fullname}

doxygen ./generate.txt
