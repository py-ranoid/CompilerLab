#include<iostream>
#include<sstream>
using namespace std;

int main(){
	string tac_seq;
	int seq_num;

	//Get the TAC Sequence.
	std::istringstream f;
    std::string line;    

    cout<<"Enter the number of TAC sequences : ";
    cin>>seq_num;

    while (seq_num-->0) {
    	tac_seq += std::getline(f,line);
    }

	cin>>tac_seq;

	cout<<"TAC Seq : "<<tac_seq<<endl;
	return 0;
}