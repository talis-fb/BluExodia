#include <BluExodia.h>

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Insira cartão");
}

void loop() {

  guy.wClean(10);
  Serial.println("Informação do Produto limpa");
  
  guy.wClean(8);
  Serial.println("Informação do valor limpa");
  
  guy.wClean(9);
  Serial.println("Informação da moeda limpa");

  Serial.println("\nRFID Pronto :)");
  Serial.println("Insira outro cartão...\n");
  
  }
