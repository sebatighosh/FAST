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

#ifndef HASH_H_
#define HASH_H_

#include "basics.h"

__m128i hkey;

ALIGN16 __m128i keyTable[9];


#define XOR(var1,var2,var3) {var3 = _mm_xor_si128(var1,var2);}
#define XORNEW(var1,var2,var3) {var3[0] = _mm_xor_si128(var1[0],var2[0]);var3[1] = _mm_xor_si128(var1[1],var2[1]);}
#define ASSIGN(var1,var2) {var1 = var2;}



void init_keyTable3()
{
	int i;
	//POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);

	keyTable[0] = hkey;

	for(i=1;i<=8;i++)
	{
		mult(keyTable[i-1],keyTable[0],keyTable[i]);

	}

	return;



}


__m128i htowHorner3(__m128i *msg, int blk)		/*calculates tow*Horner(1, m_1,..., m_blk)= tow*(...+m_{blk-1}*tow+m_blk)*/
{
	__m128i temp[2], mid, digest, temp1[2], midtmp1, temp2[2], midtmp2,temp3[2], midtmp3,temp4[2], midtmp4; 
	int rem = blk % 9, i, length;
	//POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
	length = blk - rem;
	
	temp1[1] = midtmp1 = _mm_setzero_si128();
	temp1[0] = keyTable[0];

	for(i=0;i < length; i=i+9)
	{
		XOR(temp1[0],msg[i],temp1[0]);		
		reductionbymult(temp1,midtmp1,digest);
		schoolbook3(digest,keyTable[8],temp1,midtmp1,msg[i+1],keyTable[7],temp2,midtmp2,msg[i+2],keyTable[6],temp3,midtmp3);
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		schoolbook3(msg[i+3],keyTable[5],temp2,midtmp2,msg[i+4],keyTable[4],temp3,midtmp3,msg[i+5],keyTable[3],temp4,midtmp4);	
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
		schoolbook3(msg[i+6],keyTable[2],temp2,midtmp2,msg[i+7],keyTable[1],temp3,midtmp3,msg[i+8],keyTable[0],temp4,midtmp4);	
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
		
	}

	reductionbymult(temp1,midtmp1,digest);

	if(rem){
	schoolbook(digest,keyTable[rem-1],temp1,midtmp1);
	
	
	
	for (i=1;i <= rem; i++)
	{
		schoolbook(msg[blk-i],keyTable[i-1],temp2,midtmp2);
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1, midtmp2, midtmp1);

	}

	reductionbymult(temp1,midtmp1,digest);
	}

	return(digest);
}

#endif
