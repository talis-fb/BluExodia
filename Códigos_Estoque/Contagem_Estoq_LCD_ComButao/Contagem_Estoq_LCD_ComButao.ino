#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <BluExodia.h>

LiquidCrystal lcd(7,6,5,4,3,2);
BluExodia guy;

#define quantEs 5 //<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Quantidade de produtos que serão registrados
#define but 8

int start;
int ProdutoLidos;

int cont[quantEs];//Vetor que guarda a quantidade lida de cada produto
String estoqProd[quantEs]; //Vetor que guarda o nome dos produtos lidos
String estoqValor[quantEs];//Vetor que guarda o valor dos produtos lidos

 int botao;

void setup() {
  pinMode(but,INPUT);
  
  lcd.begin(16,2);
  guy.Hearth();

  lcd.print("Contador");
    //Serial.print("Contador\n");
  lcd.setCursor(0,1);
  lcd.print("de Estoque");
    //Serial.print("de Estoque\n");
  delay(1000);
  
  lcd.clear();
   
  lcd.setCursor(0,0);
  lcd.print((String)quantEs+" produtos para");
  lcd.setCursor(0,1); 
  lcd.print("serem contados..");

    //Serial.print((String)quantEs+" produtos para\n");
    //Serial.print("serem contados..");
  delay(700);

  ProdutoLidos = 0;
  start=0;
}

void telaInf(){
  /*Função que mostra as informações do estoque atualmente 
    enquanto não há cartão no leitor 
    */
  String g[quantEs];
  String v[quantEs];
  
   for(int c=0;c<quantEs;c++){
    g[c] = estoqProd[c];
    g[c].remove(3); //Armazena numa variavel apenas as três primeiras letras do produto
    
    v[c] = cont[c];
    v[c].remove(3);
   }

   lcd.print((String)g[0]+" "+g[1]+" "+g[2]+" "+g[3]);
   lcd.setCursor(0,1);
   lcd.write(' ');
   lcd.print((String)v[0]+"   "+v[1]+"   "+v[2]+"   "+v[3]);
   delay(400);
   
     /*Serial.print((String)g[0]+" "+g[1]+" "+g[2]+" "+g[3]+"\n");
       Serial.write(' ');
       Serial.print((String)v[0]+"   "+v[1]+"   "+v[2]+"   "+v[3]+"\n\n");*/

       
  /*Caso já tenha sido registrado todos os produtos previstos na expectativa, 
     um 'X' fica na borda direita do lcd. */  
   if(ProdutoLidos>=quantEs){
     lcd.setCursor(15,0);
     lcd.write('X');
     lcd.setCursor(15,1);
     lcd.write('X');
   }
   
}

void loop() {
  botao = digitalRead(but);
  
  lcd.clear();
    //Serial.print("\n----------------\n");

  //Verifica se algum produto já foi registrado
    if(estoqProd[0]==estoqProd[(quantEs-1)]){
      lcd.print("Aguardando...");
        //Serial.print("Aguardando...\n");
    } else{
      telaInf();
    }
   //------------------------
 
     bool newProd = false; //Variavel para saber se o o produto que será inserido é novo
 
     /*No caso, o vetor 1 de cont[] guarda a quantidade de produtos lidos do vetor 1 de EstoqProd[]
      *Cada produto novo se registrará como um novo vetor no EstoqProd[] 
      *e caso outro igual passe, apenas cont[] se somará mais 1.*/

      if(botao==HIGH){

        guy.In();
        
        guy.Readf(62);
        String tProd = guy.Namef();
        guy.Readf(61);
        String tVal = guy.Namef();
        
        Serial.print(" UID: ");
        guy.ReadToSerial(0);
        Serial.print("\n");

        lcd.clear();
        lcd.print((String)"Produto: "+tProd);
        lcd.setCursor(0,1);
        lcd.print((String)"Preso: "+tVal);
     
        guy.end();

        delay(2000);

        return;
           
    } else{

      //Bloco que ler o cartão no leitor e guarda a leitura dos blocos em variaveis temporariais
        guy.In();
        
        guy.Readf(62);
        String tProd = guy.Namef();
        guy.Readf(61);
        String tVal = guy.Namef();
        
        guy.end();
        
      //----------------------

      
      //Bloco que verifica se caso o produto no leitor já tenha sido registrado em estoqProd[]
      if(tProd!="" && tVal!=""){
        int verif = 0;
       for(int c=0;c<quantEs;c++){
          if(tProd.equals(estoqProd[c]) ){
            cont[c]++;
            lcd.clear();
            lcd.print((String)"Produto: "+estoqProd[c]+"+1");
            verif=1;
          }
          if(c==(quantEs-1) && verif==0 ){
              newProd=true;
              lcd.clear();
              lcd.print("Produto NOVO: ");
              verif=0;
            }
          }
       }else{
            lcd.clear();
            lcd.print("Erro, cartão inválido...");
            delay(800);
            return;
       }
       //----------------------


       //Caso o produto não tenha sido registrado, registrasse no proximo vetor vazio
         if(newProd==true){
          lcd.setCursor(0,1);
          
          if(ProdutoLidos<quantEs){
            estoqProd[ProdutoLidos]  = tProd;
            estoqValor[ProdutoLidos] = tVal;
            cont[ProdutoLidos] = 1;
              ProdutoLidos++;
            lcd.print("Adicionado :)\n");
            newProd=false;
          }else{
            lcd.print("Limite Atingido");
            newProd=false;
            }
         }
        //----------------------    

      delay(800);
      tProd="";
      tVal="";
  } 
}
