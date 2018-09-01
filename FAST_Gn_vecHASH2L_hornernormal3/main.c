/*Implementation of FAST vector version with vecHash2L, horner is NOT with delayed reduction and is with batch size 3.*/

/*
###############################################################################
# FAST developers and authors:                                                #
#                                                                             #
# Debrup Chakraborty,  		Indian Statistical Institute                  #
# Sebati Ghosh,        		Indian Statistical Institute                  #
# Cuauhtemoc Mancillas Lopez,   CINVESTAV-IPN, Mexico                         #
# Palash Sarkar,       		Indian Statistical Institute                  #
###############################################################################
#                                                                             #
###############################################################################
#                                                                             #
# Copyright (c) 2017, Debrup Chakraborty, Sebati Ghosh,          	      #
# Cuauhtemoc Mancillas Lopez, Palash Sarkar,                                  #
#                                                                             #
# Permission to use this code for FAST is granted.                            #
#                                                                             #
# Redistribution and use in source and binary forms, with or without          #
# modification, are permitted provided that the following conditions are      #
# met:                                                                        #
#                                                                             #
# * Redistributions of source code must retain the above copyright notice,    #
#   this list of conditions and the following disclaimer.                     #
#                                                                             #
# * Redistributions in binary form must reproduce the above copyright         #
#   notice, this list of conditions and the following disclaimer in the       #
#   documentation and/or other materials provided with the distribution.      #
#                                                                             #
# * The names of the contributors may not be used to endorse or promote       #
# products derived from this software without specific prior written          #
# permission.                                                                 #
#                                                                             #
###############################################################################
#                                                                             #
###############################################################################
# THIS SOFTWARE IS PROVIDED BY THE AUTHORS ""AS IS"" AND ANY                  #
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE           #
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR          #
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE CONTRIBUTORS BE LIABLE        #
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 		      #
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 	      #
# OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR          	      #
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF      #
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING        #
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          #
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                #
###############################################################################
*/


#include "FAST.h"
#include "timedefs.h"



