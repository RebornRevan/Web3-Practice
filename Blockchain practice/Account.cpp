#include "Account.h"


std::unordered_map<std::string, Account> dataUsers;

const std::vector<std::string> library = { "Crypto", "Newcastle", "Axle", "Conduit", "Bangalore", "Fuse", "Revenant", "MadMaggie", "Ballistic", "Wraith", "Octaine", "Pathfinder", "Horizon",
"Ash", "Alter", "Bloodhound", "Seer", "Valkyrie", "Sparrow", "Vantage", "Gibraltar", "Lifeline", "Mirage", "Loba", "Wattson", "Caustic", "Rampart", "Catalyst" };

Account::Account(const std::string& n, double bal) {
	if (n.length() < 3) {
		throw std::invalid_argument("The length of the name should be at least 3 letters long\n");
	}
	if (bal < 0.0) {
		throw std::invalid_argument("The balance can't be negative!\n");
	}
	name = n;
	balance = bal;
	secretKeys = generateSecretKeys();
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

namespace UserInformation {

	void printDataUsers() {
		for (const auto& pair : dataUsers) {
			std::cout << "-----   Account   -----\n";
			std::cout << "Name of the account: " << pair.first << '\n';
			std::cout << "Balance on this account: $" << pair.second.getBalance() << "\n\n";
		}
		std::cout << "-----   That's all!   -----\n\n";

	}

	//***
		// Future implementation of checking secret key combination //
		//std::vector<std::string> keyMap;
		//for (int i = 0; i < 6; i++) {
		//	std::string key;
		//	std::cout << "Enter the secret key combination!\n";
		//	std::getline(cin, key);
		//	keyMap.push_back(key);
		//	std::cin.clear();
		//	std::cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
		//}

	//***

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
}