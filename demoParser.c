//
//  main.c
//  parser.c
//
//  Created by 김민지 on 23/05/2019.
//  Copyright © 2019 김민지. All rights reserved.
//

#include <stdio.h>

#define MAX 1024

// 오브젝트 타입 구분
typedef enum{
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMATIVE = 4
}type_t;

// 토큰 구조
typedef struct{
    type_t type;
    int start;
    int end;
    int size;
}tok_t;

int tok_index=0; //token array의 index
int j=0; //data array를 읽을 때 인덱스

tok_t token[30];

int object_f(char data[], int count);
int array_f(char data[]);
int string_f(char data[]);

int main(){
    
    FILE *fp=fopen("example.json", "r");
    int fileLength;
    fseek(fp,0,SEEK_END);
    fileLength=ftell(fp);
    
    
    rewind(fp);
    
    int length=0;
    char buffer[fileLength];
    char data[fileLength];
    
    
    while((buffer[0]=fgetc(fp))>0){
        if(buffer[0]!=0X00){
            length++;
            data[length-1]=buffer[0];
            if(length>=fileLength-1) break;
        }
    }
    data[length]=0X00;
    fclose(fp);
    
    //type!!
    
    object_f(data, length);
    
    
    printf("%d\n",length);
    int i = 0;
    while(token[i].type){
        printf("[%d] ",i);
        int k = token[i].start ;
        for(k; k<token[i].end; k++){
            printf("%c", data[k]);
        }
        printf(" (size: %d ",token[i].size);
        printf(", %d~%d , ",token[i].start, token[i].end);
        switch (token[i].type) {
            case 1 : printf("OBJECT"); break;
            case 2 : printf("ARRAY"); break;
            case 3 : printf("STRING"); break;
            case 4 : printf("PRIMATIVE"); break;
            default : printf("UNDEFINED"); break;
        }
        printf(" )\n");
        i++;
    }
    
    printf("\n");
}



int object_f(char data[], int count){
    /*
     new token t 생성
     t.start = i
     t.type = object
     size = 1
     
     data[]를 읽어온다.
     if data[i] == '"':
     string_f() 함수 호출
     if data[i] == '{':
     object_f() 함수 호출
     if data[i] == '[':
     array_f() 함수 호출
     
     if data[i] == ',': size++
     
     data[i] == '}':
     end = i
     return
     
     */
    
    int start_index = tok_index;
    int s=0;//size
    
    token[tok_index].start = j;
    token[tok_index].size = s;
    token[tok_index].type = OBJECT;
    j++;
    tok_index++;
    while(data[j]!='}'){
        if(data[j]=='"')
            string_f(data);
        else if(data[j]=='{')
            object_f(data, j);
        else if(data[j]=='[')
            array_f(data);
        else if(data[j]==','){
            s++;
        }
        j++;
    }
    
    token[start_index].size = s+1;
    token[start_index].end = j+1;
    return 0;
}

int array_f(char data[]){
    /*
     new token t 생성
     t.start = i
     t.type = object
     size = 1
     
     data[]를 읽어온다.
     if data[i] == '"':
     string_f() 함수 호출
     if data[i] == '{':
     object_f() 함수 호출
     if data[i] == '[':
     array_f() 함수 호출
     
     if data[i] == ',': size++
     
     data[i] == '}':
     end = i
     return
     */
    int start_index = tok_index;
    int s=0;
    token[tok_index].start=j;
    token[tok_index].size = s;
    
    token[tok_index].type = ARRAY;
    
    j++;
    tok_index++;
    while(data[j]!=']'){
        if(data[j]=='"')
            string_f(data);
        else if(data[j]=='{')
            object_f(data, j);
        else if(data[j]=='[')
            array_f(data);
        else if(data[j]==','){
            s++;
        }
        j++;
    }
    
    token[start_index].size = s+1;
    token[start_index].end = j+1;
    
    return 0;
}

int string_f(char data[]){
    /*
     token을 만들어서 token array에 넣음
     type: string (정해놓음)
     start, end: 민지가 쓴 함수 참고
     if string 뒤에 ':'' 있으면:
     size = 1
     else size = 0
     
     return;
     */
    token[tok_index].type = STRING;
    token[tok_index].start = j+1;
    j++;
    while(data[j]!='"'){
        j++;
    }
    
    if(data[j+1]==':')
        token[tok_index].size = 1;
    else if(data[j+1]==',')
        token[tok_index].size = 0;
    
    
    token[tok_index].end = j;
    tok_index++;

    
    return 0;
}