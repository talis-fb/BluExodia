#include <BluExodia.h>

BluExodia guy;

int start;
int quantEs;
int ProdutoLidos;

void setup() {
  guy.Hearth();

  Serial.println("Contagem de Estoque");
  Serial.print("Insira quantos produtos há para registrar no estoque no Serial: ");
  ProdutoLidos = 0;
  start=0;
}


void loop() {
  bool newProd = false; //Variavel para saber se o 
  
  if (Serial.available() > 0 && start<1) {
    quantEs = Serial.read();
    start=1;
    Serial.print("Insira os produtos...");
    Serial.println("(Digite 2 no Serial caso queira saber sobre a contagem)\n");
  }
  
  if(start>0){
    String estoqProd[quantEs]; //Vetor que guarda o nome dos produtos lidos
    String estoqValor[quantEs];//Vetor que guarda o valor dos produtos lidos
    int cont[quantEs];         //Vetor que guarda a quantidade lida de cada produto
     /*No caso, o vetor 1 de cont[] guarda a quantidade de produtos lidos do vetor 1 de EstoqProd[]
      *Cada produto novo se registrará como um novo vetor no EstoqProd[] 
      *e caso outro igual passe, apenas cont[] se somará mais 1.*/

      //Bloco que ler o cartão no leitor e guarda a leitura dos blocos em variaveis temporariais
        guy.In();
        String tProd = guy.ReadToStr(62);
        String tVal = guy.ReadToStr(61);
        guy.end();
      //----------------------
      
      //Bloco que verifica se caso o produto no leitor já tenha sido registrado em estoqProd[]
       for(int c=0;c<quantEs;c++){
          if(tProd == estoqProd[c]){
            cont[c]++;
            Serial.println("Produto: "+estoqProd[c]+"+1");
          } else if(c==(quantEs-1)){
              newProd=true;
              Serial.println("Produto NOVO: ");
            }
       }
       //----------------------

       //Caso o produto não tenha sido registrado, registrasse no proximo vetor vazio
         if(newProd){
          estoqProd[ProdutoLidos]  = tProd;
          estoqValor[ProdutoLidos] = tVal;
            ProdutoLidos++;
          Serial.print("Adicionado :)");
          }
        //----------------------     

    //Bloco para mostrar as informações da contagem caso seja solicitado
    if (Serial.available() > 0) {
     int deku = Serial.read();
      if(deku=='2'){
      Serial.println("------------------------");
      Serial.println("Expectativa de Produtos: "+quantEs);
      Serial.println("Produtos já contados:    "+ProdutoLidos);
      if(ProdutoLidos>0){
        for(int c=0;c<ProdutoLidos;c++){
            Serial.println(c+": "+estoqProd[c]);
            Serial.println("  Valor: "+estoqValor[c]);
            Serial.println("QUANTIDADE: "+cont[c]);
          }
      }
      Serial.println("------------------------");
        deku++;
        }}
    //----------------------------------------  
  }

}
