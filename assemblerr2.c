/*
 ============================================================================
 Name        : assembler.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE  *fpr;
FILE  *fpw;
unsigned int getIstruction ();
unsigned int getothersRd ();
unsigned int getothersRs ();
unsigned int getothersshift ();
unsigned int getothersI ();
unsigned int getothersJ ();
unsigned int getothersluI ();
unsigned int getothers(unsigned int);
int main(void) {
	unsigned int inst,code,others;
	/*pointer to the first line in the file 8*/
	fpr = fopen("test.txt","r");
	fpw = fopen("mem.txt","w");
while (!feof(fpr))
	{inst= getIstruction();
     others = getothers(inst);
	 code = inst | others;
	printf	 ("%d \n \n \n",code);
    fprintf	 (fpw,"%d \n",code);
	}
    fclose(fpr);
    fclose(fpw);

	return 0;
}


/*there are some instructions share same syntax
 *First type is instruction Rd,Rs,Rt  where d & t & s = 00 >> 31
• add Rd, Rs, Rt Rd = Rs + Rt (signed)
• addu Rd, Rs, Rt Rd = Rs + Rt (unsigned)
• sub Rd, Rs, Rt Rd = Rs - Rt (signed)
• subu Rd, Rs, Rt Rd = Rs - Rt (unsigned)
• and Rd, Rs, Rt Rd = Rs • Rt
• nor Rd, Rs, Rt Rd = (Rs + Rt)’
• or Rd, Rs, Rt Rd = Rs + Rt
• xor Rd, Rs, Rt Rd = Rs ⊕ Rt
• mfhi Rd Rd = hi
• mflo Rd Rd = lo
• slt Rd, Rs, Rt Rd = 1 if Rs < Rt, Rd = 0 if Rs ≥ Rt (signed)
• sltu Rd, Rs, Rt Rd = 1 if Rs < Rt, Rd = 0 if Rs ≥ Rt (unsigned)

 *Second type is instruction Rs,Rt  where t & s = 00 >> 31
• jr Rs
• in Rs                    Store the input value into Rs R 0x00 0x04
• out Rs                   Output the value of Rs R 0x00 0x0
• mult Rs,Rt
• multu Rs,Rt
• div Rs,Rt
• divu Rs,Rt
• push Rs,Rt
• pop Rs,Rt

 *Third type is instruction Rd,Rs,Sa  where d & s & Sa = 00 >> 31
• sll Rd, Rs, Sa Rd = Rs left shifted by Sa bits
• srl Rd, Rs, Sa Rd = Rs right shifted by Sa bits
• sra Rd, Rs, Sa Rd = Rs right arithmatic shifted by Sa bits

 *Fourth type is instruction Rt,Rs,IMM  where t & s & IMM
• addi Rt,Rs,immediate
• addiu Rt,Rs,immediate
• andi Rt,Rs,immediate
• ori Rt, Rs, Imm
• slti Rt,Rs,immediate
• sltiu Rt,Rs,immediate
• lw Rt,Rs, Offset Rt = word at M[Address + Rs]
• sw Rt,Rs, offset Word at M[Address + Rs] = Rt
• beq Rt,Rs,Offset
• bne Rt,Rs,Offset

 *Fifth type is instruction IMM
 • jal jump_target
 • j jump_target

 *Sixth type is instruction Rt,Imm
• lui Rt, Imm      Rt[31:16] = Imm, Rt[15:0] = 0



*/


