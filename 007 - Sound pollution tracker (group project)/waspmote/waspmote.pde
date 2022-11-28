/*  
 *  
 *  
 *  
 *  Projet d'orientation
 *  21/06/2021
 *  
 *  Ce code a été adapté à partir des exemples disponibles sur le IDE du Waspmote.
 *  Notamment la partie pour la gestion de l'input en série et l'envoi des données en début du void loop.
 *  
 *  Axel Ava
 *  Sergio Guarino
 *  Marc Savioz
 *  
 *  
 *  ------ LoRaWAN Code Example -------- 
 *  
 *  Explanation: This example shows how to configure the module
 *  and send packets to a LoRaWAN gateway without ACK after join a network
 *  using ABP
 *  
 */

#include <WaspLoRaWAN.h>

// socket to use
//////////////////////////////////////////////
uint8_t socket = SOCKET0;
//////////////////////////////////////////////

// Device parameters for Back-End registration
////////////////////////////////////////////////////////////
char DEVICE_EUI[]  = "00B6FBDE963283E4";
char DEVICE_ADDR[] = "26011724";
char NWK_SESSION_KEY[] = "F43AA99B5493B7F820772582C0F9F4AF";
char APP_SESSION_KEY[] = "2397C124765A5B56C55E212D10365F33";
////////////////////////////////////////////////////////////

// Define port to use in Back-End: from 1 to 223
uint8_t PORT = 45;

// Define data payload to send (maximum is up to data rate)
char data[] = "1";

// variable
uint8_t error;

unsigned long time = 0;
int val = 0;

char message[20];
char payload_hex[20];

void setup() 
{
  USB.ON();
  USB.println(F("LoRaWAN example - Send Unconfirmed packets (no ACK)\n"));

  //////////////////////////////////////////////
  // 1. Switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(socket);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("1. Switch ON OK"));     
  }
  else 
  {
    USB.print(F("1. Switch ON error = ")); 
    USB.println(error, DEC);
  }

  //////////////////////////////////////////////
  // 2. Change data rate
  //////////////////////////////////////////////

  error = LoRaWAN.setDataRate(3);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("2. Data rate set OK"));     
  }
  else 
  { 
    USB.print(F("2. Data rate set error= ")); 
    USB.println(error, DEC);
  }

  error = LoRaWAN.setPower(3);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("2. power rate set OK"));     
  }
  else 
  { 
    USB.print(F("2. power rate set error= ")); 
    USB.println(error, DEC);
  }

  error = LoRaWAN.getPower();

  // Check status
  if ( error == 0 )
  {
    USB.print(F("3. Power level get OK. "));
    USB.print(F("Power index:"));
    USB.println(LoRaWAN._powerIndex, DEC);
  }
  else
  {
    USB.print(F("3. Power level set error = "));
    USB.println(error, DEC);
  }




  //////////////////////////////////////////////
  // 3. Set Device EUI
  //////////////////////////////////////////////

  error = LoRaWAN.setDeviceEUI(DEVICE_EUI);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("3. Device EUI set OK"));     
  }
  else 
  {
    USB.print(F("3. Device EUI set error = ")); 
    USB.println(error, DEC);
  }


  //////////////////////////////////////////////
  // 4. Set Device Address
  //////////////////////////////////////////////

  error = LoRaWAN.setDeviceAddr(DEVICE_ADDR);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("4. Device address set OK"));     
  }
  else 
  {
    USB.print(F("4. Device address set error = ")); 
    USB.println(error, DEC);
  }


  //////////////////////////////////////////////
  // 5. Set Network Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setNwkSessionKey(NWK_SESSION_KEY);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("5. Network Session Key set OK"));     
  }
  else 
  {
    USB.print(F("5. Network Session Key set error = ")); 
    USB.println(error, DEC);
  }


  //////////////////////////////////////////////
  // 6. Set Application Session Key
  //////////////////////////////////////////////

  error = LoRaWAN.setAppSessionKey(APP_SESSION_KEY);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("6. Application Session Key set OK"));     
  }
  else 
  {
    USB.print(F("6. Application Session Key set error = ")); 
    USB.println(error, DEC);
  }


  //////////////////////////////////////////////
  // 7. Save configuration
  //////////////////////////////////////////////

  error = LoRaWAN.saveConfig();

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("7. Save configuration OK"));     
  }
  else 
  {
    USB.print(F("7. Save configuration error = ")); 
    USB.println(error, DEC);
  }


  USB.println(F("\n------------------------------------"));
  USB.println(F("Module configured"));
  USB.println(F("------------------------------------\n"));

  LoRaWAN.getDeviceEUI();
  USB.print(F("Device EUI: "));
  USB.println(LoRaWAN._devEUI);  

  LoRaWAN.getDeviceAddr();
  USB.print(F("Device Address: "));
  USB.println(LoRaWAN._devAddr);  

  USB.println();  
}



void loop() 
{
  time = millis();
  memset(&message[0], 0, sizeof(message)); // clearing array
  
  
  

  USB.println("Waiting for message");
  
  while (millis()-time < 10000)
    {
        if (USB.available() > 0)
        {
            val = USB.read();
            if (val >= 40 && val <= 122) { // just making sure the characters received by the Raspberry are valid letters.
              char received_char[10];
              snprintf(received_char, sizeof(received_char), "%c", val);
              strncat(message, received_char, 1);  // adding letters to message one by one.    
            }       
        }
        
        // Condition to avoid an overflow (DO NOT REMOVE)
        if (millis() < time)
        {
            time = millis();  
        }
    }
    
  USB.println(message);
  
  Utils.hex2str((uint8_t*)message, payload_hex, strlen(message)); // converting the message to HEX
  
  //////////////////////////////////////////////
  // 1. Switch on
  //////////////////////////////////////////////

  error = LoRaWAN.ON(socket);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("1. Switch ON OK"));     
  }
  else 
  {
    USB.print(F("1. Switch ON error = ")); 
    USB.println(error, DEC);
  }


  //////////////////////////////////////////////
  // 2. Join network
  //////////////////////////////////////////////

  error = LoRaWAN.joinABP();

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("2. Join network OK"));   

    //////////////////////////////////////////////
    // 3. Send unconfirmed packet 
    //////////////////////////////////////////////

    error = LoRaWAN.sendUnconfirmed( PORT, payload_hex);

    // Error messages:
    /*
     * '6' : Module hasn't joined a network
     * '5' : Sending error
     * '4' : Error with data length    
     * '2' : Module didn't response
     * '1' : Module communication error   
     */
    // Check status
    if( error == 0 ) 
    {
      USB.println(F("3. Send Unconfirmed packet OK")); 
      Utils.blinkGreenLED(200, 10);
      
      if (LoRaWAN._dataReceived == true)
      { 
        USB.print(F("   There's data on port number "));
        USB.print(LoRaWAN._port,DEC);
        USB.print(F(".\r\n   Data: "));
        USB.println(LoRaWAN._data);
      }
    }
    else 
    {
      USB.print(F("3. Send Unconfirmed packet error = ")); 
      USB.println(error, DEC);
      Utils.blinkRedLED(200, 10);
    }
  }
  else 
  {
    USB.print(F("2. Join network error = ")); 
    USB.println(error, DEC);
  }



  //////////////////////////////////////////////
  // 4. Switch off
  //////////////////////////////////////////////

  error = LoRaWAN.OFF(socket);

  // Check status
  if( error == 0 ) 
  {
    USB.println(F("4. Switch OFF OK"));     
  }
  else 
  {
    USB.print(F("4. Switch OFF error = ")); 
    USB.println(error, DEC);
  }

  USB.println();
  delay(60000);



}




