#include "MySQLServer.h"

MySQLServer::MySQLServer()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(DB_NAME);
	if (db.open())
	{
		qDebug() << "opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "not opened\t" << DB_NAME;
	}
	query = QSqlQuery(db);
	query.exec("CREATE TABLE users ("
		"user_id INT PRIMARY KEY AUTO_INCREMENT,"
		"login VARCHAR(50) NOT NULL UNIQUE,"
		"password VARCHAR(255) NOT NULL"
		");");

	query.exec("CREATE TABLE chats ("
		"chat_id INTEGER PRIMARY KEY,"
		"name VARCHAR(50) NOT NULL UNIQUE,"
		"created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
		");");
	query.exec("CREATE TABLE members ("
		"member_id INTEGER PRIMARY KEY,"
		"chat_id INTEGER NOT NULL,"
		"user_id INTEGER NOT NULL,"
		"created_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
		"FOREIGN KEY (chat_id) REFERENCES chats(chat_id),"
		"FOREIGN KEY (user_id) REFERENCES users(user_id)"
		");");

	query.exec("CREATE TABLE messages ("
		"message_id INTEGER PRIMARY KEY,"
		"chat_id INTEGER NOT NULL,"
		"user_id INTEGER NOT NULL,"
		"sent_at DATETIME DEFAULT CURRENT_TIMESTAMP,"
		"FOREIGN KEY (chat_id) REFERENCES chats(chat_id),"
		"FOREIGN KEY (user_id) REFERENCES users(user_id)"
		");");
	db.close();
	query.clear();
}

MySQLServer::~MySQLServer()
{
}

void MySQLServer::create_user(QString login, QString password)
{
	/*if (db.open())
	{
		qDebug() << "opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "not opened\t" << DB_NAME;
	}*/
	query = QSqlQuery(db);

	query.prepare("INSERT INTO users (login, password) VALUES (:login, :password);");
	query.bindValue(":login", login);
	query.bindValue(":password", password);
	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
}

bool MySQLServer::send_query(QSqlQuery& query)
{
	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
		return 0;
	}
	return 1;
}

int MySQLServer::generate_user_id()
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(DB_NAME);
	if (db.open())
	{
		qDebug() << "opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "not opened\t" << DB_NAME;
	}
	query = QSqlQuery(db);
	this->query.exec("SELECT * FROM users ORDER BY user_id DESC LIMIT 1;");
	if (query.next())
		return query.value(0).toInt();
	else
		return 0;
}

int MySQLServer::existence_check(QSqlQuery& query)
{
	// Возвращает количество найденных значений по первому столбцу таблицы

	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
	int result = 0;
	while (query.next())
	{
		result += query.value(0).toInt();
	}

	//delete this->query;

	return result;
}

const QSqlDatabase* MySQLServer::get_database()
{
	if (db.open())
	{
		qDebug() << "opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "not opened\t" << DB_NAME;
	}
	return &this->db;
}

QStringList MySQLServer::get_users_list()
{
	QStringList users;
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(DB_NAME);
	if (db.open())
	{
		qDebug() << "opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "not opened\t" << DB_NAME;
	}
	query = QSqlQuery(db);
	query.prepare("SELECT * FROM users");
	if (!send_query(query))
	{
		qDebug() << "Failed to execute query";
	}
	while (query.next())
	{
		qDebug() << query.value(1).toString();
		//users.append(query.value(1).toString())
	}
	//db.close();
	return users;
}
