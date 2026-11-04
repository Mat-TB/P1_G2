#include <stdio.h>
#include <math.h>

int validaramostras(int *a);
double calcMIN(double i, double min_atual);
double calcMAX(double i, double max_atual);
double calcMEDIA(double a, int b);
double calcDESVIO(double a, int b, double c);
double LISTval(int a, double b[], double c[]);
double LISTestatistica(int a, double b, double c, double d, double e);
void limpar_entrada(void);
double calcMAXIMO_e_MINIMO(int valoreslidos, double *maximo, double *minimo, double temp);

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
    validaramostras(&namostras);
    double valoresdados[namostras];
    double resultados[namostras];
    double maximo = valoresdados[n];
    double minimo = valoresdados[n];
    for (nleituras = 0; nleituras < namostras; nleituras++){
        printf("\nValor do sensor (inteiro entre 0 e 1023):");

        if (scanf(" %d",&valorsensor) != 1)
        {
            printf("Valor rejeitado, insira um número inteiro.\n");
            limpar_entrada();
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
                calcMAXIMO_e_MINIMO(valoreslidos, &maximo, &minimo, temp);
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
        media = calcMEDIA(soma, valoreslidos);
        desviopadrao = calcDESVIO(somadequadrados, valoreslidos, media);
    }
    else
    {
        media = 0;
        desviopadrao = 0;
    }
    LISTval(valoreslidos, valoresdados, resultados);
    LISTestatistica(valoreslidos, maximo, minimo, media, desviopadrao);
}





double calcMAXIMO_e_MINIMO(int valoreslidos, double *maximo, double *minimo, double temp){
//esta função calcula as temperaturas máxima e mínima
if(valoreslidos == 0)
{
    *maximo = temp;
    *minimo = temp;
}
else
{
    *minimo = calcMIN(temp, *minimo);
    *maximo = calcMAX(temp, *maximo);
}
}


int validaramostras(int *a){
//esta função valida o número de amostras que o utilizador fornece
    while (scanf(" %d", a) != 1 || *a <= 0)
    {
        printf("Valor rejeitado, insira um número inteiro positivo.\n");
        limpar_entrada();
        printf("Quantas amostras pretende ler?");
    }
}


double calcMIN(double i, double min_atual){
//esta função calcula a temperatura máxima
if (i < min_atual)
{
    return i;
}
else
{
    return min_atual;
}
}


double calcMAX(double i, double max_atual){
//esta função calcula a temperatura máxima
if (i > max_atual)
{
    return i;
}
else
{ 
    return max_atual;
}
}


double calcMEDIA(double a, int b){
//esta função calcula a temperatura média
    double media;
    media = a / b;
    return media;
}


double calcDESVIO(double a, int b, double c){
//esta função calcula o desvio padrão
    double desvio;
    desvio = sqrt(a / b - (c * c));
    return desvio;
}


double LISTval(int a, double b[], double c[]){
//esta função imprime a lista dos valores e resultados obtidos
    printf("\nValores lidos ( sensor -> temperatura ):\n\n");
    for(int i=0; i < a; i++){
        printf(" %.0f -> %.2f\n", b[i], c[i]);
}}


double LISTestatistica(int a, double b, double c, double d, double e){
//esta função inprime a lista da estatística
    printf("\nNº de valores lidos: %d\n",a);
    printf("Temperatura máxima: %.2f ºC\n",b);
    printf("Temperatura mínima: %.2f ºC\n",c);
    printf("Temperatura média: %.2f ºC\n",d);
    printf("Desvio-padrão: %.2f\n",e);

}


void limpar_entrada(void){
//esta função consome os caracteres que se encontram no buffer do teclado
    while(getchar()!='\n'){}
}