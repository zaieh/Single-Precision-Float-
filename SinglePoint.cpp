/*
Authors: Zaira Cruz, Paivikki Salmi

Program: Assginment 2. A program that converts two single precision floating point hex
		 values into binary and multiplies the values. Then converts the final product back to 
		 hex
		 
Class:	 CSCE 2610, Shanti Thiyagaraja
		 April 25, 2016	
*/
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <bitset>
#include <stdlib.h>

#define MULEN 23
#define PRM 47

using namespace std;

string add(string multiplicand_str, string product);

string hex_to_binary(string hexval);
string exponent_add(string exponent1, string exponent2);
string subtract_bias(string exponent_new, string bias);
string GetHexFromBin(string sBinary);
string find_sign(char s1,char s2);
int main(void)
{
	
	int i=0,x=0,z=49,y,len,size;
	string val1, val2, exponent1, fraction1, fraction2, exponent2;
	string multiplier, multiplicand, binval, product, str1, str2;
	char s1, s2;
	cout<<"Enter a single precision floating point (in Hex): ";//multiplier
	cin>>hex>>val1;
	
	cout<<"Enter another single precision floating point (in Hex): ";//multiplicand
	cin>>hex>>val2;
	cout<<endl;
	
	
	
	int inilenm, inilenp;
	inilenm = val1.size();
	inilenp = val2.size();
	
string butt;	
	if(inilenm<6)
	{
		while(inilenm<6)
		{
			val1 = val1 + '0';
			inilenm++;
		}
	}

	else if(inilenm>6)
	{
		while(inilenm>6)
		{

			val1 = val1.substr(0, val1.size()-1);
			inilenm--;
		}
	}
	//cout<<inilenm<<endl;
	if(inilenp<12)
	{
		while(inilenp<12)
		{
			val2 = val2 + '0';
			inilenp++;
		}
	}
	else if(inilenp>12)
	{
		while(inilenp>12)
		{

			val2 = val2.substr(0, val2.size()-1);
			inilenp--;
		}
	}
	multiplier = hex_to_binary(val1);
	multiplicand = hex_to_binary(val2);
	cout<<"Multiplier: "<<multiplier<<endl;
	cout<<"Multiplier["<<MULEN<<"]:"<<multiplier[23]<<endl;

	cout<<"Multiplicand: "<<multiplicand<<endl;

	len=multiplier.size();

	product = "000000000000000000000000000000000000000000000000";
	//int len2=product.size();

	//cout<<"Binary: "<<multiplier<<endl;
	//cout<<"Binary2: "<<multiplicand<<endl;
	
	s1 = multiplier[0];		//the s value is the first bit in the string
	exponent1 = multiplier.substr(1,8);	//exponent is eight bits after the first bit
	fraction1 = multiplier.substr(9);	//the fraction is the final bits in the string
	
	s2 = multiplicand[0];		//the s value is the first bit in the string
	exponent2 = multiplicand.substr(1,8);	//exponent is eight bits after the first bit
	fraction2 = multiplicand.substr(9);	//the fraction is the final bits in the string

//	cout<<"exp1 "<<exponent1<<" exp2 "<<exponent2<<endl;
	string exponent_new;
	exponent_new = exponent_add(exponent1, exponent2);	//add the exponents together

	cout<<"Step 1 - Add the Exponents "<<endl;
	string exp;
	string bias = "10000001";			//twos complement of the bias 127
	exp = subtract_bias(exponent_new, bias);		//subtract the bias from the added exponent
	cout<<"Result(in binary): "<<exp<<endl;
	cout<<endl;

//	cout<<"Length: "<<len<<endl;
	//Checks multiplier (binary) right most value. If value
	//is a '1', then multiplicand and product are added. Else-if
	//'0', then we shift multiplicand to the left 1-bit and then
	//we shift the multiplier to the right 1-bit.
	while(x<=len)
	{
		if(multiplier[MULEN]=='1')
		{
//			cout<< "Last val is 1"<<endl;
			//Adding the multiplicand to the product register.
			product=add(multiplicand,product);
			cout<<endl<<"Product: "<<product<<endl<<endl;
//			cout<<"HELLO!!"<<endl;
			multiplicand[PRM] = '0';
	//		cout<<endl<<"Multiplicand: "<<endl;
			for (int i = 0; i< 48; i++)
			{
				multiplicand[i] = multiplicand[i + 1];
	//			cout << multiplicand_str[i];
			}
	//		cout<<endl;

			//Takes the multiplier and shifts it one bit to the right.
			char temp;
			multiplier[MULEN] = '0';
			for (int i = 23; i >=0; i--)
			{
				temp=multiplier[i+1];
				multiplier[i+1]=multiplier[i];
				multiplier[i]=temp;
			}
	//		cout<<endl<<"Multiplier: "<<endl;
	//		cout<<multiplier<<endl;
		}
		else
		{
//			cout<<"Last val is 0!"<<endl;
	//		cout<<endl<<"Multiplicand: "<<endl;
			multiplicand[PRM] = '0';
			for (int i = 0; i < 48; i++)
			{
				multiplicand[i] = multiplicand[i + 1];
	  //			cout << multiplicand_str[i];
			}
	//		cout<<endl;

			//Takes the multiplier and shifts it one bit to the right.
			char temp;
			multiplier[MULEN] = '0';
			for (int i = 23; i >=0; i--)
			{
				temp=multiplier[i+1];
				multiplier[i+1]=multiplier[i];
				multiplier[i]=temp;
			}
	//		cout<<endl<<"Multiplier: "<<endl;
	//               cout<<multiplier<<endl;

		}
		x++;
	}
//		cout<<"Step 2 - Multiply the significands"<<endl;
//		cout<<"Result(in binary): "<<product<<endl<<endl;
	//Normalize product

		str1="1";
		int newexp;
		//int newexphex;
		size_t found=product.find(str1);
		if(found!=string::npos){
			//cout<<"'1' was found at: "<<found<<endl;
			str2=product.substr(found+1);
			newexp=2-found;
			//cout<<str2<<endl;
		}
		string other;
		stringstream ss;
		ss<<hex<<newexp;
		string newexphex (ss.str());
		
		other = hex_to_binary(newexphex);
		//cout<<other<<endl;
		
		string final_exp;	
		final_exp= exponent_add(other, exp);
		cout<<"Step 3 - Normalize the significand: "<<endl;
		cout<<"Result of fraction(in binary): "<<str2<<endl;
		cout<<"Result of exponent(in binary): "<<final_exp<<endl<<endl;

		//if newexp==2 then exponent increases by 1(since decimal moves to the left. 
		//Else if newexp==1 then exponent does not change. Stays the same.
		//Else exponent decreases by newexp+1;

	
	string sign;
	sign = find_sign(s1, s2);

	cout<<"Step 4 - Determine the sign "<<endl;
	cout<<"Result (in binary):"<<sign<<endl<<endl;
	string answer_hex;
	answer_hex = GetHexFromBin(product);
	cout<<"Product (in hex): "<<answer_hex<<endl;

return 0;
}

