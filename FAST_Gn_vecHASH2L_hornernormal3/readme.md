

As the package name indicates, this implementation is for the General setting, where the plaintext contains any number of bytes between (2n+1) and (2^{n-16}-1). The tweak is a vector of binary strings, where the maximum number of components can be 254 and length of each component can vary from 0 to (2^{n-16}-1). In the program the plaintext has been taken randomly using rand() function. After taking the number of components (k) in the tweak as user input, the length of each component has been taken from the first k entries of the file tweak.txt. Hence, to modify the lengths of the components of the tweak, the corresponding entries in the file need to be changed.

The tweak components have again been taken randomly using rand() functions. Also, the tweak components and the plaintext can be read from a file. This setting is useful for a flexible range of applications.

The hash functions in this package are obtained from the hash function vecHash2L, defined in http://tosc.iacr.org/index.php/ToSC/article/view/586. The algorithm for vecHash2L has been restated in the current paper. To implement the hash function h, the initialisation of the digest, in the algorithm for vecHash2L, must be with the field element 1 (the multiplicative identity) instead of 0 (the additive identity). For implementing h', the digest of h is further multiplied by the hash key.

To implement the rest of the algorithm of vecHash2L, we need to implement BRW on \eta = 31 (in this work) number of blocks. Also, for partial superblocks, BRW need to be implemented for 1 to 30 number of blocks. These implementations have been taken from http://tosc.iacr.org/index.php/ToSC/article/view/586. For 31-block BRW, batching level 3 has been used for the schoolbook method of polynomial multiplication and delayed reduction has been used. For other implementations of BRW also batching level more than 1 has been used wherever possible and delayed reduction has been used.

For the Horner layer at the upper level a decimation of 3 has been used, but the delayed reduction strategy has not been used here, i.e. a reduction is done per multiplication. These are indicated by "hornernormal3" in the name of the package.

As it does not have the overhead of precomputing the powers of the hash key, for tweaks and messages of length not too big (for almost the entire range of lengths in which we have experimented), it outperforms the package using delayed reduction strategy.

