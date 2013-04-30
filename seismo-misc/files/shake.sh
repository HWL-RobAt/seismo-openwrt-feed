#!/bin/bash

# Script für das systematische Aufzeichnen der Beschleunigungssensor-Daten 


#TODO: Warten nach jedem Durchlauf als Option (-w) einbauen und dann auf -w Flag in measure testen
#TODO: Clear Option um shake_output zu leeren

DURATION=30
HZ=''
NR=1
IN_DIR=/data
OUT_DIR=${IN_DIR}/shake_output
WLAN_DEV=ath1
GET_TIME=false
PROCEED=false

clear;

help() {

	echo "Usage: $0 -f -n -d -t -i -o -p"
	echo "These are optional arguments:"
	echo "-f	frequency in Hz"
	echo "-n	number of positions/records (default=$NR)"
	echo "-d	duration of the recording in sec (default=$DURATION)"
	echo "-t	do nothing, except getting date/time via GPS-Sensor and print it to stdout"
	echo "-i	location of .raw records (default=$IN_DIR)"
	echo "-o	where to store the record for each position (default=$OUT_DIR)"
	echo "-p	proceed without asking (ignore system date, preserve older records)"
	exit 1

}

get_args(){
		while getopts "f:n:d:ti:o:p" Opts
		do
						case $Opts in  
										f) HZ="$OPTARG";;
										n) NR="$OPTARG";;
										d) DURATION="$OPTARG";;
										t) GET_TIME=true;;
										i) IN_DIR="$OPTARG";;
										o) OUT_DIR="$OPTARG";;
										p) PROCEED=true;;
										\?) help;;
						esac	
		done
}
get_IP() {
				ifconfig $@ &> /dev/null
				if [ $? ]
				then
								IP=$( ifconfig $@  | grep addr: |sed s/^.*addr://| sed -e s/\ \ Bcast.*$//)
				else
						echo -e "$WLAN_DEV not found; Counldn't get IP"	
						exit 1
				fi
}

conf_info() {

	echo -e "Testlauf der Beschleunigungssensoren\n====================================\n"
	echo -e "Knoten-IP: $IP\nDuration: $DURATION (in sec)\nFrequency: $HZ (in Hz)\nNumber of Records: $NR\nInput Directory: $IN_DIR\nOutput Directory: $OUT_DIR\n\n"

}

del_files() {

	local freed=$(du -ch $@ | awk 'END{print $1}') 
	rm -rf $@
 	echo "All Files have been deleted. $freed have been freed."	

}

validate_date() {
			# return value 0 if date correct else 1
			# call "validate_date interactive" for interactive usage
			if [ "$1" == "interactive" ]
			then
					echo -e "System Date is: $(date)\nIs this correct? ([y]es \ [n]o) \c"
					read valid_date
					if [ $valid_date = "y" ]
					then
										return 0
					else
										echo "Trying to aquire correct date via GPS...(20 seconds)"
										data-provider -n STATION_NAME -P 0123 -l netcoords.so -d 5 | grep gps_set_system_time &> /dev/null &
										sleep	20
							 			killall data_provider	
								
										return 1
					fi
			else
							data-provider -n STATION_NAME -P 0123 -l netcoords.so -d 5 | grep gps_set_system_time &> /dev/null &
							sleep	20
							killall data_provider	
			fi					


}

measure(){
				if [ ! -d $OUT_DIR ]
				then
								mkdir -p $OUT_DIR
				fi
				if [ "$HZ" != "" ]
				then
								HZ="${HZ}Hz"
				fi

				it=1	
				while [ $it -le $NR ];
				do
					/etc/init.d/seedlink start 
					sleep $DURATION
					/etc/init.d/seedlink stop &> /dev/null
					echo ""
					for n in $(ls $IN_DIR/*.raw)
					do
							for i in old_recs		
							do
									if [ "$n" != "$i" ]
									then
													new_rec="${n}"
													break
									fi
							done
					done
					mv $new_rec $OUT_DIR/"${IP}_""${HZ}""${DURATION}s_""$(date +%d.%m.%y_%R:%S)".raw 
					echo -e "Finished Recording number $it.\n" 
					let "it+=1"
				done

}


if [ $# -lt 1 ]; then
				#help
				echo "Starting with default values."
fi

get_args $@
get_IP $WLAN_DEV
conf_info

#initially stop seedlink
if [ -e /etc/init.d/seedlink ]
	then	
				echo -e "Initially any running Seedlink Instance has been...\n"
				/etc/init.d/seedlink stop &> /dev/null				
				echo -e "\n\n"
	else
				echo "missing init-script: /etc/init.d/seedlink"
        exit 1
fi

if [ $GET_TIME = "true" ]
then
				validate_date
				echo -e "Node-IP: $IP Date: $(date)"
				exit 0			
fi


# check if there are .raw files left in /data
if [ $(ls $IN_DIR/*.raw 2> /dev/null | wc -l  2> /dev/null) -gt "0" -a $PROCEED = "false" ]
	then 
			echo "Older Records found in $IN_DIR"
			used=$(du *.raw | awk '{out=out+$1}END{print out}')
			free=$(df $IN_DIR 2>/dev/null| awk '/Filesystem/{getline; print $4}')
			echo -e "\n $IN_DIR got $free KB free discspace on it. \n"
			echo -e "The older Records (*.raw) use $used KB discspace."
			echo -e "Do you want to delete all .raw Files from $IN_DIR? ([y]es \ [n]o) \c"
			read ans
				if [ $ans = "y" ]	
					then		
						del_files *.raw
					else
						old_recs=$(ls $IN_DIR/*.raw)
				fi
		else
			echo "Older Records found in $IN_DIR"
			used=$(du *.raw | awk '{out=out+$1}END{print out}')
			free=$(df $IN_DIR 2>/dev/null| awk '/Filesystem/{getline; print $4}')
			echo -e "\n $IN_DIR got $free KB free discspace on it. \n"
			echo -e "The older Records (*.raw) use $used KB discspace.\n"
			old_recs=$(ls $IN_DIR/*.raw)
			echo "Continuing..."
fi

if [ $PROCEED = "false" ]
then
	  val=1
		while [ $val == 1 ]
			do
				echo "Time Validation"
				echo -e "===============\n"
				
				validate_date interactive
				val=$?
			done
		echo -e "\nValid System Time!\n\nStart Recording..."
		measure
		echo -e "Finished Recording!\nRecords are located in $OUT_DIR"
		exit 0	
else
				echo -e "Ignoring System Time.\n\nStart Recording..."
				measure
				echo -e "Finished Recording!\nRecords are located in $OUT_DIR"
				exit 0	

fi				















