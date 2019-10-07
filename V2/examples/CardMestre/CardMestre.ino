/*RFID  |   Verificador de Autorização
 *  AUTOR: Guaxinim
 *  Código da biblioteca: https://github.com/GuaxinimRadical/BluExodia
 *  
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <BluExodia.h>

int y,g = 0;
String m="";

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Põe o cartão ai mestre... \n");
}

void loop() {

  //Pega as informações do cartão atual
    guy.Readf(0);

 //Se o Readf passado não pegou nada deste o começo, encerra o loop
  if(guy.Namef()==""){ 
    return;
  }else if(y==0){ //Se é o primeiro cartão no leitor, executa bob() e o define como cartão mestre  
    bob();
    }

  //Bloco que imprime se o cartão no leitor é o mestre ou não
  if(guy.Namef() == m && g==0){
    Serial.println("Acesso AUTORIZADO :)");
    g=1;
    } else if(guy.Namef() != m && g==1){
      Serial.println("Acesso NEGADO");
      g=0;
      } else{
        return;
      }

  delay(500);
  
}

void bob(){
  m = guy.Namef(); //Define o cartão mestre
  
  Serial.println("O cartão mestre agr é: "+guy.Hexf()+"\n");
  delay(500);
  y=5;
}
