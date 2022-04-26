#include <GSM.h>
#include <GSM3CircularBuffer.h>
#include <GSM3IO.h>
#include <GSM3MobileAccessProvider.h>
#include <GSM3MobileCellManagement.h>
#include <GSM3MobileClientProvider.h>
#include <GSM3MobileClientService.h>
#include <GSM3MobileDataNetworkProvider.h>
#include <GSM3MobileMockupProvider.h>
#include <GSM3MobileNetworkProvider.h>
#include <GSM3MobileNetworkRegistry.h>
#include <GSM3MobileServerProvider.h>
#include <GSM3MobileServerService.h>
#include <GSM3MobileSMSProvider.h>
#include <GSM3MobileVoiceProvider.h>
#include <GSM3ShieldV1.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1BandManagement.h>
#include <GSM3ShieldV1BaseProvider.h>
#include <GSM3ShieldV1CellManagement.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM3ShieldV1ModemCore.h>
#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3ShieldV1MultiClientProvider.h>
#include <GSM3ShieldV1MultiServerProvider.h>
#include <GSM3ShieldV1PinManagement.h>
#include <GSM3ShieldV1ScanNetworks.h>
#include <GSM3ShieldV1ServerProvider.h>
#include <GSM3ShieldV1SMSProvider.h>
#include <GSM3ShieldV1VoiceProvider.h>
#include <GSM3SMSService.h>
#include <GSM3SoftSerial.h>
#include <GSM3VoiceCallService.h>
#include <Servo.h>



#include <SPI.h> // SPI
#include <MFRC522.h> // RFID
byte kart[4] = {90,00,A4,22};
#define SS_PIN 10
#define RST_PIN 9

//jjjj
#define PIN_LED2 13
#define pas 9

 Servo myservo;

 char data;
 int x;
//jjjjjj




// Déclaration 
MFRC522 rfid(SS_PIN, RST_PIN); 

// Tableau contentent l'ID
byte nuidPICC[4];

void setup() 
{ 



myservo.attach(7);
myservo.write(100);

  
//La LED reliée à la broche 12 est intialisé à l'état LOW
  digitalWrite(PIN_LED2,LOW);

 // pinMode(PIN_LED1,OUTPUT);
//digitalWrite(PIN_LED1,0);
Serial.begin(9600);
x=0;











  
  // Init RS232
  Serial.begin(9600);

  // Init SPI bus
  SPI.begin(); 

  // Init MFRC522 
  rfid.PCD_Init(); 
}
 
void loop() 
{









if (Serial.available()){
  data=Serial.read();
  if(data=='1') //wujjjjjjjj
  {myservo.write(0);
  Serial.write('1');
  }
  else if(data=='0') //wujjjjjjjj
  {
   // digitalWrite(PIN_LED2,LOW);
    myservo.write(100);
  Serial.write('0');
    }
else if(data=='2') //wujjjjjjjj
  {
    if(x+pas<255)
    x=x+pas;
   // analogWrite(PIN_LED1,x);
  Serial.write('x');
    }
else if(data=='3') //wujjjjjjjj
  {

    if((x>pas))
    x=x-pas;
    else 
    x=0;
   // analogWrite(PIN_LED1,x);
    }
    
}













//  Serial.println("1");


  
  // Initialisé la boucle si aucun badge n'est présent 
  if ( !rfid.PICC_IsNewCardPresent())
    return;

  // Vérifier la présence d'un nouveau badge 
  if ( !rfid.PICC_ReadCardSerial())
    return;

  // Enregistrer l'ID du badge (4 octets) 
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  
  // Affichage de l'ID 

 String myString = String(rfid.uid.uidByte[0]);
 String myString1 = String(rfid.uid.uidByte[1]);
 String myString2 = String(rfid.uid.uidByte[2]);
 String myString3 = String(rfid.uid.uidByte[3]);
 if((myString.equals("144"))&&(myString1.equals("249"))&&(myString2.equals("164"))&&(myString3.equals("34")))
 {
  Serial.print("1");
 }
 else
 {
  Serial.print("2");
 }
  
 
  // Re-Init RFID
  rfid.PICC_HaltA(); // Halt PICC
  rfid.PCD_StopCrypto1(); // Stop encryption on PCD
}
