#!/usr/bin/python
# Import smtplib for the actual sending function
import smtplib
import os

# Import the email modules we'll need
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

import sendMail_pw

# Open a plain text file for reading.  For this example, assume that
# the text file contains only ASCII characters.
#fp = open(textfile, 'rb')
# Create a text/plain message
msg = MIMEMultipart()
#fp.close()

# me == the sender's email address
# you == the recipient's email address
msg['Subject'] = 'plants vs water'
msg['From'] = ' chrischris.kindle23@gmail.com'
msg['To'] = 'christoph.klein23@googlemail.com,winter.dongwang@googlemail.com'

plantList=(
	{"realName": 'M0', "dbName": 'M0'},
	{"realName": 'M1', "dbName": 'M1'},
	{"realName": 'M2', "dbName": 'M2'},
	{"realName": 'M3', "dbName": 'M3'}
)

for plant in plantList:
	os.system("/mnt/fritz/Innostor-Innostor-00/unison/dev/plants_vs_water/plotSeries.sh \"" + plant["realName"] + "\" " + plant["dbName"])
	fp = open('/tmp/plot.png', 'rb')
	img = MIMEImage(fp.read())
	fp.close()
	os.remove("/tmp/plot.png")
	msg.attach(img)

# Send the message via our own SMTP server, but don't include the
# envelope header.
smtp = smtplib.SMTP_SSL()
#smtp.set_debuglevel(debuglevel)
smtp.connect('smtp.gmail.com')
smtp.login('chrischris.kindle23', sendMail_pw.mail_pw())

smtp.sendmail(msg['From'], msg["To"].split(","), msg.as_string())
smtp.quit()

