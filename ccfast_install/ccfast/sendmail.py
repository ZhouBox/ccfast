#!/usr/bin/python
import smtplib
import sys
import base64
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

form_email = 'XXX'
to_email = 'XXX'
smtp_server = 'XXX'
username = 'XXX'
password = 'XXX'
msg = MIMEMultipart()
msg['From'] = form_email
msg['To'] = to_email
msg['Subject'] = sys.argv[1]
body =  sys.argv[2]
con=MIMEText('<b>%s</b>' % body,'html')
msg.attach(con)

smtp = smtplib.SMTP()
smtp.connect(smtp_server,25)
smtp.ehlo()
smtp.starttls()
smtp.ehlo()
smtp.login(username,password)
smtp.sendmail(form_email, to_email, msg.as_string())
smtp.quit()
