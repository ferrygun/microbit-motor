#include "MicroBit.h"

 
MicroBit uBit;

 

#define EVENT_ID    8888
char URL[] = "https://goo.gl/";
const int8_t CALIBRATED_POWERS[] = {-49, -37, -33, -28, -25, -20, -15, -10};
char W;

uint8_t advertising = 0;
uint8_t tx_power_level = 7;
uint8_t a = 0;
uint8_t b = 0;


void onControllerEvent(MicroBitEvent e) {
  a = e.value;
  W = static_cast<char>(a);
  if (a == 126)  { //check end of sequence '~'
    uBit.bleManager.stopAdvertising();
    uBit.sleep(2000); // wait 2 sec
    uBit.bleManager.advertiseEddystoneUrl(URL, CALIBRATED_POWERS[tx_power_level-1], false);
    uBit.bleManager.setTransmitPower(tx_power_level);
    uBit.display.scroll("Ok");
    memset(URL, 0, b);
    b = 0;
  } else {
    URL[b] =  W;
    b++;
  }
}

void onConnected(MicroBitEvent) {
  //uBit.display.print("C");
}

 
void onDisconnected(MicroBitEvent){
  // uBit.display.print("D");
}

int main() {
  uBit.init();
  uBit.display.scroll("DC");
  uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
  uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
  uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);
  release_fiber();
}