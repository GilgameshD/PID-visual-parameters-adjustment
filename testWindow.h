#include "ui_testWindow.h"

class MyTestWindow : public QMainWindow, Ui::TestWindow
{
    Q_OBJECT
public:
	MyTestWindow();
	void mySetTextSend(char *data);
	void mySetTextReceive(char *data);
	char *returnChar(int *data, int n);
	bool flag;
	int read_bit(const char &c, const int &pos);
	bool returnflag();
	int receiveFirstData[8];
private:
	char *result1;
	int number;
	int number2;
};
