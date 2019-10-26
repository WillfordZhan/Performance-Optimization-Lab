#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float get_Random(float rmax){
    float x = ((float)rand()/(float)RAND_MAX)*rmax;
    return x;
}

void create_dataset(int dataSize, char* filename){
    // rule of thumb: seed only once
    srand((unsigned int)time(NULL));

    FILE *fp;
    float *data = malloc(sizeof(float) * dataSize);
    fp = fopen(filename,"wb");
    
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = get_Random(100);
    }
    free(data);
    fwrite(data, sizeof(float), sizeof(dataSize), fp);
    fclose(fp);
}

void load_dataSet(float *dataSet,int dataSize, int bufferSize, char *filename){
    FILE *fp;
    fp = fopen(filename,"rb");
    for (int i = 0; i < dataSize; i+= bufferSize)
    {
        fread(dataSet+i, sizeof(float), bufferSize, fp);
    }
    fclose(fp);
}

int main(int argc, char **argv){
    int bufferSize, dataSize;
    char *filename;
    float *dataSet;

    if (argc != 4)
    {
        printf("Usage: resow.c <dataSize> <bufferSize> <filename>\n");
        exit(1);
    }
    
    dataSize = atoi(argv[1]);
    bufferSize = atoi(argv[2]);
    filename = argv[3];

    dataSet = malloc(sizeof(float)* dataSize);

    // printf("creating dataset\n");
    // create_dataset(dataSize, filename);
    // printf("-------------Creation Over-------------\n");
    
    printf("loading dataset\n");
    load_dataSet(dataSet,dataSize,bufferSize,filename);
    printf("-------------Loading Over-------------\n");
    for (int i = 0; i < dataSize; i++)
    {
        printf("%f\n",*(dataSet+i));
    }
    free(dataSet);
    return 0;
}

