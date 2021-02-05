#!/bin/bash

if [ ! -e _${1}.cpp ]; then 
  echo "#include \"HEPAnalysis.h\"" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Define output variables" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "namespace ${1}{" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //int variable1Name;   [example]" >> _${1}.cpp
  echo "}" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Define output derivatives" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "void HEPAnalysis::Setup${1}() {" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======SETUP CUTFLOW==========================================================================" >> _${1}.cpp
  echo '    //_cutFlow.insert(pair<string,double>("CutName", 0) );   [example]'>> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======SETUP HISTOGRAMS=======================================================================" >> _${1}.cpp
  echo '    //makeHist( "histogram1DName", 40, 0., 40., "xlabel", "ylabel" );   [example]' >> _${1}.cpp
  echo '    //makeHist( "histogram2DName", 40, 0., 40., 100, 0., 50., "xlabel",  "ylabel", "zlabel", "COLZ" );   [example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======SETUP SYSTEMATIC HISTOGRAMS============================================================" >> _${1}.cpp
  echo '    //makeSysHist( "histogramSysName", 40, 0., 40., "xlabel", "ylabel" );   [example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======SETUP OUTPUT BRANCHES==================================================================" >> _${1}.cpp
  echo "    //_outputTree->Branch(\"variable1NameInTheTree\", &${1}::variable1Name );  [example]" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Define the selection region" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "bool HEPAnalysis::${1}Region() {">> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //-------------------------------------------------------------------------" >> _${1}.cpp
  echo "    // Cut description" >> _${1}.cpp
  echo "    //-------------------------------------------------------------------------" >> _${1}.cpp
  echo '    //if( !(CutCondition) ) return false;           [Example]' >> _${1}.cpp
  echo '    //_cutFlow.at("CutName") += evtWeight;          [Example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return true;">> _${1}.cpp
  echo "}">> _${1}.cpp  
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Write your analysis code here" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "void HEPAnalysis::${1}Selection() {">> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======ASSIGN VALUES TO THE OUTPUT VARIABLES==================================================" >> _${1}.cpp
  echo "    //${1}::variable1Name = 100;      [Example]" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======FILL THE HISTOGRAMS====================================================================" >> _${1}.cpp
  echo '    //_histograms1D.at("histogram1DName").Fill( var, evtWeight );               [Example]' >> _${1}.cpp
  echo '    //_histograms2D.at("histogram2DName").Fill( var1, var2, evtWeight );        [Example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    //======FILL THE OUTPUT TREE===================================================================" >> _${1}.cpp
  echo '    //_outputTree->Fill();' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Produce systematic histograms" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "void HEPAnalysis::${1}Systematic() {">> _${1}.cpp
  echo  >> _${1}.cpp
  echo '    //FillSystematic( "histogramSysName", var, evtWeight );  [Example]' >> _${1}.cpp
  echo "}">> _${1}.cpp  
  echo  >> _${1}.cpp
  echo  >> _${1}.cpp  
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "// Make efficiency plots" >> _${1}.cpp
  echo "//-------------------------------------------------------------------------------------------------" >> _${1}.cpp
  echo "void HEPAnalysis::Finish${1}() {" >> _${1}.cpp
  echo  >> _${1}.cpp
  echo '    //MakeEfficiencyPlot( _histograms1D.at("Matched_pt"), _histograms1D.at("all_pt"), "Match_pt" );   [example]' >> _${1}.cpp
  echo  >> _${1}.cpp
  echo "    return;">> _${1}.cpp
  echo "}">> _${1}.cpp
else
  echo "SOURCE FILE ALREADY EXISTS. NOT CREATING A NEW SOURCE FILE FOR Region ${1}"
fi




if ! grep -q "Setup${1}()" HEPAnalysis.h; then
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void Setup'${1}'();' HEPAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        bool '${1}'Region();' HEPAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void '${1}'Selection();' HEPAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void '${1}'Systematic();' HEPAnalysis.h
  sed -i '/INSERT YOUR SELECTION HERE/ i\        void Finish'${1}'();' HEPAnalysis.h
else
  echo "Setup${1} ALREADY KNOW TO HEPAnalysis.h. LEAVING FILE UNCHANGED"
fi

if ! grep -q "Setup${1}()" HEPAnalysis.cpp; then
  sed -i '/SETUP YOUR SELECTION HERE/ i\    else if( _SELECTION == "'${1}'" ) Setup'${1}'();' HEPAnalysis.cpp
  sed -i '/SET THE REGION OF YOUR SELECTION HERE/ i\        if( _SELECTION == "'${1}'" && !'${1}'Region() ) Selected = false;' HEPAnalysis.cpp
  sed -i '/CALL YOUR SELECTION HERE/ i\            if( _SELECTION == "'${1}'" ) '${1}'Selection();' HEPAnalysis.cpp
  sed -i '/PRODUCE THE SYSTEMATIC OF YOUR SELECTION HERE/ i\        if( _SELECTION == "'${1}'" ) '${1}'Systematic();' HEPAnalysis.cpp
  sed -i '/FINISH YOUR SELECTION HERE/ i\    if( _SELECTION == "'${1}'" ) Finish'${1}'();' HEPAnalysis.cpp
else
  echo "Setup${1} ALREADY KNOW TO HEPAnalysis.cpp. LEAVING FILE UNCHANGED"
fi


if ! grep -q "_${1}.o" Makefile; then 
  sed -i 's/HEPObjects.o/HEPObjects.o _'${1}'.o/' Makefile
else
  echo "_${1}.o ALREADY KNOWN TO Makefile. LEAVING FILE UNCHANGED"
fi




