#include <stdio.h> 
#include <unistd.h>

#define BUF_LENGTH 20
#define OK 0
#define EXIT 1 
int main(){ 
	//main of code;

	//Initialization
	unsigned int position; 
	char inBuffer[BUF_LENGTH];
	bool status = OK;	
	
	
	//Interpretation phase
	//will need to create processes to represent the different shell commands 
	//1st commit - simply calls a "demo" program;
	 
	while(!status){
		read(inBuffer)

	}	


	//Termination phase
	exit(0); 
}
