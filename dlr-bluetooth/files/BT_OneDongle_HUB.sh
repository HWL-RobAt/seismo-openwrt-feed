#!/bin/bash

# Runs an repetitive inquiry for FHS-Packets to obtain remote 
# MAC, device class and RSSI and merge them with with the current 
# time and this device ID. The result is a CSV dataset which is 
# handled by a processing chain to aggregate, pack and send the 
# data to a remote server.

# author        Oliver Zimmer <Oliver.Zimmer@dlr.de>
# date          Feb 19, 2014


# set -E -o pipefail -o errexit


loop_inq() {
	hciconfig hci0 inqmode 1
	sleep 2

	while :; do
		hcitool -i hci0 inq --flush &> /dev/null
		wait
	done
}

filter() {
	while read line; do
		if [[ $line == *'Inquiry Result with RSSI (0x22) plen 15' ]]; then
			str=$line
			read line;
			str=$str$line
			# echo $str
			read -a arr <<<$str
			# $0  date
			# $1  time
			# $12 mac
			# $18 bt_class
			# $20 rssi
			echo $(date --date="${arr[0]} ${arr[1]%.*}" +%s).${arr[1]#*.}\;${arr[12]}\;${arr[18]#*0x}\;${arr[20]}
		fi
	done
}

latitude=$(uci get seismo.installation.latitude_latest)
longitude=$(uci get seismo.installation.longitude_latest)
ip=$(ifconfig ath1  | grep inet | cut -d :  -f 2 | cut -d ' ' -f 1)

cat <<EOF > config.xml
<?xml version="1.0" standalone="no"?>
<config deviceid="HUB/BT/$ip">
	<module src="file:bam.jar">
		<!-- teile dem Modul mit, dass der Knoten stationär ist -->
		<properties>
			module_is_mobile=false
			module_delta_stop_ms=60000
		</properties>
	</module>
	<input>
		<location>
			<!-- feste Position -->
			<fixed lat="$latitude" lon="$longitude" />
		</location>
		<sensor type="bluetooth/active">
			<device>
				<!-- lese Sensor 1 von STDIN -->
				<resource res="-" />
				<struct-csv delimiter=";">
					<value type="time_seconds" />
					<value type="mac" />
					<value type="bt_class" />
					<value type="rssi" />
				</struct-csv>
			</device>
		</sensor>
	</input>
	<output>
		<!-- schreibe nach STDOUT -->
		<resource res="-" />
	</output>
</config>
EOF

loop_inq & inq_pid=$!
{

	hcidump -i hci0 -t -V \
	| filter \
	| jamvm -jar jblub.jar \
		-v \
		--force \
	| jamvm -jar upload.jar \
		--debug \
		--threshold 0 \
		--interval 1m \
		--repeat 10 \
		--exec-on-timeout "/etc/init.d/dlr-bluetooth restart" \
		--out 195.37.11.173:944
	echo "Processing chain terminated"
	kill -n 9 $inq_pid;

} 2>&1 | logger -t DLR_BT & chain_pid=$!

logger -t DLR_BT "Processing chain started"

trap "{ logger -t DLR_BT 'received kill sig'; kill -9 $inq_pid; kill -9 $chain_pid; } 2> /dev/null" EXIT TERM
wait $inq_pid