#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 70000
#define NUM_MONTHS 12

typedef struct
{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
    int rating;
} Record;

// Função para ler uma linha do arquivo CSV e retornar um registro
Record read_record(char *line)
{
    Record record;
    sscanf(line, "%d-%d-%d %d:%d:%d,%d", &record.year, &record.month, &record.day,
           &record.hour, &record.minute, &record.second, &record.rating);
    return record;
}

// Função para calcular a avaliação média de um mês
double average_rating(int month, int year, Record *records, int num_records)
{
    int total = 0;
    int count = 0;
    for (int i = 0; i < num_records; i++)
    {
        if (records[i].month == month && records[i].year == year)
        {
            total += records[i].rating;
            count++;
        }
    }
    return (double)total / count;
}

// Função para comparar duas avaliações médias
int compare_ratings(const void *a, const void *b)
{
    double x = *(double *)a;
    double y = *(double *)b;
    if (x < y)
        return 1;
    if (x > y)
        return -1;
    return 0;
}

int main()
{
    char line[MAX_LINE_LENGTH];
    Record records[MAX_LINE_LENGTH];
    int num_records = 0;

    // Abrir o arquivo CSV para leitura
    FILE *file = fopen("reviews.csv", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de dados");
        return 1;
    }

    printf("Lendo o arquivo de dados...\n");
    // Ignorar o cabeçalho do arquivo
    fgets(line, MAX_LINE_LENGTH, file);

    printf("Processando os dados...\n");
    // Ler as linhas restantes do arquivo
    
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        Record record = read_record(line);
        records[num_records++] = record;
    }

    fclose(file);

    printf("Gerando o arquivo de saida...\n");

    // Contar as avaliações por mês
    int counts[NUM_MONTHS];
    double ratings[NUM_MONTHS];
    memset(counts, 0, sizeof(counts));
    memset(ratings, 0, sizeof(ratings));
    
    for (int i = 0; i < num_records; i++)
    {
        int month = records[i].month - 1;
        counts[month]++;
        ratings[month] += records[i].rating;
    }

    // Calcular a avaliação média por mês
    for (int i = 0; i < NUM_MONTHS; i++)
    {
        ratings[i] /= counts[i];
    }

    // Classificar as avaliações médias em ordem decrescente
    qsort(ratings, NUM_MONTHS, sizeof(double), compare_ratings);

    // Escrever os resultados em um arquivo CSV
    file = fopen("averages.csv", "a");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de saída");
        return 1;
    }

    fprintf(file, "Mês,Avaliação Média\n");
    for (int i = 0; i < NUM_MONTHS; i++)
    {
        fprintf(file, "%d,%lf\n", i + 1, ratings[i]);
    }
    
    fclose(file);

    return 0;
}