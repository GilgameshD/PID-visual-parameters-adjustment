#include "communication.h"
#include <QString>
#include <QtWidgets/QMainWindow>

Communication::Communication()
{
    // COM4
    com = new Win_QextSerialPort("COM4",QextSerialBase::EventDriven);

    dataLength = 33;
    data = new char[5];
    data = "00000";
}

bool Communication::openPort()
{
    isOpened = com->open(QIODevice::ReadWrite);
    if(isOpened)
    {
        // some parameters , never mind~~
        com->setBaudRate(BAUD115200);
        com->setDataBits(DATA_8);
        com->setParity(PAR_NONE);
        com->setStopBits(STOP_1);
        com->setFlowControl(FLOW_OFF);
        com->setTimeout(500);
        return isOpened;
    }
    else
        return isOpened;
}

void Communication::sendData()
{
	if(isOpened)
	{
			/* signal of ending */
			data[31] = 0x0D;
			data[32] = 0x0A;

			com->write(data,33);   //can't send unsigned char
    }
}

void Communication::receiveData()
{
    // init the data
    for(int i = 0;i < 3;++i)
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
			if (!(receive[1] == 0x0d && receive[2] == 0x0a))
				return;
	}
}

QString Communication::returnData()
{
    return QString((QLatin1String)data);
}

void Communication::stop()
{
	com->close();
}
