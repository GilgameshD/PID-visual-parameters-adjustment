#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#include "qextserialbase.h"
#include "win_qextserialport.h"

#include "testWindow.h"        //包含测试文件

class QMainWindow;

class Communication
{

public:
	Communication(QMainWindow *parent = 0);
	bool OpenPort();                                         //打开串口
	void ReceiveData();                                     //接受数据
    void sendData();                                         //发送数据
    void stop();

private:
    Win_QextSerialPort *com; //串口操作

    char data[33];           //发送数据数组
	char receive[3];         //接受数据数组
    bool isOpened;
    //MyTestWindow *myTestWindow; //调试窗口
};

#endif // _COMMUNICATION_H
