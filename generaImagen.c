#include<stdio.h>
#include<stdlib.h>
int main(int argc, char const *argv[]){
	FILE *pointer = NULL;
	pointer = fopen("newImage.bmp","wb");
	//input = fopen("Tulips.bmp","r");
	if (pointer == NULL) {
		printf("No se pudo crear la nueva imagen\n");
		exit(1);
	}
	char imagen[10000] = "424DD60000000000000036000000280000000A000000050000000100180000000000A000000000000000000000000000000000000000FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7F7F7F00000000000000000000000000000000000000000000000000000000007F7F7F0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00007F7F7F000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF007F7F7F00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF7F7F7F0000";
	fwrite(imagen , 1 , sizeof(imagen) , pointer);
	return 0;
}