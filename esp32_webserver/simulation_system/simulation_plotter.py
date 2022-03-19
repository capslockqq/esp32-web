import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import json

inputs_data = {}
outputs_data = {}

def animate(i):
    plt.cla()
    try: 
        with open('data.json') as fd:
            dict_data = json.load(fd)
    except:
        return
    
    try:
        for input_ in dict_data['inputs']:
            inputs_data[input_['id']] = input_['value']
    except:
        pass
    try:
        for output_ in dict_data['outputs']:
            outputs_data[output_['id']] = output_['value']
    except:
        pass
    for output in outputs_data:
        time_range = list(range(0, len(outputs_data[output])))
        plt.plot(time_range, outputs_data[output])


ani = FuncAnimation(plt.gcf(), animate, interval=500)
plt.show()
