/*
get JSON file 
tokenize and store it to array
print the tokens
*/

#include <stdio.h>

int main(){

	FILE *fp;

	//file length
	fp=fopen("example.json", "r");
	int file_length;
	fseek(fp, 0, SEEK_END);
	file_length=ftell(fp);
	printf("file length: %d\n\n", file_length);
	fclose(fp);

	//get all data in a file to data[]
	fp=fopen("example.json", "r");
	char buffer[file_length];
	char data[file_length];
	int length = 0;

	while( (buffer[0] = fgetc(fp)) >0){
		length++;
		data[length-1]=buffer[0];
		if(length >= file_length-1) break;
	}
	data[length]= 0x00;

	//check data[]
	for(int i=0; i<file_length; i++){
		printf("%c", data[i]);
	}
	printf("\n");

	return 0;
    
}
