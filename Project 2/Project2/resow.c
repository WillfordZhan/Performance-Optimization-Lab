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
        printf("%f\n",data[i]);
    }
    fwrite(data, sizeof(float), dataSize, fp);
    free(data);
    fclose(fp);
}

void load_dataSet(float *dataSet,int dataSize, int recordSize, char *filename){
    FILE *fp;
    fp = fopen(filename,"rb");
    for (int i = 0; i < dataSize; i+= recordSize)
    {
        if (recordSize > dataSize - i)
        {
            recordSize = dataSize - i;
        }
        fread(dataSet+i, sizeof(float), recordSize, fp);
    }
    fclose(fp);
}

int main(int argc, char **argv){
    int recordSize, dataSize;
    char *filename;
    float *dataSet;

    if (argc != 4)
    {
        printf("Usage: resow.c <dataSize> <recordSize> <filename>\n");
        exit(1);
    }
    
    dataSize = atoi(argv[1]);
    recordSize = atoi(argv[2]);
    filename = argv[3];

    dataSet = malloc(sizeof(float)* dataSize);

    printf("creating dataset\n");
    create_dataset(dataSize, filename);
    printf("-------------Creation Over-------------\n");
    
    return 1;
    printf("loading dataset\n");
    load_dataSet(dataSet,dataSize,recordSize,filename);
    printf("-------------Loading Over-------------\n");
    printf("%f\n",*dataSet);
    return 1;
    for (int i = 0; i < dataSize; i++)
    {
        printf("%f\n",*(dataSet+i));
    }
    free(dataSet);
    return 0;
}

