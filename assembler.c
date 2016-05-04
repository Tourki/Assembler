/*
 ============================================================================
 Name        : assembler.c
 Author      : Hossam Tourki
 Version     : 0.1
 Copyright   : Proprietary
 Description : Assembler written in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fpr;
FILE *fpw;

unsigned int getIstruction ();
unsigned int getothersR ();

int main (void) {
	/* pointer to the first line in the file */
	fpr = fopen("test.txt","r");
	fpw = fopen("mem.txt","w");
	unsigned int inst, code, others;
	
	while (!feof(fpr)) {
		inst= getIstruction();
		others = getothersR();
		code = inst | others;
		printf("%d \n",code);
		fprintf(fpw,"%d \n",code);
	}

	fclose(fpr);
	fclose(fpw);

	return 0;
}

unsigned int getothersR (void) {
	unsigned int y=0;
	unsigned int temp2;
	unsigned char temp[2];
	unsigned char i=0;
	char count=0;
	char line[50];

	fgets(line, 50, fpr);

	while (line[i] != '\n') {
		if (line[i] == 'R') {
			count++;
			temp[0] = line[i+1];
			temp[1] = line[i+2];
			temp2 = atoi(temp);
			printf("%d \n", sizeof(temp2));
			printf("%d \n", temp2);
			if (count==1) {
				y |= (temp2<<11); //first reg is Rd so in the code it is shifted lift by 11
			} else if(count==2) {
				y |= (temp2<<21); //Rs
			} else if(count==3) {
				y |= (temp2<<16); //Rt
			}
			printf("%d \n", y);
		}

		i++;
	}

	printf("%s \n", line);

	return y;
}

unsigned int getIstruction (void) {
	char instruction_name[4]; /*maximum 4*/
	unsigned int x;
	fscanf(fpr, "%s", instruction_name);

	if (!strcmp(instruction_name, "sll"))
		x = 0x00000000;
	else if (!strcmp(instruction_name, "srl"))
		x = 0x00000002;
	else if (!strcmp(instruction_name, "sra"))
		x = 0x00000003;
	else if (!strcmp(instruction_name, "in"))
		x = 0x00000004;
	else if (!strcmp(instruction_name, "out"))
		x = 0x00000005;
	else if (!strcmp(instruction_name, "hlt"))
		x = 0x00000006;
	else if (!strcmp(instruction_name, "nop"))
		x = 0x00000007;
	else if (!strcmp(instruction_name, "push"))
		x = 0x0000000A;
	else if (!strcmp(instruction_name, "pop"))
		x = 0x0000000B;
	else if (!strcmp(instruction_name, "mfhi"))
		x = 0x00000010;
	else if (!strcmp(instruction_name, "mflo"))
		x = 0x00000012;
	else if (!strcmp(instruction_name, "mul"))
		x = 0x00000018;
	else if (!strcmp(instruction_name, "mulu"))
		x = 0x00000019;
	else if (!strcmp(instruction_name, "div"))
		x = 0x0000001A;
	else if (!strcmp(instruction_name, "divu"))
		x = 0x0000001B;
	else if (!strcmp(instruction_name, "add"))
		x = 0x00000020;
	else if (!strcmp(instruction_name, "addu"))
		x = 0x00000021;
	else if (!strcmp(instruction_name, "sub"))
		x = 0x00000022;
	else if (!strcmp(instruction_name, "subu"))
		x = 0x00000023;
	else if (!strcmp(instruction_name, "and"))
		x = 0x00000024;
	else if (!strcmp(instruction_name, "or"))
		x = 0x00000025;
	else if (!strcmp(instruction_name, "xor"))
		x = 0x00000026;
	else if (!strcmp(instruction_name, "nor"))
		x = 0x00000027;
	else if (!strcmp(instruction_name, "slt"))
		x = 0x0000002A;
	else if (!strcmp(instruction_name, "sltu"))
		x = 0x0000002B;
	printf("%d \n", x);
	return x;
}