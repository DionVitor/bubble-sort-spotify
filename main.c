#include <stdio.h>
#include <stdlib.h>

#define MAX_LINES 10000

struct Review {
    int Total_thumbsup;
    char *review;
};

void swap(struct Review *a, struct Review *b) {
    struct Review temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(FILE *fp_in, FILE *fp_out) {
    int i, j;
    char line[1000];
    int Total_thumbsup;
    char review[1000];
    // Read first line
    fgets(line, sizeof(line), fp_in);
    sscanf(line, "%d,%[^\n]", &Total_thumbsup, review);
    struct Review current = {Total_thumbsup, strdup(review)};

    while(!feof(fp_in)) {
        // Read next line
        fgets(line, sizeof(line), fp_in);
        sscanf(line, "%d,%[^\n]", &Total_thumbsup, review);
        struct Review next = {Total_thumbsup, strdup(review)};

        // Compare current and next line
        if (current.Total_thumbsup > next.Total_thumbsup) {
            // Write current line to output file
            fprintf(fp_out, "%d,%s\n", current.Total_thumbsup, current.review);

            // Update current line
            current = next;

            // Rewind file pointer to the beginning of the file
            rewind(fp_in);
            fgets(line, sizeof(line), fp_in); // skip the first line
        }
    }
    // Write last line to output file
    fprintf(fp_out, "%d,%s\n", current.Total_thumbsup, current.review);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *reviews = argv[1];
    char *newReviews = argv[2];

    // Open input file
    FILE *fp_in = fopen("reviews.csv", "r");
    if (fp_in == NULL) {
        printf("Failed to open input file: %s\n", reviews);
        return 1;
    }

    // Open output file
    FILE *fp_out = fopen("newReviews.csv", "w");
    if (fp_out == NULL) {
        printf("Failed to open output file: %s\n", newReviews);
        return 1;
    }

    // Sort reviews
    bubbleSort(fp_in, fp_out);

    // Close input and output files
    fclose(fp_in);
    fclose(fp_out);

    return 0;
}