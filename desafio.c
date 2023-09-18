#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUANT 8 //Quantidade de armários (começa do 0 e vai até 7)
#define MASK 1 //Máscara

int main()
{

    unsigned char code = 0; //Código de 8 bits correspondente ao status dos armários
    unsigned char input, pos; //Escolha de opções

    puts("Todos os armários estão livres");

    puts("Insira a opção desejada:");
    puts("1- Ocupar armário");
    puts("2- Liberar armário");
    puts("3- Sair");
    scanf("%hhu", &input);

    while(!(input == 3)) {
        srand(time(NULL)); //Mudar seed
        puts("\n"); //Só para facilitar a leitura
        switch(input) {
            case 1:
                if (code == 255) { //Isso evita um loop infinito
                    puts("Não há armários disponíveis"); //Ocorre quando todos os bits forem 1
                } else {
                    pos = rand()%QUANT;
                    while((code >> pos) % 2) {
                        pos = rand()%QUANT; //Se a posição já tiver ocupada, gerar outro número
                    }
                    code = code ^ (MASK << pos); //Ocupar o armário e atualizar o código, da pra fazer usando o operador "OU" também
                }
                break;
            case 2:
                puts("Insira a posição do armário para desocupar:");
                scanf("%hhu", &pos); //Talvez desse certo usar só "input", mas poderia dar erros futuros
                code = code & ~(MASK << pos); //Isso vai manter todos os bits com excessão da posição escolhida, q vai ser forçado a ser 0
                break;
            //case 3: //Só pra evitar erros futuros
                //puts("Programa encerrado");
               // break;
            default:
                puts("Opção inválida"); //Caso o número não esteja nas opções
        }

        //Mostrar o status dos armários
        for (unsigned char i = 0; i < QUANT; i++) {
            printf("Armário %hhu: %s\n", i, (code >> i) % 2 ? "OCUPADO" : "LIVRE");
        }

        //Coletar dados de novo para continuar o loop
        puts("\n");
        puts("Insira a opção desejada:");
        puts("1- Ocupar armário");
        puts("2- Liberar armário");
        puts("3- Sair");
        scanf("%hhu", &input);
    }

    return 0;
}