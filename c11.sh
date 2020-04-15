python -c 'import fileinput, glob;
for filename in glob.glob("mbed-os/tools/profiles/*.json"):
  for line in fileinput.input(filename, inplace=True):
    print (line.replace("\"-std=gnu++98\"","\"-std=c++11\", \"-fpermissive\""))'
