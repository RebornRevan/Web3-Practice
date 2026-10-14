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

	//Library for creating secret keys(consists of 6 key words), Сборник для создания секретного ключа(состоит из 6 слов)
	static const std::vector<std::string> library;
public:
	Account(std::string& n,std::string& pass, double bal);

	// Functions about password, Функции для пароля
	bool verifyPassword(std::string& inputPass) const;
	void setPassword(std::string& pass);


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

};

namespace UserInformation {
	void addUser(const Account& user);
	void printDataUsers();

	// Function to check amount of users in DataBase, проверка на кол-во пользователей
	size_t getUsersCount();

	// Check if user is in the database, проверка на наличие пользователя в базе данных
	bool hasUser(std::string& name);

	void proccessTransfer(std::string& sender, std::string& receiver, double amount);

	// Log into the session of user, Вход в аккаунт пользователя
	bool loginIntoAccount(std::string& name);

	// Check the validility of secret keys combination, проверка на комбинацию секретных ключей
	bool recoverAccountAccess(std::string& name);

}