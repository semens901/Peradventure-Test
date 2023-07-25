#include "ServerNetwork.h"

ServerNetwork::ServerNetwork()
{
	if (this->listen(QHostAddress::Any, PORT))
	{
		qDebug() << "Start server";
	}
	else
	{
		qDebug() << "Error, server don't start, restart the server and try again";
		exit(0);
	}
	next_block_size = 0;
	db = QSqlDatabase::addDatabase(DATA_BASE_TYPE);
	db.setDatabaseName(DB_NAME);
	if (db.open())
	{
		qDebug() << "Data base opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "Data base not opened" << DB_NAME << ", restart the server and try again\t";
		exit(0);
	}
	QSqlQuery query = QSqlQuery(db);

	db_initialize(query);

	db.close();
}

void ServerNetwork::incomingConnection(qintptr socket_descriptor)
{
	socket = new QTcpSocket;
	socket->setSocketDescriptor(socket_descriptor);
	connect(socket, &QTcpSocket::readyRead, this, &ServerNetwork::readyRead);
	connect(socket, &QTcpSocket::disconnected, this, &ServerNetwork::deleteLater);
	sockets.append(socket);

	qDebug() << "Client connected " << socketDescriptor();
}

void ServerNetwork::readyRead()
{
	socket = (QTcpSocket*)sender();
	QDataStream in(socket);
	in.setVersion(QDataStream::Qt_6_5);
	if (in.status() == QDataStream::Ok)
	{
		qDebug() << "read... query from client:\t" << (QTcpSocket*)sender();
		while (true)
		{
			qDebug() << "processing received packet";
			if (next_block_size == 0)
			{
				qDebug() << "nextBlockSize = 0";

				if (socket->bytesAvailable() < 2)
				{
					qDebug() << "Data < 2, break, package not accepted";
					break;
				}
				in >> next_block_size;
				qDebug() << "nextBlockSize = " << next_block_size;
			}
			if (socket->bytesAvailable() < next_block_size)
			{
				qDebug() << "Data not full, package not accepted";
				break;
			}
			in >> js_inpkg;

			next_block_size = 0;
			qDebug() << "Received packet type: " << js_inpkg.value(TYPE_PACKAGE).toString();
			if (js_inpkg.value(TYPE_PACKAGE).toString() == SIGN_UP)
			{
				sign_up(js_inpkg);
			}
			if (js_inpkg.value(TYPE_PACKAGE).toString() == LOGIN)
			{
				log_in(js_inpkg);
			}
			if (js_inpkg.value(TYPE_PACKAGE).toString() == GET_USERS_LIST)
			{
				send_users_list(js_inpkg);
			}
			if (js_inpkg.value(TYPE_PACKAGE).toString() == UPDATE_MY_DATA)
			{
				update_user_data(js_inpkg);
			}
			if (js_inpkg.value(TYPE_PACKAGE).toString() == MESSAGE)
			{
				save_message(js_inpkg);
				update_user_data(js_inpkg);
			}
			break;
		}
	}
	else
	{
		qDebug() << "DataStream error, package not accepted";
	}
}

void ServerNetwork::sign_up(QJsonObject& js_pkg)
{
	QJsonObject js_outpkg;
	qDebug() << "User registration. " << "User login: " + js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString();

	if (db.open())
	{
		qDebug() << "Data base opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "Data base not opened\t" << DB_NAME;
		return;
	}

	QSqlQuery query = QSqlQuery(db);
	query.prepare("SELECT COUNT(*) FROM users WHERE login = (:login);");
	query.bindValue(":login", js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString());

	qDebug() << "Search for matches by login in the database";

	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
	int result = 0;
	while (query.next())
	{
		result += query.value(0).toInt();
	}

	if (!result)
	{
		qDebug() << "Creating an id for the user";

		int id = generate_user_id(query) + 1;

		query.clear();
		QString salt = generate_salt();
		query = QSqlQuery(db);
		query.prepare("INSERT INTO users (user_id, login, password, salt) VALUES (:user_id, :login, :password, :salt);");
		query.bindValue(":user_id", id);
		query.bindValue(":login", js_pkg.value("DATA")["LOGIN"].toString());
		query.bindValue(":password", generate_hash(js_pkg.value("DATA")["PASSWORD"].toString(), salt));
		query.bindValue(":salt", salt);

		if (!query.exec())
		{
			qDebug() << "Failed to execute query";
			qDebug() << "User registration failed! User not registered";
			return;
		}
		js_outpkg = {
				{TYPE_PACKAGE , REGISTRATION_STATUS },
				{DATA_FROM_PACKAGE, NULL},
				{STATUS_PACKAGE, SUCCESSFUL_PACKAGE_ACCEPTANCE},
				{USER_ID, id}
				
		};
		qDebug() << "Registration was successful!";
		sendToClient(js_outpkg, socket);
	}
	else
	{
		qDebug() << "User registration failed! User not registered";
		js_outpkg = {
				{TYPE_PACKAGE , REGISTRATION_STATUS },
				{DATA_FROM_PACKAGE, NULL},
				{STATUS_PACKAGE, UNSUCCESSFUL_PACKAGE_ACCEPTANCE},
				{USER_ID, NULL}

		};
		sendToClient(js_outpkg, socket);
	}
}

