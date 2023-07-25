#pragma once
#ifndef MYSQLSERVER
#define MYSQLSERVER


#include<qsqldatabase.h>
#include<qsqlquery.h>
#include <Qstring>
#include <Qvector>
#include<QDebug>
#include <QDir>

#pragma warning(disable: 4996)

const char DB_NAME[] = "Messenger.db";

class MySQLServer
{
public:
	MySQLServer();

	~MySQLServer();

	void create_user(QString login, QString password);
	bool send_query(QSqlQuery& query);
	int generate_user_id();
	int existence_check(QSqlQuery& query);
	const QSqlDatabase* get_database();
	QStringList get_users_list();

private:
	QSqlDatabase db;
	QSqlQuery query;
	QDir dir;
};

#endif // !MYSQLSERVER