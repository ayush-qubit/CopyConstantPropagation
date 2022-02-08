#!/bin/bash

#CC="$LLVM_HOME/bin/clang"
#OPT="$LLVM_HOME/bin/opt"
DRIVER="../build/src/Driver"
# FILENAME=$(basename $1 .ll)

clear

# echo -e "${CYANB}=======================Generate LL Files using CLANG=======================${RST}"
# $CC -emit-llvm -O0 -Xclang -disable-O0-optnone -fno-discard-value-names -S -o ./outputs/$FILENAME.ll $1
# $OPT -instnamer -S ./outputs/$FILENAME.ll -o ./outputs/$FILENAME.ll

for FILE in ./outputs/SPEC/*.ll;
do
	echo -e "${REDB}==============================Running Analysis================================${REDB} \n"
	FILENAME=$(basename $FILE .ll)
	echo -e $FILENAME
	 if [[ $FILENAME == "gobmk" ]]; then
	 	#statements
	 	continue;
	 fi
#	if [[ $FILENAME == "sjeng" ]]; then
#		#statements
#		continue;
#	fi
	$DRIVER $FILE
	# echo $FILE
	echo -e "\n"
	echo -e "${REDB}==============================Analysis Over================================${REDB} \n"
done

# echo -e "${REDB}==============================Running Analysis================================${REDB} \n"
# $DRIVER ./outputs/$FILENAME.ll
# echo -e "\n"
# echo -e "${REDB}==============================Analysis Over================================${REDB}"