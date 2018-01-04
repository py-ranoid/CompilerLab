#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>

using namespace std;

int identifier_status=0,number_status=0,operator_status=0,someOp=0,multiLine=0,singleLine=0,char_status=0;


int main(){
	fstream file;
	file.open("input.txt");

	char str,prevChar='\n';
	while(file.get(str)){

		if(multiLine==1 && str!='*' && str!='/'){
			cout<<str;
			prevChar = str;
			// cout<<"hetr";
			continue;
		}

		if(char_status==1){
			if(str!='\"')
				cout<<str;
			else{
				cout<<" -> String Constant"<<endl;
				char_status = 0;
			}
				prevChar = '\n';
				continue;
		}

		if(singleLine==1){
			if(str=='\n'){
				cout<<" -> Single Line Comment"<<endl;
				prevChar = str;
				singleLine = 0;
				continue;
			}
			else{
				cout<<str;
				prevChar = str;
				continue;
			}
		}

		start:
		// cout<<str<<endl;
		if(prevChar=='\n'){
			identifier_status = 0;
		}
		// cout<<"id _status : "<<identifier_status<<"prevChar : "<<prevChar<<"Char _status : "<<char_status<<endl;
		if(isalpha(str) && identifier_status==0 && prevChar=='\n'){
			identifier_status = 1;
			cout<<str;
			prevChar = str;
		}
		else if(identifier_status==1){
			// cout<<endl<<"Here"<<endl;
			if(isalpha(str)||isdigit(str)){
				cout<<str;

				prevChar = str;
			}
			else{
				cout<<" -> identifier \n"<<endl;
				identifier_status = 0;

				cout<<str;
				switch(str){
					case '<':
						file.get(str);
						switch(str){
							case '=':
								cout<<str<<" -> Less than or equal to"<<endl;
							break;
							case '>':
								cout<<str<<" -> Not Equal"<<endl;
							break;
							default :
								cout<<" -> Less Than"<<endl;
								prevChar='\n';
								goto start;
						}
						prevChar='\n';
					break;
					case '>':
						file.get(str);
						switch(str){
							case '=':
								cout<<str<<" -> Greater than or equal to"<<endl;
							break;
							case '>':
								cout<<str<<" -> Not A operator"<<endl;
							break;
							default :
								cout<<" -> Greater Than"<<endl;
								prevChar='\n';
								goto start;
						}
						prevChar='\n';
						break;
					case '=':
						file.get(str);
						if(str=='='){
							cout<<str<<" -> Equal to"<<endl;
							prevChar='\n';
						}
						else{
							cout<<" ->Assignment Operator"<<endl;
						}
						break;
					case '\n':
						prevChar = '\n';
						break;
				}
			}
		}
		else if(isdigit(str)){
			cout<<str;
			number_status = 1;
			prevChar = str;
		}
		else if(number_status==1 && (str=='.'||str=='E'||str=='+'||str=='-')){
			cout<<str;
			prevChar = str;
		}
		else if(number_status==1 && str=='\n'){
			prevChar = str;
			cout<<" -> Number Constant"<<endl;
			number_status = 0;
		}
		else if(str=='\''){
			file.get(str);
			cout<<str<<" -> Character Constant"<<endl;
			file.get(str);
			prevChar = '\n';
		}
		else if(char_status==1){
			cout<<str;
			prevChar = str;
		}
		else if(str=='\"'){
			char_status = 1;
		}
		else{
			switch (str) {
				case '/':
					cout<<str;
					prevChar = str;
					file.get(str);
					if(str=='*'){
						cout<<str;
						multiLine = 1;
					}
					if(str=='/'){
						cout<<str;
						singleLine = 1;
						prevChar = str;
					}
					break;
				case '*':
					cout<<str;
					prevChar = str;
					file.get(str);
					if(str=='/'){
						multiLine = 0;
						cout<<str<<" -> Multi Line Comments"<<endl;
					}
					break;
					case '+': case '-': case '%':
						cout<<str<<" -> Arithmetic Operator"<<endl;
						prevChar='\n';
						break;
					case '!':
						cout<<str<<" -> Logical Operator"<<endl;
						prevChar='\n';
						break;
					case '&':
					prevChar = '&';
					file.get(str);
					switch(str){
						case '&':
							cout<<"&& -> Logical Operator"<<endl;
							prevChar='\n';
						}
						break;
					case '|':
						prevChar='|';
						file.get(str);
						switch(str){
							case '|':
							cout<<"|| -> Logical Operator"<<endl;
							prevChar='\n';
						}
						break;
				}
			}
		}

}
