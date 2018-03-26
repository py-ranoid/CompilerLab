#include<iostream>
#include<string.h>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

int stack_addr;

class activation_records;
class stack;

vector<class activation_records> stack;
vector<class activation_records>::iterator it; 

//Class to denote the activation records in the stack.
class activation_records{

	public:
	//Flag to denote if data is present or not.
	char return_address[25];
	int num_parameters;
	char type_parameters[25];
};

int main(){


	//Read a program file as input.

	//Construct the first activation record.
	activation_records node ;

	ifstream f;
	f.open("program.txt");

	char string[200];
	int c=0;
	while(f>>string){
		cout<<string<<endl;
		//If a function call is present , push the activation record for that function onto the stack.
		auto pos = strstr(string,"(");
		if (pos != NULL){
			//Going to extract the 
			substr(pos,strlen(string));
		}
	}

	/*
	strcpy(node.return_address,"200") ;
	strcpy(node.type_parameters,"int,int") ;
	stack.push_back(node);
	*/
	
	for (it = stack.begin();it!=stack.end();it++){
		cout<<(*it).return_address<<endl;
		cout<<(*it).num_parameters<<endl;
		cout<<(*it).type_parameters<<endl;
	}
	

	return 0;
}