// FileManager.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

class User {
public:
	string login;
	string password;
	bool rights[3] = { 0,0,0};

};
User PEOPLE[30];
User Client;
void UserInit(User Mx[]) {
	ifstream users;
	users.open("users.txt");
	int i = 0;
	while (!users.eof())
	{
		users >> Mx[i].login >> Mx[i].password >> Mx[i].rights[0] >> Mx[i].rights[1] >> Mx[i].rights[2];
		++i;
	}
	users.close();
}
void Clear() {
	system("cls");
}

User Login(User Mx[]) {
	string log, pas;
	int k = -1;
	Clear();
	cout << "Login - ";
	cin >> log;
	cout << "Password - ";
	cin >> pas;
	for (size_t i = 0; i < 3; i++)
	{
		if (Mx[i].login == log && Mx[i].password == pas){
			k = i;
		}
	}
	if (k > -1) {
		Clear();
		cout << "you entered as " << Mx[k].login << endl;
		return Mx[k];
	}
	else {
		throw 1;
	}
}
User init_Login() {
	string i;
	User Client;
	try {
		 Client = Login(PEOPLE);
	}
	catch (int) {
		Clear();
		cout << "wrong login or password" << endl;
		cout << "type smth to continue __" << endl;
		cin >>  i;
		init_Login();
	}
	return Client;
}
void printLogins() {
	for (int i = 0; i < 3;++i) {
			 cout << PEOPLE[i].login << " " << PEOPLE[i].password << " " << PEOPLE[i].rights[0] << " "
				 << PEOPLE[i].rights[1] << " " << PEOPLE[i].rights[2] << endl;
		 }
}
int FileOptions(User U) {
	int choice;
	if (U.rights[0]) {
		cout << "1)read " << endl;
	}
	if (U.rights[1]) {
		cout << "2)write " << endl;
	}
	if (U.rights[2]) {
		cout << "3)append " << endl;
	}
	cin >> choice;
	return  choice * U.rights[choice - 1];
}
void FileTasks(User U, string filename,int task) {
	if (task == 0) {
		cout << " this move is prohibited on your account" << endl;
		exit(1337);
	}
	int num;
	string c;
	char str[50];
	if (task == 2) {
		Clear();
		c = "notepad \"" + filename + "\"";
		system(c.c_str());
	}
	else {
		fstream file;
		file.open(filename, fstream::in | fstream::out | fstream::app);
		switch (task) {
		case 1:
			Clear();
			cout << file.rdbuf() << endl;
			system("pause");
			break;
		case 3:
			

			Clear();
			cout << "enter number of additional lines of text that are going to be added in file (line length <=50)" << endl;
			cin >> num;
			cout << "please enter the line" << endl;
			for (int i = 0; i <= num; i++) {
				cin.getline(str, 50);
				if (i != num) {
					file << str << endl;
				}
				else
					file << str;
			}

		}
		Clear();
		file.close();
	}
}
void FileManagement(User U) {
	system("pause");
	Clear();
	ifstream menu;
	int choice;
	int num;
	menu.open("menu.txt");
	ifstream playlist;
	playlist.open("playlist.txt;");
	cout << "Choose the file" << endl;
	cout << "1. menu.txt" << endl;
	cout << "2. playlist.txt" << endl;
	cin >> choice;
	Clear();
	switch (choice)
	{
	case 1:
		cout << "> menu.txt" << endl;
		FileTasks(U,"C:\\FILES\\menu.txt",FileOptions(U));
		break;
	case 2:
		cout << "> playlist.txt" << endl;
		FileTasks(U, "C:\\FILES\\playlist.txt", FileOptions(U));
		break;
	default:
		break;
	}
	playlist.close();
	menu.close();

	cout << "want to manage other files?\n 1) yes\n 2) no" << endl;
	cin >> num;
	(num == 1) ? FileManagement(Client) : exit(1);
}
int main()
{
	
	 UserInit(PEOPLE);
	 Client = init_Login();
	 FileManagement(Client);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