void ServerNetwork::log_in(QJsonObject& js_pkg)
{
	QJsonObject js_outpkg;
	QString salt;
	qDebug() << "User logs in. " << "User login: " + js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString();
	qDebug() << "Entry attempt";

	if (db.open())
	{
		qDebug() << "Data base opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "Data base not opened\t" << DB_NAME;
		qDebug() << "Database query error!\t" << DB_NAME;
	}

	qDebug() << "Checking if a user exists";
	QSqlQuery query = QSqlQuery(db);
	query.prepare("SELECT COUNT(*) FROM users WHERE login = (:login);");
	query.bindValue(":login", js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString());

	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
	int exists = 0;

	query.next();
	exists += query.value(0).toInt();

	query.prepare("SELECT salt FROM users WHERE login = (:login);");
	query.bindValue(":login", js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString());

	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
	query.next();
	salt = query.value(0).toString();

	if (exists)
	{
		int id = NULL;
		query.prepare("SELECT user_id FROM users WHERE login = (:login) AND password = (:password);");
		query.bindValue(":login", js_pkg.value(DATA_FROM_PACKAGE)[LOGIN].toString());
		query.bindValue(":password", generate_hash(js_pkg.value(DATA_FROM_PACKAGE)[PASSWORD].toString(), salt));
		if (!query.exec())
		{
			qDebug() << "Failed to execute query";
			return;
		}
		if (query.next())
		{
			id = query.value(0).toInt();
		}
		else
		{
			return;
		}
		js_outpkg = {
				{TYPE_PACKAGE , LOGIN_STATUS },
				{DATA_FROM_PACKAGE, NULL},
				{STATUS_PACKAGE, SUCCESSFUL_PACKAGE_ACCEPTANCE},
				{USER_ID, id}

		};
		qDebug() << "Login was successful!";
	}
	else
	{
		js_outpkg = {
				{TYPE_PACKAGE , LOGIN_STATUS },
				{DATA_FROM_PACKAGE, NULL},
				{STATUS_PACKAGE, UNSUCCESSFUL_PACKAGE_ACCEPTANCE},
				{USER_ID, NULL}

		};
		qDebug() << "Login or password is not correct!";
	}
	sendToClient(js_outpkg, socket);
}

void ServerNetwork::send_users_list(QJsonObject& js_pkg)
{
	qDebug() << "Request to get a list of users";
	QJsonObject js_outpkg;
	QStringList users = get_users_list(); 
	if (users[0] == "Data base query error!")
		return;
	js_outpkg = {
				{TYPE_PACKAGE, GET_USERS_LIST },
				{DATA_FROM_PACKAGE, NULL},
				{STATUS_PACKAGE, SUCCESSFUL_PACKAGE_ACCEPTANCE}

	};

	QSqlQuery query = QSqlQuery(db);
	QMap<QString, int> m_users;
	int id = 0;
	for (auto var : users)
	{
		query.prepare("SELECT user_id FROM users WHERE login = (:login)");
		query.bindValue(":login", var);
		if (!query.exec())
		{
			qDebug() << "Failed to execute query";
			return;
		}
		if (query.next())
		{
			id = query.value(0).toInt();
		}
		else
		{
			id = NULL;
		}
		m_users[var] = id;
	}
	QJsonArray data_list;
	for (auto var : users)
		data_list.append(var);
	js_outpkg[DATA_FROM_PACKAGE] = data_list;
	QJsonArray id_users;
	for (auto var : users)
	{
		id_users.append(m_users[var]);
	}
		
	js_outpkg[USERS_ID] = id_users;
	this->users[js_pkg.value(USER_ID).toInt()].push_back(socket);
	qDebug() << "sending a list of users to the requester: ";
	// Позже переписать фрагмент кода
	for (QMap<int, QVector<QTcpSocket*>>::iterator it = this->users.begin(); it != this->users.end(); ++it)
	{
		for (QVector<QTcpSocket*>::iterator it_value = it.value().begin(); it_value != it.value().end(); ++it_value)
		{
			sendToClient(js_outpkg, *it_value);
		}

	}
}

