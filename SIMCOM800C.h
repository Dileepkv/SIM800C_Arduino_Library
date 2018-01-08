#ifndef SIMCOM800C_h
#define SIMCOM800C_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class SIMCOM800C
{
  public:
  	
  	SIMCOM800C();
	boolean init();
  	boolean simTest();
  	boolean nwTest();
  	boolean nwReg();
  	boolean setupGPRS();
  	boolean setupHTTP();
  	
  	
  	String getIMEI();
  	String getModule();
  	String getCarrier();
  	
  	void set_apn();
  	
  	
  	String readSMS(int index);
  	String sendSMS(int number, String Data);
  	String deleteSMS();
  	
  	
  	String exCMD(String cmd);
  	
  	
	String HTTP_post(float data);
  	String HTTP_get(float data);
  	
  	    
  private:
  	
  	int s;
    char c;
    String command;
    String reply;
    
    String APN;
    String url;
}; 	

#endif
