BOARD = arduino:avr:uno
SERIAL_PORT = /dev/ttyUSB0
SKETCH = Sketch

compile:
	arduino-cli compile --fqbn $(BOARD) $(SKETCH)

upload:
	arduino-cli upload --fqbn $(BOARD) --port $(SERIAL_PORT) $(SKETCH)

connect:
	picocom $(SERIAL_PORT)