QStringList ServerNetwork::get_users_list()
{
	QStringList users;
	db = QSqlDatabase::addDatabase(DATA_BASE_TYPE);
	db.setDatabaseName(DB_NAME);
	if (db.open())
	{
		qDebug() << "Data base opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "Data base not opened\t" << DB_NAME;
		qDebug() << "Data base query error!\t" << DB_NAME;
		return {"Data base query error!"};
	}
	QSqlQuery query = QSqlQuery(db);
	query.prepare("SELECT * FROM users");
	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
		qDebug() << "Data base query error!\t" << DB_NAME;
		return { "Data base query error!" };
	}
	while (query.next())
	{
		qDebug() << query.value(1).toString();
		users.append(query.value(1).toString());
	}
	//db.close();
	return users;
}

int ServerNetwork::generate_user_id(QSqlQuery& query)
{
	query.exec("SELECT * FROM users ORDER BY user_id DESC LIMIT 1;");
	if (query.next())
		return query.value(0).toInt();
}

int ServerNetwork::generate_message_id(QSqlQuery& query)
{
	query.exec("SELECT * FROM messages ORDER BY message_id DESC LIMIT 1;");
	if (query.next())
		return query.value(0).toInt();
}

void ServerNetwork::db_initialize(QSqlQuery& query)
{
	query.exec("CREATE TABLE users ("
		"user_id INT AUTO_INCREMENT PRIMARY KEY,"
		"login VARCHAR(50) NOT NULL UNIQUE,"
		"password VARCHAR(255) NOT NULL,"
		"salt VARCHAR(255) NOT NULL"
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
		"message_id INT AUTO_INCREMENT PRIMARY KEY,"
		"chat_id INTEGER NOT NULL,"
		"user_id INTEGER NOT NULL,"
		"message VARCHAR(255) NOT NULL,"
		"send_to INTEGER NOT NULL,"
		"FOREIGN KEY (chat_id) REFERENCES chats(chat_id),"
		"FOREIGN KEY (user_id) REFERENCES users(user_id)"
		");");
}

void ServerNetwork::save_message(QJsonObject& js_pkg)
{
	int message_id = 0;
	if (db.open())
	{
		qDebug() << "Data base opened\t" << DB_NAME;
	}
	else
	{
		qDebug() << "Data base not opened\t" << DB_NAME;
		qDebug() << "Data base query error!\t" << DB_NAME;
	}

	QSqlQuery query = QSqlQuery(db);
	message_id = generate_message_id(query) + 1;
	qDebug() << "Message ID: " + QString::number(message_id) + " Chat ID: " + QString::number(message_id);
	qDebug() << "Message: " + js_pkg["DATA"].toString();
	qDebug() << "Send to: " + js_pkg["SENDTO"].toInt();
	query.prepare("INSERT INTO messages (message_id, chat_id, user_id, message, send_to) VALUES (:message_id, :chat_id, :user_id, :message, :send_to);");
	query.bindValue(":message_id", message_id);
	query.bindValue(":chat_id", message_id);
	query.bindValue(":user_id", js_pkg["USERID"].toInt());
	query.bindValue(":message", js_pkg["DATA"].toString());
	query.bindValue(":send_to", js_pkg["SENDTO"].toInt());
	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
		qDebug() << "Data base query error!\t" << DB_NAME;
		qDebug() << "Message not saved!";
		return;
	}
}

