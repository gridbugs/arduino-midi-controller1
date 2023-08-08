BOARD = arduino:avr:nano
SERIAL_PORT = /dev/ttyUSB0
SKETCH = Sketch
BAUDRATE = 115200

compile:
	arduino-cli compile --fqbn $(BOARD) $(SKETCH)

upload:
	arduino-cli upload --fqbn $(BOARD) --port $(SERIAL_PORT) $(SKETCH)

connect:
	picocom --baud $(BAUDRATE) $(SERIAL_PORT)

.PHONY: compile upload connect
