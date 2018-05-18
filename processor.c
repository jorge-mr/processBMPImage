#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int * getNextArrayOf(int bytes, FILE *fp){
	//Esta funcion lee los n siguientes elementos y los regresa como un arreglo
	int *arr = NULL;
	arr = (int *)malloc(bytes * sizeof(int));
	for (int i = 0; i < bytes; ++i){
		arr[i] = fgetc(fp);
		printf("%X ",arr[i]);
	}
	printf("\n");
	return arr;
}

void skipNext(int times, FILE *fp){
	int i;
	for (i = 0; i < times; i++){
		fgetc(fp);
	}
}

long sizeInBytesOfNext(int n, FILE *fp){
	//Esta funcion obtiene el tamaño de los siguientes n bytes
	long sum = 0;
	int i, j, size;
	int *arr = NULL;
	arr = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; ++i){
		arr[i] = fgetc(fp);
		printf("%X ",arr[i]);
	}
	for (i = 0, j=0; i < n; i++, j+=2){
		//printf("i:%d j:%d arr:%d\n",i,j,arr[i]);
		sum += arr[i] * pow(16,j);
	}
	//printf("-----\n");
	return sum;
}

// long sizeInBytes(int arr[]){
// 	//Esta funcion obtiene el tamaño en bytes del arreglo parametro
// 	long sum = 0;
// 	int i, j, size;
// 	size = sizeof(arr);
// 	for (i = 0, j=0; i < size; i++, j+=2){
// 		printf("i:%d j:%d arr:%d\n",i,j,arr[i]);
// 		sum += arr[i] * pow(16,j);
// 	}
// 	printf("-----\n");
// 	return sum;
// }

int main(int argc, char const *argv[]) {
	FILE *fp = NULL;
	int *nextArr = NULL;
	int i = 0;
	int integer;
	char buffer[300];
	fp = fopen("Tulips.bmp","r");
	//fp = fopen("Tulips.bmp","r");
	if (fp == NULL) {
		printf("Error, el archivo no existe\n");
		exit(1);
	}
	
	int b = fgetc(fp);
	int m = fgetc(fp);
	if(b!=66 && m!=77){
		printf("El archivo no es mbp\n");
		exit(1);
	}

	long tam  = sizeInBytesOfNext(4,fp);
	printf("tamanio archivo: %ld bytes\n",tam);
	skipNext(4,fp);//reservados
	long offset = sizeInBytesOfNext(4,fp);
	printf("offset: %ld\n",offset);
	skipNext(4,fp);//reservados
	long ancho = sizeInBytesOfNext(4,fp);
	printf("ancho: %ld\n",ancho);
	long alto = sizeInBytesOfNext(4,fp);
	printf("alto: %ld\n",alto);
	long planos = sizeInBytesOfNext(2,fp);
	printf("planos: %ld\n",planos);
	long bitsPerPixel = sizeInBytesOfNext(2,fp);
	printf("bits por pixel: %ld\n",bitsPerPixel);
	skipNext(24,fp);

	// while(!ferror(pf) && !feof(pf)){
	// 	buffer[i++] = fgetc(pf);
	// }
	while(!ferror(fp) && !feof(fp)){
		integer = fgetc(fp);
		//printf("%d - %d - %X\n",i++,integer,integer); //%X
	}
	buffer[--i] = '\0';

	if (ferror(fp))
		perror("Error durante la lectura");
	printf("\n");
	fclose(fp);
	return 0;
}