void ServerNetwork::update_user_data(QJsonObject& js_pkg)
{
	QJsonObject js_outpkg = {
		{TYPE_PACKAGE , UPDATE_MY_DATA },
		{STATUS_PACKAGE, NULL},
		{USER_ID, js_pkg.value(USER_ID).toInt()},
		{SEND_TO, js_pkg.value(SEND_TO).toInt()},
		{DATA_FROM_PACKAGE, NULL}
	};
	QJsonObject js_outpkg2 = {
		{TYPE_PACKAGE , UPDATE_MY_DATA },
		{STATUS_PACKAGE, NULL},
		{USER_ID, js_pkg.value(SEND_TO).toInt()},
		{SEND_TO, js_pkg.value(USER_ID).toInt()},
		{DATA_FROM_PACKAGE, NULL}
	};
	QSqlQuery query = QSqlQuery(db);

	query.prepare("SELECT * FROM messages WHERE (user_id = (:user_id) AND send_to = (:send_to)) OR (user_id = (:send_to) AND send_to = (:user_id));");
	query.bindValue(":user_id", js_pkg.value(USER_ID).toInt());
	query.bindValue(":send_to", js_pkg.value(SEND_TO).toInt());
	if (!query.exec())
	{
		qDebug() << "Failed to execute query";
	}
	QJsonArray users_id;
	QJsonArray messages;
	QJsonArray sends_to;
	while (query.next())
	{
		users_id.append(query.value(2).toInt());
		messages.append(query.value(3).toString());
		sends_to.append(query.value(4).toInt());
	}
	js_outpkg[USERS_ID] = users_id;
	js_outpkg[MESSAGES] = messages;
	js_outpkg[SENDS_TO] = sends_to;

	js_outpkg2[USERS_ID] = users_id;
	js_outpkg2[MESSAGES] = messages;
	js_outpkg2[SENDS_TO] = sends_to;

	for (QMap<int, QVector<QTcpSocket*>>::iterator it = users.begin(); it != users.end(); ++it)
	{
		if (it.key() == js_pkg[USER_ID].toInt())
		{
			for (auto var : it.value())
			{
				sendToClient(js_outpkg, var);
			}
		}
		if (it.key() == js_outpkg2[USER_ID].toInt())
		{
			for (auto var : it.value())
			{
				sendToClient(js_outpkg2, var);
			}
		}
	}
}

QString ServerNetwork::generate_hash(QString data)
{
	QCryptographicHash* hash = new QCryptographicHash(QCryptographicHash::Sha256);
	hash->addData(data.toUtf8());
	QString result = hash->result().toHex();
	delete hash;
	return result;
}

QString ServerNetwork::generate_hash(QString data, QString salt)
{
	QCryptographicHash* hash = new QCryptographicHash(QCryptographicHash::Sha256);
	hash->addData((data + salt).toUtf8());
	QString result = hash->result().toHex();
	delete hash;
	return result;
}

QString ServerNetwork::generate_salt()
{
	srand(time(NULL));
	size_t salt_length = 5 + rand() % 10;
	QString salt;
	for (size_t i = 0; i < salt_length; ++i)
		salt += (char)('!' + rand() % 'z');
	return salt;
}

void ServerNetwork::sendToClient(QJsonObject& js_pkg, QTcpSocket* socket)
{
	qDebug() << js_pkg.value(TYPE_PACKAGE).toString() << " Client " + socket->peerAddress().toString();
	data.clear();
	QDataStream out(&data, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_6_5);
	out << quint64(0) << js_pkg;
	out.device()->seek(0);
	out << quint64(data.size() - sizeof(quint64));
	//out << str;
	//socket->write(data);
	if(socket != NULL)
		socket->write(data);
}

void ServerNetwork::deleteLater()
{
	for (QMap<int, QVector<QTcpSocket*>>::iterator it = users.begin(); it != users.end(); ++it)
	{
		for (QVector<QTcpSocket*>::iterator it_value = it.value().begin(); it_value != it.value().end(); ++it_value)
		{
			if (*it_value == (QTcpSocket*)sender())
			{
				users[it.key()].erase(it_value);
				return;
			}
		}

	}
}
