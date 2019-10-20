#include <MFRC522.h>
#include <BluExodia.h>

BluExodia guy;

#define quantEs 5 //<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Quantidade de produtos que serão registrados

int start;
int ProdutoLidos;

int cont[quantEs];//Vetor que guarda a quantidade lida de cada produto
String estoqProd[quantEs]; //Vetor que guarda o nome dos produtos lidos
String estoqValor[quantEs];//Vetor que guarda o valor dos produtos lidos

void setup() {
  guy.Hearth();

  Serial.println("Contagem de Estoque");
  Serial.print((String)quantEs+" Produtos para serem contados... \n");
  ProdutoLidos = 0;
  start=0;
}


void loop() {
  bool newProd = false; //Variavel para saber se o 
 
    
     /*No caso, o vetor 1 de cont[] guarda a quantidade de produtos lidos do vetor 1 de EstoqProd[]
      *Cada produto novo se registrará como um novo vetor no EstoqProd[] 
      *e caso outro igual passe, apenas cont[] se somará mais 1.*/

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
            Serial.println((String)"Produto: "+estoqProd[c]+"+1");
            verif=1;
          }
          if(c==(quantEs-1) && verif==0 ){
              newProd=true;
              Serial.print("Produto NOVO: ");
              verif=0;
            }
          }
       }else{
            Serial.println("Erro, cartão inválido...\n");
            return;
       }
       //----------------------

       //Caso o produto não tenha sido registrado, registrasse no proximo vetor vazio
         if(newProd==true){
          if(ProdutoLidos<quantEs){
            estoqProd[ProdutoLidos]  = tProd;
            estoqValor[ProdutoLidos] = tVal;
            cont[ProdutoLidos] = 1;
              ProdutoLidos++;
            Serial.print("Adicionado :)\n");
            newProd=false;
          }else{
            Serial.print("Limite de Produtos Registrados :(\n");
            newProd=false;
            }
         }
        //----------------------     

    //Bloco para mostrar as informações da contagem
      Serial.println("\n------------------------");
      Serial.println((String)"Expectativa de Produtos: "+quantEs);
      Serial.println((String)"Produtos já contados:    "+ProdutoLidos);
      if(ProdutoLidos>0){
        for(int c=0;c<ProdutoLidos;c++){
            Serial.println((String)"\n"+(c+1)+": "+estoqProd[c]);
            Serial.println((String)"  Valor: R$"+estoqValor[c]+",00");
            Serial.println((String)"QUANTIDADE: "+cont[c]);
          }
      }
      Serial.println("------------------------\n");

      tProd="";
      tVal="";
  } 
