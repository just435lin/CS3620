#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h> 
#include <sys/wait.h>

uint8_t gencrc(uint8_t *data, size_t len) {
    uint8_t crc = 0xff;
    size_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
            crc = (uint8_t)((crc << 1) ^ 0x31);
            else
            crc <<= 1;
        }
    }
    return crc;
}

void fileCRC8(char* file) {
    FILE* inputfile = fopen(file, "r");
    if (inputfile == NULL) {
        perror("Error opening file");
        return;
    }
    char* buffer = NULL;
    long buffersize = 0;

    if (fseek(inputfile,0L,SEEK_END)==0) {
        buffersize = ftell(inputfile);

        if (buffersize==-1) {return;}

        buffer = malloc(sizeof(char*)*(buffersize));

        if (fseek(inputfile,0L,SEEK_SET)!=0) {return;}

        size_t len = fread(buffer,1,buffersize,inputfile);
        if (ferror(inputfile)!=0) {
            fputs("Error reading file", stderr);
        }
        u_int8_t crc = gencrc((uint8_t*)buffer,len);
        printf("%s=%d\n",file,crc);
    }
    fclose(inputfile);
    free(buffer);
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    
    for (int i=1;i<argc;i++) {
        int status;
        pid_t pid = fork();
        if (pid!=0) {
            wait(NULL);
        } else {
            fileCRC8(argv[i]);
            exit(0);
        }
    }

    //char a[] = "This is a test and only a test";
    //printf("%s crc=%d\n", a, gencrc((uint8_t *)&a, strlen(a)));
    
    return 0;
}
