#!/usr/bin/python
import serial
import re
import sqlite3
import shutil
import time
import sys
import os
import signal
import psutil
import pdb



#when getting sigterm then close db
def signal_term_handler(signal, frame):
	con.commit()
	con.close()
	sys.exit(0)
 
signal.signal(signal.SIGTERM, signal_term_handler)

#checking for other instances

script_name = os.path.basename(__file__)
for p in psutil.get_process_list():
	if script_name == p.name():
		#pdb.set_trace()
		if p.pid != os.getpid():
			p.kill()

f = open(os.devnull, 'w')
sys.stdout = f

f2 = open('/mnt/fritz/Innostor-Innostor-00/pvw/log.txt', 'a')
sys.stderr = f2

ser = sys.stdin

con = sqlite3.connect('/mnt/fritz/Innostor-Innostor-00/pvw/history.db')
cur = con.cursor()  
cur.execute("CREATE TABLE IF NOT EXISTS sensors(tstmp int, Name Text, Val Real)")

# first lines are ingored
line=ser.readline()
line=ser.readline()

commitCount=0

while True:
	line=ser.readline()

	pattern = re.compile(r"""(?P<name>[^\|]+?)       # quoted name
                             \|(?P<value>.+?)\n   # whitespace, next bar, n1
                             """, re.VERBOSE)
	match = pattern.match(line)

	name = match.group("name")
	value = float(match.group("value"))
	print(commitCount)
	print(name)
	print(value)

	row=(name, value)

	cur.execute("INSERT INTO sensors VALUES (?, ?, ?)",(time.time(), name, value))

	if commitCount>100:
		con.commit()
		commitCount=0
	else:
		commitCount=commitCount+1
