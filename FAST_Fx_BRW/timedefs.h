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

#include<wmmintrin.h>
#include<xmmintrin.h>
#include<smmintrin.h>
#include<emmintrin.h>
#include<tmmintrin.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TIME_TEST 1 /*if measuring time then 1 else 0 */

#define CACHE_WARM_ITER 1000

#ifndef MAX_ITER
	#define MAX_ITER 2000
#endif

#define M 1000

#define N 1000

#define STAMP ({unsigned res; __asm__ __volatile__ ("rdtsc" : "=a"(res) : : "edx"); res;}) /* Time stamp */

#define DO(x) do { \
int i1,j1; \
for (i1 = 0; i1 < M; i1++) { \
unsigned c2, c1;\
for(j1=0;j1<CACHE_WARM_ITER;j1++) {x;}\
c1 = STAMP;\
for (j1 = 1; j1 <= N; j1++) { x; }\
c1 = STAMP - c1;\
median_next(c1);\
} } while (0)


#if (TIME_TEST == 1)
	unsigned values[MAX_ITER];
	int num_values = 0;

	int comp(const void *x, const void *y) {return *(unsigned *)x - *(unsigned *)y; }
	
	void median_next(unsigned x) {values[num_values++] = x; }
	
	unsigned median_get(void) {
		unsigned res;
		/*for (res = 0; res < num_values; res++)
		//   printf("%d ", values[res]);
		//printf("\n");*/
		qsort(values, num_values, sizeof(unsigned), comp);
		res = values[num_values/2];
		num_values = 0;
		return res;
	}

	void median_print(void) {
		int res;
		qsort(values, num_values, sizeof(unsigned), comp);
		for (res = 0; res < num_values; res++)
		printf("%d ", values[res]);
		printf("\n");
	}

#endif
