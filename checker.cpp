#include <assert.h>
#include <iostream>

const int bpmLimit[] = {70, 150};
const int spo2Limit[] = {90, 100};
const int respRateLimit[] = {30, 95};

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

bool vitalIsOk(Alert* alert, const char* vitalName, float value, const int lowerLimit, const int upperLimit )
{
  if(value < lowerLimit)
  {
    alert->sendAlert(vitalName, "is low!");
    return false;
  }
  else if(value > upperLimit)
  {
    alert->sendAlert(vitalName, "is high!");
    return false;
  }
  else
  {
    return true;
  }
}

bool vitalsAreOk(Alert* alert, float bpm, float spo2, float respRate) {
  return (vitalIsOk(alert, "BPM", bpm, bpmLimit[0], bpmLimit[1]) 
    && vitalIsOk(alert, "SPO2", spo2, spo2Limit[0], spo2Limit[1]) 
    && vitalIsOk(alert, "Respiration Rate", respRate, respRateLimit[0], respRateLimit[1]));
}

int main() {
  Alert* alert = new AlertInSMS();
  
  assert(vitalsAreOk(alert, 80, 95, 60) == true);
  assert(vitalsAreOk(alert, 60, 90, 40) == false);

  assert(vitalIsOk(alert, "BPM", 80, 70, 150) == true);
  assert(vitalIsOk(alert, "SPO2", 80, 90, 100) == false);
  assert(vitalIsOk(alert, "Respiration Rate", 100, 30, 95) == false);

  alert->sendAlert("BPM", "is high!");

  alert = new AlertInSMS();
  alert->sendAlert("SPM", "is low!");
}
