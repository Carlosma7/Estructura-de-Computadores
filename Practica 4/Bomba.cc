// Orden de compilacion: gcc -m32 bomba.c -o bomba
// Carlos Morales Aguilera - 2o B

#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

//char password[] = "percebe\n";	// Contraseña de la bomba -> ASCII = 112 101 114 99 101 98 101
const char password[] = "shufheh\n";	// ASCII + 3
int passcode = 2708;

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("*************************\n");
	printf("*** Bomba desactivada ***\n");
	printf("*************************\n");
	exit(0);
}

void Cifrar_Password(char * password_proporcionada){
	char password_cifrada[strlen(password)];
	
	if (strlen(password_proporcionada) != strlen(password)){
		boom();
	}

	// Rellenamos un vector de caracteres auxiliar con los caracteres de la cadena introducida por teclado
	// a los que le aplicamos el mismo incremento de valor que a la cadena clave.

	for(int i=0; i < strlen(password)-1; i++){
		password_cifrada[i] = password_proporcionada[i]+3;
	}

	password_cifrada[strlen(password)-1]='\n';

	if (strncmp(password_cifrada,password,strlen(password))){
		boom();
	}
}

void Cifrar_Passcode(int passcode_proporcionado){
	if(passcode_proporcionado != passcode)
		boom();
}

int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 30
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la password: ");
	fgets(pass,SIZE,stdin);

	Cifrar_Password(pass);		// Comprobamos la password

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    boom();

	printf("Introduce el passcode: ");
	scanf("%i",&pasv);
	
	Cifrar_Passcode(pasv);		// Comprobamos el passcode

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    boom();

	defused();
}

