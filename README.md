Implementation of the new family of tweakable enciphering schemes (TES) called FAST.

This corresponds to the paper: "FAST: A New Family of Secure and Efficient Tweakable Enciphering Schemes" authored by:

Debrup Chakraborty,                                  Indian Statistical Institute;

Sebati Ghosh,                                        Indian Statistical Institute;

Cuauhtemoc Mancillas Lopez,                          CINVESTAV-IPN, Mexico;

Palash Sarkar,                                       Indian Statistical Institute;

This package contains the implementations for FAST in the two settings, mentioned in the paper; the first one is in the fixed setting, denoted by "Fx" in the package name. One significant application of this setting is disk encryption; so, the implementations in these setting can be used for the purpose of disk encryption.

The second one is in the general setting, denoted by "Gn" in the package name.

The design of FAST requires the following components:

1. Two hash functions, h and h' satisfying some properties mentioned in the paper. These hash functions 
have been constructed from a single hash function in each instantiations. 

    In the setting "Fx" we have used BRW and Horner's rule based hash functions and the package names 
    contain BRW and Horner respectively.

    In the setting "Gn" we have used vecHorner, a vector version of Horner's rule based hash function 
    and vecHash2L, explained in http://tosc.iacr.org/index.php/ToSC/article/view/586, and the 
    corresponding packages contain the names vecHorner and vecHASH2L respectively.

2. A PRF which has been instantiated with the encryption function of AES and the AES-NI instructions 
available in Intel intrinsics have been used for the efficient implementation. The file aes.h in each 
package is the corresponding file.

3. A fixed n-bit string fStr which has been initialised to the all zero element of the field.

4. Sub-routines Feistel and Feistel inverse.

In each package,

the file basics.h contains routines for basic field multiplications; we have used schoolbook method for
polynomial multiplication over GF(2) and have used reduction by multiplication method for reduction.

the file hash.h contains the routines for the basic hash function used in the package,

the file fast.h contains the routines for Feistel, Feistel inverse and the actual routines 
for FAST encryption and decryption.

For compiling any of the packages, we need to use the corresponding flags:

-mavx2 (to compile the SSE and AVX instructions)

-mpclmul (for pclmulqdq)

-maes (for AES-NI instructions)

-O3 (optimisation flag)

So, for example we use the command:

gcc main.c -mavx2 -mpclmul -maes -O3

and the executable a.out is produced.

For measuring performance of each package we have used the strategy used in http://dx.doi.org/10.1007/978-3-642-21702-9_18 and the corresponding file is timedefs.h.

Some more details on the implementations and running instructions are given in the README files inside the packages.
