/*Implementation of FAST fixed length version with BRW with delayed reduction for each 31 block component(for 4096 bytes only)*/

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

ALIGN16 unsigned char inp[MAX], outvar[MAX], dec[MAX];  /*outvar to be checked*/

int i, noOfBytes;
double tmpd;


printf("Enter no of blocks in message (m):\n");
scanf("%d", &blocks);

noOfBytes = 16*blocks;
	

	
	
for(i = 0;i < noOfBytes;i++)
{
	inp[i] = rand();
}

for(i=noOfBytes; i<noOfBytes+16; i++)
{ 
	inp[i] = outvar[i] = dec[i] = tweak[i-noOfBytes];
}

	
setUpFASTWithBRW();
	//printBytes(inp,16);
	
	DO(
	FASTEncryptBRW((__m128i *)inp, (__m128i *)outvar);
	inp[32] = outvar[0];); 		
	printBytes(outvar,16); //printf("\n\n");
	
	tmpd = ((median_get())/(double)(N*(noOfBytes+16)));
        printf("\nmedian cycles per byte (FAST-BRW)= %lf \n\n",tmpd);

	/*DO(
	FASTDecryptBRW((__m128i *)outvar, (__m128i *)dec);
	outvar[0] = dec[0];);
	//inp[0] = outvar[0];); 		
	printBytes(dec,16);
	tmpd = ((median_get())/(double)(N*noOfBytes));
        printf("\nmedian cycles per byte (FAST-Horner)= %lf \n\n",tmpd);*/

return 0;


}
