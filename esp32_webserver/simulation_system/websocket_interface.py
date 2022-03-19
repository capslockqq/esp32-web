import opcode
import websocket
import _thread
import time
import rel
import json

rel.safe_read()
class WebsocketInterface:
    def __init__(self, on_message_callback) -> None:
        self.on_message_callback = on_message_callback
        self.ws = websocket.WebSocketApp("ws://127.0.0.1:9003",
                                    on_open=self.on_open,
                                    on_message=self.on_message,
                                    on_error=self.on_error,
                                    on_close=self.on_close)
        self.ws.run_forever(dispatcher=rel)  # Set dispatcher to automatic reconnection
        rel.signal(2, rel.abort)  # Keyboard Interrupt

    def on_message(self, ws: websocket.WebSocketApp, message):
        self.on_message_callback(ws, json.loads(message))

    def on_error(self, ws, error):
        print("Error", error)

    def on_close(self, ws, close_status_code, close_msg):
        print("### closed ###")

    def on_open(self, ws):
        print("Opened connection")

