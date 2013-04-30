#!/usr/bin/python

#
# Imports
#

import os
import sys
import time
import syslog
import traceback

# 
# Params
#

# Device where the temperature is read from
temperature_device="/sys/bus/i2c/devices/0-0048/temp1_input"

# How often the temperture is checked in seconds
check_interval=30

# After how many maximum checks the temperature is logged: 40*30 secs = 20 minutes
max_check_ticks=40

# If the difference of the last logged temperature and the current temperature exceeds max_temperature_diff it is is also logged
max_temperature_diff=2000

#
# Main
#

syslog.openlog("temperature_logger")


if not os.path.exists(temperature_device):
    syslog.syslog("temperature_device "+temperature_device+" does not exist, exiting")
    sys.exit()

try:
    ticks = 0
    last_logged_temperature = 999999
    while True:
        f = file(temperature_device, "r")
        temperature = int(f.readline().rstrip())
        f.close()
        ticks = ticks + 1

        if (ticks>=max_check_ticks) or (abs(temperature-last_logged_temperature)>max_temperature_diff):
            syslog.syslog("temperature="+str(temperature)+" last_logged="+str(last_logged_temperature)+" ticks="+str(ticks))
            last_logged_temperature = temperature
            ticks = 0

        time.sleep(check_interval)


except:
    cla, exc, trbk = sys.exc_info()
    excName = cla.__name__
    try:
        excArgs = exc.__dict__["args"]
    except KeyError:
        excArgs = "<no args>"
    excTb = traceback.format_tb(trbk)
    syslog.syslog("Stopping with Exception: name="+excName+" args="+excArgs+" tb="+str(excTb))
