#include "Arduino.h"
#include <SoftwareSerial.h>
#include <SIMCOM800C.h>

SoftwareSerial mySerial(2, 3); // RX, TX

SIMCOM800C::SIMCOM800C(){
	
	mySerial.begin(19200);
	
	mySerial.println("AT+IPR=19200");
    mySerial.println("ATE1");
	mySerial.println("AT&W");

	
}

boolean SIMCOM800C::init(){
	
	
	if(exCMD("AT").endsWith("OK")){
		return true;
	}
	
	else{
		Serial.println("Error in initializing module...");
		return false;
	}
	
	
}

boolean SIMCOM800C::simTest(){
	
		if(exCMD("AT+CPIN?").endsWith("OK")){
		if(exCMD("AT+CPIN?").substring(6) = "READY")
		{
			Serial.println("SIM IS READY");
			return (true);
		}
		else
		{
		   Serial.println("SIM NOT READY");
		   return (false);
		}	
	}
	else
	{
		return (false);
	}
	
		
}

boolean SIMCOM800C::nwTest(){
	
	if(exCMD("AT+CSQ").endsWith("OK")){
		if((exCMD("AT+CSQ").substring(5,exCMD("AT+CSQ").lastIndexOf(","))).toInt()> 10)
		{
			Serial.println((exCMD("AT+CSQ").substring(5,exCMD("AT+CSQ").lastIndexOf(","))).toInt());
			return (true);
		}
	}
	else
	{
		return (false);
	}
}

boolean SIMCOM800C::nwReg(){
	
	if(exCMD("AT+CREG?").endsWith("OK")){
		
	    if(exCMD("AT+CREG?").substring(9).toInt()==1)
		{
			Serial.println("Registerd to Network");
			return (true);
		}
		else
		{
		   Serial.println("Unable Registerd to Network");
		   return (false);
		}
	}
	else
	{
		Serial.println("Error in Network Registration");
		return (false);
	}
}

boolean SIMCOM800C::setupGPRS(){
}

String SIMCOM800C::exCMD(String cmd){

   mySerial.flush();
  
  while(mySerial.available())
  mySerial.read();
  
  command = cmd;	
  reply="";
  mySerial.println(command);
  delay(50);
  s=mySerial.available();
  
  for(int i=0;i<s;i++){
         c = mySerial.read();
         reply += c;
   }
   reply.trim();
   return(reply);

}

String SIMCOM800C::getIMEI(){
	
	
	if(exCMD("AT+GSN").endsWith("OK")){
		return (exCMD("AT+GSN").substring(0,14));
	}
	else
	{
		return ("Error in getting IMEI....");
	}
	
	
}

String SIMCOM800C::getModule(){
	
	if(exCMD("AT+GMM").endsWith("OK")){
		return (exCMD("AT+GMM").substring(0,14));
	}
	else
	{
		return ("Error in getting Module information....");
	}
	
}

String SIMCOM800C::getCarrier(){
	
	
	
	if(exCMD("AT+CSPN?").endsWith("OK")){
		return (exCMD("AT+CSPN?").substring((exCMD("AT+CSPN?").indexOf('\"')+1),(exCMD("AT+CSPN?").lastIndexOf('\"'))));
	}
	else
	{
		return ("Error in getting Carrier....");
	}
	
	
}

String SIMCOM800C::readSMS(int index){
}

String SIMCOM800C::sendSMS(int number, String Data){
}

String SIMCOM800C::deleteSMS(){
}

void SIMCOM800C::set_apn(){
	
}

bool SIMCOM800C::setupHTTP(){
	
	set_apn();
	
	Serial.println(APN);
	if(exCMD("AT+SAPBR=3,1,\"Contype\",\"GPRS\"").endsWith("OK")){
		
		delay(200);
		if(exCMD(("AT+SAPBR=3,1,\"APN\",\"" + APN + "\"")).endsWith("OK")){
			
			delay(200);
			String temp = exCMD("AT+SAPBR =1,1");
				
				delay(200);
				if(exCMD("AT+SAPBR=2,1").endsWith("OK")){
					delay(200);
					Serial.println(exCMD("AT+SAPBR=2,1").substring(1));
					delay(200);
					if(exCMD("AT+SAPBR =0,1").endsWith("OK")){
						delay(200);
						Serial.println(exCMD("AT+SAPBR=2,1").substring(10));
						return true;
					}
				}
			}
		}
		
		
	
	else{
		Serial.println("Error in GPRS Setting");
		return false;
	}
	
}

String SIMCOM800C::HTTP_post(float data){
	
	
}

String SIMCOM800C::HTTP_get(float data){
	
	
}
