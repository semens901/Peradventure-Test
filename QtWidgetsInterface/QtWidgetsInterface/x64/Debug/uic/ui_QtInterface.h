/********************************************************************************
** Form generated from reading UI file 'QtInterface.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTINTERFACE_H
#define UI_QTINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtInterfaceClass
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *btn_log_in;
    QLabel *label_2;
    QLineEdit *le_password;
    QPushButton *btn_sign_up;
    QLabel *label_3;
    QLineEdit *le_server_ip;
    QLineEdit *le_login;
    QLabel *label;

    void setupUi(QMainWindow *QtInterfaceClass)
    {
        if (QtInterfaceClass->objectName().isEmpty())
            QtInterfaceClass->setObjectName("QtInterfaceClass");
        QtInterfaceClass->resize(290, 294);
        QtInterfaceClass->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(QtInterfaceClass);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(centralWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 411, 321));
        widget->setStyleSheet(QString::fromUtf8("/*-----QWidget-----*/\n"
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
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 251, 239));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        btn_log_in = new QPushButton(layoutWidget);
        btn_log_in->setObjectName("btn_log_in");
        btn_log_in->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(btn_log_in, 6, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        QFont font;
        font.setFamilies({QString::fromUtf8("XO Oriel")});
        font.setPointSize(12);
        font.setBold(true);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        le_password = new QLineEdit(layoutWidget);
        le_password->setObjectName("le_password");
        le_password->setMaxLength(32767);

        gridLayout->addWidget(le_password, 5, 0, 1, 2);

        btn_sign_up = new QPushButton(layoutWidget);
        btn_sign_up->setObjectName("btn_sign_up");

        gridLayout->addWidget(btn_sign_up, 6, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        le_server_ip = new QLineEdit(layoutWidget);
        le_server_ip->setObjectName("le_server_ip");

        gridLayout->addWidget(le_server_ip, 1, 0, 1, 2);

        le_login = new QLineEdit(layoutWidget);
        le_login->setObjectName("le_login");

        gridLayout->addWidget(le_login, 3, 0, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setFont(font);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        QtInterfaceClass->setCentralWidget(centralWidget);

        retranslateUi(QtInterfaceClass);
        QObject::connect(btn_sign_up, SIGNAL(clicked()), QtInterfaceClass, SLOT(sign_up()));
        QObject::connect(btn_log_in, SIGNAL(clicked()), QtInterfaceClass, SLOT(log_in()));

        QMetaObject::connectSlotsByName(QtInterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtInterfaceClass)
    {
        QtInterfaceClass->setWindowTitle(QCoreApplication::translate("QtInterfaceClass", "QtInterface", nullptr));
        btn_log_in->setText(QCoreApplication::translate("QtInterfaceClass", "Log in", nullptr));
        label_2->setText(QCoreApplication::translate("QtInterfaceClass", "Password", nullptr));
#if QT_CONFIG(tooltip)
        le_password->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        le_password->setInputMask(QString());
        le_password->setPlaceholderText(QString());
        btn_sign_up->setText(QCoreApplication::translate("QtInterfaceClass", "Sign up", nullptr));
        label_3->setText(QCoreApplication::translate("QtInterfaceClass", "Server IP", nullptr));
        label->setText(QCoreApplication::translate("QtInterfaceClass", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtInterfaceClass: public Ui_QtInterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTINTERFACE_H
