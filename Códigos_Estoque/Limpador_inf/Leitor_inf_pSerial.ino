#include <BluExodia.h>

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Insira cartão");
}

void loop() {

  guy.In();
  guy.ReadToSerial(62);
  //Serial.println("Informação do Produto limpa");
  
  guy.ReadToSerial(61);
  //Serial.println("Informação do valor limpa");
  
  guy.ReadToSerial(60);
  //Serial.println("Informação da moeda limpa");

  guy.end();

  Serial.println("\nRFID Pronto :)");
  Serial.println("Insira outro cartão...\n");
  
  }
