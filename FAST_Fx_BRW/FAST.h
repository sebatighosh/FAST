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

#ifndef _FAST_H
#define _FAST_H

#include "hash.h"
#include "aes.h"


__m128i hkey, hkey2, hkey4, hkey8, hkey16, hkey32, hkey64, hkey128;
ALIGN16 __m128i keySch[11];

//ALIGN16 unsigned char userkey[16]={0x3c,0x4f,0xcf,0x09,0x88,0x15,0xf7,0xab,0xa6,0xd2,0xae,0x28,0x16,0x15,0x7e,0x2b};
ALIGN16 unsigned char userkey[16]={0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0x4F,0x3C};
ALIGN16 unsigned char str[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//ALIGN16 unsigned char tweak[16]={0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0xff};
ALIGN16 unsigned char tweak[16]={0xFF,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};






void setUpFASTWithBRW() {

	AES_128_Key_Expansion(userkey,keySch);
	
	hkey = AES_128_Encrypt(((__m128i *)str)[0],keySch);
	mult(hkey,hkey,hkey2); mult(hkey2,hkey2,hkey4); mult(hkey4,hkey4,hkey8);
        mult(hkey8,hkey8,hkey16); mult(hkey16,hkey16,hkey32); mult(hkey32,hkey32,hkey64); mult(hkey64,hkey64,hkey128);
	
	
}


void feistel(__m128i A1, __m128i F1, __m128i *F2, __m128i *B2) {

__m128i H1,H2;
	
	
	H1 = AES_128_Encrypt(F1,keySch);
	XOR(A1,H1,*F2);
	H1 = AES_128_Encrypt(*F2,keySch);
	XOR(F1,H1,*B2);
	
	
}

void feistelInv(__m128i F2, __m128i B2, __m128i *A1, __m128i *F1) {

__m128i H1,H2;
	
	
	H2 = AES_128_Encrypt(F2,keySch);
	XOR(B2,H2,*F1);
	H2 = AES_128_Encrypt(*F1,keySch);
	XOR(F2,H2,*A1);
	
	
}






void FASTEncryptBRW(__m128i *msg, __m128i *cpr) {

	__m128i dig,A1,A2,B1,Z,B2, F1, F2;
	
	
	htowbrw255par3((msg+2), &dig);
	
	XOR(dig,msg[0],A1);
	mult(hkey,A1,A2);
	XOR(A2,msg[1],F1);
	//A2 = msg[1];
	feistel(A1,F1,&F2,&B2);
	/*printf("A1:" ); printBytesM(&A1);printf("\n"); 
	printf("A2:" ); printBytesM(&A2);printf("\n"); 
	printf("B1:" ); printBytesM(&B1);printf("\n"); 
	printf("B2:" ); printBytesM(&B2);printf("\n\n");*/ 
	XOR(F1,F2,Z);
	// printf("Z :"); printBytesM(&Z);printf("\n");
	AES_128_CTR(msg+2, cpr+2, (blocks-2)*16, Z, keySch);
	mult(hkey,B2,A2);
	XOR(A2,F2,cpr[0]);
	
	
	
	htowbrw255par3((cpr+2), &dig);
	mult(hkey,dig,dig);
	XOR(dig,B2,cpr[1]);
			
}

void FASTDecryptBRW(__m128i *cpr, __m128i *msg) {

	__m128i dig,A1,A2,B1,Z,B2,F1,F2;
	
	//B1 = cpr[0];

	htowbrw255par3((cpr+2), &dig);
	mult(hkey,dig,dig);
	
	XOR(dig,cpr[1],B2);

	mult(hkey,B2,A2);
	XOR(A2,cpr[0],F2);
	
	feistelInv(F2,B2,&A1,&F1);
	/* printf("A1, A2, B1, B2 from decrypt\n");
	printBytesM(&A1); printBytesM(&A2); printBytesM(&B1); printBytesM(&B2); */
	XOR(F1,F2,Z);
	AES_128_CTR(cpr+2, msg+2, (blocks-2)*16, Z, keySch);
	
	htowbrw255par3((msg+2), &dig);
	
	XOR(dig,A1,msg[0]);

	mult(hkey,A1,A2);
	XOR(A2,F1,msg[1]);
}




#endif
