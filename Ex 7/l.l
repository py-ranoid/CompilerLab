#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int stack_addr;

class activation_records;

class stack{
	int stack_top;

	//To hold the activation_records.
	class activation_records*;
};

//Class to denote the activation records in the stack.
class activation_records{
	char return_address[25];
	int num_parameters;
	char type_parameters[100];
};

int main(){


	return 0;
}