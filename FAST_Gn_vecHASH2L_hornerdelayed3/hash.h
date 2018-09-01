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



__m128i hkey,hkey2,hkey3,hkey4,hkey8,hkey16,hkey32;
ALIGN16 __m128i keyTable[10];
int blksInComps[255];

#define XOR(var1,var2,var3) {var3 = _mm_xor_si128(var1,var2);}
#define XORNEW(var1,var2,var3) {var3[0] = _mm_xor_si128(var1[0],var2[0]);var3[1] = _mm_xor_si128(var1[1],var2[1]);}
#define ASSIGN(var1,var2) {var1 = var2;}
#define LENGTHPAD(var1,var2){\
		var1 = _mm_set_epi32 (0, 0, 0, var2);}
#define LENGTHPADLAST(var1,var2,var3){\
		var1 = _mm_xor_si128(_mm_set_epi32(0, 0, 0, var2),_mm_set_epi8(var3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0));}





void init_keyTable()
{
	int i;
	//POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);

	keyTable[0] = hkey32;

	for(i=1;i<8;i++)
	{
		mult(keyTable[i-1],keyTable[0],keyTable[i]);

	}

	return;
}



void init_keyTable3()
{
	int i;
	//POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);

	keyTable[0] = hkey32;

	for(i=1;i<10;i++)
	{
		mult(keyTable[i-1],keyTable[0],keyTable[i]);

	}

	return;



}



#define evalbrw31par3(aa,dig) ({__m128i new1[2], new2[2], new26[2], new10[2];\
/* new19[2], new23[2], new27[2], new31[2], new32[2], new34[2], new33[2], new39[2], new35[2], new40[2], new42[2], sum32[2], sum37[2], sum38[2], sum41[2], sum42[2];*/\
	XOR(aa[0],hkey,btmp1);\
	XOR(aa[1],hkey2,btmp2);\
	/*XOR(aa[4],key,btmp5);\
	XOR(aa[5],key2,btmp6);\
	/*XOR(aa[7],key8,btmp8);*/\
	XOR(aa[8],hkey,btmp9);\
	XOR(aa[9],hkey2,btmp10);\
	XOR(aa[16],hkey,btmp17);\
	XOR(aa[17],hkey2,btmp18);\
	schoolbook3(btmp2,btmp1,new1,xx,btmp10,btmp9,new2,xx1,btmp18,btmp17,new26,xx2);\
	XOR(aa[2],new1[0],new1[0]);\
	XOR(aa[10],new2[0],new2[0]);\
	XOR(aa[18],new26[0],new26[0]);\
	reductionbymult3(new1,xx,btmp2,new2,xx1,btmp10,new26,xx2,btmp18);\
	XOR(aa[4],hkey,btmp1);\
	XOR(aa[5],hkey2,btmp9);\
	XOR(aa[3],hkey4,btmp17);\
	XOR(aa[24],hkey,btmp25);\
	XOR(aa[25],hkey2,btmp26);\
	schoolbook3(btmp1,btmp9,new1,xx,btmp2,btmp17,new2,xx1,btmp26,btmp25,new26,xx2);\
	XOR(aa[26],new26[0],new26[0]);\
	reductionbymult(new26,xx2,btmp26);\
	XOR(aa[6],new1[0],new1[0]);\
	/*XOR(new1[0],new2[0],new1[0]);\
	XOR(new1[1],new2[1],new1[1]);*/\
	XORNEW(new1,new2,new1);\
	XOR(xx,xx1,xx1);\
	reductionbymult(new1,xx1,btmp1);\
	XOR(aa[7],hkey8,btmp9);\
	XOR(aa[11],hkey4,btmp2);\
	XOR(aa[12],hkey,btmp17);\
	XOR(aa[13],hkey2,btmp25);\
	/*XOR(aa[11],key4,btmp12);*/\
	schoolbook3(btmp1,btmp9,new1,xx,btmp2,btmp10,new2,xx1,btmp25,btmp17,new26,xx2);\
	XOR(aa[14],new26[0],new26[0]);\
	/*XOR(new2[0],new26[0],new26[0]);\
	XOR(new2[1],new26[1],new26[1]);*/\
	XORNEW(new2,new26,new26);\
	XOR(xx1,xx2,xx2);\
	/*XOR(new1[0],new26[0],new26[0]);\
	XOR(new1[1],new26[1],new26[1]);*/\
	XORNEW(new1,new26,new26);\
	XOR(xx,xx2,xx2);\
	reductionbymult(new26,xx2,btmp25);\
	XOR(aa[15],hkey16,btmp1);\
	/*XOR(aa[16],key,btmp17);\
	XOR(aa[17],key2,btmp18);*/\
	XOR(aa[19],hkey4,btmp2);\
	XOR(aa[20],hkey,btmp9);\
	XOR(aa[21],hkey2,btmp17);\
	schoolbook3(btmp1,btmp25,new1,xx,btmp2,btmp18,new2,xx1,btmp9,btmp17,new26,xx2);\
	XOR(aa[22],new26[0],new26[0]);\
	/*XOR(new2[0],new26[0],new2[0]);\
	XOR(new2[1],new26[1],new2[1]);*/\
	XORNEW(new2,new26,new2);\
	XOR(xx1,xx2,xx1);\
	reductionbymult(new2,xx1,btmp2);\
	XOR(aa[23],hkey8,btmp9);\
	XOR(aa[27],hkey4,btmp17);\
	XOR(aa[28],hkey,btmp1);\
	XOR(aa[29],hkey2,btmp10);\
	schoolbook3(btmp2,btmp9,new2,xx1,btmp26,btmp17,new26,xx2,btmp10,btmp1,new10,xx3);\
	XOR(aa[30],new10[0],new10[0]);\
	/*XOR(new10[0],new26[0],new10[0]);\
	XOR(new10[1],new26[1],new10[1]);*/\
	XORNEW(new10,new26,new10);\
	XOR(xx3,xx2,xx3);\
	/*XOR(new10[0],new2[0],new10[0]);\
	XOR(new10[1],new2[1],new10[1]);*/\
	XORNEW(new10,new2,new10);\
	XOR(xx3,xx1,xx3);\
	/*XOR(new10[0],new1[0],new10[0]);\
	XOR(new10[1],new1[1],new10[1]);*/\
	XORNEW(new10,new1,new10);\
	XOR(xx3,xx,xx3);\
	reductionbymult(new10, xx3,dig);})





