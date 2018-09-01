

As is evident from the package name, this implementation is for the fixed length setting, where the plaintext contains 4096 bytes, i.e. 256 elements of the field GF(2^{128}). This size correponds to the sector size of modern days disks. The tweak is a single field element and is taken as a fixed 128-bit string in the program. The input message has been taken randomly using rand() functions. Both tweak and plaintext can be read from a file.

The hash functions in this package are obtained from the Bernstein-Rabin-Winograd polynomials based hash function, as is again evident from the name.

The work https://github.com/sebatighosh/HASH2L gives an implementation of BRW hash functions for 31 blocks (field elements) inputs. Here we needed BRW implementation for 255 blocks, which we have done through eight 31-blocks BRW implementations from the previous work.

In the previous work, for the 31-blocks BRW implementation we had used batching level 3 for polynomial multiplications using schoolbook method and delayed reduction strategy. This implementation is used in this work and the final result was obtained using some more multiplications and XORs. Wherever possible we have used batching level 3 for these extra multiplications as well.

