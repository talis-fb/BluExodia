
#ifndef BluExodia_h
#define BluExodia_h

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class BluExodia{
  public:
    BluExodia();
    void Hearth();
    void Clean(int block);
    void ReadToSerial(int block);
    void Write(int block, String guy);
    void Dump();
    int InGame();
    String ReadToStr(int block);
    void Readf(int block);
    char Bufferf(int f);
    String Hexf();
    String Namef();
  
  private:
    char slifer[16];

};


#endif 
