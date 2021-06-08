#!/bin/bash

# Example url: https://procomp.cs.hs-rm.de/subato/ExerciseSheet/397

# Grab args
# TODO improve this
if [ -n $1 ]; then 
  num=$1
else
  num=0
fi

if [ -n $2 ]; then
  max=$2
  echo "Grabbing Subato Exercise Sheets from $num to $max!"
else
  max=-1
  echo "Grabbing Subato Exercise Sheets from $num to infinity!"
fi

# Generate useful strings
url="https://procomp.cs.hs-rm.de/subato/ExerciseSheet/"
course="<span id=\"course\">"
close="</span>"
number="<span id=\"number\">"
exshet="<span id=\"exerciseSheet\">"

# Loop over urls, curl them and if valid, display the exercise sheet
for ((x=$num; x!=$max; x++))
do
  txt=`curl --silent $url$x`
  contcourse=`echo $txt | nokogiri -e 'puts $_.at_css("span#course")'`
  contnumber=`echo $txt | nokogiri -e 'puts $_.at_css("span#number")'`
  contexshet=`echo $txt | nokogiri -e 'puts $_.at_css("span#exerciseSheet")'`

  if [ -n "$contcourse" ] && [ -n "$contnumber" ] && [ "$contexshet" ]
  then
    echo "$url$x"
    contcoursetrim=${contcourse#$course}
    contnumbertrim=${contnumber#$number}
    contnumbertrim=${contexshet#$exshet}
    echo "    ${contcoursetrim%$close}"
    echo "    ${contnumbertrim%$close}"
    echo "    ${contexshettrim%$close}"
  fi
done
