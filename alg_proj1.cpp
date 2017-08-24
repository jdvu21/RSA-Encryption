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


#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>  
#include <sstream> 

using namespace std;

// === MAIN FUNCTIONS ================================
int main(int argc, char *argv[]) {
  srand (time(NULL));
	long pGenerator(long);
	void eea(long,long);
	bool fermatTest(long);
	string RSAencryption(long,long,string);
	void RSAdecryption(int, int, std::string);
  int gcd(int,int);
  void modInverse(long,long,long);

  long a,b;

   if (argc==1||argc>5) {
      cout <<"Wrong input format!";
      exit(1);
   }
   if (argc==2) {
      int log10pp1 = atoi(argv[1]);
      cout << "size of the prime: " << log10pp1 << endl;
      //call your random prime generator ...
      long a = pGenerator(log10pp1);
      while (fermatTest(a)==0)  // strict fermat's testing A
      {
        a = pGenerator(log10pp1);
      }

      srand(100 * time(NULL)); // recalculate the random seed for the second number

      long b = pGenerator(log10pp1);
      while (fermatTest(b)==0)  // strict fermat's testing B
        {
          b = pGenerator(log10pp1);
        }
      
      cout << a << " and " << b << endl;
   }
   if (argc==3) {
      string a = argv[1];
      string b = argv[2];
      cout << "a=" << a << ", b=" << b << endl;
      long newA = stoi(a);
      long newB = stoi(b);
      long newD = gcd(newA,newB);
      //call your Extended Euclidean Algorithm ...
      eea(newA, newB);

   }
   if (argc==4) {
      string e = argv[1];
      string p = argv[2];
      std::string q = argv[3];
      cout << "e=" << e << ", p=" << p <<", q="<< q << endl;
      //call your mod inverse func ...
      //your program should output (d,n) s.t. ed=1%(p-1)(q-1), n=pq
      long newE = stoi(e);
      long newP = stoi(p);
      long newQ = stoi(q);
      modInverse(newE,newP,newQ);
      // long long n = newP * newQ;
      // long rhs = 1 % (newP-1)*(newQ-1);
      // long d = (rhs / newE);
      // cout << "d=" << d << ", n=" << n << endl; 
   }
   if (argc==5) {
      if (argv[1][0]=='e') {
         string e = argv[2];
         string n = argv[3];
         string m = argv[4];
         cout << "e=" << e << ", n=" << n <<", message="<< m << endl;
         //call your RSA encryption ...
         long newE = stol(e); 
         long newN = stol(n);

         RSAencryption(newE,newN,m);
      }
      else if (argv[1][0]=='d'){
         string d = argv[2];
         string n = argv[3];
         string m = argv[4];
         cout << "d=" << d << ", n=" << n <<", message="<< m << endl;
         //call your RSA decryption ...
         int newD = stoi(d);
         int newN = stoi(n);
         //int newC = atoi(m.c_str());
         RSAdecryption(newD, newN,m);
      }
   }
   return 0;
}

long pGenerator(long n) // size of the prime number in digits; check using fermats test
{
	
	while (n < 0) // bounds check; no negatives, will loop until n is postive
  {
    cout << "a number cannot have negative digits. enter a postive n:" << endl;
    cin >> n;
  }
  
  long size = n;
  int numArray[size];
  std::string numberStr = "";

  for (int i = 0; i < size; i++) // each digit will be a random number from 0 - 9
  {
      if (i == 0){
            int ranNum = rand() % 9 + 1;
            numArray[i] = ranNum;
            std::string buffer = std::to_string(ranNum); 
            numberStr.append(buffer);
        }
        else{

            int ranNum = rand() % 9 + 1;
            numArray[i] = ranNum;
            std::string buffer = std::to_string(ranNum); 
            numberStr.append(buffer);
        }
  }
  std::string::size_type sz = 0;
  long primeInt = stol(numberStr);
  return primeInt;
}

bool fermatTest(long n)
{
	if (n < 2)		//By the definition of prime, numbers less than 2 are not prime
		return false;
		
	if (n == 2)		//2 is Prime
		return true;
		
	if (n % 2 == 0) // even numbers
		return false;

	for (int i = 3; i <= sqrt(n); i += 2)
	{	if (n % i == 0)
			return false;
	}
	
	return true;
}

void eea(long a, long b) 
{
    int x=0, y=1, q, lastX=1, lastY=0;
    long t0, t1, t2, t3;
    if (b>a)
    {
      t0 = a;
      a = b;
      b = t0;
    }
    while (b!=0)
    {
      q = a/b;
      t1 = a % b;
      a = b;
      b = t1;

      t2 = x;
      x = lastX - q * x;
      lastX = t2;

      t3 = y;
      y = lastY - q * y;
      lastY = t3;
    }
    cout << "x=" << lastX << ", y=" << lastY << endl;
}

std::string RSAencryption(long e, long n, string message)
{
  string encoded;
  encoded.resize(message.length() * 3 + 1);
  unsigned long int index = message.length() * 3;
  for (unsigned long int i(0); i < message.length(); i++)
  {
    unsigned char ASCII = message[i];
    encoded[index - 2] = (ASCII % 10) + '0';
    ASCII /= 10;
    encoded[index - 1] = (ASCII % 10) + '0';
    encoded[index] = (ASCII / 10) + '0';
    index -= 3;
  }
  encoded[0] = '1';
  long long m = stol(encoded);
  //cout << "before" << m << endl;
  encoded = pow(m,e);
  encoded = m % n;
  cout << "encyrpted:" << m << endl;
  return encoded;
}

void RSAdecryption(int d, int n, std::string c) // the private key d,n as ints, and the string message to be decrypted
{
	string decoded;
  decoded.resize(c.length() * 3 + 1);
  unsigned long int index = c.length() * 3;
  for (unsigned long int i(0); i < c.length(); i++)
  {
    unsigned char ASCII = c[i];
    decoded[index - 2] = (ASCII % 10) + '0';
    ASCII /= 10;
    decoded[index - 1] = (ASCII % 10) + '0';
    decoded[index] = (ASCII / 10) + '0';
    index -= 3;
  }
  decoded[0] = '1';
  unsigned long msg_c = stol(decoded);
  //unsigned long decrypted_msg = pow(msg_c,d);
  unsigned long runningTotal = msg_c;
  cout << "c=" << msg_c << ", d=" << d << endl;
  for (int i=0; i < d; ++i)
  {
    runningTotal *= msg_c;
  }
  unsigned long decrypted_msg = runningTotal;
  decrypted_msg = decrypted_msg % n;
  decrypted_msg = decrypted_msg % n;
  cout << "decrypted: " << decrypted_msg << endl;
}

// === UTILITY FUNCTIONS ================

int gcd(int u, int v) // from wikipedia
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }

    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);

    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);

    return gcd((v - u) >> 1, u);
}

// int modInverse() // https://en.wikipedia.org/wiki/Modular_multiplicative_inverse
void modInverse(long e,long p,long q)
{
  long n = p * q;
  long rhs = 1 % (p-1)*(q-1);
  long d = (rhs / e);
  cout << "d=" << d << ", n=" << n << endl; 
}

// two different string to int methods
// strong
// int a = 10;
// char *intStr = itoa(a);
// string str = string(intStr);
//
// flimsy
// int a = 10;
// stringstream ss;
// ss << a;
// string str = ss.str();



