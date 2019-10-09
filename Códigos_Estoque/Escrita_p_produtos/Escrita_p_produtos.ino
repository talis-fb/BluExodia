#include <BluExodia.h>

String product;
String val;

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Insira o cartão...");
}

void loop() {
  product = "Chocolate";
  val = "4";
  String moeda = "Reais";
  
  guy.In();
  
  //Nome do produto
  guy.Write(62,product);
  Serial.println("Produto Escrito");

  //Valor do produto
  guy.Write(61,val);
  Serial.println("Valor do produto Escrito");

  //Moeda utilizado
  guy.Write(60,moeda); 
  guy.end();

  
  Serial.println("Unidade da Moeda Escrita");

  Serial.println("\nRFID Pronto :)");
  Serial.println("Insira outro cartão...\n");


}