/*+==========================================================================================================================*/
/*============First Type=======================*/
unsigned int getothersRd (void)
{   unsigned int y=0; /*the ouput of the function*/
    char temp [2];/*temp array to get the string Reg number*/
    int temp2;/*temp int to get the integer Reg number*/
    char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rd,Rs,Rt
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the three Regs only
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",sizeof(temp2));
     printf("%d \n",temp2);
	 if (count==1)
	 {/* first reg is Rd so in the code it is shifted lift by 11 */
     y|=(temp2<<11);
	 }
     else if(count==2)
     {/* second reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21); //RS
     }
     else if(count==3)
	 {/* third reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Second Type=======================*/
unsigned int getothersRs (void)
{   unsigned int y=0;/*the ouput of the function*/
    unsigned char temp [2];/*temp array to get the string Reg number*/
    unsigned int temp2;/*temp int to get the integer Reg number*/
    char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n')
 {   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
      * as the instruction format is instruction Rs,Rt
            and the binary format is OPCODE      RS RT RD   SA FUNC
       in this type we focus on the two Regs only Rs,Rt
     */
   if (line[i]=='R')
   { count++;
	 temp [0]= line[i+1] ;
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);
     printf("%d \n",sizeof(temp2));
     printf("%d \n",temp2);
     if(count==1)
     {/* first reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21); //RS
     }
     else if(count==2)
	 {/* second reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Third Type=======================*/
unsigned int getothersshift (void)
{   unsigned int y=0;/*the ouput of the function*/
    unsigned char temp [2];/*temp array to get the string Reg number*/
    unsigned int temp2;/*temp int to get the integer Reg number*/
    unsigned char SA [2];/*temp array to get the string shift amount number*/
    unsigned int SA2=0;/*temp int to get the integer shift amount number*/
    char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n')
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rd,Rs,SA
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the two Regs and SA
       */
   { count++;
	 temp [0]= line[i+1] ;
     temp [1]= line[i+2] ;
      temp2 = atoi(temp);
     printf("%d \n",sizeof(temp2));
     printf("%d \n",temp2);
     if (count==1)
     	 {/* first reg is Rd so in the code it is shifted lift by 11 */
          y|=(temp2<<11);
     	 }
          else if(count==2)
          {/* second reg is Rs so in the code it is shifted lift by 21 */
         	y|=(temp2<<21);

         	SA[0]=line[i+4];/*getting string SA which is after the second R letter by 4 char*/
            SA[1]=line[i+5];
            SA2 = atoi(SA);/*getting integer SA*/
            y|=(SA2<<6);
          }

	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Fourth Type=======================*/
unsigned int getothersI (void)
{   unsigned int y=0; /*the ouput of the function*/
    unsigned char temp [2];/*temp array to get the string Reg number*/
    unsigned int temp2;/*temp int to get the integer Reg number*/
    unsigned char IMM [5];/*temp array to get the string imm number as the maximum number for 16bit is 65535 five decimal digits */
    unsigned int IMM2;/*temp int to get the integer imm number*/
    char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/
    unsigned char j=0;/*another line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rt,Rs,Imm
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the two Regs Rt,Rs and Imm
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
      temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",sizeof(temp2));
     printf("%d \n",temp2);
	 if (count==1)
	 {/* first reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
	 }
     else if(count==2)
     {/* second reg is Rs so in the code it is shifted lift by 21 */
    	y|=(temp2<<21);
    	while (line [i+j+4]!= '\n')
    	{   IMM [j]=line [i+j+4];/*as i now on the second R of the line meaning the imm is 4 char away*/
    		j++;
    	}
    	IMM2 = atoi(IMM);
    	y|=IMM2;

     }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Fifth Type=======================*/
unsigned int getothersJ (void)
{   unsigned int y=0; /*the ouput of the function*/
    unsigned char IMM [8];/*temp array to get the string imm number as the maximum number for 26bit is 67108863 eight decimal digits */
    unsigned int IMM2;/*temp int to get the integer imm number*/
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n') /*as i am in the same line or instruction*/
 {
       IMM [i]=line [i+1];/*as i now on the second R of the line meaning the imm is 4 char away*/
    	i++;
 }
 IMM2 = atoi(IMM);
 y|=IMM2;
 printf("%s \n",line);

 return y;
 }

/*+==========================================================================================================================*/
/*============Sixth Type=======================*/
unsigned int getothersluI (void)
{   unsigned int y=0; /*the ouput of the function*/
    unsigned char temp [2];/*temp array to get the string Reg number*/
    unsigned int temp2;/*temp int to get the integer Reg number*/
    unsigned char IMM [5];/*temp array to get the string imm number as the maximum number for 16bit is 65535 five decimal digits */
    unsigned int IMM2;/*temp int to get the integer imm number*/
    char count=0;/*counter for the Reg number in the instruction line */
    char line[50];/*temp array to get the whole line after the instruction*/
    unsigned char i=0;/*line cursor*/
    unsigned char j=0;/*another line cursor*/

    fgets(line,50,fpr);/*getting the whole line after the instruction*/
 while (line [i]!= '\n') /*as i am in the same line or instruction*/
 {
   if (line[i]=='R')
	   /*when you see  a capital R it means it indicates a Reg number but which one that what the count would tell us
	    * as the instruction format is instruction Rt,Imm
	          and the binary format is OPCODE      RS RT RD   SA FUNC
	     in this type we focus on the a Reg Rt and Imm
       */
   { count++;
	 temp [0]= line[i+1] ;/*getting the string reg number */
     temp [1]= line[i+2] ;
     temp2 = atoi(temp);/*converting the string number to integer*/
     printf("%d \n",sizeof(temp2));
     printf("%d \n",temp2);
	 /* first reg is Rt so in the code it is shifted lift by 16 */
    	 y|=(temp2<<16);//Rt
    	 while (line [i+j+4]!= '\n') /*as i am in the same line or instruction*/
    	  {
    	        IMM [j]=line [i+j+4];/*as i now on the second R of the line meaning the imm is 4 char away*/
    	     	j++;
    	  }
	 printf("%d \n",y);
   }
   i++;
 }
 printf("%s \n",line);

 return y;
 }


/*+==========================================================================================================================*/
/*this function determine the instruction layout type*/
unsigned int getothers(unsigned int x)
{  unsigned int y;
	if ( (x==0x00000020)||(x==0x00000021)||(x==0x00000022)||(x==0x00000023)||(x==0x00000024)||(x==0x00000025)||\
	     (x==0x00000026)||(x==0x00000027)||(x==0x00000010)||(x==0x00000012)||(x==0x0000002A)|| (x=0x0000002B))
		{  /*first type*/
		  printf("first type \n");
			y= getothersRd();
		}
	else if ((x==0x00000008)||(x==0x00000004)||(x==0x00000005)||(x==0x00000018)||(x==0x00000019)||(x==0x0000001A)||\
			 (x==0x0000001B)||(x==0x0000000A)||(x==0x0000000B))
			{ /*second type*/
		     printf("second type \n");
			 y= getothersRs();
			}
	else if ((x==0x00000000)||(x==0x00000002)||(x==0x00000003))
			{/*third type*/
		      printf("third type \n");
				y= getothersshift();
			}
	else if( (x==0x20000000)||(x==0x24000000)||(x==0x30000000)||(x==0x34000000)||(x==0x28000000)||(x==0x2C000000)||\
			 (x==0x8C000000)||(x==0xAC000000)||(x==0x10000000)||(x==0x14000000))
    		{/*fourth type*/
		       printf("fourth type \n");
		   	   y= getothersI();
    		}
	else if((x==0x08000000)||(x==0x0C000000))
			{/*fifth type*/
		        printf("fifth type \n");
				y= getothersJ();
			}
	else if(x==0x3C000000)
			{/*sixth type*/
		       printf("sixth type \n");
				y= getothersluI();
			}
	else if ((x==0x00000006)||(x=0x00000007))
			{/*hlt and nop*/
		        printf("hlt or nop \n");
				y=0x00000000;
			}
	return y;
}



/*+==========================================================================================================================*/
/*this function get the opcode and func of the instruction line*/
unsigned int getIstruction (void)
{ char instruction_name[4];/*maximum 4*/
unsigned int x;
	fscanf(fpr,"%s",instruction_name);
     if (! strcmp(instruction_name,"sll"))
	x=0x00000000;
else if (! strcmp(instruction_name,"srl"))
	 x=0x00000002;
else if (! strcmp(instruction_name,"sra"))
	 x=0x00000003;
else if (! strcmp(instruction_name,"in"))
	 x=0x00000004;
else if (! strcmp(instruction_name,"out"))
	 x=0x00000005;
else if (! strcmp(instruction_name,"hlt"))
	 x=0x00000006;
else if (! strcmp(instruction_name,"nop"))
	 x=0x00000007;
else if (! strcmp(instruction_name,"jr"))
	 x=0x00000008;
else if (! strcmp(instruction_name,"push"))
	 x=0x0000000A;
else if (! strcmp(instruction_name,"pop"))
	 x=0x0000000B;
else if (! strcmp(instruction_name,"mfhi"))
	 x=0x00000010;
else if (! strcmp(instruction_name,"mflo"))
	 x=0x00000012;
else if (! strcmp(instruction_name,"mult"))
	 x=0x00000018;
else if (! strcmp(instruction_name,"multu"))
	 x=0x00000019;
else if (! strcmp(instruction_name,"div"))
	 x=0x0000001A;
else if (! strcmp(instruction_name,"divu"))
	 x=0x0000001B;
else if (! strcmp(instruction_name,"add"))
	 x=0x00000020;
else if (! strcmp(instruction_name,"addu"))
	 x=0x00000021;
else if (! strcmp(instruction_name,"sub"))
	 x=0x00000022;
else if (! strcmp(instruction_name,"subu"))
	 x=0x00000023;
else if (! strcmp(instruction_name,"and"))
	 x=0x00000024;
else if (! strcmp(instruction_name,"or"))
	 x=0x00000025;
else if (! strcmp(instruction_name,"xor"))
	 x=0x00000026;
else if (! strcmp(instruction_name,"nor"))
	 x=0x00000027;
else if (! strcmp(instruction_name,"slt"))
	 x=0x0000002A;
else if (! strcmp(instruction_name,"sltu"))
	 x=0x0000002B;
else if (! strcmp(instruction_name,"j"))
	 x=0x08000000;
else if (! strcmp(instruction_name,"jal"))
	 x=0x0C000000;
else if (! strcmp(instruction_name,"beq"))
	 x=0x10000000;
else if (! strcmp(instruction_name,"bne"))
	 x=0x14000000;
else if (! strcmp(instruction_name,"addi"))
	 x=0x20000000;
else if (! strcmp(instruction_name,"addiu"))
	 x=0x24000000;
else if (! strcmp(instruction_name,"slti"))
	 x=0x28000000;
else if (! strcmp(instruction_name,"sltiu"))
	 x=0x2C000000;
else if (! strcmp(instruction_name,"andi"))
	 x=0x30000000;
else if (! strcmp(instruction_name,"ori"))
	 x=0x34000000;
else if (! strcmp(instruction_name,"lui"))
	 x=0x3C000000;
else if (! strcmp(instruction_name,"lw"))
	 x=0x8C000000;
else if (! strcmp(instruction_name,"sw"))
	 x=0xAC000000;
printf("%d \n",x);
return x;
}
