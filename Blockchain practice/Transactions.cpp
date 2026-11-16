#include "Transaction.h"
#include "Account.h"

Transaction::Transaction(const std::string s, const std::string r, double a) : sender(s), receiver(r), amount(a) {}

std::string Transaction::getSender() const { return sender; }

std::string Transaction::getReceiver() const { return receiver; }

double Transaction::getAmount() const { return amount; }
