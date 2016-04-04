set terminal png
set output "/tmp/plot.png"
set timefmt '%Y-%m-%d %H:%M:%S'
set format x "%d.%m\n%H:%M"
set xdata time
set datafile separator "|"
set y2tics
set xtics 30000
plot '/tmp/seriesData' using 1:2 title seriesName  axes x1y1, \
	'< sqlite3 /mnt/fritz/Innostor-Innostor-00/pvw/history.db "SELECT datetime(tstmp,\"unixepoch\"),val FROM sensors where name=\"T1\" and tstmp>strftime(\"%s\",datetime(\"now\",\"-2 day\"));"' using 1:2 title 'Temperatur draussen'  axes x1y2, \
	'< sqlite3 /mnt/fritz/Innostor-Innostor-00/pvw/history.db "SELECT datetime(tstmp,\"unixepoch\"),val FROM sensors where name=\"H1\" and tstmp>strftime(\"%s\",datetime(\"now\",\"-2 day\"));"' using 1:2 title 'Luftfeuchtigkeit draussen'  axes x1y2, \
	'< sqlite3 /mnt/fritz/Innostor-Innostor-00/pvw/history.db "SELECT datetime(tstmp,\"unixepoch\"),val FROM sensors where name=\"T2\" and tstmp>strftime(\"%s\",datetime(\"now\",\"-2 day\"));"' using 1:2 title 'Temperatur innen'  axes x1y2, \
	'< sqlite3 /mnt/fritz/Innostor-Innostor-00/pvw/history.db "SELECT datetime(tstmp,\"unixepoch\"),val FROM sensors where name=\"H2\" and tstmp>strftime(\"%s\",datetime(\"now\",\"-2 day\"));"' using 1:2 title 'Luftfeuchtigkeit innen'  axes x1y2
