#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>

class Account {
private:
	std::string name;		//Name of account, имя аккаунта
	std::string password;		//Password for account, пароль от аккаунта
	double balance;		//Balance of account, баланс аккаунта
	std::vector<std::string> secretKeys;	//Vector of secret keys, вектор секретных ключей
	std::string passwordHash;		//Hash of the password, хэш пароля

	//Library for creating secret keys(consists of 6 key words), Сборник для создания секретного ключа(состоит из 6 слов)
	static const std::vector<std::string> library;

	// Getter for transforming password into sha256 for exporting it into JSON, Геттер для получения sha256 пароля, чтобы занести их в JSON
	std::string SHAPassword() const;
public:
	Account(const std::string& n, const std::string& pass, double bal);

	// Functions about password, Функции для пароля
	bool verifyPassword(const std::string& inputPass) const;
	void setPassword(const std::string& pass);


	// Getters for name and balance, геттеры для имени и баланса
	std::string getName() const;
	double getBalance() const;

	// Simple adding money to the account,
	// Добавляет деньги на счет
	void deposit(double amount);

	// Withdraw money from account, Вывод денег с аккаунта
	void withdraw(double amount);

	//Generate secret keys for an account using std::randomdevice, Генерация ключей для аккаунта через функцию std::randomdevice
	std::vector<std::string> generateSecretKeys() const;


	void showSecretKeys() const;

	// Function to verify entered secret Key combination (returns True or False), Функция для подтверждение введенных ключей (возвращает True или False)
	bool verifyKeys() const;
	
	//// Getters for transforming password and secret keys into sha256 for exporting it into JSON, Геттеры для получения sha256 пароля и сидов, чтобы занести их в JSON
	//std::string SHAPassword() const;
	std::string SHASecretKeys() const;

	// Getter for hashed password, Геттер для захешированного пароля
	std::string getPasswordHash() const;

};

namespace UserInformation {

	//Function to add user(also checks if username is not already in the dataUsers(in the future need to add checking the secret key combination),
	//Функция для добавления пользователя в dataUsers + проверка на наличие имени пользователя в dataUsers(в будщем надо добавить проверку на комбинацию ключей)
	void addUser(const Account& user);
	void printDataUsers();

	// Function to check amount of users in DataBase, проверка на кол-во пользователей
	size_t getUsersCount();

	// Check if user is in the database, проверка на наличие пользователя в базе данных
	bool hasUser(const std::string& name);

	// Creates a transaction, Создает перевод
	void proccessTransfer(const std::string& sender, const std::string& receiver, double amount);

	// Log into the session of user, Вход в аккаунт пользователя
	bool loginIntoAccount(const std::string& name);

	// Recovery access by secret keys, Восстановление доступа к аккаунту по секретным ключам
	bool recoverAccountAccess(const std::string& name);

	// Collect all information about users and then, transform it to the JSON, Собрав информацию о пользователях, загружаем все в JSON
	bool transformUsersToJSON();

}