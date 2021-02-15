#include <cstring>
#include <iostream>
// to make password with '*'
#include <conio.h>
// to write on Bulgarian
#include <clocale>

using namespace std;

const int MAX_PRODUCTS_COUNT = 100;
const int MAX_ORDERS_COUNT = 100;
const int MAX_ACCOUNTS_COUNT = 100;
const int MAX_BUFFER = 1024;
// for username and password
const int MAX_SYMBOLS = 13;

int g_currentProductId = 1;
int g_currentOrderId = 1;
int generateUniqueProductId()
{
	return g_currentProductId++;
}
int generateUniqueOrderId()
{
	return g_currentOrderId++;
}

enum OrderStatus
{
	SHIPPED = 2,
	WAITING = 1,
	DELIVERED = 3
};
class Order
{
public:
	// auto incrementing id
	Order(int productId, int quantity, char* address, char* user)
		: m_productId(productId),
		m_quantity(quantity)
	{
		m_status = WAITING;
		m_address = new char[strlen(address) + 1];
		strcpy_s(m_address, strlen(address) + 1, address);
		strcpy_s(m_user, MAX_SYMBOLS, user);
		m_id = generateUniqueOrderId();
	}
	~Order()
	{
		delete[] m_address;
	}
	int getId() const
	{
		return m_id;
	}
	char* getAddress() const
	{
		return m_address;
	}
	int getProductId() const
	{
		return m_productId;
	}
	int getQuantity() const
	{
		return m_quantity;
	}
	OrderStatus getStatus() const
	{
		return m_status;
	}
	const char* getStatusChar() const
	{
		if(m_status == SHIPPED)
			return "SHIPPED";
		if(m_status == WAITING)
			return "WAITING";
		if(m_status == DELIVERED)
			return "DELIVERED";
		return nullptr;
	}
	const char* getUser() const
	{
		return m_user;
	}
	void changeStatus()
	{
		switch(m_status)
		{
		case WAITING: m_status = SHIPPED;  cout << "Успешно променихте статуса на SHIPPED." << endl;  break;
		case SHIPPED: m_status = DELIVERED;  cout << "Успешно променихте статуса на DELIVERED." << endl;  break;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const Order& other);

private:
	int m_id;
	char* m_address;
	int m_productId;
	int m_quantity;
	char m_user[MAX_SYMBOLS];
	OrderStatus m_status;
};
std::ostream& operator<<(std::ostream& out, const Order& other)
{
	out << "<------>" << endl;
	out << "ID номер: " << other.getId() << endl;
	out << "Продукт номер: " << other.getProductId() << endl;
	out << "Количество: " << other.m_quantity << " бр." << endl;
	out << "Адрес: " << other.getAddress() << endl;
	out << "Потребител: " << other.getUser() << endl;
	out << "Статус: " << other.getStatusChar() << endl;
	out << ">------<" << endl;
	out << endl;
	return out;
}

class Product {
public:
	// auto incrementing id
	Product(char* name, double price, char* desciption)
		: m_price(price)
	{
		setName(name);
		setDescription(desciption);
		m_id = generateUniqueProductId();
	}
	~Product()
	{
		delete[] m_description;
	}
	int getId() const
	{
		return m_id;
	}
	double getPrice() const
	{
		return m_price;
	}
	void setPrice(double price)
	{
		m_price = price;
	}
	char* getName() const
	{
		return (char*) m_name;
	}
	void setName(char* name)
	{
		strcpy_s(m_name, strlen(name) + 1, name);
	}
	char* getDescription() const
	{
		return m_description;
	}
	void setDescription(char* description)
	{
		delete[] m_description;
		m_description = new char[strlen(description) + 1];
		strcpy_s(m_description, strlen(description) + 1, description);
	}

