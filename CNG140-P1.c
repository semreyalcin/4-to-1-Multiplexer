#include<stdio.h>

#define LF 10	 //ASCII code for LINE FEED character

int main(){
	
	int option;		//Variable that holds user's menu choice
	int counter = 0;	//Variable that holds how many digits does the input have
	char inp;	/*Variable that is used for taking input
	I used char to handle it easily when user enters characters rather than what we want.
	Ex: a,b,c,*,?,! etc.*/
	
	//----------------------------MENU----------------------------//
	printf("Welcome to 4 to 1 multiplexer!\n");
	printf("(1) Compute and Display the Output\n");
	printf("(2) Quit\n");
	printf("You choose: ");
	scanf("%c",&inp);
	
	do{
		if (inp-48 == 1 || inp-48 == 2) 	//If input is valid, it assigns our input as option
			option = inp-48;
			
		counter ++;
		
		if (counter > 1 || inp == LF || ((inp-48 == 1 || inp-48 == 2) == 0)){ // If input is not valid, resets every variable and takes input again
			fflush(stdin);	//Clears buffer
			counter = 0;
			option = 0;
			printf("Please choose a valid option\n");
			printf("You choose: ");
			scanf("%c",&inp);
			continue;
		}
		scanf("%c",&inp);
	}while (inp != LF);		// Repeats whole process until our input is valid
	
	printf("You have choosen option %d\n",option);
	
	//-----------------------------------------------------------------//
	while(option == 1){
		
		fflush(stdin);	//To get rid of line feed character in the buffer
		
		int s0=0, s1=0;		//Variables for select lines
		int d0=0, d1=0, d2=0, d3=0;		//Variables for data lines
		int base = 0;	//Variable that holds users base choice
		counter = 0;	//Resetting counter	
		
		printf("Please enter select lines: ");
		scanf("%c",&inp);
		
		do{	//The loop where we get select lines from user
			if (counter == 0)       
				s1 = inp-48;		
			else if (counter == 1)
				s0 = inp-48;
				
			counter++;
			
			if (counter > 2 || inp == LF || ((inp-48 == 0 || inp-48 == 1) == 0)){ // If input is not valid, resets every variable and takes input again
				fflush(stdin);	//Clears buffer
				counter=0;
				s0=0;
				s1=0;
				printf("It is not a 2-digit binary number for the select lines. Please try again!\n");
				printf("Please enter select lines: ");
				scanf("%c",&inp);
				continue;
			}
			scanf("%c",&inp);
		}while (inp != LF);
		
		if (counter == 1){ //if user enters 1 digit binary number, we exchange s1 and s0 to get correct order 
			int temp=s0;
			s0=s1;
			s1=temp;
		}
		//printf("s1:%d s0:%d\n",s1,s0); //DEBUG!!
		
		printf("Which base will you use to enter data lines (base 16/10/2)? ");
		scanf("%d",&base);
		
		while((base == 2 || base == 10 || base == 16)==0){	//Asking for base until user enters valid base 
			fflush(stdin);
			printf("Please enter a valid base!\n");
			printf("Which base will you use to enter data lines (base 16/10/2)? ");
			scanf("%d",&base);
		}
		
		printf("Please enter data lines to decode: ");
		counter = 0;
		fflush(stdin);
		
		int intinp = 0;	//The variable that will hold input as decimal number
		
		switch(base){
			case 2:
				scanf("%c",&inp);
					
				do{	//The loop where we get data lines from user
					if (counter == 0)       
						d3 = inp-48;		
					else if (counter == 1)
						d2 = inp-48;
					else if (counter == 2)
						d1 = inp-48;
					else if (counter == 3)
						d0 = inp-48;
							
					counter++;
					
					if (counter > 4 || inp == LF || ((inp-48 == 0 || inp-48 == 1) == 0)){ // If input is not valid, resets every variable and takes input again
						fflush(stdin);	//Clears buffer
						counter=0;
						d3 = 0;
						d2 = 0;
						d1 = 0;
						d0 = 0;
						printf("It is not a 4-digit binary number for the data lines. Please try again!\n");
						printf("Please enter data lines to decode: ");
						scanf("%c",&inp);
						continue;
					}
					scanf("%c",&inp);
				}while (inp != LF);
			
				int counter_backup=counter;	//Because I'll change counter, I  back up it
				
				while(counter < 4){ //Shifting input if user enters less than 4-digit
					d0=d1;
					d1=d2;
					d2=d3;
					counter++;
				}
				if (counter_backup == 3)	//Correcting, old values after shifting
					d3 = 0;
				else if (counter_backup == 2){
					d3 = 0;
					d2 = 0;
				}else if (counter_backup == 1){
					d3 = 0;
					d2 = 0;
					d1 = 0;
				}
				
				printf("Output is ");	//Printing Output
				
				if (s1 == 0 && s0 == 0)
					printf("%d",d0);
				else if (s1 == 0 && s0 == 1)
					printf("%d",d1);
				else if (s1 == 1 && s0 == 0)
					printf("%d",d2);
				else if (s1 == 1 && s0 == 1)
					printf("%d",d3);
				printf("\n");
				
				break;
			
			case 10:
				
				scanf("%c",&inp);
					
				do{	
	
					if (intinp > 15){	//If input is bigger than 15, prints error message and takes input again
						fflush(stdin);
						printf("It is not possible to convert decimal %d to 4-digit binary number. Please try again!\n",intinp);
						printf("Please enter data lines to decode: ");
						scanf("%c",&inp);
						intinp = 0;
					}
				
					do{	
						
						intinp *= 10; //Converting char input to decimal number
						intinp += inp-48;
						
						
						if (((inp-48 >= 0 && inp-48 <= 9) == 0)){ // If input is not valid, resets every variable and takes input again
							fflush(stdin);	//Clears buffer
							intinp = 0;
							printf("You can't enter %c. Please try again!\n",inp);
							printf("Please enter data lines to decode: ");
							scanf("%c",&inp);
							continue;
						}
						
						scanf("%c",&inp);
					}while (inp != LF);
				}while(intinp > 15);
				
				d0 = intinp % 2;	//Converting decimal number to binary
				intinp /= 2;
				d1 = intinp % 2;
				intinp /= 2;
				d2 = intinp % 2;
				intinp /= 2;
				d3 = intinp % 2;
				
//				printf("d3:%d d2:%d d1:%d d0:%d\n",d3,d2,d1,d0);	//DEBUG!!
				
				printf("Output is ");	//Printing output
				
				if (s1 == 0 && s0 == 0)
					printf("%d",d0);
				else if (s1 == 0 && s0 == 1)
					printf("%d",d1);
				else if (s1 == 1 && s0 == 0)
					printf("%d",d2);
				else if (s1 == 1 && s0 == 1)
					printf("%d",d3);
				printf("\n");
				
				break;
			
			case 16:
				
					scanf("%c",&inp);
					
					do{	
						if((inp-48 >= 0 && inp-48 <= 9) && counter < 1){
							intinp *= 10;
							intinp += inp-48;
						}else if((inp-87 >= 10 && inp-87 <= 15) && counter < 1){
							intinp = inp-87;
						}else if((inp-55 >= 10 && inp-55 <= 15) && counter < 1){
							intinp = inp-55;
						}else{
							fflush(stdin);
							intinp = 0;
							counter = 0;
							printf("Your input is either not a hexadecimal or too big to convert 4-digit binary number. Please try again!\n",inp);
							printf("Please enter data lines to decode: ");
							scanf("%c",&inp);
							continue;
						}
						counter ++;
						scanf("%c",&inp);
					}while (inp != LF);
				
				
					d0 = intinp % 2;	//Converting decimal number to binary
					intinp /= 2;
					d1 = intinp % 2;
					intinp /= 2;
					d2 = intinp % 2;
					intinp /= 2;
					d3 = intinp % 2;
					
					printf("Output is ");	//Printing output
				
					if (s1 == 0 && s0 == 0)
						printf("%d",d0);
					else if (s1 == 0 && s0 == 1)
						printf("%d",d1);
					else if (s1 == 1 && s0 == 0)
						printf("%d",d2);
					else if (s1 == 1 && s0 == 1)
						printf("%d",d3);
					printf("\n");
					
					break;
					
				default:
					printf("How did you select that base? Well done!\n"); //If the user can somehow achieve an invalid base selection
					break;
		}


	//----------------------------MENU----------------------------//
		counter = 0;   
		option = 0;
		fflush(stdin);
		
		printf("\nWelcome to 4 to 1 multiplexer!\n");
		printf("(1) Compute and Display the Output\n");
		printf("(2) Quit\n");
		printf("You choose: ");
		scanf("%c",&inp);
		
		do{
			if (inp-48 == 1 || inp-48 == 2)
				option = inp-48;
				
			counter ++;
			
			if (counter > 1 || inp == LF || ((inp-48 == 1 || inp-48 == 2) == 0)){ 
				fflush(stdin);
				counter=0;
				s0=0;
				s1=0;
				printf("Please choose a valid option\n");
				printf("You choose: ");
				scanf("%c",&inp);
				continue;
			}
			scanf("%c",&inp);
		}while (inp != LF);	
		printf("You have chosen option %d\n",option);
	}
	
	printf("Byee!!");

	return 0;
}