void partialone(__m128i a[],__m128i *dig)
	{
		ASSIGN(*dig,a[0]);
		
	}


void partialtwo(__m128i a[],__m128i *dig)
	{
  		__m128i multpart1[2],POLY;
		
		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		schoolbook(a[0],hkey,multpart1,xx);
	        XOR(a[1],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,*dig);


	}



void partialthree(__m128i a[],__m128i *dig)
	{
  		__m128i multpart1[2],POLY;
		
		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,*dig);
	}

	

void partialfour(__m128i a[],__m128i *dig)
	{
  		__m128i multpart1[2],POLY;
		
		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		mult(btmp1,btmp2,*dig);

	}



void partialfive(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],POLY;
		
		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[4],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,*dig);

	}


  		
void partialsix(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		schoolbook2(btmp1,btmp2,multpart1,xx,a[4],hkey,multpart2,xx1);
		XOR(a[5],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);
	}


  		

void partialseven(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);

	}


void partialeight(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		mult(btmp1,btmp2,*dig);

	}


void partialnine(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[8],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,*dig);
	}


void partialten(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		schoolbook2(btmp1,btmp2,multpart1,xx,a[8],hkey,multpart2,xx1);
		XOR(a[9],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);
	}

void partialeleven(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		XOR(a[8],hkey,btmp9);
		XOR(a[9],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[10],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);

	}


void partialtwelve(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		XOR(a[8],hkey,btmp9);
		XOR(a[9],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[10],multpart2[0],multpart2[0]);
		reductionbymult(multpart2,xx1,btmp9);
		XOR(a[11],hkey4,btmp10);
		schoolbook(btmp9,btmp10,multpart2,xx1);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);
	}

void partialthirteen(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		XOR(a[8],hkey,btmp9);
		XOR(a[9],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[10],multpart2[0],multpart2[0]);
		reductionbymult(multpart2,xx1,btmp9);
		XOR(a[11],hkey4,btmp10);
		schoolbook(btmp9,btmp10,multpart2,xx1);
		XOR(a[12],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,*dig);
	}

