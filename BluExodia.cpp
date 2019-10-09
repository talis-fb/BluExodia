#include "BluExodia.h"

#define RST_PIN         9     
#define SS_PIN          10      
  
MFRC522 mfrc522(SS_PIN, RST_PIN); 

MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

BluExodia::BluExodia(){
   
}

void BluExodia::Hearth(){

  Serial.begin(9600);                                          
  SPI.begin();                                                  
  mfrc522.PCD_Init();  

}

void BluExodia::In(){

  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    
    return;

}

void BluExodia::Clean(int block){

  //Preparação para chave
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //-------------------------------------------

  //Variaveis necessárias
    byte buffer[34];
    byte len;


 //ESCRITA
  //----------Ler o que o cabra escreve no Serial
    len = 0;
    for (byte i = len; i < 30; i++) buffer[i] = 0;     // pad with spaces 
  //-------------------------------------------


  //----------Prepara para escrever no bloco e ver se ta certo
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("PCD_Authenticate() success: "));
  //-------------------------------------------
  
    //++++++++++++++++++++++++
  
  //----------Bloco que escreve o que ta no bloco anterior
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: "));
  //-------------------------------------------



  //----------Bloco de encerramento
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //-------------------------------------------

  Serial.print("Limpo");
}

void BluExodia::ReadToSerial(int block){
  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[18];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  

  //----------Imprime o nome
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  //-------------------------------------


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}

void BluExodia::Write(int block, String guy){
  
  //Preparação para chave
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //-------------------------------------------

  //Variaveis necessárias
    byte buffer[34];
    byte len;


  //ESCRITA
  //----------Ler o que o cabra enviou
    len = guy.length(); 
    for (byte i = len; i < 30; i++){ 
      buffer[i] = 0;     // pad with spaces 
    }
    guy.getBytes(buffer,len+1);
  //-------------------------------------------


  //----------Prepara para escrever no bloco e ver se ta certo
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Autenticação = Deu ruim "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    //else Serial.println(F("Autenticação = Xuxu beleza "));
  //-------------------------------------------
  
    //++++++++++++++++++++++++
  
  //----------Bloco que escreve o que ta no bloco anterior
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Escrita = Ih, deu merda :( "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("Escrita = Nice :)  "));
  //-------------------------------------------



  //----------Bloco de encerramento
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //-------------------------------------------

  Serial.print("Fim da Escrita");
  Serial.println(" ");
}

void BluExodia::Dump(){
 

	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

}

int BluExodia::InGame(){

	return mfrc522.PICC_IsNewCardPresent();

}

String BluExodia::ReadToStr(int block){

  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[len];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  //----------Armazena o nome na String
  String guy="";
  for (int i = 0; i < 16; i++)
  {
    if (buffer1[i]!=0)
    {
      guy= guy+String(buffer1[i],HEX)+" ";
    }   
  }
  //-------------------------------------

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

  return guy;
}

void BluExodia::Readf(int block){

  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[18];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  //----------Buffer salvo
  for(int i=0; i<16;i++){
    slifer[i]= buffer1[i];
   }
  //-----------------------

  delay(100); 

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}

char BluExodia::Bufferf(int f){
  return slifer[f];
}

String BluExodia::Hexf(){

    String guy="";
  
  for (int i = 0; i < 16; i++)
  {
    if (slifer[i]!=0)
    {
      guy= guy+String(slifer[i],HEX)+" ";
    }   
  }

  return guy;
}

String BluExodia::Namef(){
  
    String guy="";
  
  for (int i = 0; i < 16; i++)
  {
    if (slifer[i]!=0)
    {
      guy= guy+String(slifer[i]);
    }   
  }

  return guy;
}

//
//Funções W
//

