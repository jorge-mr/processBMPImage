#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *input = NULL;
FILE *output = NULL;
char *header = NULL;
int index_ = 0;

void skipNext(int times){
	int i, temp;
	for (i = 0; i < times; i++){
		temp = fgetc(input);
        header[index_++] = temp;
	}
}

long sizeInBytesOfNext(int n){
	//Esta funcion obtiene el tamaño de los siguientes n bytes
	long sum = 0;
	int i, j, size;
	int *arr = NULL;
	arr = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; ++i){
		arr[i] = fgetc(input);
        header[index_++] = arr[i];
		printf("%X ",arr[i]);
	}
	for (i = 0, j=0; i < n; i++, j+=2){
		sum += arr[i] * pow(16,j);
	}
	free(arr);
	return sum;
}

void grayScale(){
	while(!ferror(input) && !feof(input)){
		int r = fgetc(input);
		int g = fgetc(input);
		int b = fgetc(input);
		int gray = (r + g + b)/3;
		if (gray < 15) { fprintf(output, "%X",0); }
		fprintf(output, "%X",gray);
		if (gray < 15) { fprintf(output, "%X",0); }
		fprintf(output, "%X",gray);
		if (gray < 15) { fprintf(output, "%X",0); }
		fprintf(output, "%X",gray);
	}
}

int main(int argc, char const *argv[]) {
    int temp;
    header = (char *)malloc(6 * sizeof(char));
    
	input = fopen("test.bmp","r");
	output = fopen("newImage.bmp","wb");
	if (input == NULL) {
		printf("Error, el archivo no existe\n");
		exit(1);
	} else if (output == NULL) {
		printf("No se pudo crear la nueva imagen\n");
		exit(1);
	}
	
    int b = fgetc(input);
    header[index_++] = b;
    int m = fgetc(input);
    header[index_++] = m;
    if(b!=66 && m!=77){
        printf("El archivo no es mbp\n");
        exit(1);
    }
    long tam  = sizeInBytesOfNext(4);
    printf("tamanio archivo: %ld bytes\n",tam);
    header = (char *)realloc(header,(int)tam);
    skipNext(4);//reservados
    long offset = sizeInBytesOfNext(4);
    printf("offset: %ld\n",offset);
    skipNext(4);//reservados
    long ancho = sizeInBytesOfNext(4);
    printf("ancho: %ld\n",ancho);
    long alto = sizeInBytesOfNext(4);
    printf("alto: %ld\n",alto);
    long planos = sizeInBytesOfNext(2);
    printf("planos: %ld\n",planos);
    long bitsPerPixel = sizeInBytesOfNext(2);
    printf("bits por pixel: %ld\n",bitsPerPixel);
    skipNext(24);//reservados
    fseek(input, 0, SEEK_SET);
	
    while(!ferror(input) && !feof(input)){
	 	temp = fgetc(input);
	 	header[index_++] = temp;
	}
    
	fwrite(header, sizeof(char), 214, output);
	fclose(input);
	return 0;
}
