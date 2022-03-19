from gpg import Data
import rel
from model import Model
from websocket_interface import WebsocketInterface
import json
import copy

class DataStorage:
    def __init__(self, store_at_sample) -> None:
        self.store_at_sample = store_at_sample
        self.times_called = 0
        with open('data.json', 'w', encoding='utf-8') as f:
            pass

    def store_file(self, data):
        self.times_called += 1
        if self.times_called % self.store_at_sample != 0:
            return
        with open('data.json', 'w', encoding='utf-8') as f:
            json.dump(data, f, ensure_ascii=False, indent=4)


class RawPlantData:
    def __init__(self, model) -> None:
        self.socket = WebsocketInterface(self.io_received)
        self.all_inputs_and_outputs = {}
        self.data_to_save = {}
        self.model = model
        self.inputs_to_plant = {}
        self.storage = DataStorage(10)

    def format_data_to_save(self, first_time = False):
        for io in self.data_to_save:
            for index, _ in enumerate(self.data_to_save[io]):
                if first_time:
                    self.data_to_save[io][index]['value'] = []
                    self.data_to_save[io][index]['value'].append(self.all_inputs_and_outputs[io][index]['value'])

                else:
                    self.data_to_save[io][index]['value'].append(self.all_inputs_and_outputs[io][index]['value'])
    
    def io_received(self, ws, message):
        if (isinstance(message, dict) and message.get('all_data')):
            del message['all_data']
            self.all_inputs_and_outputs = copy.deepcopy(message)
            self.data_to_save = copy.deepcopy(message)
            self.format_data_to_save(first_time=True)
        else:
            self.update(message)
            self.format_data_to_save()
        
        self.storage.store_file(self.data_to_save)
        
        self.inputs_to_plant = self.model.simulate()

        ws.send(json.dumps(self.inputs_to_plant))

    def update_inputs_and_outputs(self, difference):
        changed_data = []
        for diff in difference:
            keys_and_indexes = diff['path'].split('/')[1:] # the first element is just empty
            if 'value' in keys_and_indexes:
                type_of_io = keys_and_indexes[0]
                index = int(keys_and_indexes[1])
                changed = keys_and_indexes[2]

                self.all_inputs_and_outputs[type_of_io][index][changed] = diff[changed]
                changed_data.append(type_of_io + str(index) + changed)
        

    def update(self, difference):
        self.update_inputs_and_outputs(difference)


if __name__ == "__main__":
    RawPlantData(model=Model())
    rel.dispatch()


    