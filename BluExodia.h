
#ifndef BluExodia_h
#define BluExodia_h

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class BluExodia{
  public:
    BluExodia(); //Instancia, não tem nenhum comando nem nada

    void Hearth(); //Aplicada na void setup, inicia funções necessarias
    void In();
    void Clean(int block); //Limpa o bloco do cartão selecionado no parametro
    void ReadToSerial(int block); //Ler o bloco selecionado no parametro e escreve no Serial
    void Write(int block, String guy); //Escreve uma String num bloco selecionado
    void Dump(); //Imprime cada bloco do cartão no Serial
    int InGame(); //Função que retorno 1 se tiver um cartão no leitor e 0 no oposto
    String ReadToStr(int block); //Retorna em String o que escrito no bloco selecionado

    void Readf(int block); //Ler o bloco do cartão e armazena numa variaveis Slifer
    char Bufferf(int f); //retorna apenas um caracter do slifer, sendo F o vetor
    String Hexf(); //Retorna uma string com o que está armazenado em Slifer em formato Hexadecimal
    String Namef(); //O mesmo da Hexf(de cima), mas retorna decodificado


    //Os mesmos códigos de cima, porém com linhas de comando q esperam ter um cartão no leitor para seguir o código
    //No caso, se você colocar uns do comandos de baixo no script, o arduino só avança no código se completar eles
    //Diferente de cima, que se caso não houver cartão no modulo, ele ignora e pula o comando
    void wClean(int block); 
    void wReadToSerial(int block); 
    void wWrite(int block, String guy); 
    void wDump(); 
    String wReadToStr(int block); 
    void wReadf(int block); 

    void end();


  private:
    char slifer[16]; //Variavel que armazena o bloco lido na função Readf
    //As funçõs Hexf, Bufferf e Namef retornam o que está armazenado nessa variavel

};


#endif 
