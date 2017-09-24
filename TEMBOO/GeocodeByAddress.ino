#include <Bridge.h>
#include <TembooYunShield.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Bridge.begin();
  Console.begin();
}

void loop() {
  if (calls <= maxCalls) {
    Console.println("Running GeocodeByAddress - Run #" + String(calls++));
    
    TembooYunShieldChoreo GeocodeByAddressChoreo;

    // Invoke the Temboo client
    GeocodeByAddressChoreo.begin();

    // Set Temboo account credentials
    GeocodeByAddressChoreo.setAccountName(TEMBOO_ACCOUNT);
    GeocodeByAddressChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    GeocodeByAddressChoreo.setAppKey(TEMBOO_APP_KEY);
    GeocodeByAddressChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
    
    // Identify the Choreo to run
    GeocodeByAddressChoreo.setChoreo("/Library/Google/Geocoding/GeocodeByAddress");
    
    // Run the Choreo; when results are available, print them to Console
    GeocodeByAddressChoreo.run();
    
    while(GeocodeByAddressChoreo.available()) {
      char c = GeocodeByAddressChoreo.read();
      Console.print(c);
    }
    GeocodeByAddressChoreo.close();
  }

  Console.println("Waiting...");
  delay(30000); // wait 30 seconds between GeocodeByAddress calls
}