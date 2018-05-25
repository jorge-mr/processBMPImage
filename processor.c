#include <stdio.h>
#include <stdlib.h>
#include <math.h>


FILE *input = NULL;
FILE *output = NULL;

int * getNextArrayOf(int bytes){
	//Esta funcion lee los n siguientes elementos y los regresa como un arreglo
	int *arr = NULL;
	int i;
	arr = (int *)malloc(bytes * sizeof(int));
	for (i = 0; i < bytes; ++i){
		arr[i] = fgetc(input);
		printf("%X ",arr[i]);
		if (arr[i] < 15) {
			fprintf(output, "%X",0);	
		}	
		fprintf(output, "%X",arr[i]);
	}
	printf("\n");
	//fprintf(output, "\n");
	return arr;
}

void skipNext(int times){
	int i;
	int hex;
	for (i = 0; i < times; i++){
		hex = fgetc(input);
		if (hex < 15) {
			fprintf(output, "%X",0);	
		}
		fprintf(output, "%X",hex);
	}
	//fprintf(output, "\n");
}

long sizeInBytesOfNext(int n){
	//Esta funcion obtiene el tamaño de los siguientes n bytes
	long sum = 0;
	int i, j, size;
	int *arr = NULL;
	arr = (int *)malloc(n * sizeof(int));
	for (i = 0; i < n; ++i){
		arr[i] = fgetc(input);
		printf("%X ",arr[i]);
		if (arr[i] < 15) {
			fprintf(output, "%X",0);	
		}
		fprintf(output, "%X",arr[i]);
	}
	for (i = 0, j=0; i < n; i++, j+=2){
		//printf("i:%d j:%d arr:%d\n",i,j,arr[i]);
		sum += arr[i] * pow(16,j);
	}
	free(arr);
	//printf("-----\n");
	//fprintf(output, "\n");
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
	int *nextArr = NULL;
	int i = 0;
	int integer;
	unsigned char buffer[352];
	int ccc = 10 / 3;
	input = fopen("test.bmp","r");
	output = fopen("newImage.bmp","wb");
	//input = fopen("Tulips.bmp","r");
	if (input == NULL) {
		printf("Error, el archivo no existe\n");
		exit(1);
	} else if (output == NULL) {
		printf("No se pudo crear la nueva imagen\n");
		exit(1);
	}
	
	// int b = fgetc(input);
	// int m = fgetc(input);
	// if(b!=66 && m!=77){
	// 	printf("El archivo no es mbp\n");
	// 	exit(1);
	// }
	// fprintf(output, "%X",m);
	// fprintf(output, "%X",b);
	// long tam  = sizeInBytesOfNext(4);
	// printf("tamanio archivo: %ld bytes\n",tam);
	// skipNext(4);//reservados
	// long offset = sizeInBytesOfNext(4);
	// printf("offset: %ld\n",offset);
	// skipNext(4);//reservados
	// long ancho = sizeInBytesOfNext(4);
	// printf("ancho: %ld\n",ancho);
	// long alto = sizeInBytesOfNext(4);
	// printf("alto: %ld\n",alto);
	// long planos = sizeInBytesOfNext(2);
	// printf("planos: %ld\n",planos);
	// long bitsPerPixel = sizeInBytesOfNext(2);
	// printf("bits por pixel: %ld\n",bitsPerPixel);
	// skipNext(24);
	// grayScale();
	int integer_;
	char header[700];
	while(!ferror(input) && !feof(input)){
	 	integer_ = fgetc(input);
	 	header[i++] = integer_;
	}
	//buffer[--i] = '\0';

	//fread(buffer, sizeof(char), 5, input);
	//static unsigned char header[54] = {66,77,0,0,0,0,0,0,0,0,54,0,0,0,40,0,0,0,0,0,0,0,0,0,0,0,1,0,24};
	fwrite(header, sizeof(char), 294, output);
	
	// if (ferror(input))
	// 	perror("Error durante la lectura");
	//fprintf(output, "\n");
	fclose(input);
	printf("%s\n", buffer);
	return 0;
}