#include <Preferences.h>

Preferences preferences;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();

  preferences.begin("references", false);  // we'll just store the ref values

  // to reset simulation
  //preferences.clear();

  int w = preferences.getInt("tds_water", 70);
  int m = preferences.getInt("tds_milk", 500);
  int e = preferences.getInt("tds_coolant", 800);

  int flag = preferences.getBool("iscalibrated", false);

  if (w >= 50 && w <= 300) {
    Serial.printf("water tds: %d", w);       //check if water tds within range
    if (m >= 100 & m <= 500) { 
      Serial.printf("milk tds: %d", m);    //if so check if milk tds within range
      if (e >= 300 && e <= 320) {  //if so check if coolang tds within range
        Serial.printf("coolant tds: %d", e);
      } else {
        Serial.println("coolant tds out of range. calibrating...");    
        e = 312;
        preferences.putInt("tds_coolant", e); // set to a value within range
      }
    } else {
      // set to a value within range
      Serial.println("milk tds out of range. calibrating...");
      m = 200;
      preferences.putInt("tds_milk", m);
    }
  } else {
    // set to a value within range
    Serial.println("water tds out of range. calibrating...");
    w = 100;
    preferences.putInt("tds_water", w);
  }
  flag = true;  //set to true if all values are within range
  preferences.putBool("iscalibrated", flag);
  Serial.println("the sensor is calibrated");

  delay(5000);
  ESP.restart();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}