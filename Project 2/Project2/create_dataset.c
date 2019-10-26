#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

float get_Random(float rmax){
    float x = ((float)rand()/(float)RAND_MAX)*rmax;
    // printf("%f\n", x);
    return x;
}

void create_dataset(char* filename, int dataSize){
    // rule of thumb: seed only once
    srand((unsigned int)time(NULL));

    FILE *fp;
    float data[dataSize];
    fp = fopen(filename,"wb");
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = get_Random(100);
        fwrite(data, sizeof(float), sizeof(dataSize), fp);
    }
    fclose(fp);
}

void main(){
    create_dataset("dataSet", 100.0);
}

