import subprocess
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

# application_process = subprocess.Popen(f'')
simulation_process = subprocess.Popen(f'python3 {dir_path}/simple_simulation.py', shell=True)
plotter = subprocess.Popen(f'python3 {dir_path}/simulation_plotter.py', shell=True)
simulation_process.wait()