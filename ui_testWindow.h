/********************************************************************************
** Form generated from reading UI file 'testWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTextEdit *text1;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QTextEdit *text2;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTextEdit *text2_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TestWindow)
    {
        if (TestWindow->objectName().isEmpty())
            TestWindow->setObjectName(QStringLiteral("TestWindow"));
        TestWindow->resize(687, 642);
        centralwidget = new QWidget(TestWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 221, 611));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        text1 = new QTextEdit(groupBox);
        text1->setObjectName(QStringLiteral("text1"));

        gridLayout->addWidget(text1, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(240, 10, 211, 611));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        text2 = new QTextEdit(groupBox_2);
        text2->setObjectName(QStringLiteral("text2"));

        gridLayout_2->addWidget(text2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(460, 10, 211, 611));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        text2_2 = new QTextEdit(groupBox_3);
        text2_2->setObjectName(QStringLiteral("text2_2"));

        gridLayout_3->addWidget(text2_2, 0, 0, 1, 1);

        TestWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TestWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 687, 23));
        TestWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TestWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        TestWindow->setStatusBar(statusbar);

        retranslateUi(TestWindow);

        QMetaObject::connectSlotsByName(TestWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TestWindow)
    {
        TestWindow->setWindowTitle(QApplication::translate("TestWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("TestWindow", "\345\217\221\351\200\201\346\225\260\346\215\256\357\274\232", 0));
        groupBox_2->setTitle(QApplication::translate("TestWindow", "\346\216\245\345\217\227\346\225\260\346\215\2561\357\274\232", 0));
        groupBox_3->setTitle(QApplication::translate("TestWindow", "\346\216\245\345\217\227\346\225\260\346\215\2562\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class TestWindow: public Ui_TestWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
