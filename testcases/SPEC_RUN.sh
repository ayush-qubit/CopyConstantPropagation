#!/bin/bash

DRIVER="../build/src/Driver"

clear

for FILE in ./outputs/SPEC/*.ll;
do
	echo -e "${REDB}==============================Running Analysis================================${REDB} \n"
	FILENAME=$(basename $FILE .ll)
	echo -e $FILENAME
	 if [[ $FILENAME == "gobmk" ]]; then
	 	#statements
	 	continue;
	 fi
	if [[ $FILENAME == "sjeng" ]]; then
		#statements
		continue;
	fi
	$DRIVER $FILE
	echo -e "\n"
	echo -e "${REDB}==============================Analysis Over================================${REDB} \n"
done

# echo -e "${REDB}==============================Running Analysis================================${REDB} \n"
# $DRIVER ./outputs/$FILENAME.ll
# echo -e "\n"
# echo -e "${REDB}==============================Analysis Over================================${REDB}"