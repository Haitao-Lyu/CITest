import subprocess
import time
import os
from datetime import datetime

# Git repository path
repo_path = os.path.abspath("/")

# Log file path
log_file_path = "build_log.txt"

def run_command(command):
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    return process.returncode, output.decode("utf-8"), error.decode("utf-8")

def poll_changes():
    while True:
        # Check for changes in the Git repository
        status_code, output, error = run_command(f"git -C {repo_path} status --porcelain")
        
        if status_code == 0 and output:
            # Changes detected
            build_and_test()
        
        time.sleep(60)  # Poll every 1 minute

def build_and_test():
    commit_id = get_current_commit_id()

    # Build Debug configuration
    build_result_debug = build_project("Debug")

    # Build Release configuration
    build_result_release = build_project("Release")

    # Run unit tests
    test_result = run_unit_tests()

    # Record results in log file
    log_result(commit_id, build_result_debug, build_result_release, test_result)

def get_current_commit_id():
    _, commit_id, _ = run_command(f"git -C {repo_path} rev-parse HEAD")
    return commit_id.strip()

def build_project(configuration):
    # Clean and reset the repository
    run_command(f"git -C {repo_path} clean -fdx")
    run_command(f"git -C {repo_path} reset --hard")

    # Pull the latest changes
    run_command(f"git -C {repo_path} pull")

    # Build using MSBuild
    msbuild_command = f"msbuild {repo_path}/YourSolution.sln /t:Build /p:Configuration={configuration}"
    status_code, _, error = run_command(msbuild_command)

    return "Success" if status_code == 0 else f"Fail: {error}"

def run_unit_tests():
    # Run unit tests using Catch2 framework
    test_command = f"{repo_path}/path/to/your/test/executable"
    status_code, _, error = run_command(test_command)

    return "Success" if status_code == 0 else f"Fail: {error}"

def log_result(commit_id, build_debug, build_release, test_result):
    with open(log_file_path, "a") as log_file:
        log_file.write(f"{datetime.now()} - Commit ID: {commit_id}\n")
        log_file.write(f"Build (Debug): {build_debug}\n")
        log_file.write(f"Build (Release): {build_release}\n")
        log_file.write(f"Unit Test Result: {test_result}\n\n")

if __name__ == "__main__":
    poll_changes()