string hex_to_binary(string hexval)	//convert the hex value to a binary value
{
	string bin_final;
	string bin;
	int len;
	
	len = hexval.size();
	//cout<<len<<endl;
	//cout<<len<<endl;
	if(len == 12)
	{	
		for(int x=0;x<12;x++)
		{
			if(hexval[x] == '0')
				bin = "0000";
			else if (hexval[x] == '1')
				bin = "0001";
			else if (hexval[x] == '2')
				bin = "0010";
			else if (hexval[x] == '3')
				bin = "0011";
			else if (hexval[x] == '4')
				bin = "0100";
			else if (hexval[x] == '5')
				bin = "0101";
			else if (hexval[x] == '6')
				bin = "0110";
			else if (hexval[x] == '7')
				bin = "0111";
			else if (hexval[x] == '8')
				bin = "1000";
			else if (hexval[x] == '9')
				bin = "1001";
			else if (hexval[x] == 'a')
				bin = "1010";
			else if (hexval[x] == 'b')
				bin = "1011";
			else if (hexval[x] == 'c')
				bin = "1100";
			else if (hexval[x] == 'd')
				bin = "1101";
			else if (hexval[x] == 'e')
				bin = "1110";
			else if (hexval[x] == 'f')
				bin = "1111";
			else
				bin = "0000";
			
		bin_final = bin_final + bin;	
		}
	}
	else if(len == 6)
	{
		for(int x=0;x<6;x++)
		{
			if(hexval[x] == '0')
				bin = "0000";
			else if (hexval[x] == '1')
				bin = "0001";
			else if (hexval[x] == '2')
				bin = "0010";
			else if (hexval[x] == '3')
				bin = "0011";
			else if (hexval[x] == '4')
				bin = "0100";
			else if (hexval[x] == '5')
				bin = "0101";
			else if (hexval[x] == '6')
				bin = "0110";
			else if (hexval[x] == '7')
				bin = "0111";
			else if (hexval[x] == '8')
				bin = "1000";
			else if (hexval[x] == '9')
				bin = "1001";
			else if (hexval[x] == 'a')
				bin = "1010";
			else if (hexval[x] == 'b')
				bin = "1011";
			else if (hexval[x] == 'c')
				bin = "1100";
			else if (hexval[x] == 'd')
				bin = "1101";
			else if (hexval[x] == 'e')
				bin = "1110";
			else if (hexval[x] == 'f')
				bin = "1111";
			else
				bin = "0000";
			
		bin_final = bin_final + bin;	
		}
	}
	else
	{
		for(int x=0;x<2;x++)
		{
			if(hexval[x] == '0')
				bin = "0000";
			else if (hexval[x] == '1')
				bin = "0001";
			else if (hexval[x] == '2')
				bin = "0010";
			else if (hexval[x] == '3')
				bin = "0011";
			else if (hexval[x] == '4')
				bin = "0100";
			else if (hexval[x] == '5')
				bin = "0101";
			else if (hexval[x] == '6')
				bin = "0110";
			else if (hexval[x] == '7')
				bin = "0111";
			else if (hexval[x] == '8')
				bin = "1000";
			else if (hexval[x] == '9')
				bin = "1001";
			else if (hexval[x] == 'a')
				bin = "1010";
			else if (hexval[x] == 'b')
				bin = "1011";
			else if (hexval[x] == 'c')
				bin = "1100";
			else if (hexval[x] == 'd')
				bin = "1101";
			else if (hexval[x] == 'e')
				bin = "1110";
			else if (hexval[x] == 'f')
				bin = "1111";
			else
				bin = "0000";
			
		bin_final = bin_final + bin;
		}
	}	
	return bin_final;	
}

