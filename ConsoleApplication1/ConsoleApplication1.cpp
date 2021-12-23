#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

class Message {
	string _text;
	string _sender;
	string _receiver;
public:
	Message(string text, string sender, string receiver) :_text(text), _sender(sender),
		_receiver(receiver) {}
	friend fstream& operator >>(fstream& is, Message& obj);
	friend ostream& operator <<(ostream& os, const Message& obj);
};

fstream& operator >>(fstream& is, Message& obj) {
	is >> obj._text;
	is >> obj._sender;
	is >> obj._receiver;
	return is;
}

ostream& operator <<(ostream& os, const Message& obj) {
	os << obj._text;
	os << ' ';
	os << obj._sender;
	os << ' ';
	os << obj._receiver;
	return os;
}

class User {
	string _name;
	string _login;
	string _pass;
public:
	User(string name, string login, string pass) :_name(name), _login(login),
		_pass(pass) {}
	friend fstream& operator >>(fstream& is, User& obj);
	friend ostream& operator <<(ostream& os, const User& obj);
};

fstream& operator >>(fstream& is, User& obj) {
	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}

ostream& operator <<(ostream& os, const User& obj) {
	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	return os;
}

int main() {
	fstream user_ele("users.txt", ios::in | ios::out);
	fstream message_ele("message.txt", ios::in | ios::out);

	if (!user_ele)
		fstream user_ele("users.txt", ios::in | ios::out | ios::trunc);
	if (!message_ele)
		fstream message_ele("message.txt", ios::in | ios::out | ios::trunc);

	if (user_ele && message_ele) {
		fs::permissions("users.txt",
			fs::perms::group_all | fs::perms::others_all,
			fs::perm_options::remove);
		fs::permissions("message.txt",
			fs::perms::group_all | fs::perms::others_all,
			fs::perm_options::remove);


		User obj("Alex", "Banana", "12345");
		Message obj1("Hi", "How_are_you?", "Bye!");
		// Запишем данные по в файл
		user_ele << obj << endl;
		message_ele << obj1 << endl;
		// Чтобы считать данные из файла, надо установить позицию для чтения в начало файла
		user_ele.seekg(0, ios_base::beg);
		message_ele.seekg(0, ios_base::beg);
		// Считываем данные из файла
		user_ele >> obj;
		message_ele >> obj1;
		cout << obj << endl;
		cout << obj1 << endl;
	}
	else {
		cout << "Could not open ele users.txt or ele message.txt!" << '\n';
		return 0;
	}
}
