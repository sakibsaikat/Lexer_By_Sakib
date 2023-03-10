#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char keywords[32][10]={"auto","break","case","char","const","continue","default",
                            "do","double","else","enum","extern","float","for","goto",
                            "if","int","long","register","return","short","signed",
                            "sizeof","static","struct","switch","typedef","union",
                            "unsigned","void","volatile","while"};
int keywordCount[32];
char operators[25][5]={"+","-","*","/","%","=","==","<",">","<=",">=","!=","&&","||","!","&","|","<<",">>","+=","-=","*=","/=","++","--"};
int operatorCount[25]={0};
char specialchar[5][2]={"#","$","^","&","@"};
int specialCount[5]={0};
char separator[2][2]={",",";"};
int separatorCount[2]={0};
char tokens[200][50];

int main(){

	FILE *file1;

	file1 = fopen("sample.txt","r");

	if(file1==NULL){
		printf("\nFile Can't Open\n");
	}

    char *line = '\0';
    char content[200];
    size_t len = 0;
    int count =0;
    *content='\0';


    //Read file and store it in content variable as a string
    while(getline(&line, &len, file1) != -1) {

         int size = strlen(line);
         if(line[0]=='#' && line[1]=='i' && line[2]=='n' && line[3]=='c'){
            continue;
         }
         strncat(content,line,size);
         count++;

     }
     int sz = strlen(content);







	char ch;
	char str[30];
	int t_count=0,control=0;
	*str='\0';
	int lineCount=0;

    //Tokenizing from the string of content variable

	do{
		ch = content[control];

		if(ch==' ')
		{
            if(strcmp(str,"\0")!=0){
                int size = strlen(str);
                strncat(tokens[t_count],str,size);
                *str='\0';
                t_count++;
		     }
		}
		else if(ch=='\n'){

            if(strcmp(str,"\0")!=0){
                int size = strlen(str);
                strncat(tokens[t_count],str,size);
                *str='\0';
                t_count++;

            }
            lineCount++;
		}
		else if(ch=='\t'){

            if(strcmp(str,"\0")!=0){
                int size = strlen(str);
                strncat(tokens[t_count],str,size);
                *str='\0';
                t_count++;
            }
		}
		else if(ch=='"'){

                int size = strlen(str);
                strncat(tokens[t_count],str,size);
                *str='\0';
                t_count++;

                char cht;
                cht = content[control];

                char *tmp_str1;
                tmp_str1 = &cht;
                strncat(str,tmp_str1,1);
                control++;


            while(content[control]!='"'){

                cht = content[control];
                tmp_str1 = &cht;
                strncat(str,tmp_str1,1);
                control++;
            }

            cht = content[control];
            tmp_str1 = &cht;
            strncat(str,tmp_str1,1);



            size = strlen(str);
            strncat(tokens[t_count],str,size);
            *str='\0';
            t_count++;


		}
        else if(ch=='(' || ch==')' || ch=='{' || ch=='}' || ch==';' || ch==',' || ch=='=' || ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='>' || ch=='<' || ch=='@' || ch=='#' ||ch=='$' ||ch=='&')
            {
                if(strcmp(str,"\0")!=0){
                    int size = strlen(str);
                    *tokens[t_count]='\0';
                    strncat(tokens[t_count],str,size);
                    *str='\0';
                    t_count++;
                }

                char *tmp_str;
                tmp_str = &ch;
                strncat(tokens[t_count],tmp_str,1);
                t_count++;

            }
		else{
			char *tmp_str;
			tmp_str = &ch;
			strncat(str,tmp_str,1);
		}

		control++;

	}while(control<sz);


    fclose(file1);



    //Lexiacal Analysis
    printf("\n\n------Lexical Analyzer----------\n\n");
	for(int i=0;i<t_count;i++){

        //keywords
        for(int key=0;key<32;key++){
            if(strcmp(keywords[key],tokens[i])==0){
                keywordCount[key]++;
                break;
            }
        }

        //operators
        for(int op=0;op<25;op++){
             if(strcmp(operators[op],tokens[i])==0){
                operatorCount[op]++;
                break;
            }
        }

        //special character
        for(int sp=0;sp<5;sp++){
             if(strcmp(specialchar[sp],tokens[i])==0){
                specialCount[sp]++;
                break;
            }
        }

        //Separator
        for(int sep=0;sep<5;sep++){
             if(strcmp(separator[sep],tokens[i])==0){
                separatorCount[sep]++;
                break;
            }
        }



	}


    printf("\n\nKeywords-");
    for(int i=0;i<32;i++){
          if(keywordCount[i]!=0){
            printf("\n%s - %d times", keywords[i],keywordCount[i]);
        }
    }
    printf("\n\nOperator-");
    for(int i=0;i<25;i++){
          if(operatorCount[i]!=0){
            printf("\n%s - %d times", operators[i],operatorCount[i]);
        }
    }
    printf("\n\nSpecial Character-");
    for(int i=0;i<5;i++){
        if(specialCount[i]!=0){
            printf("\n%s - %d times", specialchar[i],specialCount[i]);
        }
    }
    printf("\n\nSeparator-");
    for(int i=0;i<2;i++){
        if(separatorCount[i]!=0){
            printf("\n%s - %d times", separator[i],separatorCount[i]);
        }
    }

	
}

