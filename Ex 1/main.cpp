//
//  main.cpp
//  ex_1
//
//  Created by Sundararaman Venkataramani on 21/12/17.
//  Copyright © 2017 Sundararaman Venkataramani. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include<regex>

using namespace std;


int sym_num = 0;
string data_type[] = {"int","float","char","double","long"};
int data_byte[] = {2 , 4 , 1 , 8 , 8};
string preprocessors[] = {"#include" , "#define"};
string arithmetic_op[] = {"+","-","*","/","%"};
string assignment_op[] = {"+=","-=","*=","/=","%=","="};
string logical_op[] = {"&&","||","!"};
string relational_op[] = {"<","<=",">",">=","==","!="};
string bitwise_op[] = {"^","&","|","<<",">>"};
string unary_op[] = {"-","++","--"};
string special_char[] = {";",",",".","[","]","{","}","(",")"};
string functions[] = {"printf","scanf","getch","clrscr","cout","main"};
int flen = 6;
string keywords[] = { "else if" ,"if" , "else" , "switch" , "for" , "while" , "do" , "true" , "false" , "using" , "namespace" , "std"};
int klen = 9;
int rlen = 6;
int sclen = 9;
int cur_address = 1000;
int find_status = 0;
string var_name;
string var_val;
class symbol_table{
public:
    string id;
    string type;
    int bytes;
    int location;
    string value;
    
    void init(string id, string type , int bytes , string value){
        this->id = id;
        this->type = type;
        this->bytes = bytes;
        this->location = cur_address;
        cur_address += bytes;
        this->value = value;
    }
    
    void display(){
        cout<<id<<" "<<type<<" "<<bytes<<" "<<location<<" "<<value<<endl;
    }

    void display_id(){
        cout<<id<<" Variable declaration"<<endl;
    }
}sym[1000];

int check_preprocessor(string line){
    for(int i = 0 ; i < 2 ; i++){
        if(line.find(preprocessors[i]) != string::npos){
            cout<<preprocessors[i]<<" preprocessor directive\n";
        }
    }
    return 1;
}

string find_var(string line){
    for(int i=0;i<line.length();i++){
        if(line[i] == ';' || line[i]=='='){
            var_name = line.substr(0 , i);
            cout<<var_name<< " Variable declaration\n";
            line = line.substr(i , line.length() - var_name.length());
            break;
        }
    }
    return line;
}

string space_remove(string line){
    if(line[0] == ' '){
        line = line.substr(1 , line.length()-1);
        line = space_remove(line);
    }
    return line;
}

void print_special(char character){
    string spl = string(1 , character);
    for(int i = 0 ; i < 9 ; i++){
        if(spl.find(special_char[i]) != string::npos){
            cout<<spl<<" Special character\n";
        }
    }
}

string check_equal(string line){
//    cout<<endl<<"ce "<<line<<endl;
    if(line[0] == '='){
//        cout<<"ce "<<line<<endl;
        cout<<"= Assignment operator"<<endl;
        line = line.substr(1 , line.length()-1);
        line = space_remove(line);
//        cout<<"ce "<<line<<endl;
        string c_val;
        for(int i = 0; i < line.length() ; i++){
            if(line[i] == ',' || line[i] == ' ' || line[i] == ';'){
                c_val = line.substr(0 , i);
//                cout<<"cval "<<c_val;
                line = line.substr(i , line.length()-c_val.length());
                line = space_remove(line);
                print_special(line[0]);
                line = line.substr(1 , line.length()-1);
                var_val = c_val;
                return line;
            }
        }
    }
    return 0;
}



int check_declaration(string line){
    int dt = -1;
    for (int i = 0 ; i < 5 ; i++){
        if(line.find(data_type[i]) != string::npos){
//            cout<<data_type[i]<<" keyword\n";
            dt = i;
            line = line.substr(data_type[i].length()+1 , line.length()-data_type[i].length());
//            cout<<line<<endl;
            break;
        }
    }
    if(dt != -1){
        while(line.length() > 0){
//            cout<<line;
            line = space_remove(line);
            line = find_var(line);
            line = space_remove(line);
            line = check_equal(line);
            sym[sym_num++].init(var_name, data_type[dt], data_byte[dt], var_val);
        }
    }
    
    return 0;
}


int check_keywords(string line){
    line = space_remove(line);
    int func_flag = 0;
    for(int i = 0 ; i < klen ; i++){
        if(line.find(keywords[i]) != string::npos){
            cout<<keywords[i]<<" Keyword\n";
            line = line.substr(keywords[i].length(), line.length()-keywords[i].length());
            func_flag = 1;
        }

    }
    // cout<<line<<endl;
    if(func_flag == 1){
        for(int i=0 ; line.length() > 0 ; i++){
            line = space_remove(line);
            // cout<<line.length()<<endl;
            for(int j =0 ; j < sclen ; j++){
                if(special_char[j].find(string(1 , line[0])) != string::npos){
                    cout<<line[0]<<" Special character\n";
                    line = line.substr(1 , line.length());
                } 
            }
            line = space_remove(line);
            // cout<<line<<endl;
            if(line[0] != ' '){
                for(int j = 0 ; j < sym_num ; j++){
                    symbol_table t_sym = sym[j];
                    string name = t_sym.id;
                    int len = name.length();
                    string temp_var_name = line.substr(0 , len);
                    // cout<<"cmp"<<name<<" "<<temp_var_name<<endl;
                    if(name == temp_var_name){
                        cout<<name<<" Variable\n";
                        line = line.substr(name.length() , line.length());
                    }
                }
                for(int j = 0; j < rlen ; j++){
                    string expr = relational_op[j];
                    string temp_var_name = line.substr(0 , expr.length());
                    if(temp_var_name == expr){
                        cout<<expr<<" relational operator\n";
                        line = line.substr(expr.length() , line.length());
                    }
                }
            }
        }
    }
}
int check_function(string line){

    regex e ("([a-zA-Z]+)([.,/())a-zA-Z]+)(;*)");

    for(int i=0 ; i<flen ; i++){
        if(line.find(functions[i]) != string::npos){
            cout<<line<<" Function call \n";
            return 0;
        }
    }
    // cout<<"test "<<line<<endl;
    if(regex_match(line , e) && line.find("else")== string::npos){
        cout<<line<<" Function call \n";
        return 0;
    }

    return 1;
}

int main(int argc, char * argv[]) {
    freopen("input.txt", "r", stdin);
    // freopen("output.txt" , "w" , stdout);
    string line;
    string newLine;
    while(getline(cin , line)){
        find_status = 1;
        find_status = check_function(line);
        if(find_status){    
            check_preprocessor(line);
            check_declaration(line);
            check_keywords(line);
        }
    }
    cout<<endl;
    for(int i = 0 ; i < sym_num ; i++){
        sym[i].display();
    }
}
