#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

unsigned int UIMulDiv(unsigned int Number, unsigned int Numerator, unsigned int Denominator){
	// Result=~Number*Numerator/Denominator
  unsigned long long int l = Number;
  l *= Numerator;
  Numerator = l % Denominator;
  l /= Denominator;
  if (Numerator >= (Denominator >> 1))
		  l++;
  return(unsigned int)l;
}

int IMulDiv(int Number, int Numerator, int Denominator){
	// Result=~Number*Numerator/Denominator
	long long int l=(long long int)Number;
	l *= Numerator;
	Numerator = l % Denominator;
	l /= Denominator;
	if (abs(Numerator)>= abs(Denominator/2)){
		if (l<0){
			l--;
		}else{
			l++;
		}
	}
  return(unsigned int)l;
}

int32_t I32MulDiv(int32_t Number, int32_t Numerator, int32_t Denominator){
	// Result=~Number*Numerator/Denominator
	long long int l=(long long int)Number;
	l *= Numerator;
	Numerator = l % Denominator;
	l /= Denominator;
	if (abs(Numerator)>= abs(Denominator/2)){
		if (l<0){
			l--;
		}else{
			l++;
		}
	}
  return(int32_t)l;
}

unsigned long ULMulDiv(unsigned long Number, unsigned int Numerator, unsigned int Denominator){
	// Result=~Number*Numerator/Denominator
  unsigned long l=Number;
  l *= (unsigned long)Numerator;
  Numerator = l % Denominator;
  l /= Denominator;
  if (Numerator>= (Denominator>>1))
		  l++;
  return(l);
}/**/

long LMulDiv(long Number, int Numerator, int Denominator){
	// Result=~Number*Numerator/Denominator
  long l=Number;
  l *= Numerator;
  Numerator = l % Denominator;
  l /= Denominator;
  if (Numerator> (Denominator>>1))
		  l++;
  return(l);
}

double DMulDiv(double Number, double Numerator, double Denominator){
	// Result=~Number*Numerator/Denominator
  return Number * Numerator / Denominator;
}

