#include "testWindow.h"

MyTestWindow::MyTestWindow()
{
	setupUi(this);
	flag = true;
	number = 0;
	number2 = 0;
}

void MyTestWindow::mySetTextReceive(char *data)
{
	/* 显示50行之后刷新 */
	if(number2 == 50)
	{
		text2->clear();
		number2 = 0;
	}
	else
		++number2;

	for(int i = 0;i < 1;++i)
	{
		char tmp[15] = {};
		for(int j = 0;j < 8;j++) 
			tmp[7 - j] = read_bit(data[i], j) + '0'; 
		sprintf(tmp + 8, "(%02x)", (unsigned int)(unsigned char)data[i]);
		text2->append(tmp);
	}
	text2->append("-------------------------");
}

int MyTestWindow::read_bit(const char &c, const int &pos) 
{ 
	char b_mask = 0x01; 
    b_mask = b_mask << pos;
    if((c & b_mask) == b_mask)
		return 1; 
	else 
		return 0;
} 

char* MyTestWindow::returnChar(int *data, int n)
{
	result1 = new char[n];
	for(int i = 0;i < n;++i)
	{
		if(data[i] == 0)
			result1[i] = '0';
		else
			result1[i] = '1';
	}
	return result1;
}

bool MyTestWindow::returnflag()
{
	if(flag)
		return true;
	else
		return false;
}
