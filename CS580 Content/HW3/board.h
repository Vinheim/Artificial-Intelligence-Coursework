#include <iostream>
#include <list>

using namespace std;

class board {
private:
	list<string> words;
	list<string>::iterator witr;
	char cword[6][5];
	int state;
	int length;
	bool complete;
public:
	board(){
		for(int i = 0; i < 6; i++){
			for(int j = 0; j < 5; j++){
				cword[i][j] = ' ';
			}
		}
		
		this->cword[1][0] = '#';
		this->cword[1][1] = '#';
		this->cword[1][3] = '#';
		this->cword[2][0] = '#';
		this->cword[2][0] = '#';
		this->cword[3][1] = '#';
		this->cword[5][1] = '#';
		this->cword[5][2] = '#';
		this->cword[5][4] = '#';
		
		this->state = 1;
		this->length = 5;
		
		this->complete = false;
	}
	
	bool isComplete(){return complete;}
	
	void addWord(string word){
		if(state == 1){
			for(int i = 0; i < 5; i++){
				cword[0][i] = word.at(i);
			}
			words.push_back(word);
			state++;
			length = 5;
		} else if(state == 2){
			for(int i = 0; i < 5; i++){
				cword[i][2] = word.at(i);
			}
			words.push_back(word);
			state++;
			length = 5;
		} else if(state == 3){
			for(int i = 0; i < 5; i++){
				cword[i][4] = word.at(i);
			}
			words.push_back(word);
			state++;
			length = 4;
		} else if(state == 4){
			for(int i = 1; i < 5; i++){
				cword[2][i] = word.at(i - 1);
			}
			words.push_back(word);
			state++;
			length = 4;
		} else if(state == 5){
			for(int i = 2; i < 6; i++){
				cword[i][3] = word.at(i - 2);
			}
			words.push_back(word);
			state++;
			length = 3;
		} else if(state == 6){
			for(int i = 3; i < 6; i++){
				cword[i][0] = word.at(i - 3);
			}
			words.push_back(word);
			state++;
			length = 3;
		} else if(state == 7){
			for(int i = 2; i < 5; i++){
				cword[3][i] = word.at(i - 2);
			}
			words.push_back(word);
			state++;
			length = 5;
		} else if(state == 8){
			for(int i = 0; i < 5; i++){
				cword[4][i] = word.at(i);
			}
			words.push_back(word);
			state = 0;
			length = 0;
			complete = true;
		}
		
		complete = checkComplete();
	}
	
	void deleteWord(){
		if(state == 2){
			for(int i = 1; i < 5; i++){
				cword[i][2] = ' ';
			}
			words.pop_back();
			state = 1;
			length = 5;
		} else if(state == 3){
			for(int i = 1; i < 5; i++){
				cword[i][4] = ' ';
			}
			words.pop_back();
			state = 2;
			length = 5;
		} else if(state == 4){
			cword[2][1] = ' ';
			cword[2][3] = ' ';
			words.pop_back();
			state = 3;
			length = 5;
		} else if(state == 5){
			for(int i = 2; i < 6; i++){
				cword[i][3] = ' ';
			}
			words.pop_back();
			state = 4;
			length = 4;
		} else if(state == 6){
			for(int i = 3; i < 6; i++){
				cword[i][0] = ' ';
			}
			words.pop_back();
			state = 5;
			length = 4;
		} else if(state == 7){
			/*for(int i = 2; i < 5; i++){
				cword[3][i] = ' ';
			}*/
			words.pop_back();
			state = 6;
			length = 3;
		} else if(state == 8){
			/*for(int i = 0; i < 5; i++){
				cword[4][i] = ' ';
			}*/
			cword[4][1] = ' ';
			words.pop_back();
			state = 7;
			length = 3;
		}
	}
	
	void display(){
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[0][0] <<  " | " << cword[0][1] << " | " << cword[0][2] << " | " << cword[0][3] << " | " << cword[0][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[1][0] <<  " | " << cword[1][1] << " | " << cword[1][2] << " | " << cword[1][3] << " | " << cword[1][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[2][0] <<  " | " << cword[2][1] << " | " << cword[2][2] << " | " << cword[2][3] << " | " << cword[2][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[3][0] <<  " | " << cword[3][1] << " | " << cword[3][2] << " | " << cword[3][3] << " | " << cword[3][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[4][0] <<  " | " << cword[4][1] << " | " << cword[4][2] << " | " << cword[4][3] << " | " << cword[4][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
		cout << "| " << cword[5][0] <<  " | " << cword[5][1] << " | " << cword[5][2] << " | " << cword[5][3] << " | " << cword[5][4] << " | \n";
		cout << "+---+---+---+---+---+\n";
	}
	
	int getLength(){return length;}
	
	int getState(){return state;}
	
	bool consistent(string word){
		if(word.size() == length){
			if(state == 1){
					return true;
			} else if(state == 2){
				
				return(cword[0][2] == word.at(0));
			} else if(state == 3){
				return(cword[0][4] == word.at(0));
			} else if(state == 4){
				if(cword[2][2] == word.at(1)){
					return(cword[2][4] == word.at(3));
				} else {
					return false;
				}
			} else if(state == 5){
				return(cword[2][3] == word.at(0));
			} else if(state == 6){
				return true;
			} else if(state == 7){
				if(cword[3][2] == word.at(0)){
					if(cword[3][3] == word.at(1)){
						return(cword[3][4] == word.at(2));
					} else {
						return false;
					}
				} else {
					return false;
				}
			} else if(state == 8){
				if(cword[4][0] == word.at(0)){
					if(cword[4][2] == word.at(2)){
						if(cword[4][3] == word.at(3)){
							return(cword[4][4] == word.at(4));
						} else {
							return false;
						}
					} else{
						return false;
					}
				} else {
					return false;
				}
			}
		}
	}
	
	void trim(list<string> &dictionary){
		list<string>::iterator witr2;
		witr = words.begin();
		while(witr != words.end()){
			witr2 = dictionary.begin();
			while((*witr2) != (*witr)){
				witr2++;
			}
			witr2 = dictionary.erase(witr2);
			witr++;
		}
	}
	
	bool checkComplete() {
		for(int i = 0; i < 6; i++){
			for(int j = 0; j < 5; j++){
				if(cword[i][j] == ' '){
					return false;
				}
			}
		}
		
		return false;
	}
};