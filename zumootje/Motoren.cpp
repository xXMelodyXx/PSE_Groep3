#include "Motoren.h"
#include "Lijnsensor.h"

Motoren::Motoren() {
}

void Motoren::setSpeed(int links, int rechts) {

  motors.setSpeeds(links, rechts);
}

void Motoren :: initialiseer(Lijnsensor* l){
  for(int i = 0; i < 200; i++){
    delay(20);
    if(i <= 50 || i >= 150){
      motors.setSpeeds(-400,400);
      //Serial1.print(i);
      l->simpelCalibreer();
    }
    else{
      motors.setSpeeds(400,-400);
      //Serial1.println(i);
      l->simpelCalibreer();
    }
    
  }
  stop();
}

void Motoren::stop() {

  motors.setSpeeds(0, 0);
}

long Motoren::getEncoderLinks() {

  return encoders.getCountsLeft();
}

long Motoren::getEncoderRechts() {

  return encoders.getCountsRight();
}

void Motoren::resetEncoders() {

  encoders.getCountsAndResetLeft();
  encoders.getCountsAndResetRight();
}