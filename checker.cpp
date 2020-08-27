#include <assert.h>

const int bpmLimit[] = {70, 150};
const int spo2Limit[] = {90, 100};
const int respRateLimit[] = {30, 95};

bool vitalIsOk(float value, int lowerLimit, int upperLimit )
{
  return (value >= lowerLimit && value <= upperLimit);
}

bool vitalsAreOk(float bpm, float spo2, float respRate) {
  return (vitalIsOk(bpm, bpmLimit[0], bpmLimit[1]) 
    && vitalIsOk(spo2, spo2Limit[0], spo2Limit[1]) 
    && vitalIsOk(respRate, respRateLimit[0], respRateLimit[1]));
}

int main() {
  assert(vitalsAreOk(80, 95, 60) == true);
  assert(vitalsAreOk(60, 90, 40) == false);
}
