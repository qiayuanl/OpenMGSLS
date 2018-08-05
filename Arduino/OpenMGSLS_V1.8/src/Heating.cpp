#include "Heating.h"
#include "DueTimer.h"

bool IsHeating;

void Init_Heating(){
  pinMode(HEATING_PIN,OUTPUT);
  HEATING_TIMER.attachInterrupt(Heating).start(1);
}
void Start_Heating(){
  HEATING_TIMER.start(HEATING_PROPORTION*HEATING_CYCLE);
}
void Stop_Heating(){
  digitalWrite(HEATING_PIN,LOW);
  HEATING_TIMER.stop();
}
void Heating(){
  if(IsHeating){
    digitalWrite(HEATING_PIN,LOW);
    HEATING_TIMER.start((1-HEATING_PROPORTION)*HEATING_CYCLE);
    IsHeating = 0;

  }
  else{
    digitalWrite(HEATING_PIN,HIGH);
    HEATING_TIMER.start(HEATING_PROPORTION*HEATING_CYCLE);
    IsHeating = 1;
  }
}
