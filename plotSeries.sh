#!/bin/sh
sqlite3 /mnt/fritz/Innostor-Innostor-00/pvw/history.db "SELECT datetime(tstmp,\"unixepoch\"),val FROM sensors where name=\"$2\" and tstmp>strftime(\"%s\",datetime(\"now\",\"-2 day\"));" > /tmp/seriesData
/usr/bin/gnuplot -e "seriesName=\"$1\""  /mnt/fritz/Innostor-Innostor-00/unison/dev/plants_vs_water/plot.gnu
rm /tmp/seriesData
