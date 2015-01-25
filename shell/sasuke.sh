#!/bin/bash
# S.A.S.U.K.E.
# User-space LKM Rootkit detection tool

PID_MAX=$(cat /proc/sys/kernel/pid_max)

if [ $(id -u) != "0" ]; then
	echo "This script must be run as root!" >&2
	exit 1
fi

function get_procs
{
	echo "Listing potentially maliciously hidden processes."
	echo "Note that most of these are nothing to worry about."
	PROC=$(ls /proc | grep -o '[0-9]*')
	for pid in `seq 0 $PID_MAX`;
	do
		kill -0 $pid 1> /dev/null 2> /dev/null 
		if [ $? -eq 0 ]; then
			contains=`ls /proc | grep -o $pid | wc -l`
			cmdline=`cat /proc/$pid/cmdline`

			if [ $contains != "1" ]; then
				echo "$pid $cmdline"
			fi
		fi
	done;
}

get_procs
