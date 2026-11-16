#include "Blockchain.h"
#include <fstream>
#include <cmath>

BlockChain::BlockChain(int len) : length(len) {
	blockchain.push_back(createGenBlock());
}


Block BlockChain::createGenBlock() {
	return Block(0, "0", std::vector<Transaction>());
}


Block BlockChain::getLastBlock() const {
	return blockchain.back();
}

void BlockChain::createBlock() {
	if (dataBaseForTransactions.size() == 0) {
		throw std::invalid_argument("Pool is empty, no operations were completed.\n");
	}

	// Creating new block and handle to him its transactions, Создаем новый блок и даем ему транзакции
	Block newBlock(static_cast<int>(blockchain.size()), getLastBlock().hash, dataBaseForTransactions);
	newBlock.mineBlock(length);
	blockchain.push_back(newBlock);


	//All information about Block deleted, Очищаем информацию о блоке
	dataBaseForTransactions.clear();
}

bool BlockChain::isHashValid() const {
	for (size_t i = 1; i < blockchain.size(); i++) {
		Block currentBlock = blockchain[i];
		Block previousBlock = blockchain[i - 1];

		if (currentBlock.calculateHash() != currentBlock.hash) {
			std::cout << "Error - Incorrect hash of block №" << i << '\n';
			return false;
		}
		if (currentBlock.prevHash != previousBlock.hash) {
			std::cout << "Error - Incorrect previous hash of block №" << i << '\n';
			return false;
		}
	}
	return true;
}


void BlockChain::printBlockChain() const {
	std::cout << "-----   Information about BlockChain   -----\n";
	for (const auto& block : blockchain) {
		std::cout << "-----   Block   -----\n";
		std::cout << "Index: " << block.index << '\n';
		std::cout << "Previous Hash: " << block.prevHash << '\n';
		std::cout << "Hash: " << block.hash << '\n';
		std::cout << "Nonce: " << block.nonce << '\n' << '\n';
		if (block.index != 0) {
			std::cout << "-----   All operations inside this Block   -----\n";
			for (const auto& pair : block.data) {
				std::cout << "The sender <" << pair.getSender() << "> had sent " << std::to_string(pair.getAmount()) << "$ to the receiver<" << pair.getReceiver() << ">\n";
			}
			std::cout << "-----   That's all!   -----\n\n";
		}
		else {
			std::cout << "-----   This is Genesis Block!   -----\n\n";
		}
	}
}

void BlockChain::proccessTransaction(const Transaction& tr) {
	if (tr.getSender() == tr.getReceiver()) {
		throw std::invalid_argument("The receiver can't be you!\n");
	}
	if (!UserInformation::hasUser(tr.getSender())) {
		throw std::runtime_error("The sender doesn't exist in the system\n");
	}
	if (!UserInformation::hasUser(tr.getSender())) {
		throw std::runtime_error("The receiver doesn't exist in the system\n");
	}

	UserInformation::proccessTransfer(tr.getSender(), tr.getReceiver(), tr.getAmount());
	addTransaction(tr);

	std::cout << "The sender <" + tr.getSender() + "> had sent " + std::to_string(tr.getAmount()) + "$ to the receiver <" + tr.getReceiver() + ">\n";
}

void BlockChain::addTransaction(const Transaction& tr) {
	dataBaseForTransactions.push_back(tr);
}


bool BlockChain::transformTransactionsToJSON() const {
	std::ofstream file("transactions.json");


	if (!file.is_open()) {
		std::cerr << "There is an error in opening the file!\n";
		return false;
	}
	file << "[\n";
	bool firstEntry = true;
	for (const auto& block : blockchain) {
		if (block.index == 0) {
			continue; //Skip genesis block, no transactions, Пропускаем первый блок, так как транзакций там нет
		}
		for (const auto& pair : block.data) {
			// To get correct format, Правильное форматирование файла
			if (!firstEntry) {
				file << ",\n";
			}
			firstEntry = false;

			// Avoiding mistakes with float numbers(when rounding), Не допускаем ошибки с дробными числами при округлении
			long long amountCents = std::llround(pair.getAmount() * 100.0);

			//JSON format, JSON формат
			file << "  {\n"
				<< "    \"blockIndex\": \"" << block.index << ",\n"
				<< "    \"senderName\": \"" << pair.getSender() << "\",\n"
				<< "    \"receiverName\": \"" << pair.getReceiver() << "\",\n"
				<< "    \"amountCents\": " << amountCents << "\n"
				<< "  }";
		}
	}
	file << "\n]\n";

	// Checks if something happens during writing, Проверка на прерывание записи
	if (file.fail()) {
		std::cerr << "Error while writing into the file\n";
		return false;
	}

	return true;
}