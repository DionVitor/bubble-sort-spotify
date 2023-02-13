#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Dataset {
  char formated_date[20];
  double rating_sum;
  int count;
} dataset;

void bubbleSort(dataset data_set[], int dataset_size) {
  int i, j;
  dataset temp;
  for (i = 0; i < dataset_size-1; i++) {
    for (j = 0; j < dataset_size-i-1; j++) {
      if (data_set[j].rating_sum / data_set[j].count < data_set[j+1].rating_sum / data_set[j+1].count) {
        temp = data_set[j];
        data_set[j] = data_set[j+1];
        data_set[j+1] = temp;  
      }
    }
  }
}

int main() {
  FILE *reviews_file = fopen("reviews.csv", "r");
  if (!reviews_file) {
    perror("reviews.csv");
    return 1;
  }

  // Skip heading
  char heading[100];
  fgets(heading, sizeof(heading), reviews_file);

  int dataset_size = 0;
  dataset *data_set = NULL;

  char row[100];
  while (fgets(row, sizeof(row), reviews_file)) {
    char *semicolon_pos = strchr(row, ';');
    if (!semicolon_pos) {
      continue;
    }
    *semicolon_pos = '\0';
    char date_string[20];
    strcpy(date_string, row);
    struct tm date = {};
    strptime(date_string, "%Y-%m-%d %H:%M:%S", &date);
    char formated_date[20];
    strftime(formated_date, sizeof(formated_date), "%Y-%m", &date);

    int rating = atoi(semicolon_pos + 1);

    int i;
    for (i = 0; i < dataset_size; i++) {
      if (strcmp(data_set[i].formated_date, formated_date) == 0) {
        break;
      }
    }

    if (i == dataset_size) {
      dataset_size++;
      data_set = realloc(data_set, dataset_size * sizeof(dataset));
      strcpy(data_set[i].formated_date, formated_date);
      data_set[i].rating_sum = 0;
      data_set[i].count = 0;
    }

    data_set[i].rating_sum += rating;
    data_set[i].count++;
  }

  FILE *output_file = fopen("output.csv", "w");
  if (!output_file) {
    perror("output.csv");
    return 1;
  }

  bubbleSort(data_set, dataset_size);

  fprintf(output_file, "MES,Avaliacao_Media\n");
  for (int i = 0; i < dataset_size; i++) {
    fprintf(output_file, "%s, %lf\n", data_set[i].formated_date,
            (double)data_set[i].rating_sum / data_set[i].count);
  }
	
	fclose(reviews_file);
	fclose(output_file);
	
  return 0;
}