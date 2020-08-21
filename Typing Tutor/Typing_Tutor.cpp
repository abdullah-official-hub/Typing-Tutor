// ------------------------------------------------ START

// HEADER FILES
#include <iostream>	// Input Output Stream
#include <fstream>	// File Handling
#include <conio.h>	//	For getch() , getche() etc
#include <cstdlib>	// For Random Values , Clear Screen
#include <ctime>	// Time Operations
#include <stdio.h>	
#include <windows.h>		// For Titles
#include <ctime>			// for Time
#include <sstream>			// String Streaming
using namespace std;

#define name_size 36	// name_size=36 (Constant)
#define pass_size 24	// pass_size=24 (Constant)

fstream binary_file;	// Stream a file named binary_file

// Global Variables
int start=1;
int size,mistake=0,accuracy,level_count,level[5];
int level_count_1,level_1[5],count_plus=0;
char *name,*pass,*real_name,*check_name,*check_pass;
string use_name,use_pass,check_use_pass,check_use_name;
bool pass_flag=false,show_once_flag=false,exist_flag=false;
bool flag_word=false, flag_sentence=false;
bool pass_call_from_fun_flag=false,pass_call_from_main_flag=false;

// Void (Non_Returning) Function ProtoTypes
void titles (int a);			// Titles Function
void delay(int a);				// Delay Function ProtoType
void realname_and_hidepass ();	// Show Name & Hide_pass Function
void loading();					// Loading Function
void _end();					// End Program Function
void information();				// Information Desk Function
void close_program();			// Close_Program Options
void put_levels();				// Put New Scores in Binary
void front_page();				// First View Function
void Exchange();				// Exchange Scores for Editing
void get_levels();				// Get Levels From Binary
void remove_data();				// Remove all Pointers & more
void lesson_reader();			// Read Lessons From A-ONE.BCSF16A508 File
void level_viewer();			// Function for Show Levels
void view();
void hide_passcode(string hide_pass);	// Make Password ****
void _color(string value1,string value2);	// Color Functions

// Int (Returning) Function Prototypes
int put_scores(string a);		// Put Scores corresponding to name
int check_WPM();				// Words Per Minute Function
int upper(char a[]);			// Convert Upper Function ProtoType
int password(char a[]);			// Password Function ProtoType
int isExist(string a);			// Check Existance Function
int Remove(string a);			// Remove Specific Record
int Input(char a[]);			// Input Name
int Remove_Practice_Logout();	// User Front Page and Options
int Lessons_Typing(string a);	// Lesson Typing Function
int Typing(string a);			// Typing Words & Sentences
int practice();					// Prectice Mode Function
int MainMenu();					// Main Menu Function

