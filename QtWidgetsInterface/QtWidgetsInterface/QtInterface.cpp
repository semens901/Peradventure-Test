#include "QtInterface.h"
#include <QMessageBox>

QtInterface::QtInterface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &QtInterface::readyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    next_block_size = 0;

    ui.le_server_ip->setText(LOCAL_IP);
    ui.le_password->setEchoMode(QLineEdit::Password);
}

QtInterface::~QtInterface()
{

}

void QtInterface::sign_up()
{
    QJsonObject js_outpkg;
    if ((ui.le_login->text() != "") && (ui.le_password->text() != "") && (ui.le_server_ip->text() != ""))
    {
        ip_address = ui.le_server_ip->text();
        socket->connectToHost(ip_address, PORT); //127.0.0.1
        js_outpkg = {
                {TYPE_PACKAGE , SIGN_UP},
                {DATA_FROM_PACKAGE, QJsonObject { { LOGIN, ui.le_login->text()}, {PASSWORD, ui.le_password->text() } } },
                {STATUS_PACKAGE, NULL}
        };

        my_login = ui.le_login->text();

        ui.le_login->clear();
        ui.le_password->clear();

        sendToServer(js_outpkg);
    }
    else if((ui.le_login->text() == "") && (ui.le_password->text() == ""))
    {
        QMessageBox msgBox;
        msgBox.setText("Login or password cannot be empty!");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("IP address cannot be empy!");
        msgBox.exec();
    }
}

void QtInterface::log_in()
{
    QJsonObject js_outpkg;
    if ((ui.le_login->text() != "") && (ui.le_password->text() != "") && (ui.le_server_ip->text() != ""))
    {
        ip_address = ui.le_server_ip->text();
        socket->connectToHost(ip_address, 2000); //127.0.0.1
        js_outpkg = {
                {TYPE_PACKAGE , LOGIN},
                {DATA_FROM_PACKAGE, QJsonObject { { LOGIN, ui.le_login->text()}, {PASSWORD, ui.le_password->text() } } },
                {STATUS_PACKAGE, NULL}
        };

        my_login = ui.le_login->text();

        ui.le_password->clear();

        sendToServer(js_outpkg);
    }
    else if((ui.le_login->text() == "") && (ui.le_password->text() == ""))
    {
        QMessageBox msgBox;
        msgBox.setText("Login or password cannot be empty!");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("IP address cannot be empy!");
        msgBox.exec();
    }
}

void QtInterface::readyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_5);
    if (in.status() == QDataStream::Ok)
    {
        while (true)
        {
            if (next_block_size == 0)
            {
                if (socket->bytesAvailable() < 2) break;
                in >> next_block_size;
            }
            if (socket->bytesAvailable() < next_block_size) break;
            in >> js_inpkg;
            next_block_size = 0;
            if (js_inpkg.value(TYPE_PACKAGE).toString() == REGISTRATION_STATUS)
            {
                if (js_inpkg.value(STATUS_PACKAGE).toString() == SUCCESSFUL_PACKAGE_ACCEPTANCE)
                {
                    QMessageBox msgBox;
                    msgBox.setText("Registration Success!");
                    msgBox.exec();
                    messenger = new Messenger();
                    messenger->set_my_login(my_login);
                    messenger->set_ip_address(ip_address);
                    messenger->set_my_userid(js_inpkg[USER_ID].toInt());
                    socket->disconnectFromHost();
                    connect(this, &QtInterface::send_to_messenger, messenger, &Messenger::get_signal_interface);
                    this->hide();
                    messenger->show();
                    emit send_to_messenger(js_inpkg);
                }
                else if (js_inpkg.value(STATUS_PACKAGE).toString() == UNSUCCESSFUL_PACKAGE_ACCEPTANCE)
                {
                    QMessageBox msgBox;
                    msgBox.setText("Such a user already exists!");
                    msgBox.exec();
                }
            }
            if (js_inpkg.value(TYPE_PACKAGE).toString() == LOGIN_STATUS)
            {
                if (js_inpkg.value(STATUS_PACKAGE).toString() == SUCCESSFUL_PACKAGE_ACCEPTANCE)
                {
                    QMessageBox msgBox;
                    msgBox.setText("Login Success!");
                    msgBox.exec();
                    messenger = new Messenger();
                    messenger->set_my_login(my_login);
                    messenger->set_ip_address(ip_address);
                    messenger->set_my_userid(js_inpkg[USER_ID].toInt());
                    socket->disconnectFromHost();
                    connect(this, &QtInterface::send_to_messenger, messenger, &Messenger::get_signal_interface);
                    this->hide();
                    messenger->show();
                    emit send_to_messenger(js_inpkg);
                }
                else if (js_inpkg.value(STATUS_PACKAGE).toString() == UNSUCCESSFUL_PACKAGE_ACCEPTANCE)
                {
                    QMessageBox msgBox;
                    msgBox.setText("Login or password is not correct!");
                    msgBox.exec();
                }
            }
            break;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Error");
        msgBox.exec();
    }
}

void QtInterface::sendToServer(const QJsonObject& js_pkg)
{
    data.clear();
    QDataStream out(&data, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_6_5);
    out << quint64(0) << js_pkg;
    out.device()->seek(0);
    out << (quint64)(data.size() - sizeof(quint64));
    socket->write(data);
}