void BluExodia::wClean(int block){

  //Preparação para chave
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //-------------------------------------------

  //Detecta se tem um cartão no leitor, se sim, prosegue
  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    
  //-------------------------------------------


  //Variaveis necessárias
    byte buffer[34];
    byte len;


 //ESCRITA
  //----------Ler o que o cabra escreve no Serial
    len = 0;
    for (byte i = len; i < 30; i++) buffer[i] = 0;     // pad with spaces 
  //-------------------------------------------


  //----------Prepara para escrever no bloco e ver se ta certo
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("PCD_Authenticate() success: "));
  //-------------------------------------------
  
    //++++++++++++++++++++++++
  
  //----------Bloco que escreve o que ta no bloco anterior
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("MIFARE_Write() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("MIFARE_Write() success: "));
  //-------------------------------------------



  //----------Bloco de encerramento
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //-------------------------------------------

  Serial.print("Limpo");
}

void BluExodia::wReadToSerial(int block){
  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  //Detecta se tem um cartão no leitor, se sim, prosegue

  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    
  //---------------------------------------


  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[18];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  

  //----------Imprime o nome
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  //-------------------------------------

  delay(500); 

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}

void BluExodia::wWrite(int block, String guy){
  
  //Preparação para chave
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  //-------------------------------------------


  //Detecta se tem um cartão no leitor, se sim, prosegue

  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    
  //-------------------------------------------
  Serial.println(F("Cartão Detectado!"));



  //Variaveis necessárias
    byte buffer[34];
    byte len;


  //ESCRITA
  //----------Ler o que o cabra enviou
    len = guy.length(); 
    for (byte i = len; i < 30; i++){ 
      buffer[i] = 0;     // pad with spaces 
    }
    guy.getBytes(buffer,len+1);
  //-------------------------------------------


  //----------Prepara para escrever no bloco e ver se ta certo
    //Serial.println(F("Authenticating using key A..."));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Autenticação = Deu ruim "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    //else Serial.println(F("Autenticação = Xuxu beleza "));
  //-------------------------------------------
  
    //++++++++++++++++++++++++
  
  //----------Bloco que escreve o que ta no bloco anterior
    status = mfrc522.MIFARE_Write(block, buffer, 16);
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Escrita = Ih, deu merda :( "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      return;
    }
    else Serial.println(F("Escrita = Nice :)  "));
  //-------------------------------------------



  //----------Bloco de encerramento
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  //-------------------------------------------

  Serial.print("Fim da Escrita");
  Serial.println(" ");
}

void BluExodia::wDump(){
  
  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    

	mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

}

String BluExodia::wReadToStr(int block){

  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  //Detecta se tem um cartão no leitor, se sim, prosegue
    do{
      while ( ! mfrc522.PICC_IsNewCardPresent()) {
        //Um grande e magnifico nada :)
        }
     }while (! mfrc522.PICC_ReadCardSerial());
    

  //---------------------------------------


  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[len];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  //----------Armazena o nome na String
  String guy="";
  for (int i = 0; i < 16; i++)
  {
    if (buffer1[i]!=0)
    {
      guy= guy+String(buffer1[i],HEX)+" ";
    }   
  }
  //-------------------------------------

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

  return guy;
}

void BluExodia::wReadf(int block){

  //Preparação para chave
     for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    //Variaveis q ira se precisar
    byte len;

  //-------------------------------------------

  //Detecta se tem um cartão no leitor, se sim, prosegue
  
  do{
    while ( ! mfrc522.PICC_IsNewCardPresent()) {
      //Um grande e magnifico nada :)
      }
    }while (! mfrc522.PICC_ReadCardSerial());
    

  //---------------------------------------


  len = 18; //Aparentemente len deve ser igual ao tamanho dos Buffers
  
  //-----------------Pega e ver se ta certo
  byte buffer1[18];
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  //-------------------------------------

  //----------Buffer salvo
  for(int i=0; i<16;i++){
    slifer[i]= buffer1[i];
   }
  //-----------------------

  delay(100); 

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

}

