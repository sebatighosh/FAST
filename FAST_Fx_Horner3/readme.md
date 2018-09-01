

As is evident from the package name, this implementation is for the fixed length setting, where the plaintext contains 4096 bytes, i.e. 256 elements of the field GF(2^{128}). This size correponds to the sector size of modern days disks. The tweak is a single field element and is taken as a fixed 128-bit string in the program. The input message has been taken randomly using rand() functions. Both tweak and plaintext can be read from a file.

The hash functions in this package are obtained from the Horner's rule based hash function, as is again evident from the name.

The number "3" in the package name indicates the decimation level used for polynomial multiplications in computing Horner, i.e. we have computed 3 independent polynomial multiplications through schoolbook method in parallel.

Also, we have used here the delayed reduction strategy, i.e. have computed only one reduction per 8 multiplications. For delaying the reduction, at first we had to compute and store 8 powers of the hash-key, i.e. the powers from 2 to 9. However, for small messages, this pre-computation overhead is likely to cause a performance penalty.

