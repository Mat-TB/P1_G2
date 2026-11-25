#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define TIPOS_SENSOR 3
#define MAX_LEITURAS 100
#define MAX_AMOSTRAS 10

// Variáveis globais
char *nome_sensor[] = {"TEMP1", "TEMP2", "TEMP3"};
int ganho[] = {260, 250, 240};
int desvio[] = {-20, -15, -10};

// Protótipos
int validar_sensor(char *nome);
int valida_instante(char *instante);
int valida_temperatura(char *temperatura);
double converter(double temperatura, int sensor);

double calcular_media(double temperatura[], int contadores);
double calcular_dv(double temperatura[], int contadores);
double calcular_minimo(double temperatura[], int contadores);
double calcular_maximo(double temperatura[], int contadores);

void imprime_dados(int contadores, double max, double min,
                   double media, double dv);

int main(void)
{
    char valores[100];
    char *dados;
    char *item[TIPOS_SENSOR];

    int sensor;
    int instante;
    int valor;
    int total = 0;

    double temperatura_convertida;
    double min, max, media, dv;

    int contadoreses[TIPOS_SENSOR] = {0};

    // Guardar as temperaturas convertidas de cada sensor
    double temperatura[TIPOS_SENSOR][MAX_LEITURAS];

    // Guardar informação de todas as leituras
    int sensores_lidos[TIPOS_SENSOR * MAX_LEITURAS];
    int instantes[TIPOS_SENSOR * MAX_LEITURAS];
    int valores_lidos[TIPOS_SENSOR * MAX_LEITURAS];
    double temperatura_lidas[TIPOS_SENSOR * MAX_LEITURAS];

    while (total < MAX_AMOSTRAS)
    {
        printf("Insira os dados no formato [sensor instante valor]: ");

        if (fgets(valores, sizeof(valores), stdin) == NULL)
        {
            break;
        }

        valores[strcspn(valores, "\n")] = '\0';

        dados = strtok(valores, " ");

        // Verificar FIM
        if (dados != NULL && strcmp(dados, "FIM") == 0)
        {
            printf("recolha de dados terminada\n");
            break;
        }

        // Recolher os três elementos
        int i = 0;

        while (i < 4 && dados != NULL)
        {
            item[i] = dados;
            i++;
            dados = strtok(NULL, " ");
        }

        // Verificar número de argumentos
        if (i < 3)
        {
            printf("Foram colocados dados insuficientes...\n");
            continue;
        }
        else if (i > 3)
        {
            printf("Foram colocados demasiados dados...\n");
            continue;
        }

        // Validar sensor
        sensor = validar_sensor(item[0]);

        if (sensor == -1)
        {
            continue;
        }

        // Validar instante
        instante = valida_instante(item[1]);

        if (instante == -1)
        {
            continue;
        }

        // Validar valor bruto do sensor
        if (valida_temperatura(item[2]) == 0)
        {
            continue;
        }

        valor = atoi(item[2]);

        // Verificar limite de leituras
        if (contadoreses[sensor] >= MAX_LEITURAS)
        {
            printf("Limite de leituras atingido para %s!\n",
                   nome_sensor[sensor]);
            continue;
        }

        // Converter temperatura
        temperatura_convertida = converter(valor, sensor);

        // Guardar temperatura na posição correspondente ao sensor
        temperatura[sensor][contadoreses[sensor]] =
            temperatura_convertida;

        contadoreses[sensor]++;

        // Guardar informação da leitura
        sensores_lidos[total] = sensor;
        instantes[total] = instante;
        valores_lidos[total] = valor;
        temperatura_lidas[total] = temperatura_convertida;

        total++;
    }

    // Apresentar todas as leituras registadas
    printf("\nLeituras Registadas (Sensor instante: Valor -> Temperatura):\n\n");

    for (int i = 0; i < total; i++)
    {
        printf("%s %d: %d -> %.2f ºC\n",
               nome_sensor[sensores_lidos[i]],
               instantes[i],
               valores_lidos[i],
               temperatura_lidas[i]);
    }

    // Apresentar estatísticas de cada sensor
    for (int i = 0; i < TIPOS_SENSOR; i++)
    {
        if (contadoreses[i] > 0)
        {
            printf("\nEstatísticas do sensor %s:\n", nome_sensor[i]);

            max = calcular_maximo(temperatura[i], contadoreses[i]);
            min = calcular_minimo(temperatura[i], contadoreses[i]);
            media = calcular_media(temperatura[i], contadoreses[i]);
            dv = calcular_dv(temperatura[i], contadoreses[i]);

            imprime_dados(contadoreses[i], max, min, media, dv);
        }
    }

    return 0;
}


// Validar sensor
int validar_sensor(char *nome)
{
    for (int i = 0; i < TIPOS_SENSOR; i++)
    {
        if (strcmp(nome, nome_sensor[i]) == 0)
        {
            return i;
        }
    }

    printf("Sensor desconhecido ou inválido. Deverá ser TEMP1, TEMP2 ou TEMP3.\n");

    return -1;
}


// Validar instante
int valida_instante(char *instante)
{
    char *fim;
    long inst = strtol(instante, &fim, 10);

    if (*fim != '\0' || fim == instante || inst < 0 || inst > 2147483647)
    {
        printf("Instante não reconhecido. Deverá ser um inteiro não negativo.\n");
        return -1;
    }

    return (int)inst;
}


// Validar valor bruto do sensor
int valida_temperatura(char *temperatura)
{
    char *fim;
    long valor = strtol(temperatura, &fim, 10);

    if (*fim != '\0' || fim == temperatura ||
        valor < 0 || valor > 1023)
    {
        printf("Valor rejeitado! Deve ser um inteiro entre 0 e 1023.\n");
        return 0;
    }

    return 1;
}


// Converter temperatura
double converter(double temperatura, int sensor)
{
    double temp;

    temp = (double)ganho[sensor] * temperatura / 1023
           + desvio[sensor];

    return temp;
}


// Imprimir estatísticas
void imprime_dados(int contadores, double max, double min,
                   double media, double dv)
{
    printf("Nº de valores lidos: %d\n", contadores);
    printf("Temperatura máxima: %.2f ºC\n", max);
    printf("Temperatura mínima: %.2f ºC\n", min);
    printf("Temperatura média: %.2f ºC\n", media);
    printf("Desvio-padrão: %.2f\n", dv);
}


// Calcular desvio-padrão
double calcular_dv(double temperatura[], int contadores)
{
    double somadequadrados = 0;
    double media;
    double desviopadrao;

    media = calcular_media(temperatura, contadores);

    for (int i = 0; i < contadores; i++)
    {
        somadequadrados += temperatura[i] * temperatura[i];
    }

    desviopadrao = sqrt(somadequadrados / contadores - media * media);

    return desviopadrao;
}


// Calcular mínimo
double calcular_minimo(double temperatura[], int contadores)
{
    double min = temperatura[0];

    for (int i = 1; i < contadores; i++)
    {
        if (min > temperatura[i])
        {
            min = temperatura[i];
        }
    }

    return min;
}


// Calcular máximo
double calcular_maximo(double temperatura[], int contadores)
{
    double max = temperatura[0];

    for (int i = 1; i < contadores; i++)
    {
        if (max < temperatura[i])
        {
            max = temperatura[i];
        }
    }

    return max;
}


// Calcular média
double calcular_media(double temperatura[], int contadores)
{
    double med = 0;
    double soma = 0;

    for (int i = 0; i < contadores; i++)
    {
        soma += temperatura[i];
    }

    med = soma / contadores;

    return med;
}
        
      
    
        





