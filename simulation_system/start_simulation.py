import signal
import subprocess
import pathlib
import os
import time
import atexit


import psutil


def kill(proc_pid):
    process = psutil.Process(proc_pid)
    for proc in process.children(recursive=True):
        proc.kill()
    process.kill()

dir_path = os.path.dirname(os.path.realpath(__file__))


subprocess.run(['make -C esp32_webserver native'], shell=True)
application_process = subprocess.Popen('make -C esp32_webserver run_native', shell=True, preexec_fn=os.setsid)
simulation_process = subprocess.Popen(f'python3 {dir_path}/simple_simulation.py', shell=True, preexec_fn=os.setsid)
plotter_process = subprocess.Popen(f'python3 {dir_path}/simulation_plotter.py', shell=True, preexec_fn=os.setsid)

try:
    simulation_process.wait()
except KeyboardInterrupt:
    kill(plotter_process.pid)
    kill(simulation_process.pid)
    time.sleep(0.1)
    kill(application_process.pid)