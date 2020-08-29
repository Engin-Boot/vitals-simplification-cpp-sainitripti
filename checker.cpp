#include <assert.h>
#include <iostream>

enum
{
  BPM,
  SPO2,
  RESPRATE,
  VITAL_LIST_SIZE
};

class Vital
{
  public:
  const char* name;
  int lowerLimit;
  int upperLimit;

  Vital(const char* vitalName, int lowerLimit, int upperLimit)
  {
    this->name = vitalName;
    this->lowerLimit = lowerLimit;
    this->upperLimit = upperLimit;
  }
};

const Vital bpm("BPM", 70, 150);
const Vital spo2("SP02", 90, 100);
const Vital respRate("Respiration Rate", 30, 95);

const Vital vitals[VITAL_LIST_SIZE] = {bpm, spo2, respRate};

class Alert
{
  public:
    virtual void sendAlert(const char* vitalName, const char* message) = 0;
};

class AlertInSMS : public Alert
{
  public:
    void sendAlert(const char* vitalName, const char* message) override
    {
      std::cout << "SMS sent: " << vitalName << "" << message << std::endl;
    }
};

class AlertInSound: public Alert
{
  public:
    void sendAlert(const char* vitalName, const char* message) override
    {
      std::cout << "Alarm sound: " << vitalName << "" << message << std::endl;
    }
};

void vitalIsOk(Alert* alert, const Vital vital, float value)
{
  if(value < vital.lowerLimit)
  {
    alert->sendAlert(vital.name, " is low!");
  }
  else if(value > vital.upperLimit)
  {
    alert->sendAlert(vital.name, " is high!");
  }
}

void vitalsAreOk(Alert* alert, const int* values) {
  for(int vitalNum = 0; vitalNum < VITAL_LIST_SIZE; vitalNum++){
    vitalIsOk(alert, vitals[vitalNum], values[vitalNum]);
  }
}

int main() {

  Alert* alert = new AlertInSMS();

  int values[VITAL_LIST_SIZE] = {80, 95, 60};

  vitalsAreOk(alert, values);             // no alert

  values[BPM] = 60;
  values[SPO2] = 90;
  values[RESPRATE] = 40;

  vitalsAreOk(alert, values);             // BPM low alert
  
  values[BPM] = 200;
  values[SPO2] = 80;
  values[RESPRATE] = 20;                  // BPM high, SPO2 low, RESPRATE low alerts

  vitalsAreOk(alert, values);

  alert = new AlertInSound();

  vitalIsOk(alert, vitals[BPM], 80);      // no alert
  vitalIsOk(alert, vitals[SPO2], 80);     // SPO2 low alert
}
