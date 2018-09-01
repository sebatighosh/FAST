

This implementation is also for "Gn", i.e. the General setting, where the plaintext contains any number of bytes between (2n+1) and (2^{n-16}-1). The tweak is a vector of binary strings, where the maximum number of components can be 254 and length of each component can vary from 0 to (2^{n-16}-1). In the program the plaintext has been taken randomly using rand() function. After taking the number of components (k) in the tweak as user input, the length of each component has been taken from the first k entries of the file tweak.txt. Hence, to modify the lengths of the components of the tweak, the corresponding entries in the file need to be changed.

The tweak components have again been taken randomly using rand() functions. Also, the tweak components and the plaintext can be read from a file. This setting is useful for a flexible range of applications.

The hash functions in this package are obtained from the hash function vecHorner, defined in the paper and the algorithm for vecHorner is also stated there. To implement the hash function h, the initialisation of the digest, in the algorithm for vecHorner, must be with the field element 1 (the multiplicative identity) instead of 0 (the additive identity). For implementing h', the digest of h is further multiplied by the hash key.

To implement the algorithm of vecHorner, we have used the decimation of level 3, which is indicated in the name of the package. Also, we have used delayed reduction strategy, where a single reduction is done per 8 multiplications. Hence, we needed to pre-compute and store 8 powers of the hash key, i.e. the powers from 2 to 9, in this case.

