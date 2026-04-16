#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <future>
// so that async code doesn't have a race condition
#include <mutex>

#include "Database.h"

class Warehouse
{
public:
	static void processOrders();
private:
};
#endif // !WAREHOUSE_H


