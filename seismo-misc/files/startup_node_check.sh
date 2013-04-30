#!/bin/sh

export PATH=/bin:/sbin:/usr/bin:/usr/sbin

# setup opkg repository url from uci config
OPKG_REPO_URL=$(uci get seismo.installation.opkg_repo_url)
sed -i "s/src\/gz packages .*/src\/gz packages $OPKG_REPO_URL/" /etc/opkg.conf

# delete startup scripts that perform ntp sync on startup
# happens only once
if [ -f /etc/hotplug.d/iface/20-ntpd ]; then
        rm -f /etc/hotplug.d/iface/20-ntpd
fi

if [ -f /etc/hotplug.d/iface/20-ntpclient ]; then
        rm -f /etc/hotplug.d/iface/20-ntpclient
fi

# wait some time until network connects
sleep 120
 

mkdir -p /data/node_check_log
FILENAME_PREFIX=`date +%Y-%m-%d-%H:%M:%S`
CDIR=`ifconfig ath1 | grep 'inet addr:' | cut -d: -f2 | awk '{ print $1}'`
mkdir -p /data/node_check_log/$CDIR

LOG=/data/node_check_log/$CDIR/$FILENAME_PREFIX.log

echo "### OUTPUT: iwconfig ###" >> $LOG
iwconfig >> $LOG 2>&1
echo "### OUTPUT: ifconfig ###" >> $LOG
ifconfig >> $LOG 2>&1
echo "### OUTPUT: route -n ###" >> $LOG
route -n >> $LOG 2>&1
echo "### OUTPUT: iptables -L -n -v ###" >> $LOG
iptables -L -n -v >> $LOG 2>&1
echo "### OUTPUT: ps ###" >> $LOG
ps >> $LOG 2>&1
echo "### OUTPUT: dmesg ###" >> $LOG
dmesg >> $LOG 2>&1
echo "### OUTPUT: nc 127.0.0.1 2007 ###"
echo "\n" | nc 127.0.0.1 2007 >> $LOG 2>&1

exit 0
