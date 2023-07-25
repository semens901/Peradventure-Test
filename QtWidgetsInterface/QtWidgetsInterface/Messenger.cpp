#include "Messenger.h"

Messenger::Messenger(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	socket = new QTcpSocket(this);
	connect(socket, &QTcpSocket::readyRead, this, &Messenger::readyRead);

	next_block_size = 0;
	keyEnter = new QShortcut(this);
	keyEnter->setKey(Qt::Key_Return);
	connect(keyEnter, &QShortcut::activated, this, &Messenger::send_message);
}

Messenger::~Messenger()
{}

void Messenger::set_socket(QTcpSocket* socket)
{
	this->socket = socket;
}

void Messenger::set_my_login(QString my_login)
{
	this->my_login = my_login;
	ui.lbl_my_login->setText(this->my_login);
}

void Messenger::set_my_userid(int id)
{
	my_userid = id;
	get_users_list();
}

void Messenger::set_ip_address(QString ip_address)
{
	this->ip_address = ip_address;
}

void Messenger::update_my_data()
{
	QJsonObject js_outpkg = {
		{TYPE_PACKAGE , UPDATE_MY_DATA },
		{MY_NAME, my_login},
		{USER_ID, my_userid},
		{DATA_FROM_PACKAGE, NULL},
		{STATUS_PACKAGE, NULL},
		{SEND_TO , js_user_selected[USER_ID].toInt()}
	};
	sendToServer(js_outpkg);
}

void Messenger::populate_dialog_box(QJsonObject js_pkg)
{
	if (js_user_selected.value(USER_ID).toInt() == js_pkg.value(SEND_TO).toInt())
	{
		QVector<int> users_id;
		for (auto id : js_pkg.value(USERS_ID).toArray())
			users_id.append(id.toInt());
		QVector<int>::iterator it_users_id = users_id.begin();

		QStringList messages;
		for (auto message : js_pkg.value(MESSAGES).toArray())
			messages.append(message.toString());
		QStringList::iterator it_messages = messages.begin();

		QVector<int> sends_to;
		for (auto send_to : js_pkg.value(SENDS_TO).toArray())
			sends_to.append(send_to.toInt());
		QVector<int>::iterator it_sends_to = sends_to.begin();

		ui.textBrowser->clear();

		while ((it_users_id != users_id.end()) && (it_messages != messages.end()) && (it_sends_to != sends_to.end()))
		{
			if ((*it_users_id == my_userid) && (*it_sends_to == js_user_selected.value(USER_ID).toInt()))
			{
				ui.textBrowser->append("[Your]\n" + *it_messages);
			}
			if ((js_user_selected.value(USER_ID).toInt() == *it_users_id) && (my_userid == *it_sends_to))
			{
				ui.textBrowser->append("[" + js_user_selected.value(LOGIN).toString() + "]" + "\n" + *it_messages);
			}

			++it_users_id;
			++it_messages;
			++it_sends_to;
		}
	}
}

void Messenger::populate_users_box(QJsonObject js_pkg)
{
	if (js_pkg.value(STATUS_PACKAGE).toString() == SUCCESSFUL_PACKAGE_ACCEPTANCE)
	{
		QStringList temp_users_names;
		ui.list_friends->clear();
		for (auto user : js_pkg.value(DATA_FROM_PACKAGE).toArray())
		{
			temp_users_names.append(user.toString());
			QListWidgetItem* newItem = new QListWidgetItem;
			if (user.toString() != my_login)
			{
				newItem->setText(user.toString());
				ui.list_friends->addItem(newItem);
			}
		}
		QVector<int> users_id;
		for (auto id : js_pkg.value(USERS_ID).toArray())
			users_id.push_back(id.toInt());

		QStringList::iterator it_temp_users_names = temp_users_names.begin();
		QVector<int>::iterator it_users_id = users_id.begin();
		while ((it_temp_users_names != temp_users_names.end()) && (it_users_id != users_id.end()))
		{
			m_users[*it_temp_users_names] = *it_users_id;
			++it_temp_users_names;
			++it_users_id;
		}

	}
	else if (js_inpkg.value(STATUS_PACKAGE).toString() == UNSUCCESSFUL_PACKAGE_ACCEPTANCE)
	{
		QMessageBox msgBox;
		msgBox.setText("Error");
		msgBox.exec();
	}
}

void Messenger::readyRead()
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
			if (js_inpkg.value(TYPE_PACKAGE).toString() == GET_USERS_LIST)
			{
				populate_users_box(js_inpkg);
			}
			if (js_inpkg.value(TYPE_PACKAGE).toString() == UPDATE_MY_DATA)
			{
				populate_dialog_box(js_inpkg);

			}
			break;
		}
	}
}

void Messenger::user_selected(QListWidgetItem* item)
{
	js_user_selected[LOGIN] = item->text();
	js_user_selected[USER_ID] = m_users[item->text()];
	update_my_data();
}

void Messenger::send_message()
{
	if ((ui.le_message->text() != ""))
	{
		QJsonObject js_outpkg = {
			{TYPE_PACKAGE, MESSAGE},
			{MY_NAME, my_login},
			{USER_ID, my_userid},
			{DATA_FROM_PACKAGE, ui.le_message->text()},
			{STATUS_PACKAGE, NULL},
			{SEND_TO, js_user_selected[USER_ID].toInt()}
		};
		ui.le_message->clear();
		sendToServer(js_outpkg);
	}
}

void Messenger::sendToServer(const QJsonObject& js_pkg)
{
	data.clear();
	QDataStream out(&data, QIODevice::ReadWrite);
	out.setVersion(QDataStream::Qt_6_5);
	out << quint64(0) << js_pkg;
	out.device()->seek(0);
	out << (quint64)(data.size() - sizeof(quint64));
	socket->write(data);
}

void Messenger::get_users_list()
{
	QJsonObject js_outpkg = {
		{TYPE_PACKAGE , GET_USERS_LIST },
		{MY_NAME, my_login},
		{DATA_FROM_PACKAGE, NULL},
		{USER_ID, my_userid},
		{STATUS_PACKAGE, NULL}
	};
	socket->connectToHost(ip_address, 2000);
	sendToServer(js_outpkg);
}

void Messenger::get_signal_interface(QJsonObject js_pkg)
{
	/*if (js_pkg.value("TYPE").toString() == "USERSLIST")
	{
		for (QJsonValue user : js_pkg.value("DATA").toArray())
		{
			QListWidgetItem* newItem = new QListWidgetItem;
			newItem->setText(user.toString());
			ui.list_friends->addItem(newItem);
			delete newItem;
		}
	}*/
}