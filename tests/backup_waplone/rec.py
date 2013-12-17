import re

f = open('./temp_site.txt', 'r+')

Lines = ""
for i in f:
	Lines += i
	
options = re.findall('<option  value="(.+?)"', Lines)

Opt = ""
for i in options:
	Opt += i
	Opt += "\n"

f.close()
f = open('./temp_site.txt', 'w')
f.write(Opt)

f.close()
