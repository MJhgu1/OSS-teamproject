//
//  main.c
//  parser.c
//
//  Created Parser by Minji Kim, Jiwon Kim on 23/05/2019.
//  Copyright © 2019 Minji Kim. All rights reserved.
//  Created Menu by Hyeonji Kim on 02/06/2019.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 오브젝트 타입 구분
typedef enum
{
    UNDEFINED = 0,
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    PRIMATIVE = 4,
} type_t;

// 토큰 구조
typedef struct
{
    type_t type;
    int start;
    int end;
    int size;
    char key[20];
} tok_t;

int tok_index = 0; //token array의 index
int j = 0;         //data array를 읽을 때 인덱스

tok_t token[100];

int object_f(char data[], int count);
int array_f(char data[]);
int string_f(char data[]);
int primative_f(char data[]);

int main(int argc, char **argv)
{

    FILE *fp = fopen(argv[1], "r");
    int fileLength;
    fseek(fp, 0, SEEK_END);
    fileLength = ftell(fp);

    rewind(fp);

    int length = 0;
    char buffer[fileLength];
    char data[fileLength];

    while ((buffer[0] = fgetc(fp)) > 0)
    {
        if (buffer[0] != 0X00)
        {
            length++;
            data[length - 1] = buffer[0];
            if (length >= fileLength - 1)
                break;
        }
    }
    data[length] = 0X00;
    fclose(fp);



    //Menu
    int flag1=1;
    printf("\n************************************\n");
    printf("<Patient Information Inquiry System>\n");
    printf("************************************\n");
    while(flag1){
        printf("\n               Log In\n");
        printf("\n            ID : ");
        char id[10];
        int pw;
        scanf("%s", id);
        if (strcmp(id,"doctor")==0)
        {
            printf("          Password : ");
            scanf("%d", &pw);
            if (pw == 1234)
            {
                int flag2 = 1;
                int num;

                while(flag2){
                    
                    printf("\n************* Welcome! *************\n");
                    printf("1. Basic View: Result of Parsing\n");
                    printf("2. A list of Patients\n");
                    printf("3. My Patients\n");
                    printf("4. Patient Who Needs Care\n");
                    printf("5. Exit\n");
                    printf("************************************\n");

                    printf("Please select the number of information you want to see : ");
                    scanf("%d", &num);
                    if(num==1){
                            //type
                            object_f(data, length);
                            //printf("%d\n",length);
                            
                            int i=0;
                            while(token[i].type){
                                printf("[%d] ",i);
                                
                                for(int k = token[i].start ; k<token[i].end; k++){
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
                                printf(")\n");
                                i++;
                            }//end_while(token[i].type)
                            printf("\n");
                    }//end_if(num==1)
                    else if(num==2){
                        printf("\n***** A list of Patients *****\n");

                        object_f(data, length);
                        printf("\n");
                        for(int i=0; i<tok_index; i++){
                            if(strcmp(token[i].key, "name")==0){

                                for(int k = token[i+1].start; k<token[i+1].end; k++){
                                    printf("%c", data[k]);
                                }
                                printf("\n");
                            }
                        }
                        
                    }
                    else if(num==3){
                        printf("\n***** My Patients *****\n");
                        object_f(data, length);
                        
                        char doctor_name[10];
                        printf("Doctor: ");
                        scanf("%s", doctor_name);

                        for(int i=0; i<tok_index; i++){
                            if(strcmp(token[i].key, "doctor")==0 && strcmp(token[i+1].key, doctor_name)==0){

                                for(int k = token[i-15].start; k<token[i-15].end; k++){
                                    printf("%c", data[k]);
                                }
                                printf("\n");
                            }
                        }

                    }
                    else if(num==4){
                        printf("\n***** Patient Who Needs Care *****\n");
                        printf("@Patient whose systolic pressure is higher than 140 or lower than 100 needs care\n");
                        printf("@Patient whose pulse is higher than 90\n\n");
                        object_f(data, length);
                        
                        int c=0;
                        for(int i=0; i<tok_index; i++){
                            if(strcmp(token[i].key, "systolic pressure")==0){
                                //printf("%d\n",token[i+1].start);
                                //printf("%d\n",token[i+1].end);
                                //printf("%c\n",data[token[i+1].start]);
                                char press_num[20]="\0";
                                for(int k=token[i+1].start ; k<token[i+1].end; k++){
                                    char add_char[10]={data[k]};
                                    strcat(press_num, add_char);
                                }

                                
                                if(atoi(press_num)>=140 || atoi(press_num)<=100){
                                    c++;
                                    printf("%d. ", c);
                                    for(int k = token[i-5].start; k<token[i-5].end; k++){
                                        printf("%c", data[k]);
                                    }
                                    printf(": %d", atoi(press_num));
                                    printf(" (pressure)\n");
                                }
                                
                            }//end_if(strcmp(token[i].key, "systolic pressure")==0)

                            if(strcmp(token[i].key, "pulse")==0){
                                char pulse_num[20]="\0";
                                for(int k=token[i+1].start ; k<token[i+1].end; k++){
                                    char add_char[10]={data[k]};
                                    strcat(pulse_num, add_char);
                                }

                                
                                if(atoi(pulse_num)>=90){
                                    c++;
                                    printf("%d. ", c);
                                    for(int k = token[i-9].start; k<token[i-9].end; k++){
                                        printf("%c", data[k]);
                                    }
                                    printf(": %d", atoi(pulse_num));
                                    printf(" (pulse)\n");
                                }
                                
                            }
                        }//end_for(int i=0; i<tok_index; i++)
                    
                    }
                    else if(num==5){
                        flag2=0;
                        printf("The program has been terminated.\n");
                    }
                    else{
                        printf("Please re-select the number.\n");
                        printf("(If you input CHARACTER, then program will exit. Please start again.)\n");
                        flag2=0;
                    }

                }//end_while(flag2)
                
                flag1=0;
                
            } //end_if(pw==1234)
            else
            {
                printf("This is not a registered Password\nPlease check your Password\n");
            }
        } //end_if(id=="doctor")
        else
        {
            printf("This is not a registered ID\nPlease check your ID\n");
        } //end else

    }//end_while


    return 0;
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
    token[tok_index].type = OBJECT;
    token[tok_index].size = s;
    
    j++;
    tok_index++;
    while(data[j]!='}'){
        if(data[j]=='"')
            string_f(data);
        else if(data[j]=='{')
            object_f(data, j);
        else if(data[j]=='[')
            array_f(data);
        else if((47<data[j] && data[j]<58) || data[j]==84 || data[j]==116 || data[j]==70 || data[j]==102)
            primative_f(data);
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
        else if((47<data[j] && data[j]<58) || data[j]==84 || data[j]==116 || data[j]==70 || data[j]==102 )
            primative_f(data);
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
    token[tok_index].start = j+1;
    token[tok_index].type = STRING;
    j++;
    while(data[j]!='"'){
        j++;
    }
    
    if(data[j+1]==':')
        token[tok_index].size = 1;
    else if(data[j+1]==',')
        token[tok_index].size = 0;
    
    
    token[tok_index].end = j;

    //if(token[tok_index].size == 1){
        int num_char=token[tok_index].end-token[tok_index].start;
        //printf("%d ", num_char);
        for(int k=0; k<num_char; k++){
            //if(isdigit(data[token[tok_index].start+k])){
                //sprintf(&token[tok_index].key[k], "%d", data[token[tok_index].start+k]);
            //}
            token[tok_index].key[k]=data[token[tok_index].start+k];
            //printf("%c ", token[tok_index].key[k]);
        }
        token[tok_index].key[num_char]=0x00;
    //}
    
    

    tok_index++;
    
    return 0;
}

int primative_f(char data[]){
    /*
     token을 만들어서 token array에 넣음
     type: string (정해놓음)
     start, end: 민지가 쓴 함수 참고
     if string 뒤에 ':'' 있으면:
     size = 1
     else size = 0
     
     return;
     */
    token[tok_index].type = PRIMATIVE;
    token[tok_index].start = j;
    token[tok_index].size = 0;
    j++;
    while(data[j] != ','){
        j++;
    }
    
    token[tok_index].end = j;
    j--;
    tok_index++;
    
    return 0;
}
