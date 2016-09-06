#!/usr/bin/env python
import subprocess
from timeit import default_timer as timer

grupo = 6
semilla = 72057594037927935
#semilla = 720575940379279

with open("hashes.txt", "r") as f:
	for last in f: pass
	semilla=last.split(",")[1]

while True:
	comando = ["./groupNumberGenerator", str(grupo), str(semilla)]
	#print comando
	t_start = timer()
	p = subprocess.Popen(comando,
						stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	stdout, stderr = p.communicate()
	t_end = timer()
	output = str(stdout).strip()+",%s"%(t_end-t_start)
	print output
	with open("hashes.txt", "a") as f:
	    f.write(output+"\n")
	semilla = int(output.split(",")[1])
