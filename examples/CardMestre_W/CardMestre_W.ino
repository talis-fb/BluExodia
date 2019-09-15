#include <BluExodia.h>

int y = 0;
String m="";

BluExodia guy;

void setup() {
  guy.Hearth();
  Serial.println("Põe o cartão ai mestre... \n");
}

void loop() {

  //Pega as informações do cartão atual
  guy.wReadf(0);

  //Se for o primeiro cartão define ele como Cartão Mestre
  if(y==0){
    m = guy.Namef();
    Serial.println("O cartão mestre agr é: "+guy.Hexf()+"\n");
    y = 5;
    return;
  }

  //Bloco que imprime se o cartão no leitor é o mestre ou não
  if(guy.Namef()==m){
    Serial.println("OK :)");
  } else{
    Serial.println("NOT");
  }
  
  delay(100);
}
