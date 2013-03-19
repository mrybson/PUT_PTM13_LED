// hid_con.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hid.h"
#include <iostream>
using namespace std;

char buffer_out[64];
char buffer_in[64];
int c=0;
void dioda()
{
	if(c%4==0)
	buffer_out[1]=1;
	if(c%4==1)
	buffer_out[1]=2;
	if(c%4==2)
	buffer_out[1]=8;
	if(c%4==3)
	buffer_out[1]=4;
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Starting George, please wait...\n";
	cout << "Initializing CPU";
	for(int a=0;a<5;a++)
	{
		cout <<".";
		Sleep(100);
	}cout << "[Done]\n";
	cout << "Initializing memory unit";
	for(int a=0;a<5;a++)
	{
		cout <<".";
		Sleep(100);
	}cout << "[Done]\n";
	cout << "Loading pins\n";
	int l=0;
	for(int a=0;a<10;a++)
	{
		cout << "Initiating Pin" << l << " ........[Done]\n";
		Sleep(100);
		l++;
	}cout << "[Done]\n";

	cout << "====================================================================\n";
	cout << "                                GEORGE                                \n";
	cout << "---------------------------------------------------------------------\n";
	cout << "Welcome to George,\n";
	cout << "Switching to monitor mode...\n";
	Sleep(100);
	cout << "Monitor mode : ON\n";
	cout << "George engine status:......[Ready]\n";
	cout << ">>Terminal\n";
	
	for (int i=0;i<64;i++) {
		buffer_out[i]=0;	
		buffer_in[i]=0;
	}
	
	FindTheHID();
	while(1)
	{
		getchar();
		dioda();
		WriteOutputReport(buffer_out);
		c++;
		//ReadInputReport(buffer_in);
		//WriteOutputReport(buffer_out);
		Sleep(100);
	}
	system("pause");

	return 0;
}

