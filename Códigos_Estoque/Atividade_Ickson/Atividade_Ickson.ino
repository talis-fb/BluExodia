#include <BluExodia.h>

String product;
String val;

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Insira o cartão...");
}

void loop() {
  product = "Feijão";
  val = "10";
  String moeda = "Reais";

  //Nome do produto
  guy.wWrite(10,product);
  Serial.println("Produto Escrito");

  //Valor do produto
  guy.wWrite(8,val);
  Serial.println("Valor do produto Escrito");

  //Moeda utilizada
  guy.wWrite(9,moeda); 
  Serial.println("Unidade da Moeda Escrita");

  Serial.println("\nRFID Pronto :)");
  Serial.println("Insira outro cartão...\n");


}
