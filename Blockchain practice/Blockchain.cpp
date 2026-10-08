#include "Blockchain.h"


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
	for (auto& block : blockchain) {
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

