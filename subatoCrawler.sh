#!/bin/bash

# This script crawls through Subato (https://www.subato.org) and 
# looks for available ExerciseSheet pages.
# Example url: https://procomp.cs.hs-rm.de/subato/ExerciseSheet/397
# 
# How does it work?
# 1) Starting point is the first ExerciseSheet
#    https://procomp.cs.hs-rm.de/subato/ExerciseSheet/0
# 2) for loop goes until 50 non-valid results
# 3) grab the page with curl and look for these specific tags
#      <h4>(<span id="course">Objektorientierte Softwareentwicklung (AI)</span> <span id="term">WS 2017</span>)</h4>
#      <h2><span id="number">Exercise Sheet 1</span></h2>
#      <h3><span id="exerciseSheet">Klassen für Zeitangaben</span></h3>
# 4) 

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





url="https://procomp.cs.hs-rm.de/subato/ExerciseSheet/"
course="<span id=\"course\">"
close="</span>"
number="<span id=\"number\">"
exshet="<span id=\"exerciseSheet\">"

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
