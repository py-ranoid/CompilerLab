#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;


struct SymbolTable{                                                                             //symbol table for identifiers
	string IdentifierName;
	string dataType;
	string value;
	int location;
	int numBytes;
}st[100];

int IdNum = 0;                                                                                  //To record the number of identifiers

int find(string fileStr, string array[], int arraysize){                                        //Classify the tokens 

	for(int i = 0; i < arraysize; i ++){
		if(fileStr.compare(array[i]) == 0)
			return 1;
	}
	return 0;
}
int validIdentifier(string fileStr){                                                            //To check if an identifier is valid/invalid

	if((fileStr[0] >= 65 && fileStr[0] <= 90) || (fileStr[0] >= 97 && fileStr[0] <= 122))
		return 1;
	return 0;
}
int findSize(string DataType){                                                                  //Returns size of an identifier

	if(DataType.compare("int") == 0)
		return sizeof(int);
	else if(DataType.compare("float") == 0)
		return sizeof(float);
	else if(DataType.compare("string") == 0)
		return sizeof(string);
	else if(DataType.compare("char") == 0)
		return sizeof(char);
	else if(DataType.compare("double") == 0)
		return sizeof(double);
	else return 0;
}
void printSymbolTable(){                                                                        //Print the entire symbol table

	int i = 0;
	cout << "\n\t\tCONTENTS OF SYMBOL TABLE "<< endl;
	cout << "IDENTIFIERNAME\tTYPE\tNUMBERofBYTES\tLOCATION\tVALUE\n";
	st[0].location = 1000;
	for(i = 0; i < IdNum; i ++){
		cout << "\t" << st[i].IdentifierName;
		cout << "\t" << st[i].dataType;
		cout << "\t\t" << st[i].numBytes;
		if(i != 0)
			st[i].location = st[i-1].location + st[i].numBytes;
		cout << "\t  " << st[i].location;
		cout << "\t\t" << st[i].value << endl;
	}
}	
int classify(string fileStr){                                                                   //To function call classify the tokens

	string Keywords[9] = {"int", "float", "char", "if", "while", "else", "return", "true", "false"};
	string PreprocessorDirectives[4] = {"#include<stdio.h>", "#include<string.h>", "#include<iostream>", "#DEFINE"};
	string SpecialCharacters[9] = {"{", "}", "(", ")", ",", ";", ".", "[", "]"};	
	string FunctionCalls[5] = {"main()", "printf", "scanf", "clrscr", "getch"};
	string ArithmeticOperators[5] = {"+", "-", "*", "/", "%"};
	string ArithmeticAssignmentOperators[5] = {"+=", "-=", "*=", "/=", "%="};
	string LogicalOperators[3] = {"&&", "||", "!"};
	string RelationalOperators[6] = {">", ">=", "<", "<=", "==", "!=" };
	string BitwiseOperators[5] = {"&", "|", ">>", "<<", "^"};
	string UnaryOperators[2] = {"++", "--"};
	
	if(fileStr.compare("=") == 0)			                                                    //Assigment Operator
		return 0;
	else if(find(fileStr, Keywords, 9))
		return 1;
	else if(find(fileStr, PreprocessorDirectives, 4))
		return 2;
	else if(find(fileStr, SpecialCharacters, 9))
		return 3;
	else if(find(fileStr, FunctionCalls, 5))
		return 4;		
	else if(find(fileStr, ArithmeticOperators, 5))
		return 5;
	else if(find(fileStr, ArithmeticAssignmentOperators, 5))
		return 6;
	else if(find(fileStr, LogicalOperators, 3))
		return 7;
	else if(find(fileStr, RelationalOperators, 6))
		return 8;
	else if(find(fileStr, BitwiseOperators, 5))
		return 9;
	else if(find(fileStr, UnaryOperators, 2))
		return 10;
	else if(fileStr[0] == 40)		                                                        	//Parenthesis => Argument to a function
		return 11;
	else if(validIdentifier(fileStr))
		return 12;
	else						                                                                //Constant
		return 13;
}

int main(){

	ifstream file;
	char fileName[100];
	int i = 0, j = 0, k = 0, index = 0;
	bool Recorded = false;	
	string msgLine, msgs[50], CategoryName[14] = {"Assignment Operator", "Keyword", "Preprocessor Directive", "Special Character", "Function Call",
                                                "Arithmetic Operators", "Arithmetic Assignment Operators", "Logical Operators", "Relational Operators",
                                                "Bitwise Operators", "Unary Operators", "Argument", "Identifier", "Constant"};
							
	cout << "Enter file name: ";                                                                
	cin >> fileName;

	file.open(fileName, ios::in);
	if(!file)
		cout << "Error opening file\n";
	else{

		cout << "File opened\n";
		cout << "\n\t\t\tTOKENS IDENTIFIED \n\n";		

		while(!file.eof()){
			index = 0;
			getline(file, msgLine);                                                        //reading the file line by line

			for(i = 0; i < msgLine.length(); i ++){
				k = 0;
				while(msgLine[i] != ' ' && i < msgLine.length()){
					msgs[index] += msgLine[i++];                                           //taking in every word of each line and storing it in an array of string
				}				
				index ++;
			}

			for(i = 0; i < index; i ++){
				Recorded = false;
				cout << (string)msgs[i]<<"\t";
				int Category = classify((string)msgs[i]);                                  //Classifying the strings
				cout << " \t\t: " << CategoryName[Category] <<endl;
				
				if(Category == 12)                                                         // Identifier
				{
					                                                                       // Check if identifier already exists in symbol table
					for(j = 0; j < IdNum; j ++){
						if((st[j].IdentifierName).compare(msgs[i]) == 0){
							Recorded = true;                                               //marking record as True since the record is already present in struct
							break;
						}
					}
					
					                                                                       //If not already recorded in symbol table
					if(!Recorded){			
						                                                                   //Name is current msgs string				
						st[IdNum].IdentifierName = msgs[i];	
						                                                                   //Datatype must have been previous msgs string
						if(classify(msgs[i-1]) == 1)
							st[IdNum].dataType = msgs[i-1];	
						                                                                   //Or datatype of previous identifier
						else
							st[IdNum].dataType = st[IdNum-1].dataType;
						                                                                   //Find size of that datatype
						st[IdNum].numBytes = findSize(st[IdNum].dataType);
						                                                                   //Value of this identifier is the message after the assignment operator, if any*/
						if(classify(msgs[i+1]) == 0)
							st[IdNum].value = msgs[i+2];			
						else
							st[IdNum].value = "Not initialised";
						IdNum ++ ;
					}
				}						
			}
			for(i = 0; i < index; i ++)
				msgs[i] = "\0";
		}
		file.close();
		printSymbolTable();
		
	}
}