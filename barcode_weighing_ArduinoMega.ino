////////Arduino//////

/*
 * This code has 2 parts"
 * Barcode Scanning
 * Weight Comparison
 * 
 * 
 * USB host is used to connect the barcode scanner to Arduino Mega Board
 * Loadcell is used for weighing the items in the trolley
 */

#include <hid.h> //Add to Oleg Mazurov code to Bar Code Scanner
#include <hiduniversal.h> //Add to Oleg Mazurov code to Bar Code Scanner
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <Usb.h>
#include <usbhub.h>
#include <avr/pgmspace.h>
#include <hidboot.h>
#include <HX711_ADC.h>
#include <EEPROM.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(30,31);

const int HX711_dout = 34; //mcu > HX711 dout pin
const int HX711_sck = 35; //mcu > HX711 sck pin

HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
long t;
String bar;
String bar1 = "";
String wt;

USB Usb;
HIDUniversal Hid(&Usb); //Add this line so that the barcode scanner will be recognized, I use "Hid" below
HIDBoot<HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);

class KbdRptParser : public KeyboardReportParser
{
void PrintKey(uint8_t mod, uint8_t key); // Add this line to print character in ASCII
protected:
virtual void OnKeyDown (uint8_t mod, uint8_t key);
virtual void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);
  if (c)
  OnKeyPressed(c);
}

/* what to do when symbol arrives */
void KbdRptParser::OnKeyPressed(uint8_t key)
{
  if(key!=19) {
//     bar1 = '\0';
     bar += (char)key;
     if (bar.length()==13){ 
      bar1 = bar;
      bar = '\0';
      }
     }
//  else mySerial.write((char)0x0D);
};
KbdRptParser Prs;

void setup()
{
  //Serial.begin(9600);
  mySerial.begin(9600);
   
  if(Usb.Init()==-1) mySerial.write("OSC did not start.");
 // else mySerial.write("Barcode is Ready");
  Hid.SetReportParser(0,(HIDReportParser*)&Prs); //Change "Keyboard" for "Hid"

  LoadCell.begin();
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = 202.84433221; // uncomment this if you want to set the calibration value in the sketch
#if defined(ESP8266)|| defined(ESP32)
  //EEPROM.begin(512); // uncomment this if you use ESP8266/ESP32 and want to fetch the calibration value from eeprom
#endif
  //EEPROM.get(calVal_eepromAdress, calibrationValue); // uncomment this if you want to fetch the calibration value from eeprom

  long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    //Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    //Serial.println("Startup is complete");
  }
}

int i1,c;
float i2;
char a[6];
String wt1;

void loop()
{
  Usb.Task();//for barcode scanner
  
  /*For Weighing Sensor*/
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity
  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;
  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      if(((int)i > (i1 + 5)) || ((int)i < (i1 - 5))){ 
      i2 = i;
      c = 1;      
      } 
      else if(c == 1){
        itoa(i2,a,10);
        wt1 = String (a);
        wt = bar1 + wt1; 
        if(bar1.length() == 13){ 
          for (int i = 0; i<17; i++){
            mySerial.write(wt[i]);
            }
          bar1 = "";
          wt1 = "";
        }  
        c = 0;
      }
      
      i1 =(int)i;
      newDataReady = 0;
      t = millis();
      
    }//delay(2000);
  }
}
