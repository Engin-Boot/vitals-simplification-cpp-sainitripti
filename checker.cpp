#include <assert.h>

const int bpmLowerLimit = 70;
const int bpmUpperLimit = 150;
const int spo2Limit = 90;
const int respRateLowerLimit = 30;
const int respRateUpperLimit = 95;

bool bpmIsOk(float bpm) {
  return (bpm >= bpmLowerLimit && bpm <= bpmUpperLimit);
}

bool spo2IsOk(float spo2) {
  return spo2 >= spo2Limit;
}

bool respRateIsOk(float respRate) {
  return (respRate >= respRateLowerLimit && respRate <= respRateUpperLimit);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  if( bpmIsOk(bpm) && spo2IsOk(spo2) && respRateIsOk(respRate)) {
    return true;
  }
  return false;
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