void partialfourteen(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],multpart3[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		XOR(a[8],hkey,btmp9);
		XOR(a[9],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[10],multpart2[0],multpart2[0]);
		reductionbymult(multpart2,xx1,btmp9);
		XOR(a[11],hkey4,btmp10);
		schoolbook2(btmp9,btmp10,multpart2,xx1,a[12],hkey,multpart3,xx2);
		XOR(a[13],multpart3[0],multpart3[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		XORNEW(multpart1,multpart3,multpart1);
		XOR(xx,xx2,xx);
		reductionbymult(multpart1,xx,*dig);

	}

void partialfifteen(__m128i a[],__m128i *dig)
	{
  		
		__m128i multpart1[2],multpart2[2],multpart3[2],POLY;

		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		XOR(a[0],hkey,btmp1);
		XOR(a[1],hkey2,btmp2);
		schoolbook(btmp1,btmp2,multpart1,xx);
		XOR(a[2],multpart1[0],multpart1[0]);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[3],hkey4,btmp2);
		XOR(a[4],hkey,btmp9);
		XOR(a[5],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[6],multpart2[0],multpart2[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		reductionbymult(multpart1,xx,btmp1);
		XOR(a[7],hkey8,btmp2);
		XOR(a[8],hkey,btmp9);
		XOR(a[9],hkey2,btmp10);
		schoolbook2(btmp1,btmp2,multpart1,xx,btmp9,btmp10,multpart2,xx1);
		XOR(a[10],multpart2[0],multpart2[0]);
		reductionbymult(multpart2,xx1,btmp9);
		XOR(a[11],hkey4,btmp10);
		XOR(a[12],hkey,btmp1);
		XOR(a[13],hkey2,btmp2);
		schoolbook2(btmp9,btmp10,multpart2,xx1,btmp1,btmp2,multpart3,xx2);
		XOR(a[14],multpart3[0],multpart3[0]);
		XORNEW(multpart1,multpart2,multpart1);
		XOR(xx,xx1,xx);
		XORNEW(multpart1,multpart3,multpart1);
		XOR(xx,xx2,xx);
		reductionbymult(multpart1,xx,*dig);

		
	}


		
void partialrest(__m128i a[],int noOfBlock,__m128i * dig, __m128i  dig1)
	{
		__m128i *dig3 = &dig1,tmpdig[2],POLY;
		POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
		
		partialfifteen(a,dig);
		
		
		XOR(a[15],hkey16,btmp1);  		
		schoolbook(*dig,btmp1,tmpdig,xx);
		reductionbymult(tmpdig,xx,*dig);

		
		if(noOfBlock == 16)
			return;
		if(noOfBlock == 17)
		{
			XOR(a[16],tmpdig[0],tmpdig[0]);
			reductionbymult(tmpdig,xx,*dig);
			return;

		}
		switch(noOfBlock)
		{
		/*case 17:
			partialone(a+16,key,dig3);
			break;*/
		case 18:
			partialtwo(a+16,dig3);
			break;
		case 19:
			partialthree(a+16,dig3);
			break;
		case 20:
			partialfour(a+16,dig3);
			break;
		case 21:
			partialfive(a+16,dig3);
			break;
		case 22:
			partialsix(a+16,dig3);
			break;
		case 23:
			partialseven(a+16,dig3);
			break;
		case 24:
			partialeight(a+16,dig3);
			break;
		case 25:
			partialnine(a+16,dig3);
			break;
		case 26:
			partialten(a+16,dig3);
			break;
		case 27:
			partialeleven(a+16,dig3);
			break;
		case 28:
			partialtwelve(a+16,dig3);
			break;
		case 29:
			partialthirteen(a+16,dig3);
			break;
		case 30:
			partialfourteen(a+16,dig3);
			break;
		}
		XOR(*dig, *dig3, *dig);
	}


#define brwpartial(aa,noOfBlock,dig){\
	__m128i dig1, *dig2 = &dig;\
	switch(noOfBlock){\
        case 1:\
	partialone(aa,dig2);\
	break;\
	case 2:\
	partialtwo(aa,dig2);\
	break;\
	case 3:\
	partialthree(aa,dig2);\
	break;\
	case 4:\
	partialfour(aa,dig2);\
	break;\
	case 5:\
	partialfive(aa,dig2);\
	break;\
	case 6:\
	partialsix(aa,dig2);\
	break;\
	case 7:\
	partialseven(aa,dig2);\
	break;\
	case 8:\
	partialeight(aa,dig2);\
	break;\
	case 9:\
	partialnine(aa,dig2);\
	break;\
	case 10:\
	partialten(aa,dig2);\
	break;\
	case 11:\
	partialeleven(aa,dig2);\
	break;\
	case 12:\
	partialtwelve(aa,dig2);\
	break;\
	case 13:\
	partialthirteen(aa,dig2);\
	break;\
	case 14:\
	partialfourteen(aa,dig2);\
	break;\
	case 15:\
	partialfifteen(aa,dig2);\
	break;\
	default:\
	if(noOfBlock>=16 && noOfBlock<=30)\
	partialrest(aa,noOfBlock,dig2,dig1);}}



__m128i horner3key32(__m128i *msg, int blk)		/*calculates Horner(1, m_1,..., m_blk)= (...+m_{blk-1}*(tow^{32})+m_blk)*/
{
	__m128i temp[2], mid, digest, temp1[2], midtmp1, temp2[2], midtmp2,temp3[2], midtmp3,temp4[2], midtmp4; 
	int rem = blk % 10, i, length;
	//POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);
	length = blk - rem;
	
	temp1[0] = temp1[1] = midtmp1 = _mm_setzero_si128();
	
	if (length >= 10)
	{
		schoolbook3(msg[0],keyTable[8],temp2,midtmp2,msg[1],keyTable[7],temp3,midtmp3,msg[2],keyTable[6],temp4,midtmp4);
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
		schoolbook3(msg[3],keyTable[5],temp2,midtmp2,msg[4],keyTable[4],temp3,midtmp3,msg[5],keyTable[3],temp4,midtmp4);	
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
		schoolbook3(msg[6],keyTable[2],temp2,midtmp2,msg[7],keyTable[1],temp3,midtmp3,msg[8],keyTable[0],temp4,midtmp4);	
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
		XOR(temp1[0],msg[9],temp1[0]);
		

	for(i=10;i <= length-10; i=i+10)
	{
				
		reductionbymult(temp1,midtmp1,digest);
		schoolbook(digest,keyTable[9],temp1,midtmp1);
		schoolbook3(msg[i],keyTable[8],temp2,midtmp2,msg[i+1],keyTable[7],temp3,midtmp3,msg[i+2],keyTable[6],temp4,midtmp4);
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1,midtmp2,midtmp1);
		XORNEW(temp1,temp3,temp1);
		XOR(midtmp1,midtmp3,midtmp1);
		XORNEW(temp1,temp4,temp1);
		XOR(midtmp1,midtmp4,midtmp1);
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
		XOR(temp1[0],msg[i+9],temp1[0]);
		
	}
	}
	reductionbymult(temp1,midtmp1,digest);

	if(rem){
	schoolbook(digest,keyTable[rem-1],temp1,midtmp1);
	
	XOR(temp1[0],msg[blk-1],temp1[0]);
	
	for (i=2;i <= rem; i++)
	{
		schoolbook(msg[blk-i],keyTable[i-2],temp2,midtmp2);
		XORNEW(temp1,temp2,temp1);
		XOR(midtmp1, midtmp2, midtmp1);

	}

	reductionbymult(temp1,midtmp1,digest);
	}

	return(digest);
}





__m128i vecHash2l(__m128i *inp1, __m128i *inp2)
{

	__m128i digest, digest1[MAX], digest2, temp, mid, temp1[2], midtmp1, temp2[2], midtmp2;

	int i=0,j=0,index = 0,cntr = 0, fullBlocks,remaining, blk=0, index1=0;

//	digest = _mm_setzero_si128();
	//XOR(hkey, _mm_set_epi32 (0, 0, 0, 128),digest);  
	digest = _mm_set_epi32 (0, 0, 0, 1); /*1.putting digest = 1*/
	for(i=0; i<comps; i++)
	{
		mult(digest,hkey32,digest);		/*8.do the mult. of current digest with \tau^32 here*/
		fullBlocks = blksInComps[i]/31;
		blk = fullBlocks;
		remaining = blksInComps[i]%31;
		//printf("blksInComps[i]=%d\n",blksInComps[i]);
		
		for(j = index;j < index+fullBlocks;j = j+1,cntr = cntr+31)
		{
			
			evalbrw31par3((inp1+cntr),digest1[j]);
			
			
		}
		index1 = index;
		index = index+fullBlocks;
		
		if(remaining)
		{
			//partialrest((inp1+cntr),remaining,, digest2);
			brwpartial((inp1+cntr),remaining,digest1[j]);
			index = index+1;
			blk = blk+1;
		}
		cntr= cntr+remaining;
		XOR(digest,digest1[index1],digest1[index1]);		/*9.xor the multiplied digest with the first BRW result which will be subjected to Horner with \tau^32*/
		digest = horner3key32((digest1+index1), blk);           /*10.put the result of horner in digest and mult. it with \tau*/
		//mult(digest,hkey32,digest);
		//XOR(digest,digest2,digest);
		mult(digest,hkey,digest);
		XOR(digest,inp1[cntr],digest);
		
		cntr=cntr+1;

	}
	mult(digest,hkey32,digest);		/*11.do the mult. of current digest with \tau^32 here*/

	fullBlocks = blksInComps[i]/31;
	blk = fullBlocks;
	remaining = blksInComps[i]%31;
	cntr = 0;
	
	for(j = index;j < index+fullBlocks;j = j+1,cntr = cntr+31)
	{
		
		evalbrw31par3((inp2+cntr),digest1[j]);
		
	}

	index1 = index;
	index = index+fullBlocks;
		
	if(remaining)
	{
		brwpartial((inp2+cntr),remaining,digest1[j]);
		index = index+1;
		blk = blk+1;
	}
		cntr= cntr+remaining;
		XOR(digest,digest1[index1],digest1[index1]);		/*12.xor the multiplied digest with the first BRW result which will be subjected to Horner with \tau^32*/
		digest = horner3key32((digest1+index1), blk);    /*13.put the result of horner in digest and mult. it with \tau*/
		//mult(digest,hkey32,digest);
		//XOR(digest,digest2,digest);
		mult(digest,hkey,digest);
		XOR(digest,inp2[cntr],digest);
	

	mult(digest,hkey,digest);
	return(digest);

}


#endif
