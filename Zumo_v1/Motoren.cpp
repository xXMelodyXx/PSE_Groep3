#include "Motoren.h"

Motoren::Motoren() {
}

void Motoren::setSpeed(int links, int rechts) {

  motors.setSpeeds(links, rechts);
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