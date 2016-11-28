#include "syscalls.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

#define STDOUT 1
#define STDIN 0
#define BUF_SIZE 100

static char *convert(unsigned int num, int base);

//Lee un caracter de entrada estandar y lo devuelve


//Imprime un caracter en la salida estandar
void putchar(char c){
  sys_write(STDOUT, &c, 1);
}


void getline(char * buf, int max){
    int c;
    int i = 0;
    while((c = getchar()) != '\n'){
        if(c == '\b'){
            if(i > 0){ //Borro del buffer de comando
            i--;
            putchar(c); //Y de la pantalla
            }

        } else if(i < max - 1){ //Dejo espacio para el 0
            buf[i++] = c; //Agrego al buffer
            putchar(c);
        }
    }
        putchar('\n');

    buf[i] = 0; //Null termination
    return;
}


//Scanf con %d, %s
int scanf(char* fmt, ...) 
{
/* 
    char *traverse;
    unsigned int i; 

    char * str; 
    int * int_ptr;

    int count = 0;

    va_list arg; 
    va_start(arg, fmt); 

    char line[BUF_SIZE];
    char * buf = line;
    char aux[BUF_SIZE];

    getline(line, BUF_SIZE);

    for(traverse = fmt; *traverse != '\0' && *buf != '\0'; traverse++) 
    { 
        while( *traverse != '%'){ //Avanzo hasta el %
            //Si no matchean
            if(*traverse != *buf){ //Dejo de leer, ya no cumple el formato
                  va_end(arg);
                return count; 
            }

            buf++;
            traverse++; 
        } 

        if(*traverse == 0){
            va_end(arg); 
            return count; //Termine
        }

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) { 
            case 'd' :
                        int_ptr = va_arg(arg,int *); //Leo puntero

                        if(*buf != '-' && !isdigit(*buf)){
                            va_end(arg);
                            return count;
                        }
                      

                        aux[0] = *(buf++); //Copio el primero (digito o '-')
                        for(i=1; isdigit(*buf) && i < BUF_SIZE - 1; buf++, i++){ 
                            //Copio el resto de los digitos
                            aux[i] = *buf;
                        }
                        aux[i] = '\0';
                        *int_ptr = atoi(aux);
                        count++;

                        break; 

            case 's' : str = va_arg(arg, char *);       //Fetch string
                      strncpy(str, buf, strlen(buf)); //Copio hasta el final en s
                      count++;
                      va_end(arg); 
                      return count;
                      break; 

        }   
    } 

    //Cerrando la lista variable
    va_end(arg); 
    return count;

*/
    return 1;
} 


static char *convert(unsigned int num, int base) 
{ 
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50]; 
    char *ptr; 

    ptr = &buffer[49]; 
    *ptr = '\0'; 

    do 
    { 
        *--ptr = Representation[num%base]; 
        num /= base; 
    }while(num != 0); 

    return(ptr); 
}



