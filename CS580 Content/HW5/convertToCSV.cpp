#include <iostream>
#include <fstream>

using namespace std;

int main(){
	char input = ' ';
	string skip = "";
	
	ifstream infile;
	ofstream outfile1;
	ofstream outfile2;
	
	infile.open("optdigits-orig.windep");
	outfile1.open("digitInput.csv");
	outfile2.open("digitTarget.csv");
	
	for(int i = 0; i < 21; i++){
		getline(infile, skip);
	}
	
	for(int i = 0; i < 1797; i++){
		for(int i = 0; i < 1024; i++){
			if((i % 32) == 31){
				input = infile.get();
				infile.ignore(1);
			} else {
				input = infile.get();
			}
			if(i == 0){
				outfile1 << input;
			} else {
				outfile1 << "," << input;
			}
		}
		outfile1 << "\n";
		
		infile.ignore(1);
		input = infile.get();
		
		switch(input){
			case '0':
				outfile2 << "0,0,0,0,0,0,0,0,0,1\n";
				break;
			case '1':
				outfile2 << "1,0,0,0,0,0,0,0,0,0\n";
				break;
			case '2':
				outfile2 << "0,1,0,0,0,0,0,0,0,0\n";
				break;
			case '3':
				outfile2 << "0,0,1,0,0,0,0,0,0,0\n";
				break;
			case '4':
				outfile2 << "0,0,0,1,0,0,0,0,0,0\n";
				break;
			case '5':
				outfile2 << "0,0,0,0,1,0,0,0,0,0\n";
				break;
			case '6':
				outfile2 << "0,0,0,0,0,1,0,0,0,0\n";
				break;
			case '7':
				outfile2 << "0,0,0,0,0,0,1,0,0,0\n";
				break;
			case '8':
				outfile2 << "0,0,0,0,0,0,0,1,0,0\n";
				break;
			case '9':
				outfile2 << "0,0,0,0,0,0,0,0,1,0\n";
				break;
		}
		infile.ignore(1);
	}
	
	infile.close();
	outfile1.close();
	outfile2.close();
}