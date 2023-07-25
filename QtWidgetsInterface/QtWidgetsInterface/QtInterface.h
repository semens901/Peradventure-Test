#pragma once
#ifndef QTINTERFACE
#define QTINTERFACE
#include <QtWidgets/QMainWindow>
#include "ui_QtInterface.h"
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include "Messenger.h"

class QtInterface : public QMainWindow
{
    Q_OBJECT

public:
    QtInterface(QWidget *parent = nullptr);
    ~QtInterface();
    
private:
    Ui::QtInterfaceClass ui;
    QTcpSocket* socket;
    QByteArray data;
    quint64 next_block_size;
    QJsonObject js_inpkg;
    QString my_login;
    Messenger* messenger;
    QString ip_address;
    
    void sendToServer(const QJsonObject& js_pkg);

public slots:
    void sign_up();
    void log_in();
    void readyRead();

signals:
    void send_to_messenger(QJsonObject js_pkg);
    
};

#endif // !QTINTERFACE