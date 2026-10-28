#include <stdio.h>
#include <math.h>
#define MAX 10 //Define o número máximo de leituras que podem ser feitas.
int main()
{
    // Declaração de leitura de variáveis
double Dado;
int número [MAX+1];
    printf("Programa de leitura do sensor de temperatura\n");
    printf("Para sair do programa digite: -1\n");
    printf("Indique o número de leituras que deseja fazer (inteiro entre 1 e %d):", MAX);
       if( scanf("%d",&número[0]) !=1 )
        {
            printf("Quantidade invalida\n");
            return 1;
        }

        if (número[0] == -1)
        {
            printf("Programa terminado\n");
            return 0;
        }

        if (número[0] < 1 || número[0] > MAX)
        {
            printf("Quantidade invalida\n");
            return 1;
        }
    // Loop para ler os valores do sensor
    for (int leitura = 1; leitura <= número[0]; leitura++) {
    int Dado;

    while (1) {
            printf("Valor do sensor (0 a 1023, ou -1 para terminar): ");    

            if (scanf("%d", &Dado) != 1) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF) {}
                printf("Valor inválido. Tente novamente.\n");
                continue;
                }

            if (Dado == -1) {
            número[0] = leitura - 1;  // quantidade realmente recolhida
            break;
            }

            double resultado = 260.0 * Dado / 1023.0 - 20.0;

            if (Dado < 0 || Dado > 1023 || resultado < -10 || resultado > 190) {
            printf("Valor inválido ou fora da gama. Tente novamente.\n");
            continue;
            }

            número[leitura] = Dado;
            break;
        }

        if (Dado == -1) {
        break;  // sai da recolha, mas continua para a tabela e estatísticas
        }
    }
    printf("\n");
    // Loop para calcular e exibir os resultados
    for (int leitura = 1; leitura <= número[0]; leitura++)
    {
            float Temperatura = 260*((float)número[leitura])/1023-20;
        printf("Valor inserido: %d | Temperatura: %.2f ºC\n",
           número[leitura], Temperatura );
    }    
    printf("\n");
    // Estatísticas
    if (número[0] == 0) {
    printf("Não foram inseridos valores.\n");
    } else {
    
        float soma = 0, media, desvio_padrao, min = 190, max = -10;
        for (int leitura = 1; leitura <= número[0]; leitura++)
        {
        float Temperatura = 260*((float)número[leitura])/1023-20;
        soma += Temperatura;
        if (Temperatura < min)
            min = Temperatura;
        if (Temperatura > max)
            max = Temperatura;
        }
        media = soma / número[0];
    
        // Cálculo do desvio padrão
        float soma_quadrados = 0;
        for (int leitura = 1; leitura <= número[0]; leitura++)
        {
        float Temperatura = 260*((float)número[leitura])/1023-20;
        soma_quadrados += (Temperatura - media) * (Temperatura - media);
        }
        desvio_padrao = sqrt(soma_quadrados / número[0]);  

        printf("Estatísticas:\n");
        printf("Número de leituras: %d\n", número[0]);
        printf("Temperatura Média: %.2f ºC\n", media);
        printf("Temperatura Mínima: %.2f ºC\n", min);
            printf("Temperatura Máxima: %.2f ºC\n", max);
        printf("Desvio Padrão: %.2f ºC\n", desvio_padrao);
    }
}    
