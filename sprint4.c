#include <stdio.h>
#include <math.h>
int main(void)
{
    int valorsensor;
    int namostras;
    int nleituras;
    double temp;
    double somadequadrados = 0;
    double media;
    double desviopadrao;
    double soma = 0;
    int valoreslidos = 0;
    int n;
    printf("_________________________________________________\n\n");
    printf("           Calculadora de temperatura\n");
    printf("_________________________________________________\n\n");
    printf("Se pretende sair do programa digite o número -1 !\n\n");
    printf("Quantas amostras pretende ler?");
    while (scanf(" %d",&namostras) != 1 || namostras <= 0)
    {
        printf("Valor rejeitado, insira um número inteiro positivo.\n");
        while(getchar()!='\n') {}
        printf("Quantas amostras pretende ler?");
    }
    double valoresdados[namostras];
    double resultados[namostras];
    double maximo = valoresdados[n];
    double minimo = valoresdados[n];
    for (nleituras = 0; nleituras < namostras; nleituras++){
        printf("\nValor do sensor (inteiro entre 0 e 1023):");

        if (scanf(" %d",&valorsensor) != 1)
        {
            nleituras == nleituras + 1;
            printf("Valor rejeitado, insira um número inteiro.\n");
            while(getchar()!='\n') {}
            valoreslidos += 0;
        }
        else
        {
            temp = 260.0*valorsensor/1023-20;
            if (valorsensor == -1)
            {
                break;
            }
            else if (temp > -10 && temp < 190)
            {
                printf("O valor da temperatura é: %.2f ºC\n", temp);
                valoresdados[valoreslidos] = valorsensor;
                resultados[valoreslidos] = temp;
                if(valoreslidos == 0)
                {
                    maximo = temp;
                    minimo = temp;
                }
                else
                {
                    if (temp > maximo)
                    {
                        maximo = temp;
                    }
                    if (temp < minimo)
                    {
                        minimo = temp;
                    }
                }
                soma += temp;
                somadequadrados += temp * temp;
                valoreslidos++;
            }
            else
            {
                printf("Valor fora da gama.\n");
            }
        }
    }
    if (valoreslidos > 0)
    {
        media = soma / valoreslidos;
        desviopadrao = sqrt(somadequadrados / valoreslidos - (media * media));
    }
    else
    {
        media = 0;
        desviopadrao = 0;
    }
    printf("\nValores lidos ( sensor -> temperatura ):\n\n");
    for(int i=0; i < valoreslidos; i++){
        printf(" %.0f -> %.2f\n", valoresdados[i], resultados[i]);
    }
    
    printf("\nNº de valores lidos: %d\n",valoreslidos);
    printf("Temperatura máxima: %.2f ºC\n",maximo);
    printf("Temperatura mínima: %.2f ºC\n",minimo);
    printf("Temperatura média: %.2f ºC\n",media);
    printf("Desvio-padrão: %.2f\n",desviopadrao);
}