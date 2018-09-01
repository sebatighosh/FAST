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



__m128i hkey,hkey2,hkey3,hkey4,hkey8,hkey16,hkey32,hkey64,hkey128;


#define XOR(var1,var2,var3) {var3 = _mm_xor_si128(var1,var2);}
#define XORNEW(var1,var2,var3) {var3[0] = _mm_xor_si128(var1[0],var2[0]);var3[1] = _mm_xor_si128(var1[1],var2[1]);}
#define ASSIGN(var1,var2) {var1 = var2;}



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






void htowbrw255par3(__m128i *aa, __m128i *dig) {

unsigned char i;

__m128i A1,A2,A3,A4,A5,A6,A7,A8,B1,B2,B3,B4,B5,B6,B7,C1,C2,C3,C4,D1,D2,D3,T1,T2; 

	
	evalbrw31par3(aa,A1); 
	evalbrw31par3((aa+32),A2); 
	evalbrw31par3((aa+64),A3);
	evalbrw31par3((aa+96),A4);
	evalbrw31par3((aa+128),A5);
	evalbrw31par3((aa+160),A6);
	evalbrw31par3((aa+192),A7);
	evalbrw31par3((aa+224),A8);
	XOR(hkey32,aa[31],B1);
	XOR(hkey32,aa[95],B2);
	XOR(hkey32,aa[159],B3);
	XOR(hkey32,aa[223],B4);
	XOR(hkey64,aa[63],B5);
	XOR(hkey64,aa[191],B6);
	XOR(hkey128,aa[127],B7);
	//mult3(A1,A5,A3,B1,B3,B2,C1,C2,C3);
	mult3(A1,B1,C1,A5,B3,C2,A3,B2,C3);


	XOR(C1,A2,T1);
	XOR(C2,A6,T2);
	//mult3(A7,T1,T2,B4,B5,B6,C4,D1,D2);
	mult3(A7,B4,C4,T1,B5,D1,T2,B6,D2);
	XOR(D1,C3,T1);
	XOR(T1,A4,T2);
	mult(T2,B7,D3);
	XOR(D2,D3,T1);
	XOR(C4,T1,T2);
	XOR(T2,A8,*dig);
	mult(*dig,hkey,*dig);
}




#endif
