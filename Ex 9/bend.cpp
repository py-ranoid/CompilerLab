#include<iostream>
#include<regex>
#include<stdlib.h>
#include<map>
#include<ctype.h>

using namespace std;

map <string, string> vars;
map <string, string>::iterator it;

int rc = 0;

int main(){
	int n;
	char tmp[100];
	cout<<"Enter no. of statements: ";
	cin>>n;
	cin.getline(tmp, sizeof(tmp));
	
	cout<<"Enter TAC:\n";
	string s[100];
	for(int i=0; i<n; i++){
		char str[100];
		cin.getline(str, sizeof(str));
		s[i] = string(str);
	}

	cout<<"\nGiven TAC:\n";
	for(int i=0; i<n; i++){
		cout<<s[i]<<"\n";
	}

	cout<<"\nMachine Code:\n";
	regex label("(\\w+): ?(\.*)");
	regex cond("((\\w+): ?)?if (\\w+)\(<|>|<=|>=|==|!=)(\\w+) goto (\\w+)");
	regex ass("(\\w+)=(\\d+)");
	regex arith("(\\w+)=(\\w+)\([+]|[-]|[*]|[/])(\\w+)");
	regex vass("(\\w+)=(\\w+)");
	regex jump("goto (\\w+)");

	for(int i=0; i<n; i++){
		string str = s[i];
		smatch sm;
		if(regex_search(str, sm, cond)){
			//cout<<"Test : "<<sm[0]<<endl;
			string r = "R" + to_string(rc);
			rc++;
			//vars.insert(pair <string, string> (sm[2], r));
			cout<<"\tMOV "<<r<<", #"<<sm[5]<<"\n";
			cout<<sm[2]<<":\t"<<"CMP "<<vars[sm[3]]<<", "<<r<<"\n";
			cout<<"\tJLE "<<sm[6]<<"\n";
			continue;
		}
		else if(regex_search(str, sm, label))
		{
			cout<<sm[1]<<":";
			str = sm[2];
		}
		if(regex_search(str, sm, ass))
		{
			//cout<<"Test : "<<sm[0]<<endl;
			string r = "R" + to_string(rc);
			rc++;
			cout<<"\tMOV "<<r<<", #"<<sm[2]<<"\n";
			vars.insert(pair <string, string> (sm[1], r));
		}
		else if(regex_search(str, sm, jump))
		{
			//cout<<"Test : "<<sm[0]<<endl;
			cout<<"\tJMP "<<sm[1]<<"\n";
		}
		else if(regex_search(str, sm, arith))
		{
			/*
				Subcase to be handled : 
				If one of the operands to an arithmetic expression, is a constant,
				then first move the constant to a register and then add the contents
				of that register.
			*/
			string op = "NULL";
			string tmp(sm[3]);
			//cout<<"Test : "<<sm[0]<<endl;
			char ch = tmp.c_str()[0];
			switch(ch)
			{
				case '+':	op = "ADD"; break;
				case '-':	op = "SUB"; break;
				case '*':	op = "MUL"; break;
				case '/':	op = "DIV"; break;
				default: break;
			}
			//This is where we handle the special case.
			rc++;
			//Assign the constant to a register.
			//Check if sm[4] is a number.
			
			//vars.insert(pair <string, string> (sm[2], r));

			cout<<"\t"<<op<<" "<<vars[sm[2]]<<", ";
			//cout<<"NOW"<<sm[1]<<endl;
			if(vars[sm[1]] == ""){
				//cout<<"Check"<<sm[1]<<endl;
				cout<<sm[1]<<" ";
				string r = "R" + to_string(rc);
				cout<<r<<endl;
				rc++;
				vars.insert(pair <string, string> (sm[1], r));
			}
			
			if(vars[sm[4]].length())
				cout<<vars[sm[4]]<<"\n";
			else
				cout<<"#"<<sm[4]<<"\n";

			string next = s[i+1];
			smatch nm;
			if(regex_search(next, nm, vass))
				if(nm[2] == sm[1])
					if(nm[1] == sm[2])
						i++;
					
		}
		else if(regex_match(str, sm, vass))
		{
			//cout<<"Test : "<<sm[0]<<endl;
			cout<<"\tMOV "<<vars[sm[1]]<<", "<<vars[sm[2]]<<"\n";
		}
	}
	cout<<"\n";

	cout<<rc<<endl;
	//Printing the contents of the map.
	for(it = vars.begin();it!=vars.end();it++){
		cout<<it->first<<" "<<it->second<<endl;
	}
}
/*
x=0
i=1
L3: if i<=10 goto L1
goto L2
L1: t1=x+i
x=t1
t2=i+1
i=t2
goto L3
L2:
*/