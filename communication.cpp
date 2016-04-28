#include "communication.h"
#include <QString>
#include <QtWidgets/QMainWindow>

Communication::Communication(QMainWindow *parent)
{
	/* 定义串口4为使用串口 */
    com = new Win_QextSerialPort("COM4",QextSerialBase::EventDriven);

    //myTestWindow = new MyTestWindow;
    //myTestWindow->show();
}

/* 打开串口的函数 */
bool Communication::OpenPort()
{
    isOpened = com->open(QIODevice::ReadWrite);//双向口
    if(isOpened)                               //检查是否成功打开串口
    {
        com->setBaudRate(BAUD115200);          //波特率 115200
        com->setDataBits(DATA_8);                     //数据位 8
        com->setParity(PAR_NONE);                   //校验位 无
        com->setStopBits(STOP_1);                     //停止位 1
        com->setFlowControl(FLOW_OFF);          //数据流控制 无
        com->setTimeout(500);                           //延时 500ms
        return isOpened;
    }
    else
        return isOpened;
}

/* 发送数据的函数 */
void Communication::sendData()
{
	if(isOpened)
	{
			/* signal of ending */
			data[31] = 0x0D;
			data[32] = 0x0A;
		
			com->write(data,33);   //can't send unsigned char

            //if(myTestWindow->returnflag())
            //	myTestWindow->mySetTextSend(data);
    }
}

/* 接受数据的函数 */
void Communication::ReceiveData()
{
	for(int i = 0;i < 3;++i)      //初始化接受数据数组
		receive[i] = 0x00;

	char tmp;
	if(isOpened) 
	{
			while(!(receive[1] == 0x0d && receive[2] == 0x0a) && com->read(&tmp, 1))
			{
				receive[0] = receive[1];
				receive[1] = receive[2];
				receive[2] = tmp;
			}
            //myTestWindow->mySetTextReceive(receive);
			if (!(receive[1] == 0x0d && receive[2] == 0x0a))
				return;
	}
}

/* 关闭串口的函数 */
void Communication::stop()
{
	com->close();
}
