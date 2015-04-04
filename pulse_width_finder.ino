/*

  This program will print the width of each pulse it receives on a new line.
  Use it to find the pulse width of a bill acceptor.

  Just set the min_pulse_width to something lower than what you expect the pulse width to be.
  It is not common to have pulses of less than 8 ms so I set it to 8.

*/

#define INPUTPIN (10)

int min_pulse_width; // the minimum pulse width to acccept
int max_pulse_width; // the maximum pulse width to accept
int debounce_speed; // ignore changes in input line state that happen faster than this
int pulse_count; // how many pulses have been received so far in this pulse train

unsigned long pulse_duration; // how long was the last pulse
unsigned long pulse_begin; // when did the last pulse begin
unsigned long pulse_end; // if they pulse was within min and max pulse width, when did it end
unsigned long curtime; // what is the current time
int post_pulse_pause; // how long to wait after last pulse before sending pulse count
int pulse_state; // what is the current input line state (1 for high, 0 for low)
int last_state; // what was the last input line state

void setup() {
  delay(2000);
  pinMode(INPUTPIN, INPUT);
  Serial.begin(115200);

//  Keyboard.begin();
  pulse_begin = 0;
  last_state = 0;
  min_pulse_width = 8;
  max_pulse_width = 1000;
  debounce_speed = 4;
  post_pulse_pause = 2000;
  pulse_end = 0;
  pulse_count = 0;
}

void loop() {

  pulse_state = digitalRead(INPUTPIN);
  curtime = millis();
  if((pulse_state == 1) && (last_state == 0)) {
    pulse_begin = curtime;
    last_state = 1;
  } else if((pulse_state == 0) && (last_state == 1)) {
    pulse_duration = curtime - pulse_begin;
    if(pulse_duration > debounce_speed) {
      last_state = 0;
    }
    if(pulse_duration > min_pulse_width) {
      pulse_end = curtime;
      Serial.print(pulse_duration);
      Serial.println();      
      pulse_count++;
    }
  }
}



