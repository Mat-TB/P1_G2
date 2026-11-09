#include <stdio.h>
#include <math.h>
#define MAX_AMOSTRAS 10

int obter_leituras(int *p, int N);
// Esta função preenche um vetor com valores de inteiros indicados pelo utilizador
// O vetor é dado pelo ponteiro p e tem capacidade máxima dada pelo parâmetro N
// A função retorna o número de valores efetivamente lido
// A leitura termina quando o utilizador insere um valor 'sentinela' (-1) ou
// a capacidade do vetor é esgotada.
// Deve rejeitar valores fora da gama [-1, 1023]
//Também deve rejeita valores que correspondam a temperatura fora da gama [-10, 190]

double converter(int *p);
double media(int *p, int N);
double dv(int *p, int N, double media);
double maximo(int *p, int N);
double minimo(int *p, int N);
void imprime_lista(int *p, int N);
void imprime_dados(int a, double b, double c, double d, double e);
void limpar_entrada(void);



int main(void){
    int leituras[MAX_AMOSTRAS]; //reserva espaço para um certo número de nº inteiros
    int n_leituras; // número de leituras a considerar
    double med, max, min, desvio;

    n_leituras = obter_leituras(leituras, MAX_AMOSTRAS);
    med = media(leituras, n_leituras);
    max = maximo(leituras, n_leituras);
    min = minimo(leituras, n_leituras);
    desvio = dv(leituras, n_leituras, med);
    imprime_lista(leituras, n_leituras);
    imprime_dados(n_leituras, max, min, med, desvio);
}


void imprime_lista(int *p, int N){
//esta função imprime a lista dos valores e a sua respetiva temperatura
    printf("\nValores lidos ( sensor -> temperatura ):\n\n");
    for(int i=0; i < N; i++){
        printf(" %d -> %.2f\n", p[i], converter(&p[i]));
    }
}


void imprime_dados(int a, double b, double c, double d, double e){
//esta função inprime a lista da estatística
    printf("\nNº de valores lidos: %d\n",a);
    printf("Temperatura máxima: %.2f ºC\n",b);
    printf("Temperatura mínima: %.2f ºC\n",c);
    printf("Temperatura média: %.2f ºC\n",d);
    printf("Desvio-padrão: %.2f\n",e);
}


double dv(int *p, int N, double media){
//esta função calcula o desvio padrão
    double desviopadrao;
    double somadequadrados = 0;
    for (int i = 0; i < N; i++){
        double valor = converter(&p[i]);
        somadequadrados += valor * valor;
    }
    desviopadrao = sqrt(somadequadrados / N - (media * media));
    return desviopadrao;
}


double minimo(int *p, int N){
//esta função calcula a temperatura mínima
    double min = converter(&p[0]);
    for (int i = 0; i < N; i++){
        double valor = converter(&p[i]);
        if (min > valor){
            min = valor;
        }
    }
    return min;
}


double maximo(int *p, int N){
//esta função calcula a temperatura máxima
    double max = converter(&p[0]);
    for (int i = 0; i < N; i++){
        double valor = converter(&p[i]);
        if (max < valor){
            max = valor;
        }
    }
    return max;
}


double media(int *p, int N){
//esta função calcula a temperatura média
    double med = 0;
    for(int i = 0; i < N; i++){
        med += converter(&p[i]);
    }
    med /= N;
    return med;
}


double converter(int *p){
//esta função converte o valor recebido do utilizador para temperatura
    double temp;
    temp = 260.0**p/1023-20;  
    return temp; 
}


int obter_leituras(int *p, int N){

    double temp[N];
    int i = 0;
    while(i < N){
        printf("Valor do sensor (inteiro entre 0 e 1023):");
        if(scanf("%d",&p[i]) != 1){
            printf("\nValor rejeitado, insira um número inteiro.\n");
            limpar_entrada();
        }
        else if (p[i] == -1){
            break;
        }
        else if (p[i] < -1 | p[i] > 1023) {
            printf("\nValor rejeitado! Deve estar entre 0 e 1023.\n");
        }
        else{
            temp[i] = converter(&p[i]);
            i++;
        }
    }
    return i;
}


void limpar_entrada(void){
//esta função consome os caracteres que se encontram no buffer do teclado
    while(getchar()!='\n'){}
}