	friend std::ostream& operator<<(std::ostream& out, const Product& other);

private:
	int m_id;
	double m_price;
	char m_name[100];
	char* m_description;
};
std::ostream& operator<<(std::ostream& out, const Product& other)
{
	out << "<------>" << endl;
	out << "ID номер: " << other.getId() << endl;
	out << "Име: " << other.getName() << endl;
	out << "Цена: " << other.getPrice() << " лв." << endl;
	out << "Описание: " << other.getDescription() << endl;
	out << ">------<" << endl;
	out << endl;
	return out;
}

class Account
{
public:
	Account(char* username, char* password, char* email, char* name, char* address): m_status(0)
	{
		strcpy_s(m_username, strlen(username) + 1, username);
		strcpy_s(m_password, strlen(password) + 1, password);
		m_email = new char[strlen(email) + 1];
		strcpy_s(m_email, strlen(email) + 1, email);
		m_name = new char[strlen(name) + 1];
		strcpy_s(m_name, strlen(name) + 1, name);
		m_address = new char[strlen(address) + 1];
		strcpy_s(m_address, strlen(address) + 1, address);
	}
	Account(Account const& other)
	{
		copy(other);
	}
	Account& operator=(Account const& other)
	{
		if(this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	~Account()
	{
		del();
	}
	bool getStatus() const
	{
		return m_status;
	}
	const char* getUsername() const
	{
		return m_username;
	}
	const char* getPassword() const
	{
		return m_password;
	}
	const char* getAddress() const
	{
		return m_address;
	}
	void setStatus(bool status)
	{
		m_status = status;
	}
	void setPassword(char* password)
	{
		strcpy_s(m_password, strlen(password) + 1, password);
	}
	void setEmail(char* email)
	{
		delete[] m_email;
		m_email = new char[strlen(email) + 1];
		strcpy_s(m_email, strlen(email) + 1, email);
	}
	void setName(char* name)
	{
		delete[] m_name;
		m_name = new char[strlen(name) + 1];
		strcpy_s(m_name, strlen(name) + 1, name);
	}
	void setAddress(char* address)
	{
		delete[] m_address;
		m_address = new char[strlen(address) + 1];
		strcpy_s(m_address, strlen(address) + 1, address);
	}
	bool truePassword(char* password)
	{
		return !(strcmp(m_password, password));
	}

	friend std::ostream& operator<< (std::ostream& out, const Account& other);

private:
	// user = 0, admin = 1
	bool m_status;
	char m_username[MAX_SYMBOLS];
	char m_password[MAX_SYMBOLS];
	char* m_email;
	char* m_name;
	char* m_address;

	void del()
	{
		delete[] m_email;
		delete[] m_name;
		delete[] m_address;
	}
	void copy(Account const& other)
	{
		m_status = other.m_status;
		strcpy_s(m_username, strlen(other.m_username) + 1, other.m_username);
		strcpy_s(m_password, strlen(other.m_password) + 1, other.m_password);
		m_email = new char[strlen(other.m_email) + 1];
		strcpy_s(m_email, strlen(other.m_email) + 1, other.m_email);
		m_name = new char[strlen(other.m_name) + 1];
		strcpy_s(m_name, strlen(other.m_name) + 1, other.m_name);
		m_address = new char[strlen(other.m_address) + 1];
		strcpy_s(m_address, strlen(other.m_address) + 1, other.m_address);
	}
};
std::ostream& operator<<(std::ostream& out, const Account& other)
{
	out << "<------>" << endl;
	out << "Потребителско име: " << other.m_username << endl;
	out << "Статус: ";
	if(other.m_status) out << "администратор" << endl;
	else out << "потребител" << endl;
	out << "Име: " << other.m_name << endl;
	out << "Имейл: " << other.m_email << endl;
	if(!other.m_status)
		out << "Адрес: " << other.m_address << endl;
	out << ">------<" << endl;
	out << endl;
	return out;
}

class BickieShop
{
public:
	BickieShop()
	{
		m_productsCount = 0;
		m_ordersCount = 0;
		m_accountsCount = 0;
	}
	~BickieShop()
	{
		for(int i = 0; i < m_productsCount; ++i)
			delete m_products[i];
		for(int i = 0; i < m_ordersCount; ++i)
			delete m_orders[i];
		for(int i = 0; i < m_accountsCount; ++i)
			delete m_accounts[i];
	}

	/*****************
	*  Order utils  *
	*****************/

	Order* findOrderById(int id)
	{
		for(int i = 0; i < m_ordersCount; ++i)
			if(m_orders[i]->getId() == id)
				return m_orders[i];
		return nullptr;
	}
	void addOrder(int productId, int quantity, char* address, char* user = (char*) "guest")
	{
		if(m_ordersCount < MAX_ORDERS_COUNT)
		{
			m_orders[m_ordersCount] = new Order(productId, quantity, address, user);
			m_ordersCount++;
		}
		else cout << "Опитайте пак по-късно, в момента нямаме възможност да изпълним поръчката Ви." << endl;
	}
	void removeOrder(int orderId)
	{
		for(int i = 0; i < m_ordersCount; ++i)
			if(m_orders[i]->getId() == orderId)
			{
				delete m_orders[i];
				for(int j = i; j < m_ordersCount - 1; ++j)
					m_orders[j] = m_orders[j + 1];
				--m_ordersCount;
			}
	}
	enum sortBy
	{
		BY_ID,
		BY_PRODUCT,
		BY_STATUS
	};
	Order** sortOrdersBy(Order** orders, sortBy sort)
	{
		Order* temp;
		bool flag = 0;

		for(int i = 0; i < m_ordersCount - 1; ++i)
			for(int j = 0; j < m_ordersCount - i - 1; ++j)
			{
				switch(sort)
				{
				case BY_ID: flag = (orders[j]->getId() > orders[j + 1]->getId()); break;
				case BY_PRODUCT: flag = (orders[j]->getProductId() > orders[j + 1]->getProductId()); break;
				case BY_STATUS: flag = (orders[j]->getStatus() > orders[j + 1]->getStatus()); break;
				}
				if(flag)
				{
					temp = orders[j + 1];
					orders[j + 1] = orders[j];
					orders[j] = temp;
				}
			}
		return orders;
	}

	/*******************
	*  Product utils  *
	*******************/

	Product* findProductById(int id)
	{
		for(int i = 0; i < m_productsCount; ++i)
			if(m_products[i]->getId() == id)
				return m_products[i];
		return nullptr;
	}
	void addProduct(char* name, double price, char* desciption)
	{
		if(m_productsCount < MAX_PRODUCTS_COUNT)
		{
			m_products[m_productsCount] = new Product(name, price, desciption);
			m_productsCount++;
		}
		else
			cerr << "Магазинът е пълен! Не могат да се добавят повече продукти!";
	}
	void editProduct(int id, char* name = nullptr, char* desc = nullptr, double price = -1)
	{
		Product* product = findProductById(id);

		if(name)
			product->setName(name);
		if(desc)
			product->setDescription(desc);
		if(price >= 0)
			product->setPrice(price);
	}
	void removeProduct(int productId)
	{
		for(int i = 0; i < m_productsCount; ++i)
			if(m_products[i]->getId() == productId)
			{
				delete m_products[i];
				for(int j = i; j < m_productsCount - 1; ++j)
					m_products[j] = m_products[j + 1];
				--m_productsCount;
			}
	}

	/*******************
	*  Accounts utils  *
	*******************/

	void addAccount(char* username, char* password, char* email, char* name, char* address)
	{
		if(m_accountsCount < MAX_ACCOUNTS_COUNT)
		{
			m_accounts[m_accountsCount] = new Account(username, password, email, name, address);
			m_accountsCount++;
		}
		else cout << "В момента не можем да Ви регистрираме. Моля, опитайте по-късно.";
	}
	void makeAdmin(char* username)
	{
		for(int i = 0; i < m_accountsCount; ++i)
			if(!strcmp(m_accounts[i]->getUsername(), username))
				m_accounts[i]->setStatus(1);
	}
	Account* findAccountByUsername(char* username)
	{
		for(int i = 0; i < m_accountsCount; ++i)
			if(!strcmp(m_accounts[i]->getUsername(), username))
				return m_accounts[i];
		return nullptr;
	}
	// if the email contains '@'
	bool realEmail(char* email)
	{
		for(unsigned i = 0; i < (strlen(email)); ++i)
			if(email[i] == '@') return 1;
		return 0;
	}

	/***********
	*  VIEWS  *
	************/

	void showIndexView()
	{
		currUser = nullptr;

		cout << endl;
		cout << "Ако искате да влезете в профила си, моля натиснете 1." << endl;
		cout << "Ако искате да се регистрирате, моля натиснете 2." << endl;
		cout << "Ако искате да продължите без регистрация, моля натиснете 3." << endl;

		char answer = '0';
		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3');

		switch(answer)
		{
		case '1': cin.ignore(); showLogInView(); break;
		case '2': showSighInView(); break;
		case '3': showProductsListView(m_products, m_productsCount); break;
		default: showIndexView();
		}
	}
	void showLogInView()
	{
		char password[MAX_SYMBOLS];
		char user[MAX_SYMBOLS];
		char tempPass;
		int i = 0;
		bool status = 0;
		bool flagPass = 1;

		do
		{
			cout << "username: ";
			cin.getline(user, MAX_SYMBOLS);
			currUser = findAccountByUsername(user);

			if(currUser)
			{
				do
				{
					cout << "password: ";
					// to view password as *****
					do
					{
						tempPass = _getch();
						if(tempPass != 13)
						{
							cout << "*";
							password[i] = tempPass;
						}
						else password[i] = '\0';
						++i;
					} while(i < MAX_SYMBOLS - 1 && tempPass != 13);
					if(i == MAX_SYMBOLS - 1) password[i] = '\0';
					cout << endl;
					i = 0;
					for(int i = 0; i < m_accountsCount; ++i)
						if(m_accounts[i]->truePassword(password))
						{
							flagPass = 0;
							cout << endl;
							cout << "Здравейте, влезнахте успешно в профила си!" << endl;
							status = m_accounts[i]->getStatus();
						}
					if(flagPass) cout << "Невалиднa парола. Моля, опитайте отново." << endl;
				} while(flagPass);
			}
			else
			{
				cout << endl;
				cout << "Невалидно потребителско име." << endl;
				showIndexView();
			}
		} while(!currUser);

		if(status)
			showAdminView();
		else
			showUserView();
	}
	void showSighInView()
	{
		char username[MAX_SYMBOLS];
		char password[MAX_SYMBOLS];
		char* email;
		char* name;
		char* address;
		char buffer[MAX_BUFFER];

		cout << "!!! Потребителското Ви име трябва да е до 12 символа." << endl;
		cout << "username: ";
		cin.ignore();
		cin.getline(username, MAX_SYMBOLS);
		while(findAccountByUsername(username))
		{
			cout << endl;
			cout << "Това потребителско име вече е заето, моля въведете друго." << endl;
			cout << "!!! Потребителското Ви име трябва да е до 12 символа." << endl;
			cout << "username: ";
			cin.getline(username, MAX_SYMBOLS);
		}

		cout << "!!! Паролата Ви трябва да е до 12 символа." << endl;
		cout << "password: ";
		cin.getline(password, MAX_SYMBOLS);

		cout << "email: ";
		cin.getline(buffer, MAX_BUFFER);
		while(!realEmail(buffer))
		{
			cout << "Невалиден имейл! Въведете отново!" << endl;
			cout << "email: ";
			cin.getline(buffer, MAX_BUFFER);
		}
		email = new char[strlen(buffer) + 1];
		strcpy_s(email, strlen(buffer) + 1, buffer);

		cout << "Въведете имената си: ";
		cin.getline(buffer, MAX_BUFFER);
		name = new char[strlen(buffer) + 1];
		strcpy_s(name, strlen(buffer) + 1, buffer);

		cout << "Въведете адреса си: ";
		cin.getline(buffer, MAX_BUFFER);
		address = new char[strlen(buffer) + 1];
		strcpy_s(address, strlen(buffer) + 1, buffer);

		addAccount(username, password, email, name, address);
		cout << "Вие се регистрирахте успешно. Моля, влезте в профила си." << endl;
		showLogInView();
	}

	/*****************
	*  User pages  *
	*****************/

	void showUserView()
	{
		cout << endl;
		cout << "Ако искате да разгледате нашите продукти, моля натиснете 1." << endl;
		cout << "Ако искате да видите вашите поръчки, моля натиснете 2." << endl;
		cout << "Ако искате да редактирате профила си, моля натиснете 3." << endl;
		cout << "Ако искате да излезете от профила си, моля натиснете 4." << endl;

		char answer = '0';
		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3' && answer != '4');

		switch(answer)
		{
		case '1': showProductsListView(m_products, m_productsCount); break;
		case '2': showMyOrdersView(); break;
		case '3': showEditAccountView(currUser); break;
		case '4': showIndexView(); break;
		default: showIndexView();
		}
	}
	void showProductsListView(Product** products, int count)
	{
		cout << endl;
		cout << "Предлагаме Ви следния асортимент от продукти: " << endl;
		cout << endl;

		for(int i = 0; i < count; ++i)
		{
			cout << "<------>" << endl;
			cout << "ID номер: " << products[i]->getId() << endl;
			cout << "Име: " << products[i]->getName() << endl;
			cout << "Цена: " << products[i]->getPrice() << " лв." << endl;
			cout << ">------<" << endl;
			cout << endl;
		}

		cout << "Ако искате да разгледате/купите продукт, моля въведете неговия ID номер." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 0." << endl;

		int answer;
		do
		{
			cin >> answer;
			if(answer == 0)
			{
				cout << "Връщане назад..." << endl;
				if(currUser) showUserView();
				else showIndexView();
			}
			else if(findProductById(answer)) showProductDetailsView(findProductById(answer));
			else cout << "Няма такъв продукт, моля въведете отново." << endl;
		} while(!findProductById(answer));
	}
	void showProductDetailsView(Product* product)
	{
		cout << endl;
		cout << "======" << endl;
		cout << "===== " << product->getName() << " =====" << endl;
		cout << "Описание: " << product->getDescription() << endl;
		cout << "Цена: " << product->getPrice() << " лв." << endl;

		cout << "Искате ли да го купите? (y/n)" << endl;
		char answer;
		cin >> answer;
		int quantity = 1;

		switch(answer)
		{
		case 'Y':
		case 'y':
			cout << "Колко броя искате да закупите?" << endl;
			cin >> quantity;
			while(quantity == 0)
			{
				cout << "Не може да поръчате 0 продукта. Моля, въведете отново желаната бройка." << endl;
				cin >> quantity;
			}
			cout << "Завършване на поръчката..." << endl;
			if(currUser) showOrderViewUser(product, quantity);
			else  showOrderViewGuest(product, quantity);
			break;
		case 'N':
		case 'n':
			cout << "Връщане назад..." << endl;
			showProductsListView(m_products, m_productsCount);
			break;
		default:
			cout << "Грешка!" << endl;
			showProductsListView(m_products, m_productsCount);
		}
	}
	void showOrderViewUser(Product* product, int quantity)
	{
		cout << endl;
		cout << "============ ============= ==============" << endl;
		cout << "Ще закупите: " << product->getName() << endl;
		cout << "Количество: " << quantity << " бр." << endl;
		cout << "Крайна цена: " << (product->getPrice()) * quantity << " лв." << endl;
		cout << "Доставка на адрес: " << currUser->getAddress() << endl;

		cout << endl;
		cout << "Искате ли да завършите окончателно поръчката си? (y/n)" << endl;

		char answer = '0';

		do
		{
			cin >> answer;
		} while(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');

		switch(answer)
		{
		case 'Y':
		case 'y':
			cout << endl;
			cout << "Благодарим Ви, че пазарувахте от нашия магазин!" << endl;
			cout << "Ще Ви изпратим имейл, за да потвърдим поръчката!" << endl;
			addOrder(product->getId(), quantity, (char*) (currUser->getAddress()), (char*) (currUser->getUsername()));
			break;
		case 'N':
		case 'n':
			cout << "Връщане назад..." << endl;
			showProductDetailsView(product);
			break;
		default:
			cout << "Грешка!" << endl;
			showProductDetailsView(product);
		}

		cout << endl;
		cout << "Ако искате да разгледате нашите продукти отново, моля натиснете 1." << endl;
		cout << "Ако искате да видите направените поръчки, моля натиснете 2." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 3." << endl;

		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3');
		switch(answer)
		{
		case '1': showProductsListView(m_products, m_productsCount); break;
		case '2': showMyOrdersView(); break;
		case '3': showUserView(); break;
		default: showIndexView();
		}
	}
	void showOrderViewGuest(Product* product, int quantity)
	{
		cout << endl;
		cout << "============ ============= ==============" << endl;
		cout << "Ще закупите: " << product->getName() << endl;
		cout << "Количество: " << quantity << " бр." << endl;
		cout << "Крайна цена: " << (product->getPrice()) * quantity << " лв." << endl;

		char buffer[200];

		cout << "Моля, добавете име, адрес и имейл:" << endl;
		cin.ignore();
		cin.getline(buffer, 200);
		addOrder(product->getId(), quantity, (char*) buffer);

		cout << endl;
		cout << "Благодарим Ви, че пазарувахте от нашия магазин!" << endl;
		cout << "Ще Ви изпратим имейл, за да потвърдим поръчката." << endl;
		cout << endl;

		cout << "Ако искате да разгледате нашите продукти отново, моля натиснете 1." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 2." << endl;

		char answer = '0';
		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2');
		switch(answer)
		{
		case '1': showProductsListView(m_products, m_productsCount); break;
		case '2': showIndexView(); break;
		default: showIndexView();
		}
	}
	void showMyOrdersView()
	{
		cout << endl;
		cout << "Вашите поръчки са:" << endl;

		bool flag = 1;

		for(int i = 0; i < m_ordersCount; ++i)
			if(!strcmp(m_orders[i]->getUser(), currUser->getUsername()))
			{
				flag = 0;
				cout << *m_orders[i];
			}
		if(flag) cout << "Още не сте направили поръчки." << endl << endl;

		cout << "Ако искате да отмените някоя поръчка, моля въведете ID номера й." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 0." << endl;

		int answer = 0;
		do
		{
			cin >> answer;
			if(answer == 0) showUserView();
			else if(findOrderById(answer))
			{
				if(findOrderById(answer)->getStatus() == WAITING)
				{
					removeOrder(answer);
					cout << "Отменихте поръчката успешно!" << endl;
					showMyOrdersView();
				}
				else if(findOrderById(answer)->getStatus() == SHIPPED)
				{
					cout << "Продуктът вече е изпратен. Не може да отмените поръчката." << endl;
					showUserView();
				}
				else
				{
					cout << "Поръчката е завършена. Не може да я отмените." << endl;
					showUserView();
				}
			}
		} while(!findOrderById(answer));
	}
	void showEditAccountView(Account* user)
	{
		cout << endl;
		cout << "Ако исксате да редактирате" << endl;
		cout << "    паролата си, моля натиснете 1." << endl;
		cout << "    имейла си, моля натиснете 2." << endl;
		cout << "    името си, моля натиснете 3." << endl;
		cout << "    адрса си, моля натиснете 4." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 5." << endl;

		char answer = '0';

		char tempPass[MAX_SYMBOLS];
		char buffer[MAX_BUFFER];

		if(currUser)
		{
			do
			{
				cin >> answer;
			} while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5');

			switch(answer)
			{
			case '1':
				cout << "!!! Паролата Ви трябва да е до 12 символа." << endl;
				cout << "Моля, въведете новата парола: ";
				cin.ignore();
				cin.getline(tempPass, MAX_SYMBOLS);
				user->setPassword(tempPass);
				cout << endl;
				cout << "Успешно променихте паролата си." << endl;
				showEditAccountView(currUser);
				break;
			case '2':
				cout << "Въведете нов имейл: ";
				cin.ignore();
				cin.getline(buffer, MAX_BUFFER);
				while(!realEmail(buffer))
				{
					cout << "Невалиден имейл! Въведете отново!" << endl;
					cout << "email: ";
					cin.getline(buffer, MAX_BUFFER);
				}
				user->setEmail(buffer);
				cout << endl;
				cout << "Успешно променихте имейла си." << endl;
				showEditAccountView(currUser);
				break;
			case '3':
				cout << "Въведете имената си: ";
				cin.ignore();
				cin.getline(buffer, MAX_BUFFER);
				user->setName(buffer);
				cout << endl;
				cout << "Успешно променихте имената си." << endl;
				showEditAccountView(currUser);
				break;
			case '4':
				cout << "Въведете адреса си: ";
				cin.ignore();
				cin.getline(buffer, MAX_BUFFER);
				user->setAddress(buffer);
				cout << endl;
				cout << "Успешно променихте адреса си." << endl;
				showEditAccountView(currUser);
				break;
				break;
			case '5': showUserView(); break;
			default: showIndexView();
			}
		}
		else
		{
			cout << "Грешка!" << endl;
			showIndexView();
		}
	}

	/*****************
	*  Admin pages  *
	*****************/

	void showAdminView()
	{
		cout << endl;
		cout << "Ако искате да видите наличните продукти, моля натиснете 1." << endl;
		cout << "Ако искате да видите текущите поръчки, моля натиснете 2." << endl;
		cout << "Ако искате да видите наличните профили, моля натиснете 3." << endl;
		cout << "Ако искате да излезете профила си, моля натиснете 4." << endl;

		char answer = '0';
		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3' && answer != '4');

		switch(answer)
		{
		case '1': showProductsView(m_products); break;
		case '2': showOrdersView(sortOrdersBy(m_orders, BY_ID));  break;
		case '3': showAccountsView(m_accounts); break;
		case '4': showIndexView(); break;
		default: showIndexView();
		}
	}
	void showProductsView(Product** products)
	{
		cout << endl;
		cout << "Продуктите, предлагани в магазина са:" << endl;
		cout << endl;
		for(int i = 0; i < m_productsCount; i++)
			cout << *(products[i]);

		cout << "Ако искате да редактирате някой продукт, моля натиснете 1." << endl;
		cout << "Ако искате да добавите нов продукт, моля натиснете 2." << endl;
		cout << "Ако искате да изтриете продукт, моля натиснете 3." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 4." << endl;

		char answer = '0';
		int answerEdit = 0;
		int answerDel = 0;

		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3' && answer != '4');

		switch(answer)
		{
		case '1':
			cout << "Въведете ID номера на продукта, който искате да редактирате: ";
			cin >> answerEdit;
			showEditProductView(findProductById(answerEdit));
			break;
		case '2': showAddProductView(); break;
		case '3':
			cout << "Въведете ID номера на продукта, който искате да изтриете: ";
			cin >> answerDel;
			removeProduct(answerDel);
			cout << "Изтрихте продукта успешно!" << endl;
			cout << endl;
			showProductsView(m_products);
			break;
		case '4': showAdminView(); break;
		default: showIndexView();
		}
	}
	void showEditProductView(Product* product)
	{
		cout << endl;
		cout << "Ако искате да редактирате" << endl;
		cout << "    името, моля натиснете 1." << endl;
		cout << "    цената, моля натиснете 2." << endl;
		cout << "    описанието, моля натиснете 3." << endl;
		cout << "Ако искате да се върнете към наличните продукти, моля натиснете 4." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 5." << endl;

		char answer = '0';
		char buffer[MAX_BUFFER];
		double tempPrice;

		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3' && answer != '4' && answer != '5');

		switch(answer)
		{
		case '1':
			cout << "Въведете новото име: ";
			cin.ignore();
			cin.getline(buffer, MAX_BUFFER);
			product->setName(buffer);
			showEditProductView(findProductById(product->getId()));
			break;
		case '2':
			cout << "Въведете нова цена: ";
			cin >> tempPrice;
			product->setPrice(tempPrice);
			showEditProductView(findProductById(product->getId()));
			break;
		case '3':
			cout << "Въведете новото описание: ";
			cin.ignore();
			cin.getline(buffer, MAX_BUFFER);
			product->setDescription(buffer);
			showEditProductView(findProductById(product->getId()));
			break;
		case '4': showProductsView(m_products);; break;
		case '5': showAdminView(); break;
		default: showIndexView();
		}
	}
	void showAddProductView()
	{
		char tempName[100];
		double tempPrice;
		char buffer[MAX_BUFFER];

		cout << endl;
		cout << "Въведете име на продукта: " << endl;
		cin.ignore();
		cin.getline(tempName, 100);
		cout << "Въведете цена на продукта: " << endl;
		cin >> tempPrice;
		cout << "Въведете описание на продукта: " << endl;
		cin.ignore();
		cin.getline(buffer, MAX_BUFFER);

		addProduct(tempName, tempPrice, buffer);
		cout << endl;
		cout << "Добавихте продукт успешно!" << endl;
		cout << endl;
		showProductsView(m_products);
	}
	void showOrdersView(Order** orders)
	{
		cout << endl;
		cout << "Текущи поръчки: " << endl;
		if(m_ordersCount == 0) cout << "Няма налични поръчки." << endl << endl;
		else
			for(int i = 0; i < m_ordersCount; i++)
				cout << *(orders[i]);

		cout << "Ако искате да подредите поръчките по продкт, моля натиснете 1." << endl;
		cout << "Ако искате да подредите поръчките по статус, моля натиснете 2." << endl;
		cout << "Ако искате да промените статуса на някоя поръчка, моля натиснете 3." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 4." << endl;

		char answer;
		do
		{
			cin >> answer;
		} while(answer != '1' && answer != '2' && answer != '3' && answer != '4');

		switch(answer)
		{
		case '1': showOrdersView(sortOrdersBy(m_orders, BY_PRODUCT)); break;
		case '2': showOrdersView(sortOrdersBy(m_orders, BY_STATUS)); break;
		case '3': showEditOrderView(); break;
		case '4': showAdminView(); break;
		}
	}
	void showEditOrderView()
	{
		cout << "Моля, въведете ID номера на поръчката, чийто статус искате да промените." << endl;
		cout << "Ако искате да се върнете към списъка с поръчки, моля натиснете 0." << endl;

		int answer = 0;
		do
		{
			cin >> answer;
			if(answer == 0) showOrdersView(m_orders);
			else if(findOrderById(answer))
				if(findOrderById(answer)->getStatus() == DELIVERED)
				{
					cout << "Поръчката вече е доставена, не може да промените статуса." << endl;
					showOrdersView(m_orders);
				}
				else
				{
					findOrderById(answer)->changeStatus();
					showEditOrderView();
				}
			else
			{
				cout << "Грешка! Няма такава поръчка!" << endl;
				cout << endl;
				showEditOrderView();
			}
		} while(!findProductById(answer));
	}
	void showAccountsView(Account** Accounts)
	{
		cout << endl;
		cout << "Налични профили: " << endl;
		cout << endl;
		for(int i = 0; i < m_accountsCount; i++)
			cout << *(Accounts[i]);

		cout << "Ако искате да направите някой акаунт администраторски, моля въведете потребителското му име." << endl;
		cout << "Ако искате да се върнете в началото, моля натиснете 0." << endl;

		char answer[MAX_SYMBOLS];
		do
		{
			cin.ignore();
			cin.getline(answer, MAX_SYMBOLS);
			if(!strcmp(answer, "0")) showAdminView();
			else if(findAccountByUsername(answer))
			{
				makeAdmin(answer);
				cout << endl;
				cout << "Успешно направихте профила " << answer << " администраторски." << endl;
				showAdminView();
			}
		} while(!findAccountByUsername(answer));
	}

private:
	Product* m_products[MAX_PRODUCTS_COUNT];
	int m_productsCount;

	Order* m_orders[MAX_ORDERS_COUNT];
	int m_ordersCount;

	Account* m_accounts[MAX_ACCOUNTS_COUNT];
	int m_accountsCount;

	// guest -> nullptr
	Account* currUser = nullptr;
};

int main()
{
	setlocale(LC_ALL, "bulgarian");

	BickieShop shop;

	shop.addProduct((char*) "мляко", 2, (char*) "прясно, 2%");
	shop.addProduct((char*) "маса", 79.99, (char*) "кръгла");
	shop.addProduct((char*) "лаптоп", 1001, (char*) "най-хубавия");
	shop.addProduct((char*) "картоф", 5, (char*) "варен");
	shop.addProduct((char*) "кофа", 3.8, (char*) "5 литра, синя");
	shop.addAccount((char*) "magi", (char*) "magi", (char*) "magi@magi", (char*) "magi", (char*) "magi");
	// admin profile cannot be created
	shop.addAccount((char*) "admin", (char*) "admin", (char*) "admin@admin", (char*) "admin", (char*) "admin");
	shop.makeAdmin((char*) "admin");

	cout << endl;
	cout << "Здравейте! Добре дошли в нашия магазин!" << endl;

	shop.showIndexView();

	system("pause");
	return 0;
}