// MAIN CODING
int main (){
	
	if (start==1){
		front_page();
		start++;
	}
	_color("f","0");
	
	srand(time(0));
	real_name=new char[name_size];
	name=new char[name_size];
	check_name=new char[name_size];
	pass=new char[pass_size];
	check_pass=new char[pass_size];
	
	binary_file.open("Records_Binary.bin",ios::binary|ios::in|ios::out|ios::app);
	char NoCode[]={'0','\0'};
	MainMenu();
	titles(1);
	Input(name);
	
	if (isExist(use_name))
	{
		titles(2);
		check_use_pass=string(check_pass);
		if (check_use_pass!="0"){
			AgainPass :
			system("CLS");
			titles(2);
			cout << "UserName       : " << real_name;
			cout << "\n\n\t\tEnter Password : ";
			password(pass);
			use_pass=string(pass);
			if (check_use_pass==use_pass){
				cout << "\t(Access Granted)\n";
				pass_upper :
				if (show_once_flag)
					realname_and_hidepass();
				Remove_Practice_Logout();
				show_once_flag=true;
				goto pass_upper;
			}
			else
				cout << "\t(Access Denied)";
				cout << "\n\n\t\tPress '1' to again Enter PassCode\n\t\t";
				cout << "Press Any other key for Main Menu";
				char sub_main;
				sub_main=getch();
				if (sub_main=='1')
					goto AgainPass;
		}
		else{
			cout << "Name     : " << real_name << '\n' << '\t';
			cout << "\tPassword : No Password Protection\n";
			No_pass_upper :
			if (show_once_flag)
				realname_and_hidepass();
			Remove_Practice_Logout();
			show_once_flag=true;
			goto No_pass_upper;
		}
	}
	else
	{
		titles(3);
		char pass_choice;
		cout << "Name : " << real_name;
		cout << "\n\n\t\tMake Passcode 'OPTIONAL' (y/n) : ";
		cin >> pass_choice;
		titles(3);
		level_count=0;
		for (int i=0;i<5;i++)
			level[i]=0;
			if (pass_choice=='y' || pass_choice=='Y'){
				cout << "Username : " << real_name << "\n\n\t\t";
				cout << "Enter Passcode under length 24 digits\n";
				cout << "\t\tEnter Passcode : ";
				password(pass);
				binary_file.write((char*)name,name_size);
				binary_file.write((char*)pass,pass_size);
				check_use_pass=string(pass);
			}
		else{
			binary_file.write((char*)name,name_size);
			binary_file.write((char*)NoCode,pass_size);
			check_use_pass="0";
		}
		put_levels();
		titles(3);
		again0 :
		realname_and_hidepass();
		Remove_Practice_Logout();
		goto again0;
	}
	
	binary_file.close();
	remove_data();
	return main();
	
}
// Delay Function
void delay(int a){		
	int b;
	for (int i=0;i<a*1000000;i++)
		b=b*i;
}
// Convert Upper Function
int upper(char a[]){
	delete []real_name;
	real_name=new char[name_size];
	for (int i=0;i<name_size;i++)
		{
			real_name[i]=a[i];
			if (a[i]==' ')
				name[i]='_';
			else if (int(a[i])>=97 && a[i]<=122)
				a[i]=int(a[i]-32);
		}
}
// Password Function
int password(char pass[]){
for (int i=0;i<pass_size;i++){
	pass :
		pass[i]=getch();
		if (int(pass[i]==8)){
			if (i>0){
				cout << '\b' << ' ' << '\b';
				i--;
			}
			goto pass;
		}
		else if (int(pass[i]==13))
		{
			pass[i]='\0';
			break;
		}
		else if (int(pass[i])==32)
		{
			MessageBox(NULL,"Spaces are not allowed in password\nPress OK to Continue.....\nClose to Continue.....","Wrong Input",MB_ICONERROR);
			i--;
		}
		else{
			cout << pass[i];
			delay(20);
			cout << '\b' << '*';
			}
			}
}
// Input Name
int Input(char a[]){
	cout << "User Full Name : ";
	cin.getline(a,name_size);
	upper(a);
	use_name=string(a);
}
// Titles Function
void titles (int a){
	if (a==1)
	{
		system("CLS");		// Clear Screen
		SetConsoleTitle("Typing Tutor");	// Title
		cout << "\n\n\t\t******** TYPING TUTOR ********\n\n\t\t";
	}
	else if (a==2)
	{
		system("CLS");		// Clear Screen
		SetConsoleTitle("Existing User");	// Title
		cout << "\n\n\t\t******** EXISTING USER ********\n\n\t\t";
	}
	else if (a==3)
	{
		system("CLS");		// Clear Screen
		SetConsoleTitle("New User");	// Title
		cout << "\n\n\t\t******** NEW USER ********\n\n\t\t";
	}
}
// Check Existance Function
int isExist(string a){
	binary_file.seekg(0,ios::end);	// Put Pointer in last
	size=binary_file.tellg();		// Get a file size
	binary_file.seekg(0,ios::beg);	// Put Pointer in Beginning
	// Place a Condition when size is greater than pointer value then true
	while (size>binary_file.tellg())
	{
		binary_file.read((char*)check_name,name_size);	// Get Data of 36 bytes from binary file
		check_use_name=string(check_name);	// TypeCasting a 36 byte char into string to compare with input name
		if (a==check_use_name)	// Compare both strings if DONE then flag becomes true and finish the loop
		{
			binary_file.read((char*)check_pass,pass_size);
			get_levels();
			Exchange();
			exist_flag=true;
			return true;
		}
		else
			binary_file.seekg(48,ios::cur); // Jump pass_size + Levels_size
	}
	return false;
}
// Remove Specific Record
int Remove(string a){
	if(isExist(a)){
		if (pass_call_from_fun_flag){
		cout << "\n\tUserName Exists";
		check_use_pass=string(check_pass);
			if (check_use_pass=="0"){
				pass_flag=true;
				cout << "\n\tNo PassCode Protection";
			}
			else{
				cout << "\n\tEnter Password : ";
				password(pass);
				use_pass=string(pass);
			if (check_use_pass==use_pass && !pass_flag)
				pass_flag=true;
		}
		}
		if (pass_flag || pass_call_from_main_flag){
			fstream binary_file1;
			binary_file1.open("temp.bin",ios::binary|ios::out);
			binary_file.seekg(0,ios::end);	// Put Pointer in last
			size=binary_file.tellg();		// Get a file size
			binary_file.seekg(0,ios::beg);	// Put Pointer in Beginning
			char *del_name,*del_pass;
			while (size>binary_file.tellg()){
				del_name=new char[name_size];
				del_pass=new char[pass_size];
				binary_file.read((char*)del_name,name_size);	// Get Data of 36 bytes from binary file
				binary_file.read((char*)del_pass,pass_size);
				get_levels();
				check_use_name=string(del_name);	// TypeCasting a 36 byte char into string to compare with input name
				if (a!=check_use_name){	// Compare both strings if DONE then flag becomes true and finish the loop
					binary_file1.write((char*)del_name,name_size);
					binary_file1.write((char*)del_pass,pass_size);
					binary_file1.write((char*)&level_count,sizeof(int));
					for (int i=0;i<5;i++)
					binary_file1.write((char*)&level[i],sizeof(int));
				}
			delete []del_name;
			delete []del_pass;
		}
		binary_file.close();
		binary_file1.close();
		remove("Records_Binary.bin");
		rename("temp.bin","Records_Binary.bin");
		cout << "\n\n\tDeleted Record named \"" << real_name << "\" Successfly";
		cout << "\n\n\tPress any key for Main Menu ........";
		getch();
		remove_data();
		return main();
		}
		else
			cout << "\tWrong Password";
		}
		else
			cout << "\n\tUserName Not Exists";
}
// Main Menu Function
int MainMenu(){
	HANDLE hstdout;
	hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	_color("f","0");
	system("CLS");
	time_t current=time(0);
	SetConsoleTitle("Main Menu");
	cout << "\n\n\t\t";
	SetConsoleTextAttribute( hstdout , 759);
	cout << " Date_Time : " << ctime(&current) << ' ';
	SetConsoleTextAttribute( hstdout , 240);
	cout << "\n\n\t\t******** TYPING TUTOR [MAIN MENU] ********\n\n\t\t";
	SetConsoleTextAttribute( hstdout , 249);
	cout << "1. Lets Start\n\t\t";
	cout << "2. Information Panel\n\t\t";
	cout << "3. View Records\n\t\t";
	cout << "4. Delete Record\n\t\t";
	cout << "5. Quit Typing Tutor\n\t\t";
	SetConsoleTextAttribute( hstdout , 242);
	cout << "\n\n\t\tYour Choice : ";
	char choice;
	cin >> choice;
	cin.ignore();
	_color("f","0");
	if (choice=='2'){
		system("CLS");
		information();
	}
	else if (choice=='3'){
		view();
	}
	else if (choice=='4'){
		SetConsoleTitle("Delete Record");
		again_password1 :
		exist_flag=false;
		system("CLS");
		binary_file.seekg(0,ios::end);
		size=binary_file.tellg();
		if (size!=0){
			cout << "\n\n\t";
			Input(name);
			pass_call_from_fun_flag=true;
			Remove(use_name);
			if (!exist_flag){
				system("CLS");
				char abc;
				cout << "\n\n\tNo User Found of name \'" << real_name << "\'\n\n\t";
				cout << "Press '1' for again\n\n\tAny Other key for Main Menu\n\n\t";
				abc=getch();
				if (abc=='1')
				goto again_password1;
				else
				MainMenu();
			}
			if (!pass_flag){
				system("CLS");
				char bcd;
				cout << "\n\n\t!!! Wrong Password !!!\n\n\t";
				cout << "Press '1' for again\n\n\tAny Other key for Main Menu\n\n\t";
				bcd=getch();
				if (bcd=='1')
				goto again_password1;
				else
				MainMenu();
			}
		}
		else{
			cout << "\n\n\tNo Accounts for Deletions";
			cout << "\n\n\tPress any key for Main Menu ........";
			getch();
			MainMenu();
		}
	}
	else if (choice=='1');
	else if (choice=='5')
		close_program();
	else{
		cout << "\n\n\t\tWrong Input\n\n\t\t";
		system("PAUSE");
		MainMenu();
	}
}
// View Records (Name, HidePass, Passed Stages)
void view(){
	SetConsoleTitle("View Records");
	binary_file.seekg(0,ios::end);
	size=binary_file.tellg();
	binary_file.seekg(0,ios::beg);
	if (size!=0){
		system("CLS");
		int number=1;
		cout << '\n';
		while (size>binary_file.tellg()){
			cout << '\n' << '\t' << "User No." << number << '\t';
			binary_file.read((char*)check_name,name_size);	
			cout << check_name << '\n' << '\t' << '\t' << '\t';
			binary_file.read((char*)check_pass,pass_size);
			hide_passcode(check_pass);
			cout << '\n' << '\t' << '\t' << '\t';
			level_viewer();
			cout << '\n';
			number++;
	}
	}
	else{
		system("CLS");
		cout << "\n\n\tNo Records Found\n";
	}
	cout << "\n\tPress any key for Main Menu ........";
	getch();
	MainMenu();
}
// Give ForeGround & BackGround Color
void _color(string value1,string value2){
	if (value1.length()==1 and value2.length()==1){
		string value="color "+value1+value2;
		system(value.c_str());
	}
}
// Typing Words & Sentences Function
int Typing(string a){
	bool mistake_flag;
	_color("f","0");
	if (flag_word)
		cout << a << "\n\t\t\t";
	else if (flag_sentence)
		cout << a << "\n\t";
	count_plus=count_plus+a.length();
	char *check;
	check=new char[a.length()];
	for (int i=0;i<a.length();i++){
		mistake_flag=true;
		check_word :
		check[i]=getche();
		if (int(check[i])==8){
			if (i>0){
				cout << ' ' << '\b';
		i--;
			}
		goto check_word;
		}
		else if (check[i]!=a[i]){
			_color("c","0");
			cout << '\b';
			delay (10);
			cout << ' ' << '\b';
		if (mistake_flag)
			mistake++;
		mistake_flag=false;
		goto check_word;
	}
	else
		_color("f","0");
	}
	delete []check;
}
// Prectice Mode Function
int practice(){
	time_t t1,t2;
	mistake=0;
	count_plus=0;
	ifstream in("A-ONE.BCSF16A508");
	system("CLS");
	cout << "\n\n\t\t1. Practice on Words\n\t\t";
	cout << "2. Practice on Sentences\n";
	cout << "\n\t\t Any other key to Back\n\n\t\t";
	int count;
	string *word;
	cout << "Your Choice : ";
	int choice;
	string check1;
	cin >> choice;
	if (choice==1){
		while(!in.eof()){
			in >> check1;
			if (check1=="lesson_words_start:"){
				in >> count;
				flag_word=true;
				break;
			}
		}
	}
	else if (choice==2){
		while(!in.eof()){
			in >> check1;
			if (check1=="lesson_sentences_start:"){
				in >> count;
				flag_sentence=true;
				break;
			}
		}
	}
	else{
		system("CLS");
		realname_and_hidepass();
		Remove_Practice_Logout();
	}
	word=new string[count];
	for (int i=0;i<count;i++){
		if (flag_word)
			in >> word[i];
		else if(flag_sentence)
			getline(in,word[i]);
	}	
	int run_size,get;
	if (flag_word)
		cout << "\n\t\tHow many Words do you want to Type : ";
	else if (flag_sentence)
		cout << "\n\t\tHow many Sentences do you want to Type : ";
	cin >> run_size;
	system("CLS");
	cout << "\n\n\tPress any key to Continue and times Start .........";
	getch();
	time(&t1);
	for (int i=0;i<run_size;i++){
		if (flag_word){
			system("CLS");
			cout << "\n\n\n\t\t\t";
			get=rand()%count;
			Typing(word[get]);	
		}
		else if(flag_sentence){
			system("CLS");
			cout << "\n\n\t";
			get=rand()%count;
			Typing(word[get]);
		}
	system("CLS");	
	}
	time(&t2);
	delete []word;
	in.close();
	loading();
	system("CLS");
	if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 90)
		cout << "\n\n\tExcellent Accuracy *****";
	else if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 70)
		cout << "\n\n\tGood Accuracy ****";
	else if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 60)
		cout << "\n\n\tNormal Accyracy ***";
	else
		cout << "\n\n\tBad Accuracy *";
	cout << "\n\n\tYour Mistakes are : " << mistake << '\n';
	cout << "\tYour accuracy is  : " << (float)((count_plus-(float)mistake)/count_plus)*100 << '%' << '\n' << '\t';
	cout << "You have type " << count_plus << " characters in " << t2-t1 << " Seconds" << '\n' << '\n' << '\t';
	cout << "Press any key to Continue.....";
	flag_word=false,flag_sentence=false;
	getch();
	system("CLS");
	cout << "\n\n";
}
// User Front Page and Options
int Remove_Practice_Logout(){
	cout << "\n\n\t\t0. Remove My Account";
	cout << "\n\t\t1. Familier with Keyboard";
	cout << "\n\t\t2. Practice Mode";
	cout << "\n\t\t3. Start Lessons";
	cout << "\n\t\t4. Check Typing Speed in WPM";
	cout << "\n\t\t5. Sign Out\n\n\t\tYour Choice : ";
	int choice;
	cin >> choice;
	if (choice==0){
		pass_call_from_main_flag=true;
		Remove(use_name);
	}
	else if (choice==1){
		system("CLS");
		Nearby :
		cout << "\n\n\t\tQ    W    E    R    T    Y    U    I    O    P";
		cout << "\n\n\t\tA    S    D    F    G    H     J    K    L    ;";
		cout << "\n\n\t\t  Z    X    C    V    B    N    M    ,    .\n\n\n\t";
		system("PAUSE");
		system("CLS");
		cout << "\n\n\t1. Upper-Row Practice";
		cout << "\n\t2. Home-Row Practice";
		cout << "\n\t3. Bottom_Row Practice";
		cout << "\n\n\tAny Other key to User Menu";
		cout << "\n\n\n\tChoice : ";
		char Key_choice;
		cin >> Key_choice;
		string row1,row2,row3,use_row;
		row1="qwertyuiop";
		row2="asdfghjkl;";
		row3="zxcvbnm,.";
		int  run_key,size1,a;
		if (Key_choice=='1'){
			use_row=row1;
			size1=10;
		}
		else if (Key_choice=='2'){
			use_row=row2;
			size1=10;
		}
		else if (Key_choice=='3'){
			use_row=row3;
			size1=9;	
		}
		else{
		system("CLS");
		cout << "\n\n";
		realname_and_hidepass();
		Remove_Practice_Logout();
		}
		system("CLS");
		cout << "\n\n\tHow many Times do you want to Practice : ";
		cin >> run_key;
		char *show;
		int value;
		string work;
		for (int i=0;i<run_key;i++){
			show=new char[4];
			for (int j=0;j<4;j++){
				value=rand()%size1;
				show[j]=use_row[value];
			}
			system("CLS");
			work=string(show);
			delete []show;
			cout << "\n\n\n\n\t\t" << work << "\n\n\t\t";
			Typing(work);
		}
		system("CLS");
		cout << "\n\n\tCompleted......\n\n\t";
		system("pause");
		system("CLS");
		goto Nearby;
	}
	else if (choice==2)
		practice();
	else if (choice==3){
		lesson_reader();
	}
	else if (choice==5){
		remove_data();
		return main();
	}
	else if (choice==4)
		check_WPM();
	else{
		cout << "\n\n\tWrong Input\n\n\t";
		system("PAUSE");
		system("CLS");
		realname_and_hidepass();
		Remove_Practice_Logout();
	}
}
// Make Password ****	
void hide_passcode(string hide_pass){	
	int p_size=hide_pass.length();
	float run((float)p_size/2.5);
	if (hide_pass!="0"){
		for (int i=0;i<p_size;i++){
			if (i<=p_size-(int)run-1)
				cout << '*';		
			else
				cout << hide_pass[i];
		}
	}
	else
		cout << "No Password Protection";
}
// Show User Name and Their Password in Hidden Form
void realname_and_hidepass(){
		cout << "\n\t\tName     : " << real_name;
		cout << "\n\t\tPassword : ";
		hide_passcode(check_use_pass);
		cout << '\n' << '\t';
}
// Remove all Pointers & more
void remove_data(){
	binary_file.close();
	pass_flag=false;
	flag_word=false,flag_sentence=false,show_once_flag=false;
	pass_call_from_fun_flag=false,pass_call_from_main_flag=false;
	mistake=0,count_plus=0;
	delete []real_name;
	delete []name;
	delete []check_name;
	delete []pass;
	delete []check_pass;
}
// Put New Scores in Binary	
void put_levels(){
	binary_file.write((char*)&level_count,sizeof(int));
	for (int i=0;i<5;i++)
		binary_file.write((char*)&level[i],sizeof(int));
}
// Get Levels From Binary
void get_levels(){
	binary_file.read((char*)&level_count,sizeof(int));
	for (int i=0;i<5;i++)
		binary_file.read((char*)&level[i],sizeof(int));
}
// Function for Show Levels
void level_viewer(){
	get_levels();
	if (level_count==0)
		cout << "Pass No Stage";
	else{
		cout << "Passed " << level_count << " Stage";
		if (level_count>1)
			cout << 's' ;
		cout << '\t' << '[';
		if (level[0]!=0){
			cout << level[0] << ',' ;
		if (level[1]!=0){
			cout << level[1] << ',';
		if (level[2]!=0){
			cout << level[2] << ',';
		if (level[3]!=0){
			cout << level[3] << ',' ;
		if (level[4]!=0){
			cout << level[4] << ',' ;
		}
		}
		}
		}
		}
		cout << '\b' << ']';
	}
}
// Lesson Typing Function
int Lessons_Typing(string a){
	HANDLE hstdout;
	hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	bool mistake_flag=false;
//	_color("f","0");
	char *check;
	a=a+" ";
	count_plus=count_plus+a.length();
	check=new char[a.length()];
	for (int i=0;i<a.length();i++){
	mistake_flag=true;
	SetConsoleTextAttribute( hstdout , 240);
	check_word :
	check[i]=getche();
	if (int(check[i])==13){
		if (check[i-1]=='.'){
			check[i]=' ';
			cout << '\n' << '\t';
		}
		else{
		//	cin.ignore();
			cout << ' ' << '\b';
			goto check_word;
		}
	}
	else if (int(check[i])==32 && i==0)
		goto check_word;
	if (int(check[i])==8){
		if (i>0){
			cout << ' ' << '\b';
			i--;
	}
	else
		cout  << ' ';
	goto check_word;
	}
	else if(int(check[i])==32){
		break;
	}
	else if (check[i]!=a[i]){
//		_color("c","0");
//		cout << '\b' << ' ' << '\b';
//		_color("f","0");
		SetConsoleTextAttribute( hstdout , 252);
		cout << '\b' << check[i];
	if (mistake_flag){
		mistake++;
		mistake_flag=false;
	}
//	goto check_word;
	}
	}
	delete []check;
	accuracy=(float)((count_plus-(float)mistake)/count_plus)*100;
}
// Read Lessons From A-ONE.BCSF16A508 File
void lesson_reader(){
	HANDLE hstdout;
	hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	time_t t1,t2;
	time_t end;
	mistake=0;
	count_plus=0;
	fstream lesson_file;
	int score;
	system("CLS");
	cout << "\n\n\t1. Lesson No.1\t\t[ KnockOut Score : " << level[0] << ']';
	cout << "\n\t2. Lesson No.2\t\t[ KnockOut Score : " << level[1] << ']';
	cout << "\n\t3. Lesson No.3\t\t[ KnockOut Score : " << level[2] << ']';
	cout << "\n\t4. Lesson No.4\t\t[ KnockOut Score : " << level[3] << ']';
	cout << "\n\t5. Lesson No.5\t\t[ KnockOut Score : " << level[4] << ']';
	cout << "\n\n\n\t6. Start Knockout Typing From where LEFT   ";
	cout << '[' << level[0] << ',' << level[1] << ','  << level[2] << ',' << level[3] << ',' << level[4] << ']';
	cout << "\n\n\tAny Other key to Back";
	cout << "\n\n\tChoice : ";
	stringstream str;
	int lesson_choice;
	bool knock_out=false;
	string lesson_number,check,line,word;
	cin >> lesson_choice;
	if (lesson_choice==6){
		if (level_count!=0){
			str << level_count+1;
			str >> lesson_number;
			knock_out=true;
		}
		else{
			lesson_number="1";
			knock_out=true;
		}
	}
	else if (lesson_choice<=5 && lesson_choice>=1){
		str << lesson_choice;
		str >> lesson_number;
	}
	else{
		system("CLS");
		realname_and_hidepass();
		Remove_Practice_Logout();
	}
	lesson_number="Lesson_No."+lesson_number+":";
	system("CLS");
    cout << "\n\n\tPassing Conditions :\n\n\tYou have to Type in One Minute.";
	cout << "\n\tSpeed (WPM) should be Greater than 25";
	cout << "\n\tAccuracy should be Greater than 70%\n\n\t";
	cout << "Press any to start 60 seconds time and continue......";
    getch();
    system("CLS");
    end=time(NULL)+60;
	lesson_file.open("A-ONE.BCSF16A508",ios::in);
	bool lesson_flag=false;
	system("CLS");
	while (!lesson_file.eof()){
		lesson_file >> check;
		if (check==lesson_number)
			lesson_flag=true;
		if (lesson_flag){
			while (lesson_flag){
				getline(lesson_file,line);
				if (line!="-1")
					cout << '\n' << '\t' << line ;
				else
					lesson_flag=false;
			}
		}
	}
	cout << '\n' << '\n' << '\t';
	lesson_file.close();
	lesson_file.open("A-ONE.BCSF16A508",ios::in);
	int word_count_1=0;
	while (!lesson_file.eof()){
		lesson_file >> check;
		if (check==lesson_number)
			lesson_flag=true;
		if (lesson_flag){
			time(&t1);
			while (lesson_flag && time(NULL)<end){
				lesson_file >> word;
				word_count_1++;
				if (word!="-1")
					Lessons_Typing(word);
				else
					lesson_flag=false;
			}
			time(&t2);
		}
	}
	system("CLS");
	loading();
	cout << "\n\n\t";
	system("Pause");
	int level_score;
	level_score=((count_plus-mistake)*100/count_plus)/10;
	system("CLS");
	
	if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 90)
		cout << "\n\n\tExcellent Performance in Accuracy *****";
	else if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 70)
		cout << "\n\n\tGood Performance in Accuracy ****";
	else if ((float)((count_plus-(float)mistake)/count_plus)*100 >= 60)
		cout << "\n\n\tNormal Performance in Accuracy ***";
	else
		cout << "\n\n\tBad Performance in Accuracy *";
		SetConsoleTextAttribute( hstdout , 253);
	cout << "\n\n\tYour Mistakes are : " << mistake << '\n';
	cout << "\tYour accuracy is  : " << (float)((count_plus-(float)mistake)/count_plus)*100 << '%' << '\n' << '\t';
	cout << "Speed is " << word_count_1 << " WPM\n\t";
	cout << "You have type " << count_plus << " characters in 60 Seconds" << '\n' << '\n' << '\t';
	SetConsoleTextAttribute( hstdout , 240);
	if (knock_out){	
	cout << "Old Knockout Score (Accuracy) = " << level[level_count] << '\n' << '\t';
	cout << "New Knockout Score (Accuracy) = " << level_score << '\n' << '\n' << '\t';
	if (level_score>=7 && word_count_1>25){
	level_1[level_count_1]=level_score;
	level_count_1++;
	cout << "Passing Condition are :\n\n\tWPM   = Greater than 25\n\t";
	cout << "Score = Greater than 7\n\n\t";
	cout << '\n' << '\t';
	SetConsoleTextAttribute( hstdout , 416);
	cout << "!!!Conratulation !!!";
	SetConsoleTextAttribute( hstdout , 240);
	cout << '\n' << '\t';
	SetConsoleTextAttribute( hstdout , 416);
	cout << "Status : PASS";
	put_scores(use_name);
	}
	else{
		cout << "Passing Condition are :\n\n\tWPM   = Greater than 25\n\t";
		cout << "Score = Greater than 7\n\n\t";
		SetConsoleTextAttribute( hstdout , 463);
		cout << "Status : FAIL" ;
	}
	}
	else
		cout << "Score = " << level_score;
	SetConsoleTextAttribute( hstdout , 240);
	cout << '\n' << '\n' << '\t';
	cout << "Press Any key to Continue .....";
	getch();
	system("CLS");
	_color("f","0");
	cout << "\n\n";
}
// Exchange Scores for Editing
void Exchange(){
	level_count_1=level_count;
	for (int i=0;i<5;i++)
		level_1[i]=level[i];
}
// Put Scores corresponding to name
int put_scores(string a){
	binary_file.seekg(0,ios::end);	// Put Pointer in last
	size=binary_file.tellg();		// Get a file size
	binary_file.seekg(0,ios::beg);	// Put Pointer in Beginning
	fstream binary_file2;
	binary_file2.open("temp.bin",ios::binary|ios::out);
	char *check_name1,*check_pass1;
	while (size>binary_file.tellg()){
		check_name1=new char[name_size];
		check_pass1=new char[pass_size];
		binary_file.read((char*)check_name1,name_size);	// Get Data of 36 bytes from binary file
		binary_file.read((char*)check_pass1,pass_size);
		get_levels();
		check_use_name=string(check_name1);	// TypeCasting a 36 byte char into string to compare with input name
		if (a==check_use_name)	// Compare both strings if DONE then flag becomes true and finish the loop
		{
			binary_file2.write((char*)check_name1,name_size);
			binary_file2.write((char*)check_pass1,pass_size);
			binary_file2.write((char*)&level_count_1,sizeof(int));
			for (int i=0;i<5;i++)
			binary_file2.write((char*)&level_1[i],sizeof(int));
		}
		else{
			binary_file2.write((char*)check_name1,name_size);
			binary_file2.write((char*)check_pass1,pass_size);
			binary_file2.write((char*)&level_count,sizeof(int));
			for (int i=0;i<5;i++)
			binary_file2.write((char*)&level[i],sizeof(int));
		}
		delete []check_name1;
		delete []check_pass1;
	}
	binary_file.close();
	binary_file2.close();
	remove("Records_Binary.bin");
	rename("temp.bin","Records_Binary.bin");
	binary_file.open("Records_Binary.bin",ios::binary|ios::in|ios::out|ios::app);
	if(isExist(use_name));
}
// Starting Page at First Time
void front_page(){
	_color("e","0");
	SetConsoleTitle("WELCOME TO TYPING TUTOR");
	string main_heading="PROJECT TITLE : TYPING TUT0R";
	cout << "\n\n\t   ";
	main_heading.length();
	for (int i=0;i<main_heading.length();i++){
		cout << main_heading[i];
		delay(3);
	}
	cout << "\n\n\t";
	string line1=" _________________________________________________________";
	string line2="|                                                         |";
	string line3="|                                                         |";
	string line4="|                                                         |";
	string line5="|                                                         |";
	string line6="|_________________________________________________________|";
	for (int i=0;i<line1.length();i++){
		cout << line1[i];
		delay(1);
	}
	cout << "\n\t" << line2;
	delay(3);
	cout << "\n\t" << line3;
	delay(3);
	cout << "\n\t" << line4;
	delay(3);
	cout << "\n\t" << line5;
	cout << "\n\t";
	for (int i=0;i<line6.length();i++){
		cout << line6[i];
		delay(1);
	}
	system("CLS");
	cout << "\n\n\t   " << main_heading;
	string name="Abdullah Zafar";
	string Roll="BCSF16A 5O8";
	string Wrong_sub="Introduction to Programmi";
	string Subject="Programming Fundamentals";
	cout << "\n\n\n\n\t    Name           : ";
	for (int i=0;i<name.length();i++){
		cout << name[i];
		delay(2);
	}
	cout << "\n\t    Roll Number    : ";
	for (int i=0;i<Roll.length();i++){
		cout << Roll[i];
		delay(2);
	}
	cout << "\n\t    Subject        : ";
	for (int i=0;i<Wrong_sub.length();i++){
		cout << Wrong_sub[i];
		delay(2);
	}
	for (int i=0;i<Wrong_sub.length();i++){
		cout << '\b' << ' ' << '\b';
		delay (1);
	}
	for (int i=0;i<Subject.length();i++){
		cout << Subject[i];
		delay(2);
	}
	system("CLS");
	cout << "\n\n\t   " << main_heading;
	cout << "\n\n\t _________________________________________________________";
	cout << "\n\t|                                                         |";
	cout << "\n\t|   Name           : Abdullah Zafar                       |";
	cout << "\n\t|   Roll Number    : BCSF16A 508                          |";
	cout << "\n\t|   Subject        : Programming Fundamentals             |";
	cout << "\n\t|_________________________________________________________|";
	cout << "\n\n\t";
	string uni_1="     Punjab University Co";
	string uni_2="PUNJAB UNIVERSITY COLLEGE OF INFORMATION & TECHNOLOGY (PUCIT)";
	for (int i=0;i<uni_1.length();i++){
		cout << uni_1[i];
		delay(2);
	}
	for (int i=0;i<uni_1.length();i++){
		cout << '\b' << ' '  << '\b';
		delay(1);
	}
	for (int i=0;i<uni_2.length();i++){
		cout << uni_2[i];
		delay(2);
	}
	string sir_name_2="PROFESSOR ABDUL_MATEEN";
	cout << "\n\n\n\t\t\t    Submitted To : ";
	for (int i=0;i<sir_name_2.length();i++){
		cout << sir_name_2[i];
		delay(3);
	}
	cout <<"\n\n\n\n\t";
	_color("b","0");
	system("PAUSE");
}
// Function to Finds the Speed in WPM (Words Per Minute)
int check_WPM(){
	fstream lesson_file;
	string check,line,word;
	bool lesson_flag=false;
	time_t end;
	system("CLS");
	cout << "\n\n\t1. One Minute (60 Seconds)\n\t2. Two Minutes (120 Seconds)\n\n\tAny other key to Back\n\n\tEnter Choice : ";
	int seconds,t_choice;
	cin >> t_choice;
	if (t_choice==1)
	seconds=60;
	else if (t_choice==2)
	seconds=120;
	else{
		system("CLS");
		realname_and_hidepass();
		Remove_Practice_Logout();
	}
    system("CLS");
    cout << "\n\n\tPress any to start " << seconds << " seconds time and continue......";
    getch();
    system("CLS");
    end=time(NULL)+seconds;
    lesson_file.open("A-ONE.BCSF16A508",ios::in);
    while (!lesson_file.eof()){
		lesson_file >> check;
		if (check=="WPM_Typing_Lesson:")
			lesson_flag=true;
		if (lesson_flag){
			while (lesson_flag){
				getline(lesson_file,line);
				if (line!="-1")
					cout << '\n' << '\t' << line ;
				else
					lesson_flag=false;
			}
		}
	}
	cout << '\n' << '\n' << '\t';
	lesson_file.close();
	lesson_file.open("A-ONE.BCSF16A508",ios::in);
	int word_count=0;
	while (!lesson_file.eof()){
		lesson_file >> check;
		if (check=="WPM_Typing_Lesson:")
			lesson_flag=true;
		if (lesson_flag){
			while (lesson_flag && time(NULL)<end){
				lesson_file >> word;
				word_count++;
				if (word!="-1")
					Lessons_Typing(word);
				else
					lesson_flag=false;
			}
		}
	}
	loading();
	system("CLS");
	cout << "\n\n\tSpeed is " << (word_count*60)/seconds << " Words Per Minute (WPM)";
	cout << "\n\tMistakes = " << mistake;
	cout << "\n\tAccuracy is " << accuracy << "%";
	cout << "\n\n\t";
	system("PAUSE");
	system("CLS");
	cout << "\n\n";
}
// Make Program Effective (Useless) with loading Function
void loading(){
	string dot="......";
	for (int i=0;i<3;i++){
		system("CLS");
		cout << "\n\tWait a While Loading Your Result";
		for (int i=0;i<dot.length();i++){
			cout << dot[i];
			delay(20);
		}
	}
}
// Options of Quiting the Program
void close_program(){
	SetConsoleTitle("Quit Options");
	_color("c","7");
	system("CLS");
	cout << "\n\n\t1. Close Program Only\n\t2. Close Program and Shutdown Computer";
	cout << "\n\t3. Close Program and Restart Computer\n\n\tAny other key for MainMenu\n\n\t Choice : ";
	char close_choice;
	cin >> close_choice;
	if (close_choice=='1'){
		_color("a","0");
		_end();
		exit(0);
	}
	else if (close_choice=='2'){
		_color("a","0");
		_end();
		system("c:\\windows\\system32\\shutdown /s /t 2");
		exit(0);
	}
	else if (close_choice=='3'){
		_color("a","0");
		_end();
		system("c:\\windows\\system32\\shutdown /r /t 2");
		exit(0);
	}
	else
		MainMenu();
}
// Information Panel View and Options
void information(){
	fstream info_panel;
	string line;
	char button;
	SetConsoleTitle("Information Panel");
	system("CLS");
	char info;
	cout << "\n\n\t******** TYPING TUTOR INFORMATION PANEL ********";
	cout << "\n\n\tPress 1. Features of this \'TYPING TUTOR\'\n\t";
	cout << "Press 2. Fingers Placement\n\t";
	cout << "Press 3. Standard KeyBoard Figure\n\t";
	cout << "Press 4. Register your FeedBack related to Typing Tutor\n\n";
	cout << "\t Press any Other key for Main Menu\n\n\n";
	info=getch();
	cout << "\n\t";
	if (info=='1'){
		_info_1 :
		system("CLS");
		cout << "Use Back_Space for back\n\n";
		info_panel.open("A-ONE.BCSF16A508",ios::in);
		while(!info_panel.eof()){
			getline(info_panel,line);
			if (line=="Features_TT:"){
				getline(info_panel,line);
				while (line!="-1"){
					cout << line << '\n';
					getline(info_panel,line);
			}
		}
		}
		info_panel.close();
		button=getch();
		if (int(button)==8)
			information();
		else
			goto _info_1;
	}
	else if (info=='2'){
		info_panel.open("A-ONE.BCSF16A508",ios::in);
		while(!info_panel.eof()){
			getline(info_panel,line);
			if (line=="Finger Placements_TT:")
				for (int i=0;i<3;i++){
					system("CLS");
					getline(info_panel,line);
				while (line!="-1"){
					cout << line << '\n';
					getline(info_panel,line);
			}
			cout << "\n\n\n ";
			system("PAUSE");
		}
		}
		info_panel.close();
		information();
	}
	else if (info=='3'){
		_info_3 :
		system("CLS");
		cout << "Use Back_Space for Back\n";
		cout << "\n\n\n\n\t\tQ    W    E    R    T    Y    U    I    O    P";
		cout << "\n\n\t\tA    S    D    F    G    H     J    K    L    ;";
		cout << "\n\n\t\t  Z    X    C    V    B    N    M    ,    .\n\n\n";
		button=getch();
		if (int(button)==8)
			information();
		else
			goto _info_3;
	}
	else if (info=='4'){
		system("CLS");
		cout << "\n\n\t";
		system("pause");
		system("CLS");
		ofstream out("FeedBack.txt",ios::app);
		string complainer,complain;
		cout << "\n\n\tName : ";
		getline(cin,complainer);
		out << complainer << " : ";
		cout << "\n\tFeedBack : ";
		getline(cin,complain);
		out << complain << '\n';
		out.close();
		system("CLS");
		cout << "\n\n\tYour FeedBack Successfly Sent to FeedBack.txt in Same Directory\n\n\t";
		system("pause");
		information();
	}
	else
	MainMenu();
}
// Program Quiting
void _end(){
	string end="Thank You For Using Typing Tutor";
	cout << "\n\n\n\n\t\t************************************\n\n\t\t  ";
	for (int i=0;i<end.length();i++){
		cout << end[i];
		delay(5);
	}
	cout << "\n\n\t\t************************************";
	delay(30);
}

// ------------------------------------------------------------- END
// SETTING _____ OK
// INDENTATION ______OK
