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

#ifndef _AES_H
#define _AES_H

#include "basics.h"

#define BPI 8  /* Number of AES calls to be done in parallel. Do not change this, other values not implemented */

inline __m128i AES_128_ASSIST (__m128i temp1, __m128i temp2) {
 __m128i temp3;
 temp2 = _mm_shuffle_epi32 (temp2 ,0xff);
 temp3 = _mm_slli_si128 (temp1, 0x4);
 temp1 = _mm_xor_si128 (temp1, temp3);
 temp3 = _mm_slli_si128 (temp3, 0x4);
 temp1 = _mm_xor_si128 (temp1, temp3);
 temp3 = _mm_slli_si128 (temp3, 0x4);
 temp1 = _mm_xor_si128 (temp1, temp3);
 temp1 = _mm_xor_si128 (temp1, temp2);
 return temp1; 
}


void AES_128_Key_Expansion (unsigned char *userkey, __m128i *Key_Schedule) {
   __m128i temp1, temp2;

 temp1 = _mm_loadu_si128 ((__m128i*)userkey);
Key_Schedule[0] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x1);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[1] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x2);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[2] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x4);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[3] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x8);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[4] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x10);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[5] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x20);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[6] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x40);
temp1 = AES_128_ASSIST(temp1, temp2);
Key_Schedule[7] = temp1;
temp2 = _mm_aeskeygenassist_si128 (temp1,0x80);
temp1 = AES_128_ASSIST(temp1, temp2);
 Key_Schedule[8] = temp1;
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x1b);
 temp1 = AES_128_ASSIST(temp1, temp2);
 Key_Schedule[9] = temp1;
 temp2 = _mm_aeskeygenassist_si128 (temp1,0x36);
 temp1 = AES_128_ASSIST(temp1, temp2);
 Key_Schedule[10] = temp1;
}


 __m128i  AES_128_Encrypt(__m128i ptext, __m128i *keySchedule){
      int j;
      __m128i tmp;

      tmp = _mm_xor_si128 (ptext,keySchedule[0]);
      for(j=1; j <10; j++){
         tmp = _mm_aesenc_si128 (tmp,keySchedule[j]);
      }
      tmp = _mm_aesenclast_si128 (tmp,keySchedule[j]);
      /*_mm_storeu_si128 (&((__m128i*)out)[0],tmp);*/
      return(tmp);

}

void AES_128_ECB_Encrypt(__m128i *text, int nBlocks, __m128i *keySchedule)
{   int i,j;
   // __m128i tmp;

    for(i=0; i< nBlocks; i++)
       text[i] = _mm_xor_si128(text[i], keySchedule[0]);

    for(j=1; j<10 ; j++)
       for(i=0; i< nBlocks; i++)
            text[i] = _mm_aesenc_si128 (text[i],keySchedule[j]);

    for(i=0; i< nBlocks; i++)
      text[i] = _mm_aesenclast_si128 (text[i],keySchedule[j]);
}

void AES_128_CTR(__m128i *msgblks, __m128i *cprblks, unsigned int len, __m128i iv, __m128i *keySchedule)
{        __m128i  ctr, one;
        __m128i ta[BPI];
        unsigned int i, k, nBlocks, block8, lastblock, restBlocks;

        nBlocks = len >> 4;
        lastblock = len %16;
        if(lastblock!=0) nBlocks++;

        block8 = nBlocks >>3;
        restBlocks = nBlocks % 8;

        ctr = _mm_setzero_si128();
        one = _mm_set_epi32(0x00,0x00,0x00,0x01);

        for(i=0; i< block8  ; i++)
                {       k = BPI * i;
                        ctr = _mm_add_epi64(ctr,one);  ta[0] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[1] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[2] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[3] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[4] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[5] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[6] = _mm_xor_si128(ctr,iv);
                        ctr = _mm_add_epi64(ctr,one);  ta[7] = _mm_xor_si128(ctr,iv);

                        /*if(i==0){ printf("\n\n CTR value\n");
				printBytesM(&ta[0]);
				printBytesM(&ta[1]);
				printBytesM(&ta[2]);
				printBytesM(&ta[3]);
				printBytesM(&ta[4]);
				printBytesM(&ta[5]);
				printBytesM(&ta[6]);
				printBytesM(&ta[7]);
                              } */ 
                        AES_128_ECB_Encrypt(ta,BPI,keySchedule);
                        /* if(i==0){ printf("\n\n E(CTR) value\n");
				printBytesM(&ta[0]);
				printBytesM(&ta[1]);
				printBytesM(&ta[2]);
				printBytesM(&ta[3]);
				printBytesM(&ta[4]);
				printBytesM(&ta[5]);
				printBytesM(&ta[6]);
				printBytesM(&ta[7]);
                              }  */

                        cprblks[k+0] = _mm_xor_si128(ta[0],msgblks[k+0]); cprblks[k+1]= _mm_xor_si128(ta[1],msgblks[k+1]) ;
                        cprblks[k+2] = _mm_xor_si128(ta[2],msgblks[k+2]); cprblks[k+3]= _mm_xor_si128(ta[3],msgblks[k+3]) ;
                        cprblks[k+4] = _mm_xor_si128(ta[4],msgblks[k+4]); cprblks[k+5]= _mm_xor_si128(ta[5],msgblks[k+5]) ;
                        cprblks[k+6] = _mm_xor_si128(ta[6],msgblks[k+6]); cprblks[k+7]= _mm_xor_si128(ta[7],msgblks[k+7]) ;
                }

        if(restBlocks != 0)
                {       k = block8 * BPI;
                        for(i=0; i<restBlocks ; i++)
                                {
                                        ctr = _mm_add_epi64(ctr,one);
                                        //printBytesM(&ctr);
                                        ta[i] = _mm_xor_si128(ctr,iv);
                                }

                        AES_128_ECB_Encrypt(ta,restBlocks,keySchedule);

                        for(i=0; i<restBlocks ; i++)
                                        cprblks[k+i] = _mm_xor_si128(ta[i],msgblks[k+i]);

                }
}

#endif        
        





