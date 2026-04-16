#include "Warehouse.h"

void Warehouse::processOrders()
{
	auto orders = Database::GetInstance().getUnprocessedOrders();
	std::vector<std::future<void>> futures;
	std::mutex sync;

	while (orders.size() != 0)
	{
		auto order = orders.front();
		// Executes asyncronously 
		futures.push_back(std::async([&](CartRecord order) {

			Email email;
			email.recipient = order.email;
			email.subject = "Order Shipped";
			email.message = "Your order has been shipped. Package should arive within the week";

			sync.lock();
			Database::GetInstance().setProcessedOrders(order);
			Database::GetInstance().addEmail(order.email,email);
			sync.unlock();

			}, order)
		);

		orders.pop();
	}
	
	for (int i = 0; i < futures.size(); i++)
	{
		futures[i].wait();
	}
}
