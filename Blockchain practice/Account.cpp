#include "Account.h"

const std::vector<std::string> Account::library = { "Crypto", "Newcastle", "Axle", "Conduit", "Bangalore", "Fuse", "Revenant", "MadMaggie", "Ballistic", "Wraith", "Octaine", "Pathfinder", "Horizon",
"Ash", "Alter", "Bloodhound", "Seer", "Valkyrie", "Sparrow", "Vantage", "Gibraltar", "Lifeline", "Mirage", "Loba", "Wattson", "Caustic", "Rampart", "Catalyst" };

Account::Account(std::string& n, std::string& pass, double bal) {
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

bool Account::verifyPassword(std::string& pass) const {
	return !password.empty() && password == pass;
}
void Account::setPassword(std::string& pass) {
	if (pass.length() >= 5) {
		password = pass;
	}
	else{
		throw std::invalid_argument("Password must contain at least 5 characters. Try again.\n");
	}
}


std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }



void Account::deposit(double amount) { balance += amount; }


void Account::withdraw(double amount) {
	if (amount > balance) {
		throw std::runtime_error("Insufficient funds for withdrawal.\n");
	}
	else if (amount < 0) {
		throw std::runtime_error("Withdrawal amount cannot be negative.\n");
	}
	else {
		balance -= amount;
	}
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
	for (int i = 0; i < secretKeys.size(); ++i) {
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

	//Function to add user(also checks if username is not already in the dataUsers(in the future need to add checking the secret key combination),
	//Функция для добавления пользователя в dataUsers + проверка на наличие имени пользователя в dataUsers(в будщем надо добавить проверку на комбинацию ключей)
	void addUser(const Account& user) {
		if (dataUsers.count(user.getName()) == 0) {
			dataUsers.insert({ user.getName(), user });
			std::cout << "You successfully registered your account!\n";
		}
		else {
			std::cout << "You can't use this username - choose another one\n";
		}
	}

	bool hasUser(std::string& name) {
		if (dataUsers.count(name) == 0) {
			return false;
		}
		return true;
	}


	void proccessTransfer(std::string& sender, std::string& receiver, double amount) {
		Account& from = dataUsers.at(sender);
		Account& to = dataUsers.at(receiver);

		from.withdraw(amount);
		to.deposit(amount);
	}



	bool loginIntoAccount(std::string& username) {
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

	// Recovery access by secret keys, Восстановление доступа к аккаунту по секретным ключам
	bool recoverAccountAccess(std::string& username) {
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
}