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

#ifndef BASICS_H_
#define BASICS_H_

#include<wmmintrin.h>
#include<xmmintrin.h>
#include<smmintrin.h>
#include<emmintrin.h>
#include<tmmintrin.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdint.h>


#define MAX 10000

__m128i btmp1,btmp2,btmp9,btmp10,btmp17,btmp18,btmp25,btmp26,xx,xx1,xx2,xx3;
int blocks;
__m128i r,s,p,r1,s1,p1,r2,s2,p2;


#define align __attribute__ ((aligned (16)))

#if !defined (ALIGN16)
	# if defined (__GNUC__)
		# define ALIGN16 __attribute__ ( (aligned (16)))
	# else
		# define ALIGN16 __declspec (align (16))
	# endif
#endif

#define BPI 8  /* Number of AES calls to be done in parallel. Do not change this, other values not implemented */

#define schoolbook(aa,bb,cc,xx)  ({\
	cc[0] =_mm_clmulepi64_si128( aa, bb, 0x00 );\
	cc[1] =_mm_clmulepi64_si128( aa, bb, 0x11 );\
	r = _mm_clmulepi64_si128( aa, bb, 0x01 );\
	s = _mm_clmulepi64_si128( aa, bb, 0x10 );\
	xx = _mm_xor_si128(r,s);\
	})


	#define reductionbymult(cc,xx,dd)   ({\
	__m128i POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);\
	p = _mm_slli_si128 (xx, 8);\
	s = _mm_srli_si128 (xx, 8);\
	cc[0] = _mm_xor_si128(cc[0],p);\
	cc[1] = _mm_xor_si128(cc[1],s);\
    	r = _mm_clmulepi64_si128( cc[1], POLY, 0x01 );\
	p = _mm_srli_si128 (r, 8);\
	p = _mm_xor_si128(p,cc[1]);\
	s =_mm_clmulepi64_si128( p, POLY, 0x00 );\
	p = _mm_slli_si128 (r, 8);\
	dd = _mm_xor_si128(s,p);\
	dd = _mm_xor_si128(dd,cc[0]);})

	

	#define mult(aa,bb,dd) ({__m128i cc[2],xx;\
	schoolbook(aa,bb,cc,xx);\
	reductionbymult(cc,xx,dd);})


	#define schoolbook2(aa,bb,cc,xx,aa1,bb1,cc1,xx1) ({\
	cc[0] =_mm_clmulepi64_si128( aa, bb, 0x00 );\
	cc[1] =_mm_clmulepi64_si128( aa, bb, 0x11 );\
	r = _mm_clmulepi64_si128( aa, bb, 0x01 );\
	s = _mm_clmulepi64_si128( aa, bb, 0x10 );\
	cc1[0] =_mm_clmulepi64_si128( aa1, bb1, 0x00 );\
	cc1[1] =_mm_clmulepi64_si128( aa1, bb1, 0x11 );\
	r1 = _mm_clmulepi64_si128( aa1, bb1, 0x01 );\
	s1 = _mm_clmulepi64_si128( aa1, bb1, 0x10 );\
	xx = _mm_xor_si128(r,s);\
	/*p = _mm_slli_si128 (r, 8);\
	s = _mm_srli_si128 (r, 8);\
	cc[0] = _mm_xor_si128(cc[0],p);\
	cc[1] = _mm_xor_si128(cc[1],s);*/\
	xx1 = _mm_xor_si128(r1,s1);\
	})
    	

	#define reductionbymult2(cc,xx,dd,cc1,xx1,dd1)   ({\
	__m128i POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);\
	p = _mm_slli_si128 (xx, 8);\
	s = _mm_srli_si128 (xx, 8);\
	cc[0] = _mm_xor_si128(cc[0],p);\
	cc[1] = _mm_xor_si128(cc[1],s);\
	p = _mm_slli_si128 (xx1, 8);\
	s = _mm_srli_si128 (xx1, 8);\
	cc1[0] = _mm_xor_si128(cc1[0],p);\
	cc1[1] = _mm_xor_si128(cc1[1],s);\
	r = _mm_clmulepi64_si128( cc[1], POLY, 0x01 );\
	r1 = _mm_clmulepi64_si128( cc1[1], POLY, 0x01 );\
	p = _mm_srli_si128 (r, 8);\
	p1 = _mm_srli_si128 (r1, 8);\
	p = _mm_xor_si128(p,cc[1]);\
	p1 = _mm_xor_si128(p1,cc1[1]);\
	s =_mm_clmulepi64_si128( p, POLY, 0x00 );\
	s1 =_mm_clmulepi64_si128( p1, POLY, 0x00 );\
	p = _mm_slli_si128 (r, 8);\
	dd = _mm_xor_si128(s,p);\
	dd = _mm_xor_si128(dd,cc[0]);\
	p1 = _mm_slli_si128 (r1, 8);\
	dd1 = _mm_xor_si128(s1,p1);\
	dd1 = _mm_xor_si128(dd1,cc1[0]);})


	#define mult2(aa,bb,dd,aa1,bb1,dd1) ({__m128i cc[2],cc1[2],xx,xx1;\
	schoolbook2(aa,bb,cc,xx,aa1,bb1,cc1,xx1);\
	reductionbymult2(cc,xx,dd,cc1,xx1,dd1);\
	})



	


	#define schoolbook3(aa,bb,cc,xx,aa1,bb1,cc1,xx1,aa2,bb2,cc2,xx2) ({\
	cc[0] =_mm_clmulepi64_si128( aa, bb, 0x00 );\
	cc[1] =_mm_clmulepi64_si128( aa, bb, 0x11 );\
	r = _mm_clmulepi64_si128( aa, bb, 0x01 );\
	s = _mm_clmulepi64_si128( aa, bb, 0x10 );\
	cc1[0] =_mm_clmulepi64_si128( aa1, bb1, 0x00 );\
	cc1[1] =_mm_clmulepi64_si128( aa1, bb1, 0x11 );\
	r1 = _mm_clmulepi64_si128( aa1, bb1, 0x01 );\
	s1 = _mm_clmulepi64_si128( aa1, bb1, 0x10 );\
	cc2[0] =_mm_clmulepi64_si128( aa2, bb2, 0x00 );\
	cc2[1] =_mm_clmulepi64_si128( aa2, bb2, 0x11 );\
	r2 = _mm_clmulepi64_si128( aa2, bb2, 0x01 );\
	s2 = _mm_clmulepi64_si128( aa2, bb2, 0x10 );\
	xx = _mm_xor_si128(r,s);\
	/*p = _mm_slli_si128 (r, 8);\
	s = _mm_srli_si128 (r, 8);\
	cc[0] = _mm_xor_si128(cc[0],p);\
	cc[1] = _mm_xor_si128(cc[1],s);*/\
	xx1 = _mm_xor_si128(r1,s1);\
	/*p = _mm_slli_si128 (r, 8);\
	s = _mm_srli_si128 (r, 8);\
	cc1[0] = _mm_xor_si128(cc1[0],p);\
	cc1[1] = _mm_xor_si128(cc1[1],s);*/\
	xx2 = _mm_xor_si128(r2,s2);\
	/*p = _mm_slli_si128 (r, 8);\
	s = _mm_srli_si128 (r, 8);\
	cc2[0] = _mm_xor_si128(cc2[0],p);\
	cc2[1] = _mm_xor_si128(cc2[1],s);*/})


	#define reductionbymult3(cc,xx,dd,cc1,xx1,dd1,cc2,xx2,dd2)   ({\
	__m128i POLY = _mm_set_epi32(0x0,0x0,0x0,0x00000087);\
	p = _mm_slli_si128 (xx, 8);\
	s = _mm_srli_si128 (xx, 8);\
	cc[0] = _mm_xor_si128(cc[0],p);\
	cc[1] = _mm_xor_si128(cc[1],s);\
	p = _mm_slli_si128 (xx1, 8);\
	s = _mm_srli_si128 (xx1, 8);\
	cc1[0] = _mm_xor_si128(cc1[0],p);\
	cc1[1] = _mm_xor_si128(cc1[1],s);\
	p = _mm_slli_si128 (xx2, 8);\
	s = _mm_srli_si128 (xx2, 8);\
	cc2[0] = _mm_xor_si128(cc2[0],p);\
	cc2[1] = _mm_xor_si128(cc2[1],s);\
	r = _mm_clmulepi64_si128( cc[1], POLY, 0x01 );\
	r1 = _mm_clmulepi64_si128( cc1[1], POLY, 0x01 );\
	r2 = _mm_clmulepi64_si128( cc2[1], POLY, 0x01 );\
	p = _mm_srli_si128 (r, 8);\
	p1 = _mm_srli_si128 (r1, 8);\
	p2 = _mm_srli_si128 (r2, 8);\
	p = _mm_xor_si128(p,cc[1]);\
	p1 = _mm_xor_si128(p1,cc1[1]);\
	p2 = _mm_xor_si128(p2,cc2[1]);\
	s =_mm_clmulepi64_si128( p, POLY, 0x00 );\
	s1 =_mm_clmulepi64_si128( p1, POLY, 0x00 );\
	s2 =_mm_clmulepi64_si128( p2, POLY, 0x00 );\
	p = _mm_slli_si128 (r, 8);\
	dd = _mm_xor_si128(s,p);\
	dd = _mm_xor_si128(dd,cc[0]);\
	p1 = _mm_slli_si128 (r1, 8);\
	dd1 = _mm_xor_si128(s1,p1);\
	dd1 = _mm_xor_si128(dd1,cc1[0]);\
	p2 = _mm_slli_si128 (r2, 8);\
	dd2 = _mm_xor_si128(s2,p2);\
	dd2 = _mm_xor_si128(dd2,cc2[0]);})



	#define mult3(aa,bb,dd,aa1,bb1,dd1,aa2,bb2,dd2) ({__m128i cc[2],cc1[2],cc2[2],xx,xx1,xx2;\
	schoolbook3(aa,bb,cc,xx,aa1,bb1,cc1,xx1,aa2,bb2,cc2,xx2);\
	reductionbymult3(cc,xx,dd,cc1,xx1,dd1,cc2,xx2,dd2);\
	/*reductionbymult(cc1,dd1);\
	reductionbymult(cc2,dd2);*/})



void printBytesM(__m128i *data)
{ int i;
  unsigned char *ar = (unsigned char *)data;

  for(i=0; i<16; i++)
    printf("%02x ", ar[i]);
    printf("\n");
}

void printBytes(unsigned char *data, int num)
{ int i;

  for(i=0; i<num; i++)
    printf("%02x ", data[i]);
    printf("\n");
}
#endif
