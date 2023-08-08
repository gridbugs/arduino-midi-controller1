#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define SYNC_PIN 12
int sync_state = 1;

#define MIDI_CHANNEL 0

#define NUM_ANALOG_PINS 8

const int analog_pins[NUM_ANALOG_PINS] = {A0, A1, A2, A3, A4, A5, A6, A7};

int analog_state_curr[NUM_ANALOG_PINS] = {0};
int analog_state_prev[NUM_ANALOG_PINS] = {0};

int midi_state_curr[NUM_ANALOG_PINS] = {0};
int midi_state_prev[NUM_ANALOG_PINS] = {0};

unsigned long analog_timestamp[NUM_ANALOG_PINS] = {0};
unsigned long analog_timer[NUM_ANALOG_PINS] = {0};

#define ANALOG_TIMEOUT_MS 300
#define ANALOG_TIMEOUT_THRESHOLD 10

void setup() {
    Serial.begin(115200);
    pinMode(SYNC_PIN, INPUT_PULLUP);
    for (int i = 0; i < NUM_ANALOG_PINS; i++) {
        analog_state_curr[i] = analogRead(analog_pins[i]);
        midi_state_prev[i] = midi_state_curr[i];
        MIDI.sendControlChange(21 + i, midi_state_curr[i], MIDI_CHANNEL + 1);
    }
}

void loop() {
    const int sync_state_new = digitalRead(SYNC_PIN);
    const int sync = sync_state && !sync_state_new;
    sync_state = sync_state_new;
    if (sync) {
        for (int i = 0; i < NUM_ANALOG_PINS; i++) {
            MIDI.sendControlChange(21 + i, midi_state_curr[i], MIDI_CHANNEL + 1);
        }
    }
    for (int i = 0; i < NUM_ANALOG_PINS; i++) {
        analog_state_curr[i] = analogRead(analog_pins[i]);
        midi_state_curr[i] = map(analog_state_curr[i], 0, 1023, 0, 127);
        int delta = abs(analog_state_curr[i] - analog_state_prev[i]);
        if (delta > ANALOG_TIMEOUT_THRESHOLD) {
            analog_timestamp[i] = millis();
        }
        analog_timer[i] = millis() - analog_timestamp[i];
        int moving = analog_timer[i] < ANALOG_TIMEOUT_MS;
        if (moving) {
            if (midi_state_curr[i] != midi_state_prev[i]) {
                MIDI.sendControlChange(21 + i, midi_state_curr[i], MIDI_CHANNEL + 1);
                analog_state_prev[i] = analog_state_curr[i];
                midi_state_prev[i] = midi_state_curr[i];
            }
        }
    }
}
