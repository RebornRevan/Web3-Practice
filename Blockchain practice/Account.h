#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>

class Account;
//Library for creating secret keys(consists of 6 key words), Сборник для создания секретного ключа(состоит из 6 слов)
extern const std::vector<std::string> library;

//All information about users, Вся информация о пользователях
extern std::unordered_map<std::string, Account> dataUsers;

class Account {
private:
	std::string name;		//Name of account, имя аккаунта
	std::string password;		//Password for account, пароль от аккаунта
	double balance;		//Balance of account, баланс аккаунта
	std::vector<std::string> secretKeys;	//Vector of secret keys, вектор секретных ключей
public:
	Account(const std::string& n, double bal);

	// Getters for name and balance, геттеры для имени и баланса
	std::string getName() const;
	double getBalance() const;

	// Simple adding money to the account(in the future will be divided by whom: account user itself or by other user),
	// Добавляет деньги на счет(потом будет разделено на пополнение счета и на перевод с другого счета)
	void deposit(double amount);

	// Withdraw money from account(same as deposit plans, but it will be about withdrawing money from the account), Вывод денег с аккаунта(планы такие же, как и у deposit, вывод денег с аккаунта)
	void withdraw(double amount);

	//Generate secret keys for an account using std::randomdevice, Генерация ключей для аккаунта через функцию std::randomdevice
	std::vector<std::string> generateSecretKeys() const;

};

namespace UserInformation {
	void addUser(const Account& user);
	void printDataUsers();
}