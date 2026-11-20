#include "Account.h"
#include "SHA.h"
#include <cmath>
#include <fstream>
#include <algorithm>

const std::vector<std::string> Account::library = { "Crypto", "Newcastle", "Axle", "Conduit", "Bangalore", "Fuse", "Revenant", "MadMaggie", "Ballistic", "Wraith", "Octaine", "Pathfinder", "Horizon",
"Ash", "Alter", "Bloodhound", "Seer", "Valkyrie", "Sparrow", "Vantage", "Gibraltar", "Lifeline", "Mirage", "Loba", "Wattson", "Caustic", "Rampart", "Catalyst" };

Account::Account(const std::string& n, const std::string& pass, double bal) {
	if (n.length() < 3) {
		throw std::invalid_argument("The length of the name should be at least 3 letters long\n");
	}
	if (bal < 0.0) {
		throw std::invalid_argument("The balance can't be negative!\n");
	}
	name = n;
	balance = bal;
	setPassword(pass);
	secretKeys = generateSecretKeys();
	showSecretKeys();
}

bool Account::verifyPassword(const std::string& pass) const {
	return !password.empty() && password == pass;
}
void Account::setPassword(const std::string& pass) {
	if (pass.length() < 5) {
		throw std::invalid_argument("Password must contain at least 5 characters. Try again.\n");
	}
	password = pass;
	passwordHash = SHAPassword();
}


std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }



void Account::deposit(double amount) {
	if (amount <= 0) {
		throw std::runtime_error("Amount should be only positive number.\n");
	}
	balance += amount;
}


void Account::withdraw(double amount) {
	if (amount <= 0.0) {
		throw std::invalid_argument("Withdrawal amount should be positive!.\n");
	}
	if (amount > balance) {
		throw std::runtime_error("Insufficient fund for withdrawal.\n");
	}
	balance -= amount;
}



std::vector<std::string> Account::generateSecretKeys() const {
	//Generating random numbers by requesting data from Windows
	//Генерация рандомных чисел через запросы в Windows
	//Idea of this method: https://www.youtube.com/watch?v=1NXPf6Loshc 
	std::random_device rd;
	std::mt19937 rand(rd());
	std::uniform_int_distribution<int> distance(0, static_cast<int>(library.size()) - 1);

	std::vector<std::string> dict;

	while (dict.size() < 6) {
		std::string word = library[distance(rand)];

		if (find(dict.begin(), dict.end(), word) == dict.end()) {
			dict.push_back(word);
		}
	}

	return dict;
}

void Account::showSecretKeys() const {
	std::cout << "\n-----IMPORTANT: Write down your secret keys, if you lose access to the account, you can recover it using them. Do not share them with ANYONE!-----\n";
	for (int i = 0; i < 6; ++i) {
		std::cout << (i + 1) << ". " << secretKeys[i] << "\n";
	}
	std::cout << "---------------------------------------------------------------\n\n";
}

bool Account::verifyKeys() const {
	std::cout << "Enter your 6 secret key words in the CORRECT order:\n";
	for (size_t i = 0; i < secretKeys.size(); ++i) {
		std::string inputKey;
		std::cout << "Enter key word number <" << (i + 1) << ">: ";

		if (!(std::cin >> inputKey)) {
			return false;
		}

		if (inputKey != secretKeys[i]) {
			std::cout << "Access Denied\n";
			return false;
		}
	}
	std::cout << "Successful verification!\n";
	return true;
}

std::string Account::SHAPassword() const {
	return "0x" + sha256(password);
}

std::string Account::SHASecretKeys() const {
	std::string keys;
	for (const auto& key : secretKeys) {
		keys += key;
	}
	return "0x" + sha256(keys);
}

std::string Account::getPasswordHash() const {
	return passwordHash;
}



namespace UserInformation {

	//All information about users, Вся информация о пользователях
	std::unordered_map<std::string, Account> dataUsers;


	void printDataUsers() {
		for (const auto& pair : dataUsers) {
			std::cout << "-----   Account   -----\n";
			std::cout << "Name of the account: " << pair.first << '\n';
			std::cout << "Balance on this account: $" << pair.second.getBalance() << "\n\n";
		}
		std::cout << "-----   That's all!   -----\n\n";

	}

	size_t getUsersCount() {
		return dataUsers.size();
	}


	void addUser(const Account& user) {
		if (!hasUser(user.getName())) {
			dataUsers.insert({ user.getName(), user });
			std::cout << "You successfully registered your account!\n";
		}
		else {
			throw std::invalid_argument("You can't use this username - choose another one\n");
		}
	}

	bool hasUser(const std::string& name) {
		if (dataUsers.count(name) == 0) {
			return false;
		}
		return true;
	}


	void proccessTransfer(const std::string& sender, const std::string& receiver, double amount) {
		Account& from = dataUsers.at(sender);
		Account& to = dataUsers.at(receiver);

		from.withdraw(amount);
		to.deposit(amount);
	}



	bool loginIntoAccount(const std::string& username) {
		if (dataUsers.count(username) == 0) {
			std::cout << "The account is NOT found!\n";
			return false;
		}

		std::string inputPassword;
		std::cout << "Enter password for <" << username << ">: ";
		std::cin >> inputPassword;

		Account& user = dataUsers.at(username);

		if (user.verifyPassword(inputPassword)) {
			std::cout << "Login successful!\n";
			return true;
		}

		std::cout << "Invalid password.\n";
		return false;
	}


	bool recoverAccountAccess(const std::string& username) {
		if (dataUsers.count(username) == 0) {
			std::cout << "The account is NOT found\n";
			return false;
		}

		Account& user = dataUsers.at(username);

		if (!user.verifyKeys()) {
			std::cout << "Recovery failed. Invalid secret keys.\n";
			return false;
		}

		std::string newPassword;
		std::cout << "Enter new password for <" << username << ">: ";
		std::cin >> newPassword;

		try {
			user.setPassword(newPassword);
			std::cout << "Password changed successfully! Access restored. Enjoy your session!\n";
			return true;
		}
		catch (const std::exception& e) {
			std::cout << e.what() << " Recovery denied.\n";
			return false;
		}
	}

	bool transformUsersToJSON() {
		std::ofstream file("users.json");


		if (!file.is_open()) {
			std::cerr << "There is an error in opening the file!\n";
			return false;
		}
		file << "[\n";
		bool firstEntry = true;

		for (const auto& [name, user] : dataUsers) {
			// To get correct format, Правильное форматирование файла
			if (!firstEntry) {
				file << ",\n";
			}
			firstEntry = false;

			// Avoiding mistakes with float numbers(when rounding), Не допускаем ошибки с дробными числами при округлении
			long long balanceCents = std::llround(user.getBalance() * 100.0);


			//JSON format, JSON формат
			file << "  {\n"
				<< "    \"name\": \"" << name << "\",\n"
				<< "    \"passwordHash\": \"" << user.getPasswordHash() << "\",\n"
				<< "    \"balanceCents\": " << balanceCents << ",\n"
				<< "    \"secretKeysHash\": \"" << user.SHASecretKeys() << "\"\n"
				<< "  }";
		}
		file << "\n]\n";

		// Checks if something happens during writing, Проверка на прерывание записи
		if (file.fail()) {
			std::cerr << "Error while writing into the file\n";
			return false;
		}

		return true;
	}
}