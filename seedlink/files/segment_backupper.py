#!/usr/bin/python

#
# Imports
#

from __future__ import with_statement
import os
import subprocess
import sys
import time
import syslog
import traceback

# 
# Params
#

backup_dir="/data/seedlink"                 # Where to backup the segments
max_backup_segments=80                      # How much segments should be kept
segment_size=8388608                        # How big is a segment when finished
block_size=65536                            # Block size for copying with dd
seedlink_ini="/var/seedlink/seedlink.ini"   # Where is the seedlink ini file
sleep_interval=1800                         # How often should it check for new finished segments

src_segments=0    # Filled by read_params_from_seedlink_ini(): How much segments are in the src dir
src_dir=""        # Filled by read_params_from_seedlink_ini(): Which is the src dir


#
# Reads the parameters segments, station_name and filebase from
# seedlink.ini file to fill src_segments and src_dir
#

def read_params_from_seedlink_ini():
    filebase = ""
    station_name = ""
    global src_segments
    global src_dir

    with open(seedlink_ini) as f:
        for line in f:
            if line.startswith("             name ="):
                station_name = line.partition(" = ")[2].rstrip()
            if line.startswith("segments ="):
                src_segments = line.partition(" = ")[2].rstrip()
            if line.startswith("filebase ="):
                filebase = line.partition(" = ")[2].rstrip()
                

    if src_segments == 0 or station_name == "" or filebase == "":
        syslog.syslog("seedlink.ini param missing, station_name="+station_name+" src_segments="+src_segments+" filebase="+filebase)
        sys.exit(1)
    else:
        src_dir=filebase+"/"+station_name+"/segments"
        syslog.syslog("read_params: src_segments="+src_segments+" src_dir="+src_dir)


#
# This function finds all files that are finished (have size segment_size) 
# in src_dir which don't already exist in backup_dir and returns them
#

def find_finished_uncopied_segments():
    src_files = os.listdir(src_dir)
    backup_files = os.listdir(backup_dir)
    segments = []

    for segment in src_files:
        if os.path.getsize(src_dir + "/" + segment) == segment_size:
            if segment not in backup_files:
                segments += [segment]
    return segments

#
# Deletes the oldest segment file in backup_dir (where "oldest" means
# the file with the smallest name
#

def delete_oldest_backup_segment():
    backup_files = os.listdir(backup_dir)
    backup_files.sort()
    syslog.syslog("Removing "+backup_dir+"/"+backup_files[0])
    os.remove(backup_dir+"/"+backup_files[0])

#
# Copies a segment from src to dst with dd and the specified block_size
# Output is redirected to /dev/null
#

def copy_segment(src, dst):
    ret_value = subprocess.Popen("dd if="+src+" of="+dst+" bs="+str(block_size), shell=True, stdout=open('/dev/null', 'w'), stderr=subprocess.STDOUT).wait()
    return ret_value

#
# Does all the work for backupping the files...
# 1. uses find_finished_uncopied_segments() to find the segments which should get backupped
# 2. calls delete_oldest_backup_segment() as often as needed
# 3. copies the segments with copy_segment()
#

def backup_segments():
    finished_uncopied_segments = find_finished_uncopied_segments()
    files_in_backup_dir = len(os.listdir(backup_dir))

    while files_in_backup_dir + len(finished_uncopied_segments) > max_backup_segments:
        delete_oldest_backup_segment()
        files_in_backup_dir = len(os.listdir(backup_dir))

    for segment in finished_uncopied_segments:
        return_value = copy_segment(src_dir+"/"+segment, backup_dir+"/"+segment)
        stat_value = os.stat(src_dir+"/"+segment)
        syslog.syslog("Backupped "+src_dir+"/"+segment+" to "+backup_dir+"/"+segment+" mtime="+time.ctime(stat_value.st_mtime)+" return_value="+str(return_value))

#
# This function is the reverse function of backup_segment and should
# get called at initialization before the seedlink server is started.
# It copies [src_segments] segments from the backup_dir to the src_dir.
#
def init_from_backups():
    backup_files = os.listdir(backup_dir)
    backup_files.sort()
    backup_files.reverse()

    n = int(src_segments)
    if n > len(backup_files): n = len(backup_files)

    for i in range(0, n):
        return_value = copy_segment(backup_dir+"/"+backup_files[i], src_dir+"/"+backup_files[i])
        syslog.syslog("Initial copy from "+backup_dir+"/"+backup_files[i]+" to "+src_dir+"/"+backup_files[i]+" return_value="+str(return_value))

#
# Main
#

syslog.openlog("segment_backupper")
syslog.syslog("segment_backupper started")


try:
    read_params_from_seedlink_ini()

    if len(sys.argv) > 1 and sys.argv[1] == "init": 
        if not os.path.exists(src_dir):
            syslog.syslog("makedirs("+src_dir+")")
            os.makedirs(src_dir)
        if not os.path.exists(backup_dir): 
            syslog.syslog("makedirs("+backup_dir+")")
            os.makedirs(backup_dir)
        init_from_backups()

    else: 
        while True:
            backup_segments()
            time.sleep(sleep_interval)

except:
    cla, exc, trbk = sys.exc_info()
    excName = cla.__name__
    try:
        excArgs = exc.__dict__["args"]
    except KeyError:
        excArgs = "<no args>"
    excTb = traceback.format_tb(trbk)
    syslog.syslog("Stopping with Exception: name="+excName+" args="+excArgs+" tb="+str(excTb))
