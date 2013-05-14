#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include "hid.h"

using namespace std;

char buffer_out[64];
char buffer_in[64];
#pragma once

namespace George {

	

#pragma endregion
	public: void tobuffer(int val)
	{
		char help[4];
		if (val >= 1 && val <= 9)
	{
		buffer_out[1] = '0';
		buffer_out[2] = '0';
		itoa (val, help, 10);
		buffer_out[3] = help[0];
	}

	else if (val >= 10 && val <= 99)
	{
		buffer_out[1] = '0';
		itoa (val, help, 10);
		buffer_out[2] = help[0];
		buffer_out[3] = help[1];
	}

	else if (val >= 100 && val <= 255)
	{
		itoa (val, help, 10);
		buffer_out[1] = help[0];
		buffer_out[2] = help[1];
		buffer_out[3] = help[2];
	}
	}
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
			{
				for (int i=0;i<64;i++)
				{
					buffer_out[i]=0;	
				   buffer_in[i]=0;
				}
				
			}
	private: System::Void ScrollR1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e)
			{
	
				int valueR1 = ScrollR1->Value;
				labelR1->Text = System::Convert::ToString(ScrollR1->Value);
				int c=valueR1;
				tobuffer(c);
				buffer_out[4]='0';
				buffer_out[5]='1';
					FindTheHID();
				
					WriteOutputReport(buffer_out);
					
					//ReadInputReport(buffer_in);
					//WriteOutputReport(buffer_out);
			}
	private: System::Void ScrollG1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e)
			{
				int valueG1 = ScrollG1->Value;
				labelG1->Text = System::Convert::ToString(ScrollG1->Value);
				int c=valueG1;
				tobuffer(c);
				buffer_out[4]='0';
				buffer_out[5]='2';
				FindTheHID();
				
					WriteOutputReport(buffer_out);
			}
	private: System::Void ScrollB1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e)
			{
				int valueB1 = ScrollB1->Value;
				labelB1->Text = System::Convert::ToString(ScrollB1->Value);
				int c=valueB1;
				tobuffer(c);
				buffer_out[4]='0';
				buffer_out[5]='3';
				FindTheHID();
				
					WriteOutputReport(buffer_out);
			}
	