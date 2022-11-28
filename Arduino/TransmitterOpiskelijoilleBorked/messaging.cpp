#include "messaging.h"
#include "accelerator.h"
#include <arduino.h>

Messaging::Messaging()
{
  Serial.println("messaging created!");
  pmanager = new RHReliableDatagram(driver, TRANSMITTER_ADDRESS);
 
  if (!pmanager->init())
    Serial.println("Radiohead manager init failed");

}

Messaging::~Messaging()
{
  Serial.println("Messaging deleted!");
  delete pmanager;
}
void Messaging::createMessage(Measurement m)
{
      //int test = 420;
      uint8_t highx = m.x>>8;
      uint8_t lowx = m.x&0x00ff;
      uint8_t highy = m.y>>8;
      uint8_t lowy = m.y&0x00ff;
      uint8_t highz = m.z>>8;
      uint8_t lowz = m.z&0x00ff;

      data[0] = highx;
      data[1] = lowx;
      data[2] = highy;
      data[3] = lowy;
      data[4] = highz;
      data[5] = lowz;
      
      Serial.println(highx);
      Serial.println(lowx);
      Serial.println(highy);
      Serial.println(lowy);
      Serial.println(highz);
      Serial.println(lowz);

      messageLength = 6;
}
bool Messaging::sendMessage(uint8_t id, uint8_t flags)
{
     unsigned long start = millis(); 
     unsigned long timeout = millis()-start;
     while(timeout<500)
     {
      timeout = millis()-start; 
     }
     driver.setModeTx();
     uint8_t to = RECEIVER_ADDRESS;
     uint8_t from = TRANSMITTER_ADDRESS;
     
     pmanager->setHeaderTo(to);
     pmanager->setHeaderFrom(from);
     pmanager->setHeaderId(id);
     pmanager->setHeaderFlags(flags);
     
     bool returnValue = false;
  
     if (pmanager->sendto(data, messageLength, RECEIVER_ADDRESS))
     {
        returnValue = true;
     }
     pmanager->waitPacketSent();   
     return returnValue;

}
bool Messaging::receiveACK()
{
    driver.setModeRx();
    unsigned long start = millis(); 
    unsigned long timeout = millis()-start;
    bool receiverResult = false;
    uint8_t to;
    uint8_t from;
    uint8_t len;
    uint8_t id;
    uint8_t flags;
    while((timeout<1500) && (!pmanager->available()))
    {
      timeout = millis()-start;       
    }

    // Jos while luupista päästään, niin on saatu ACK tai on kulunut 1s
    receiverResult = pmanager->recvfrom(buf,&len,&from,&to,&id,&flags);
    if(receiverResult)
    {
      Serial.println("ACK received");
      Serial.println((char *)buf);
      Serial.print("Lähetettiin osoitteesta = ");
      Serial.println(from);
      Serial.print("ID = ");
      Serial.println(id);
      Serial.print("flags = ");
      Serial.println(flags);
      return true;
    }
    else
    {
      Serial.println("ACK not received, retransmit");
      return false;
    }

}
