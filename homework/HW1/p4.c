#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void csv(FILE*, FILE*);

int main(int argc, char* argv[]) {
    char* input = argv[1];
    char* output = argv[2];
    FILE* input_File = fopen(input, "r");
    if (input_File == NULL) {
        perror("Error opening file");
        return 1;
    }
    FILE* output_File = fopen(output, "w");
    if (output_File == NULL) {
        perror("Error opening file");
        return 1;
    }
    csv(input_File, output_File);
}

void csv(FILE* input, FILE* output) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), input)) {
        char* val1;
        val1 = strtok(buffer, ",");
        char* val2;
        val2 = strtok(NULL, "\n");
        int sum = atoi(val1) + atoi(val2);
        fprintf(output, "%s,%s,%d\n", val1, val2, sum);
    }
}
