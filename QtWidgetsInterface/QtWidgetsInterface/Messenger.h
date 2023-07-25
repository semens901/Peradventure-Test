#pragma once
#include <QMainWindow>
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QMessageBox>
#include <QMap>
#include <QVector>
#include <QShortcut>
#include "ui_Messenger.h"
#include "Constans.h"

class Messenger : public QMainWindow
{
	Q_OBJECT

public:
	Messenger(QWidget *parent = nullptr);
	~Messenger();

	void set_socket(QTcpSocket* socket);
	void set_my_login(QString my_login);
	void set_my_userid(int id);
	void set_ip_address(QString ip_address);

private:
	Ui::MessengerClass ui;

	QByteArray data;
	QTcpSocket* socket;
	QString my_login;
	QJsonObject js_inpkg;
	quint64 next_block_size;
	int my_userid;
	QMap<QString, int> m_users;
	QJsonObject js_user_selected;
	QJsonObject messages_information;
	QString ip_address;

	QShortcut* keyEnter;

	void update_my_data();
	void populate_dialog_box(QJsonObject js_pkg);
	void populate_users_box(QJsonObject js_pkg);

	void sendToServer(const QJsonObject& js_pkg);
	void get_users_list();

public slots:
	void get_signal_interface(QJsonObject js_pkg);
	void readyRead();
	void user_selected(QListWidgetItem*);
	void send_message();
};
