// LAB_7_DOP.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
using namespace std;


void proc(void);
void echo(string s);
void alarm(int sec);
mutex mtx;
void proc(void) 
{
	string cmd;
	cin >> cmd;
	if (cmd == "echo")
	{
		string s;
		getline(cin, s);
		thread t(echo, ref(s));
		t.join();
	}
	else if (cmd == "alarm")
	{
		int sec;
		cin >> sec;
		thread t(alarm, ref(sec));
		t.detach();
	}
	return;
}


void echo(string s) 
{
	cout << s << endl;
	return;
}
void alarm(int secs) {
	this_thread::sleep_for(chrono::milliseconds(secs * 1000));
	cout << "\nAlarm!!!" << endl;
	cout.flush();
	return;
}
int main(void)
{
	while (!cin.eof())
		proc();
	return 0;
}