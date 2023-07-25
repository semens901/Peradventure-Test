/********************************************************************************
** Form generated from reading UI file 'Messenger.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGER_H
#define UI_MESSENGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessengerClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *textLabel;
    QLabel *lbl_my_login;
    QListWidget *list_friends;
    QTextBrowser *textBrowser;
    QLineEdit *le_message;
    QPushButton *btn_send;

    void setupUi(QMainWindow *MessengerClass)
    {
        if (MessengerClass->objectName().isEmpty())
            MessengerClass->setObjectName("MessengerClass");
        MessengerClass->resize(537, 265);
        centralWidget = new QWidget(MessengerClass);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setStyleSheet(QString::fromUtf8("/*-----QWidget-----*/\n"
"QWidget\n"
"{\n"
"	background-color: #0f0f0f;\n"
"	color: #fff;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLabel-----*/\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QPushButton-----*/\n"
"QPushButton\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border: 1px solid #d10000;  \n"
"	border-radius: 2px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::hover\n"
"{\n"
"	background-color: #ad0000;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"QPushButton::pressed\n"
"{\n"
"	background-color: #e00000;\n"
"	color: #fff;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QToolButton-----*/\n"
"QToolButton\n"
"{\n"
"	background-color: transparent;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-color: #000000;\n"
"\n"
"}\n"
"\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-radius: 15px"
                        ";\n"
"	border-color: #d10000;\n"
"\n"
"}\n"
"\n"
"\n"
"QToolButton::pressed\n"
"{\n"
"	background-color: #d10000;\n"
"	color: #000000;\n"
"	border-style: solid;\n"
"	border-width: 0px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QLineEdit-----*/\n"
"QLineEdit{\n"
"	background-color: #4d4d4d;\n"
"	color: #fff;\n"
"	font-weight: bold;\n"
"	border-style: solid;\n"
"	border-radius: 5px;\n"
"	padding: 5px;\n"
"\n"
"}\n"
"\n"
"\n"
"/*-----QCheckBox-----*/\n"
"QCheckBox\n"
"{\n"
"	background-color: transparent;\n"
"	color: #b9b9bb;\n"
"	font-weight: bold;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator\n"
"{\n"
"    color: #b1b1b1;\n"
"    background-color: #00111d;\n"
"    border: 1px solid #d10000;\n"
"    width: 12px;\n"
"    height: 12px;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:checked\n"
"{\n"
"    image:url(\"./ressources/check.png\"); /*To replace*/\n"
"	background-color: #d10000;\n"
"    border: 1px solid #d10000;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:unchecked:hover\n"
"{\n"
"    border: 1px solid #ff0000;\n"
""
                        "\n"
"}\n"
"\n"
"\n"
"QCheckBox::disabled\n"
"{\n"
"	color: #656565;\n"
"\n"
"}\n"
"\n"
"\n"
"QCheckBox::indicator:disabled\n"
"{\n"
"	background-color: #656565;\n"
"	color: #656565;\n"
"    border: 1px solid #656565;\n"
"\n"
"}\n"
""));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 10, 520, 246));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        textLabel = new QLabel(layoutWidget);
        textLabel->setObjectName("textLabel");

        gridLayout->addWidget(textLabel, 0, 0, 1, 1);

        lbl_my_login = new QLabel(layoutWidget);
        lbl_my_login->setObjectName("lbl_my_login");

        gridLayout->addWidget(lbl_my_login, 0, 1, 1, 1);

        list_friends = new QListWidget(layoutWidget);
        list_friends->setObjectName("list_friends");

        gridLayout->addWidget(list_friends, 1, 0, 1, 2);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName("textBrowser");

        gridLayout->addWidget(textBrowser, 1, 2, 1, 2);

        le_message = new QLineEdit(layoutWidget);
        le_message->setObjectName("le_message");

        gridLayout->addWidget(le_message, 2, 0, 1, 3);

        btn_send = new QPushButton(layoutWidget);
        btn_send->setObjectName("btn_send");

        gridLayout->addWidget(btn_send, 2, 3, 1, 1);

        MessengerClass->setCentralWidget(centralWidget);

        retranslateUi(MessengerClass);
        QObject::connect(list_friends, SIGNAL(itemClicked(QListWidgetItem*)), MessengerClass, SLOT(user_selected(QListWidgetItem*)));
        QObject::connect(btn_send, SIGNAL(clicked()), MessengerClass, SLOT(send_message()));

        QMetaObject::connectSlotsByName(MessengerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MessengerClass)
    {
        MessengerClass->setWindowTitle(QCoreApplication::translate("MessengerClass", "Messenger", nullptr));
        textLabel->setText(QCoreApplication::translate("MessengerClass", "My Login:", nullptr));
        lbl_my_login->setText(QCoreApplication::translate("MessengerClass", "TextLabel", nullptr));
        btn_send->setText(QCoreApplication::translate("MessengerClass", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MessengerClass: public Ui_MessengerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
