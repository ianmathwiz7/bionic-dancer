#define MIDI_NOTE_MSG 144
#define CONTROLLER_MSG 176
#define NUM_ANALOG_SENSORS 6
#define THROTTLE 30

int buttonStates[14];
int scalars[6];
int offsets[6];

boolean DEBUG = true;//if you use serial monitor, set to true; otherwise false

void setup(){
  
  Serial.begin(9600);
  //this is a comment. it has no effect on the program
  /*
  this
  is 
  a 
  long
  comment
  */
  scalars[0] = 1; //light sensor
  scalars[1] = 6; //accel
  scalars[2] = 6; //accel
  scalars[3] = 6; //accel
  scalars[4] = 2; //flex 1
  scalars[5] = 1; //flex 2
  
  offsets[0] = 0;
  offsets[1] = -20;
  offsets[2] = -20;
  offsets[3] = -20;
  offsets[4] = -100;
  offsets[5] = 0;
  
  
}

void loop(){
  int readValue;
  int msgValue;
  //read digital pins
  for(int i = 3; i <=13; i++){
   readValue = digitalRead(i);
     if(readValue == HIGH){
       msgValue = 127;
      } else {
       msgValue = 0;
      }
    if(msgValue != buttonStates[i]){
      Serial.write(MIDI_NOTE_MSG);
      Serial.write(i);
      Serial.write(msgValue);
    }
    buttonStates[i] = msgValue;
  }
  //read analog pins
  
  for (int a = 0; a < NUM_ANALOG_SENSORS; a++){
    int val = analogRead(a);
    val = val/scalars[a];
    val = val + offsets[a];
    
    if(DEBUG){
      Serial.print(val);
      Serial.print(", ");
    } else {
      val = min(127, val);
      val = max(0, val);
      Serial.write(CONTROLLER_MSG);
      Serial.write(a);
      Serial.write(val);
      delay(10);
    }
  } 
  if(DEBUG)
  Serial.println("");
  delay(THROTTLE);
}
