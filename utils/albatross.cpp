// albatross.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <fstream>


#define __int8 int

using namespace std;


// GLOBAL VARIABLES:
vector < pair<int, int> > gear_rotor_1(26);
vector < pair<int, int> > gear_rotor_2(26);
vector < pair <int, int> > gear_rotor_3(26);



//SPECIAL SECURITY FOR ALBATROSS:
vector < pair <char, char> > switch_;



//counters:
unsigned __int8 rotor_1_counter = 0;
unsigned __int8 rotor_2_counter = 0;
//unsigned __int8 rotor_3_counter = 0;

bool init_switch() {
	ifstream file;
	cout << "input name of file" << endl;
	string str_;
	cin >> str_;
	file.open(str_);
	if (file.is_open()) {
		cout << "file is open" <<  endl;
	}
	else {
		cout << "file is not open " <<  endl;
	}
	string str;
	while (file) {
		getline(file, str);
		pair  <char, char>pair_ (str[0], str[2]);
		
		switch_.push_back(pair_);
	}

	cout << "-------------------" << endl;
	return true;
}






bool init_rotors() {
	//-----------------------------
	gear_rotor_1[0].second = 15;
	gear_rotor_1[1].second = 17;
	gear_rotor_1[2].second = 4;
	gear_rotor_1[3].second = 9;
	gear_rotor_1[4].second = 24;
	gear_rotor_1[5].second = 7;
	gear_rotor_1[6].second = 6;
	gear_rotor_1[7].second = 13;
	gear_rotor_1[8].second = 3;
	gear_rotor_1[9].second = 10;
	gear_rotor_1[10].second = 25;
	gear_rotor_1[11].second = 8;
	gear_rotor_1[12].second = 12;
	gear_rotor_1[13].second = 20;
	gear_rotor_1[14].second = 18;
	gear_rotor_1[15].second = 23;
	gear_rotor_1[16].second = 16;
	gear_rotor_1[17].second = 0;
	gear_rotor_1[18].second = 1;
	gear_rotor_1[19].second = 2;
	gear_rotor_1[20].second = 11;
	gear_rotor_1[21].second = 19;
	gear_rotor_1[22].second = 14;
	gear_rotor_1[23].second = 21;
	gear_rotor_1[24].second = 22;
	gear_rotor_1[25].second = 5;
	//----------------------------
	gear_rotor_2[0].second = 14;
	gear_rotor_2[1].second = 24;
	gear_rotor_2[2].second = 7;
	gear_rotor_2[3].second = 11;
	gear_rotor_2[4].second = 18;
	gear_rotor_2[5].second = 5;
	gear_rotor_2[6].second = 20;
	gear_rotor_2[7].second = 16;
	gear_rotor_2[8].second = 0;
	gear_rotor_2[9].second = 25;
	gear_rotor_2[10].second = 15;
	gear_rotor_2[11].second = 1;
	gear_rotor_2[12].second = 8;
	gear_rotor_2[13].second = 22;
	gear_rotor_2[14].second = 2;
	gear_rotor_2[15].second = 12;
	gear_rotor_2[16].second = 10;
	gear_rotor_2[17].second = 3;
	gear_rotor_2[18].second = 6;
	gear_rotor_2[19].second = 17;
	gear_rotor_2[20].second = 19;
	gear_rotor_2[21].second = 21;
	gear_rotor_2[22].second = 13;
	gear_rotor_2[23].second = 9;
	gear_rotor_2[24].second = 23;
	gear_rotor_2[25].second = 4;
	//---------------------------------
	gear_rotor_3[0].second = 17;
	gear_rotor_3[1].second = 5;
	gear_rotor_3[2].second = 11;
	gear_rotor_3[3].second = 25;
	gear_rotor_3[4].second = 0;
	gear_rotor_3[5].second = 13;
	gear_rotor_3[6].second = 8;
	gear_rotor_3[7].second = 22;
	gear_rotor_3[8].second = 9;
	gear_rotor_3[9].second = 12;
	gear_rotor_3[10].second = 6;
	gear_rotor_3[11].second = 1;
	gear_rotor_3[12].second = 20;
	gear_rotor_3[13].second = 10;
	gear_rotor_3[14].second = 3;
	gear_rotor_3[15].second = 24;
	gear_rotor_3[16].second = 7;
	gear_rotor_3[17].second = 14;
	gear_rotor_3[18].second = 16;
	gear_rotor_3[19].second = 23;
	gear_rotor_3[20].second = 2;
	gear_rotor_3[21].second = 18;
	gear_rotor_3[22].second = 15;
	gear_rotor_3[23].second = 21;
	gear_rotor_3[24].second = 4;
	gear_rotor_3[25].second = 19;



	return true;

}




