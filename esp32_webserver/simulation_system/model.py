class PlantInput:
    def __init__(self, name, id, value, inputs) -> None:
        inputs.update({
            str(name): {
                "id": id,
                "value": value
            }
        })

class Model:
    def __init__(self) -> None:
        self.plant_inputs_to_send = {"inputs": []}

        self.plant_inputs = {}
        PlantInput("pwm_signal", "some id", 12, self.plant_inputs)

    def update_plant_inputs(self):
        self.plant_inputs_to_send['inputs'] = []
        for plant_input in self.plant_inputs:
            self.plant_inputs_to_send['inputs'].append(self.plant_inputs[plant_input])

    def simulate(self):
        self.update_plant_inputs()
        return self.plant_inputs_to_send
