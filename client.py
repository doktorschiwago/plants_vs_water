#!/usr/bin/python
import serial
import re
import sqlite3
import shutil
import time

ser = serial.Serial('/dev/ttyACM0', 9600)

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
