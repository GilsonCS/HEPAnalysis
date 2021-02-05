#!/bin/bash

if grep -q "Setup${1}()" HEPAnalysis.h; then
  sed -i '/void Setup'${1}'();/d' HEPAnalysis.h
  sed -i '/bool '${1}'Region();/d' HEPAnalysis.h
  sed -i '/void '${1}'Selection();/d' HEPAnalysis.h
  sed -i '/void '${1}'Systematic();/d' HEPAnalysis.h
  sed -i '/void Finish'${1}'();/d' HEPAnalysis.h
else
  echo "Setup${1} DOESN'T EXIST IN HEPAnalysis.h. LEAVING FILE UNCHANGED"
fi

if grep -q "Setup${1}()" HEPAnalysis.cpp; then
  sed -i '/if( _SELECTION == "'${1}'" ) Setup'${1}'();/d' HEPAnalysis.cpp
  sed -i '/if( _SELECTION == "'${1}'" && !'${1}'Region() ) Selected = false;/d' HEPAnalysis.cpp
  sed -i '/if( _SELECTION == "'${1}'" ) '${1}'Selection();/d' HEPAnalysis.cpp
  sed -i '/if( _SELECTION == "'${1}'" ) '${1}'Systematic();/d' HEPAnalysis.cpp
  sed -i '/if( _SELECTION == "'${1}'" ) Finish'${1}'();/d' HEPAnalysis.cpp
else
  echo "Setup${1} DOESN'T EXIST IN HEPAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if grep -q "_${1}.o" Makefile; then 
  sed -i 's/ _'${1}'.o / /' Makefile
else
  echo "_${1}.o DOESN'T EXIST IN Makefile. LEAVING FILE UNCHANGED"
fi

rm _${1}.o
