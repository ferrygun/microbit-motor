#include "MicroBit.h"
MicroBit uBit;

#define EVENT_ID		 8888
#define DC_BUTTON_LEFT   1001
#define DC_BUTTON_RIGHT  1002
#define DC_STOP			 1003

uint8_t l = 0;
uint8_t r = 0;

void onConnected(MicroBitEvent) {
  //uBit.display.print("C");
}

 
void onDisconnected(MicroBitEvent){
  // uBit.display.print("D");
}


void onControllerEvent(MicroBitEvent e) {
	//Check if "Left" button is pressed ?
	if (e.value == DC_BUTTON_LEFT && l == 0)  {
		l = 1;
	}	
	if (l == 1) {
		if (e.value != DC_BUTTON_LEFT) {
			uBit.io.P12.setAnalogValue(1000 - e.value);
			uBit.io.P8.setDigitalValue(1);
			l = 0;
		}
	}

	//Check if "Right" button is pressed ?
	if (e.value == DC_BUTTON_RIGHT && r == 0)  { 
		r = 1;
	}	
	if (r == 1) {
		if (e.value != DC_BUTTON_RIGHT) {
			uBit.io.P8.setAnalogValue(1000 - e.value);
			uBit.io.P12.setDigitalValue(1);
			r = 0;
		}
	}

	//Check if buttons are released
	if (e.value == DC_STOP)  {
		uBit.io.P8.setDigitalValue(0);
		uBit.io.P12.setDigitalValue(0);
		r = 0; l = 0;
	}

}

int main() {
    uBit.init();

    uBit.init();
	uBit.display.scroll("DC");
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
	uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);
	release_fiber();
}
