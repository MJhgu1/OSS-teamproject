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

/*
@ Global variable
int i=0; token array의 index
int j=0; data array를 읽을 때 인덱스

token_array 생성(tok_t type)
*/

//start, end
object_f(){
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
}

array_f(){
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
}

string_f(){
/*
token을 만들어서 token array에 넣음
type: string (정해놓음)
start, end: 민지가 쓴 함수 참고
if string 뒤에 ':'' 있으면:
    size = 1
else size = 0

return;
*/
}

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

    Parser(data, length);
    
    printf("\n");
}