int main() {

ALIGN16 unsigned char inp[MAX], outvar[MAX], dec[MAX], msg[MAX];  /*outvar to be checked*/

int i, j = 0, length, partial = 0, index = 0, divLen=0, copy=0, pad =0; /*3.value of j to be initialised*/
__m128i lengthPad;
FILE *fp;
double tmpd;


printf("Enter no of bytes in message (>32):\n");
scanf("%d", &noOfBytes);

if (noOfBytes <= 32)                   /*5.handling wrong input for message length*/
{printf("Message must have more than 32 bytes!!\n");
exit(1);
}

printf("Enter no of components in tweak (0 to 254):\n");
scanf("%d", &comps);

if((comps<0) || (comps >254))
{printf("Tweak must have component within 0 to 254!!\n");   /*6.handling wrong input for tweak component number*/
exit(1);
}	

	
	
for(i = 0;i < noOfBytes;i++)
{
	msg[i] = rand();
	
}

//if (noOfBytes==0)   /*4.message must have more than 32 bytes*/
//	pad = 16;
//else
//{
partial = noOfBytes % 16;
if(partial)
pad = 16-partial;
//}

for(i=noOfBytes; i<noOfBytes+pad; i++)
{ 
	msg[i] = 0;
	outvar[i] = dec[i] = msg[i];
}

copy = noOfBytes-32+pad;
//total = noOfBytes-32+pad;


	LENGTHPADLAST(lengthPad,(noOfBytes-32)*8,(comps+1)); /*2.component number is comps+2*/
	

	msg[noOfBytes+pad] = _mm_extract_epi8 (lengthPad, 0);
	msg[noOfBytes+pad+1] = _mm_extract_epi8 (lengthPad, 1);
	msg[noOfBytes+pad+2] = _mm_extract_epi8 (lengthPad, 2);
	msg[noOfBytes+pad+3] = _mm_extract_epi8 (lengthPad, 3);
	msg[noOfBytes+pad+4] = _mm_extract_epi8 (lengthPad, 4);
	msg[noOfBytes+pad+5] = _mm_extract_epi8 (lengthPad, 5);
	msg[noOfBytes+pad+6] = _mm_extract_epi8 (lengthPad, 6);
	msg[noOfBytes+pad+7] = _mm_extract_epi8 (lengthPad, 7);
	msg[noOfBytes+pad+8] = _mm_extract_epi8 (lengthPad, 8);
	msg[noOfBytes+pad+9] = _mm_extract_epi8 (lengthPad, 9);
	msg[noOfBytes+pad+10] = _mm_extract_epi8 (lengthPad, 10);
	msg[noOfBytes+pad+11] = _mm_extract_epi8 (lengthPad, 11);
	msg[noOfBytes+pad+12] = _mm_extract_epi8 (lengthPad, 12);
	msg[noOfBytes+pad+13] = _mm_extract_epi8 (lengthPad, 13);
	msg[noOfBytes+pad+14] = _mm_extract_epi8 (lengthPad, 14);
	msg[noOfBytes+pad+15] = _mm_extract_epi8 (lengthPad, 15);
	
	for(i = noOfBytes+pad;i < noOfBytes+pad+16;i++)
		outvar[i] = dec[i] = msg[i];
	
	

copy = copy+16;

//total = total+16;
if(comps)
{
	fp = fopen("tweak.txt", "r"); if (fp == NULL) {printf("Cannot open tweak.txt\n"); exit(1);}		/*input contains tweak*/
	//index = i;

	for(j=0;j < comps;j++)
	{
		pad = partial = 0;
		fscanf(fp, "%d", &length);
		if(length <0)
		{
			printf("Tweak component must have length >= 0 and < 2^(n-16)!!\n");   /*7.handling wrong input for tweak component length; not doing anything for the upper bound, as violating that is quite unlikely*/
			exit(1);
		}

		for(i = index;i < index+length;i++)
		{
			inp[i] = rand();
			//outvar[i] = dec[i] = inp[i];
		}

		index = index+length;

		if (length==0)
			pad = 16;
		else
		{
			partial = length % 16;
			if(partial)
			pad = 16-partial;
		}
		
		for(i=index; i<index+pad; i++)
		{ 
			inp[i] = 0;
			//outvar[i] = dec[i] = inp[i];
		}

		index = index+pad;
		
		LENGTHPAD(lengthPad,length*8);
		
		
		inp[index] = _mm_extract_epi8 (lengthPad, 0);
		inp[index+1] = _mm_extract_epi8 (lengthPad, 1);
		inp[index+2] = _mm_extract_epi8 (lengthPad, 2);
		inp[index+3] = _mm_extract_epi8 (lengthPad, 3);
		inp[index+4] = _mm_extract_epi8 (lengthPad, 4);
		inp[index+5] = _mm_extract_epi8 (lengthPad, 5);
		inp[index+6] = _mm_extract_epi8 (lengthPad, 6);
		inp[index+7] = _mm_extract_epi8 (lengthPad, 7);
		inp[index+8] = _mm_extract_epi8 (lengthPad, 8);
		inp[index+9] = _mm_extract_epi8 (lengthPad, 9);
		inp[index+10] = _mm_extract_epi8 (lengthPad, 10);
		inp[index+11] = _mm_extract_epi8 (lengthPad, 11);
		inp[index+12] = _mm_extract_epi8 (lengthPad, 12);
		inp[index+13] = _mm_extract_epi8 (lengthPad, 13);
		inp[index+14] = _mm_extract_epi8 (lengthPad, 14);
		inp[index+15] = _mm_extract_epi8 (lengthPad, 15);

		//for(i = index;i < index+16;i++)
			//outvar[i] = dec[i] = inp[i];		
		
	
		index = index+16;
	
		//total = total + length + pad + 16;
		divLen = divLen + length;
		blksInComps[j] = (length+pad)/16;
	}
	
}
divLen = divLen + noOfBytes;
//printf("j=%d\n",j);
blksInComps[j] = (copy-16)/16;
//total = total+copy;

//blocks=total/16;

setUpFASTWithVecHash2l();	
	printf("msg\n");
	printBytes(msg,16);
	

	DO(
	FASTEncryptVecHash2l((__m128i *)msg,(__m128i *)inp, (__m128i *)outvar);
	inp[0] = outvar[0];);
	printf("out\n"); 		
	printBytes(outvar,16); //printf("\n\n");
	tmpd = ((median_get())/(double)(N*divLen));
        printf("\nmedian cycles per byte (FAST-Horner)= %lf \n\n",tmpd);
	
	/*DO(
	FASTDecryptVecHash2l((__m128i *)outvar, (__m128i *)inp, (__m128i *)dec);
	outvar[0] = dec[0];);
	//inp[0] = outvar[0];); 
	printf("dec\n");		
	printBytes(dec,16);
	tmpd = ((median_get())/(double)(N*divLen));
        printf("\nmedian cycles per byte (FAST-Horner)= %lf \n\n",tmpd);*/

return 0;


}
