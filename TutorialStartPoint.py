#################################################################
##### Haitao 23/11/2023 - UnitTest: Catch2 - Build: MsBuild #####
#################################################################

from sre_constants import SUCCESS
import threading
import time
import os
import sys
import subprocess

# Log file path
log_file_path = "CI_log.txt"

def log_message(message):
    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
    log_line = f"[{timestamp}] {message}\n"

    with open(log_file_path, "a") as log_file:
        log_file.write(log_line)

def RunBatchFile():
	print("||################################## Build Project ##################################|| \n")
	args = ['VS_Build.bat']
	try:
		result = subprocess.run(args, shell=True, capture_output=True, check=True)
		print("Build Result: \n" + result.stdout.decode("ascii"))
	except subprocess.CalledProcessError as e:
		print("VS Build Error: \n", e.stdout.decode("ascii"))
	
	log_message(result.stdout.decode("ascii") )


def RunGitCommand():
	print("||################################## Git Command ##################################|| \n")
	args = ['git', 'status']
	try:
		result = subprocess.run(args, capture_output=True, check=True)
		print("Git status Result: " + result.stdout.decode("ascii") )
	except subprocess.CalledProcessError as e:
		print("Git Command Error: \n", e.stderr.decode("ascii"))
	log_message(result.stdout.decode("ascii"))
		
	pullCommand = ['git', 'pull']
	try:
		result = subprocess.run(pullCommand, capture_output=True, check=True)
		if result.returncode == 0: #SUCCESS?
			print("Pull Command Success ")
		else:
			print("Pull Command failed")
		print("Git Pull Result: " + result.stdout.decode("ascii"))
	except subprocess.CalledProcessError as e:
		print("Git Command Error: \n", e.stderr.decode("ascii"))
	log_message(result.stdout.decode("ascii") )

def RunUnitTest():
	print("||################################## Unit Test ##################################|| \n")
	testCommand = ['TC_UnitTest.bat']
	result = subprocess.run(testCommand, capture_output=True, check=True)
	if(result.returncode == 1):
		print("Unit Test Start Fail")
	else:
		print("UnitTest Start Success: \n" + result.stdout.decode("ascii"))
	log_message(result.stdout.decode("ascii") )
	

def PollForChanges():
	print("CI Start: " + time.ctime())
	RunBatchFile()
	RunGitCommand()
	RunUnitTest()

def RunForever():
	WAIT_TIME_SECONDS = 10
	#ticker = threading.Event()
	#while not ticker.wait(WAIT_TIME_SECONDS):
	#	PollForChanges()
	#	print("Wait For the Next Pull")
		
	while True:
		print("Wait For the Next Pull")
		for remaining_seconds in range(WAIT_TIME_SECONDS, 0, -1):
			print(f"Countdown: {remaining_seconds} seconds", end='\r')
			time.sleep(1)
		PollForChanges()


#PollForChanges()
#input("Press Enter to exit...")
RunForever()
