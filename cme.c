#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

struct {
	char numero[7];
	char letra;
} typedef Dicionario;

int main() {
    void beepConfig(int quatidade, int frequencia, int tempo);
    FILE *arq, *myFile;
    int contaCaracteres = 0;

    arq = fopen("dicionario.txt", "rt");
    myFile = fopen("message.txt", "w");

    if (arq == NULL || myFile == NULL){
		printf("Erro ao abrir o dicionário");
		beepConfig(1, 493, 500);
	}else{
        char linhaArquivo[8];
        Dicionario oTranslator[32];
        int resposta = 1, comparaLetra;

        for(int contLinhaArq = 0; contLinhaArq <= 31; contLinhaArq++){
            int contCompara = 0;
            fscanf(arq, "%7s", linhaArquivo);

            for(int i = 0; i <= 5; i++) {
                oTranslator[contLinhaArq].numero[i] = linhaArquivo[i];
            }

            oTranslator[contLinhaArq].letra = linhaArquivo[6];
        }

        fclose(arq);

        beepConfig(1,261,500);
        do {
            void continuar(int *resposta);
            int numeroEntrada, contaDigitos = 0;
            int valor, potencia, digito;
            int coordBraile[3][2];
            char buffer[7];

            for(int i = 0; i <= 3; i++){
                for(int j = 0; j <= 2; j++){
                    coordBraile[i][j] = 0;
                }
            }

            beepConfig(2,293,250);
            printf("\nLetra: ");
            scanf("%d", &numeroEntrada);

            if (numeroEntrada == 0) {
                contaDigitos = 1;
            } else {
                valor = numeroEntrada;
                while (valor != 0) {
                    contaDigitos = contaDigitos + 1;
                    valor = valor / 10;
                }
            }

            for (int count = 0; count < contaDigitos; count++) {
                int letraFrag[6];

                for (int i = contaDigitos; i >= 1; i--) {
                    potencia = pow(10, i);
                    digito = numeroEntrada % potencia;
                }

                letraFrag[count] = digito;
                numeroEntrada = (numeroEntrada - digito) / 10;

                switch (letraFrag[count]) {
                    case 7:
                        coordBraile[0][0] = 1;
                        break;
                    case 8:
                        coordBraile[0][1] = 1;
                        break;
                    case 4:
                        coordBraile[1][0] = 1;
                        break;
                    case 5:
                        coordBraile[1][1] = 1;
                        break;
                    case 1:
                        coordBraile[2][0] = 1;
                        break;
                    case 2:
                        coordBraile[2][1] = 1;
                        break;
                    case 0:
                        beepConfig(1, 329, 500); // Nota Mi
                        break;
                    default:
                        printf("Entrada %d invalida", letraFrag[count]);
                        beepConfig(1, 440, 500); // Nota La
                        break;
                }
            }

            sprintf(
                buffer,
                "%d%d%d%d%d%d",
                coordBraile[0][0],
                coordBraile[0][1],
                coordBraile[1][0],
                coordBraile[1][1],
                coordBraile[2][0],
                coordBraile[2][1]);

            for(int indiceLinha = 0; indiceLinha <= 31; indiceLinha++){
                comparaLetra = 0;
                for(int indiceStruct = 0; indiceStruct <= 5; indiceStruct++){
                    if(oTranslator[indiceLinha].numero[indiceStruct] == buffer[indiceStruct]){
                        comparaLetra++;
                    }
                }
                if(comparaLetra == 6) {
                    fprintf(myFile, "%c", oTranslator[indiceLinha].letra);
                    beepConfig(1, 392, 250);
                }
            }

            contaCaracteres++;

            if(contaCaracteres % 10 == 0){
                beepConfig(1, 349, 300); // Nota Fa
                continuar(&resposta);
            }

        } while(resposta != 1);
        fclose(myFile);
        beepConfig(2,261,500);
    }

    return 0;
}

void continuar(int *ponteiro) {
    printf("Zero para continuar");
    scanf("%d", ponteiro);
}

void beepConfig(int quatidade, int frequencia, int tempo){
    for(int i = 1; i <= quatidade; i++){
        Beep(frequencia, tempo);
    }

    // printf("Dó\n") ;
    // Beep (261, tempo);

    // printf("Ré\n");
    // Beep (293, tempo);

    // printf("Mi\n");
    // Beep (329, tempo);

    // printf("Fá\n");
    // Beep (349, tempo);

    // printf("Sol\n");
    // Beep (392, tempo);

    // printf("Lá\n");
    // Beep (440, tempo);

    // printf("Si\n");
    // Beep (493, tempo);
}
