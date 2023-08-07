## Setup

Install `USB-MIDI` Arduino library:
```
$ arduino-cli lib install USB-MIDI
```

Add your unix user to the `dialout` group for non-root access to the serial
port.

## Common Commands

### List Connected Boards

```
$ arduino-cli board list
```

### Compile a Sketch

Code must be in the file Sketch/Sketch.ino.
```
$ arduino-cli compile -b arduino:avr:uno Sketch/
```

### Upload Sketch

```
$ arduino-cli upload -b arduino:avr:uno -p /dev/ttyUSB0 Sketch/
```

### Connect a terminal to the serial port

Press Ctrl-a, Ctrl-x to exit.

```
$ picocom /dev/ttyUSB0
```
