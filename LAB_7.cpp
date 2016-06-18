// ConsoleApplication33.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <condition_variable>



bool ready = false;
std::mutex m_x, m_y;
std::condition_variable c_v;
void f1()
{
	int k = 0;
	std::lock_guard<std::mutex> lock(m_x);
	do {
		int r = rand() % 1 + 1;
		for (int i = 0; i < r; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "bbbbb \n" << k;
			k++;
			if (k > 50) 
			{
				ready = true;
				c_v.notify_one();
			}
		}
	} while (k < 100);
}
void f2()
{
	std::unique_lock<std::mutex> lock(m_y);
	c_v.wait(lock);
	if (ready == true) {
		for (int i = 0; i < 100; i++)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "aaaaa \n" << i;
		}
	}
}
int main()
{
	std::thread t1(f1);
	std::thread t2(f2);
	t1.join();
	t2.join();
	system("pause");
}