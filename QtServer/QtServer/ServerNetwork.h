#pragma once
#ifndef SERVERNETWORK
#define SERVERNETWORK

#include <QTcpServer>
#include<QCoreApplication>
#include <QTcpSocket>
#include <Qvector>
#include <Qstring>
#include <QJsonObject>
#include <QJsonArray>
#include<qsqldatabase.h>
#include<qsqlquery.h>
#include <QMap>
#include<QCryptographicHash>
#include "Constans.h"
#include<ctime>

class ServerNetwork: public QTcpServer
{
	Q_OBJECT

public:
	ServerNetwork();

private:
	QTcpSocket* socket;
	QMap<int, QVector<QTcpSocket*>> users;
	QVector<QTcpSocket*> sockets;
	QByteArray data;
	quint64 next_block_size;
	QJsonObject js_inpkg;
	//QStringList dirs;
	QSqlDatabase db;

	void sendToClient(QJsonObject& js_pkg, QTcpSocket* socket);
	void sign_up(QJsonObject & js_pkg);
	void log_in(QJsonObject& js_pkg);
	void send_users_list(QJsonObject& js_pkg);
	QStringList get_users_list();
	int generate_user_id(QSqlQuery& query);
	int generate_message_id(QSqlQuery& query);
	void db_initialize(QSqlQuery& query);
	void save_message(QJsonObject& js_pkg);
	void update_user_data(QJsonObject& js_pkg);
	QString generate_hash(QString data);
	QString generate_hash(QString data, QString salt);
	QString generate_salt();

public slots:
	void incomingConnection(qintptr socket_descriptor); //Обработчик новых подключений
	void readyRead(); // Обработчик полученных от клиента сообщений
	void deleteLater();

};

#endif // SERVERNETWORK