#!/usr/bin/python3

import subprocess, os, time
from datetime import datetime

INDEX_PATH = "/home/iti/index"  # List of files to verify
LOG_FILE = "/var/log/fsverity.log"  # Output log file

# Function to verify if FS-Verity is enabled on file
# Input: output of command lsattr
# Output: boolean, True if FS-Verity is enabled, False otherwise
def check_verity(attr: str) -> bool:
    if attr[20] == "V":
        return True
    else:
        return False


# Function to get attributes of file passed as argument
# Input: file path
# Output: attributes of file
def get_file_attr(file: str) -> str:
    cmd = "lsattr " + file
    r = subprocess.run(["lsattr", file], capture_output=True)
    r = str(r.stdout, "UTF-8")  # return is binary. Converting to string.
    return r


# Function to log all non FS-Verity files
# Input: timestamp, string formatted; log entry, string formatted
# Output: None
def log_entry(timestamp: str, entry: str) -> None:
    with open(LOG_FILE, "a") as log:
        log.writelines(timestamp + " " + entry)  # adding log entry


if __name__ == "__main__":
    with open(INDEX_PATH, "r") as index:
        lines = index.readlines()
        # print(lines)
        for file in lines:
            file = file[:-1]  # removing \n

            if not os.path.exists(file):  # skipping inexistent paths
                continue
            if not os.path.isfile(file):  # skipping directories
                continue

            file_attr = get_file_attr(file)

            if not check_verity(file_attr):
                timestamp = datetime.now().replace(microsecond=0)  # getting current time. Precision at seconds
                log_entry(str(timestamp), file_attr[23:])
    
    time.sleep(10) # wait 10 seconds before checking again