string exponent_add(string exponent1, string exponent2)	//add the two exponent strings together
{
 string result;  // To store the sum bits
 
    // make the lengths same before adding
    int length = 8;
 
    int carry = 0;  // Initialize carry
 
    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = exponent1.at(i) - '0';
        int secondBit = exponent2.at(i) - '0';
 
        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';
 
        result = (char)sum + result;
 
        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }
 
    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;
    

//    result.erase(result.size() - 1);
	return result;

}

string subtract_bias(string exponent_new, string bias)	//subtract the bias by adding the twos complement to the exponent
{
 string result;  // To store the sum bits

    // make the lengths same before adding
    int length = 8;

    int carry = 0;  // Initialize carry

    // Add all bits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = exponent_new.at(i) - '0';
        int secondBit = bias.at(i) - '0';

        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';

        result = (char)sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }

    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;

    return result;

}
string find_sign(char s1, char s2)
{
	string sign = "";//0 is positive, 1 is negative
	if((s1 == '0') && (s2 == '0'))
	{
		sign = "0";
	}
	else if((s1 == '1') && (s2 == '1'))
	{
		sign = "0";
	}
	else if((s1 == '0') && (s2 == '1'))
	{
		sign = "1";
	}
	else if((s1 == '1') && (s2 == '0'))
	{	
		sign = "1";
	}
	return sign;
}
string add(string multiplicand_str, string product)
{
    string result;

    int length=48;

    int carry = 0;

    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstBit = multiplicand_str.at(i) - '0';
        int secondBit = product.at(i) - '0';

        // boolean expression for sum of 3 bits
        int sum = (firstBit ^ secondBit ^ carry)+'0';


        result = (char)sum + result;

        // boolean expression for 3-bit addition
        carry = (firstBit & secondBit) | (secondBit & carry) | (firstBit & carry);
    }

    // if overflow, then add a leading 1
    if (carry)
        result = '1' + result;

    return result;

}
string GetHexFromBin(string sBinary)
{
	string rest("0x"),tmp,chr = "0000";
	int len = sBinary.length()/4;
	chr = chr.substr(0,len);
	sBinary = chr+sBinary;
	for (int i=0;i<sBinary.length();i+=4)
	{
		tmp = sBinary.substr(i,4);
		if (!tmp.compare("0000"))
		{
			rest = rest + "0";
		}
		else if (!tmp.compare("0001"))
		{
			rest = rest + "1";
		}
		else if (!tmp.compare("0010"))
		{
			rest = rest + "2";
		}
		else if (!tmp.compare("0011"))
		{
			rest = rest + "3";
		}
		else if (!tmp.compare("0100"))
		{
			rest = rest + "4";
		}
		else if (!tmp.compare("0101"))
		{
			rest = rest + "5";
		}
		else if (!tmp.compare("0110"))
		{
			rest = rest + "6";
		}
		else if (!tmp.compare("0111"))
		{
			rest = rest + "7";
		}
		else if (!tmp.compare("1000"))
		{
			rest = rest + "8";
		}
		else if (!tmp.compare("1001"))
		{
			rest = rest + "9";
		}
		else if (!tmp.compare("1010"))
		{
			rest = rest + "A";
		}
		else if (!tmp.compare("1011"))
		{
			rest = rest + "B";
		}
		else if (!tmp.compare("1100"))
		{
			rest = rest + "C";
		}
		else if (!tmp.compare("1101"))
		{
			rest = rest + "D";
		}
		else if (!tmp.compare("1110"))
		{
			rest = rest + "E";
		}
		else if (!tmp.compare("1111"))
		{
			rest = rest + "F";
		}
		else
		{
			continue;
		}
	}
	return rest;
}
