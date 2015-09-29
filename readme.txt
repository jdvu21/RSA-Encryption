/* ****************************************************************************
 *
 * Jeff Vu 
 * Algorithms - Fall 2015
 * Project 1 - RSA encryption (C++)
 * This file is part of rsa - the RSA implementation in C++.
 *
 * This file contains the procederal implementation for the encryption.
 * 
 * 
 * ****************************************************************************
 */

-This program is confirmed to compile with g++ 4.2.1
- '-o' is the only additonal parameter needed to compile // g++ alg_proj1.cpp -o test
- an exec file has been included in the submission // ./test d 420 13 123
-Due to lack of time, the program was written all in one .cpp file.
-Main() is the driver program which calls in the five main functions: 
	-pGenerator() //prime generator with strict fermats testing
	-modInverse()
	-eea() // extended euclidean algorithm
	-rsaEncryption()
	-rsaDecryption()
-'long' and 'long long' were used to enable prime numbers greater than 9 digits
- Therefore, this program is most likely incredibly memory intensive and inefficient
- rsaEncryption() and rsaDecryption() may not handle the math correctly

// -mordor:alg_proj1 Jeff$ g++ --version
// Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
// Apple LLVM version 7.0.0 (clang-700.0.72)
// Target: x86_64-apple-darwin14.5.0
// Thread model: posix
// mordor:alg_proj1 Jeff$ 