bool swaping(unsigned __int8 number_of_roter) {
	vector <int> rotor(26);
	if (number_of_roter == 1) {

		for (unsigned __int8 i = 0; i <= 25; ++i) {
			rotor[i] = gear_rotor_1[i].second;
		}
		for (unsigned __int8 i = 0; i <= 24; ++i) {
			gear_rotor_1[i].second = rotor[i + 1];
		}
		gear_rotor_1[25].second = rotor[0];
	}
	else if (number_of_roter == 2) {
		for (unsigned __int8 i = 0; i <= 25; ++i) {
			rotor[i] = gear_rotor_2[i].second;
		}
		for (unsigned __int8 i = 0; i <= 24; ++i) {
			gear_rotor_2[i].second = rotor[i + 1];
		}
		gear_rotor_2[25].second = rotor[0];
	}
	else {
		for (unsigned __int8 i = 0; i <= 25; ++i) {
			rotor[i] = gear_rotor_3[i].second;
		}
		for (unsigned __int8 i = 0; i <= 24; ++i) {
			gear_rotor_3[i].second = rotor[i + 1];
		}
		gear_rotor_3[25].second = rotor[0];
	}




	return true;
}


//-----------------
// static int A;
class encryption_ {
public:

	void init_gears(int number_gear_3, int number_gear_2, int number_gear_1) {
		number_gear_3--;
		number_gear_2--;
		number_gear_1--;

		for (unsigned __int8 i = 0; i < 26; ++i) {
			gear_rotor_1[i].first = i;
			gear_rotor_2[i].first = i;
			gear_rotor_3[i].first = i;
		}

		while (gear_rotor_3[0].second != number_gear_3) {
			swaping(3);
		}
		while (gear_rotor_2[0].second != number_gear_2) {
			swaping(2);
		}
		while (gear_rotor_1[0].second != number_gear_1) {
			swaping(1);
		}

	}

	int search_letter(char A) {
		int B = (int)A;
		if (B > 96) B -= 97;
		else if (B > 64) B -= 65;
		return B;
	}



	int rotor_1(int input) {


		int signal = gear_rotor_1[input].second;
		swaping(1);
		rotor_1_counter++;
		return signal;

	}
	int rotor_2(int input) {


		int signal = gear_rotor_2[input].second;
		if (rotor_1_counter >= 26) {
			swaping(2);
			rotor_1_counter = 0;
			rotor_2_counter++;
		}
		return signal;
	}

	int rotor_3(int input) {

		int signal = gear_rotor_3[input].second;
		if (rotor_2_counter >= 26) {
			swaping(3);
			rotor_2_counter = 0;
		}
		return signal;
	}

	char search_letter_encr(int input) {
		input += 65;
		return (char)input;
	}


	char albatross_sec_1(char char_) {
		for (unsigned __int8 i = 0; i < switch_.size(); ++i) {
			if (char_ == switch_[i].first) {
				return switch_[i].second;
			}
		}
		return char_;
	}



}encryption;



int main()
{
	cout << "ALBATROSS START" << endl;
	cout << "-----------------" << endl;
	cout << "-----------------" << endl;
	init_switch();
	init_rotors();
	int   number_gear_1, number_gear_2, number_gear_3;
	cout << "input numbers of gear" << endl;
	//cin >> number_gear_3 >> number_gear_2 >> number_gear_1;
	scanf("%d", &number_gear_3);
	scanf("%d", &number_gear_2);
	scanf("%d", &number_gear_1);
	encryption.init_gears(number_gear_3, number_gear_2, number_gear_1);
	cout << "init is sucessfull" << endl;
	cout << "-----------------------" << endl;
	cout << "input your charaters" << endl;
	cout << ' ' << endl;



	int input;
	char char_;
	for (;;) {
		//char_ = getch();
		cin >> char_;
		if (char_ == '~') break;
		if ((int)char_ == 10 || (int)char_ == 13) {
			cout << ' ' << endl;
			continue;
		}
		if (((int)char_ < 65) || ((int)char_>122) || ((int)char_>90 && (int)char_ < 97)) {
			cout << char_;
			continue;
		}
		input = encryption.search_letter(char_);
		input = encryption.rotor_1(input);
		input = encryption.rotor_2(input);
		input = encryption.rotor_3(input);
		char_ = encryption.search_letter_encr(input);
		char_ = encryption.albatross_sec_1(char_);
		cout << char_;
	}
	cout << ' ' << endl;
	cout << "---------------" << endl;
	cout << "end of crypting" << endl;
	cout << "---------------" << endl;
	system("pause");
	return 0;
}

