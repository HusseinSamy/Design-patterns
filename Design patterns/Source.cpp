#include <iostream> 
#include <string>
#include<vector>
#include<fstream>
using namespace std; 

// Single responsibility principle 
class journal
{

	string title;

public: 
	vector<string> entries; 

public: 
	journal(const string &title)
		: title(title), entries(NULL) {}

	void create_entrie(const string &entry)
	{
		static int count = 0; 
		entries.push_back(to_string(count++) + ": " + entry);
	}
};
class persistenceManager
{
public:
	static void save(const journal &jr, const string &filename )
	{
		ofstream file(filename);
		for (auto &el : jr.entries)
		{
			file << el << endl;
		}
	}
};













// Open-Closed pricnciple  (Open for extention, closed for modification)
	enum class Color { red, green, blue };
	enum class Size { small, medium, large };
	enum class BookType { SciFi, Novel, Technical };
struct product
{
	Color color;
	Size size;
	string name;
	product(string name, Color color, Size size)
		:name (name), color(color), size(size){};
};

struct book
 {
	 string name;
	 int pages; 
	 BookType type;
	 book(string name, int pages, BookType type)
		 : name{ name }, pages { pages }, type{ type } {}
 };

 template<typename T> class Specification
{ 
public:
	 virtual bool is_found(T *item) const = 0;
};

 //template <typename T> class Filter
 //{
 //public: 
	// virtual vector<T*> filter(vector<T*>, Specification<T>& spec) = 0;
 //};

 template<typename T> class AndSpecification : public Specification<T>
 {
 public:
	 Specification<T>& first; 
	 Specification<T>& second; 

	 AndSpecification(Specification<T> &first, Specification<T> &second)
		 : first{ first }, second{ second }{};
	  bool is_found(T* item)  const override
	 {
		 return (first.is_found(item) && second.is_found(item));
	 };
 };
 
 class colorSpecification : public Specification<product>
 {
 public:
	 Color color; 

	 colorSpecification(Color color)
		 :color{ color } {};

	 bool is_found(product *item) const override
	 {
		 return item->color == color;
	 }
 };

 class sizeSpecification : public Specification<product>
 {
 public:
	 Size size;

	 sizeSpecification(Size size)
		 :size{ size } {};

	 bool is_found(product* item) const override
	 {
		 return item->size == size;
	 }
 };

 template<typename T> class bookTypeSpecification : public Specification<T>
 {
 public:
	 BookType type;

	 bookTypeSpecification(BookType type)
		 :type{ type} {};

	 bool is_found(T* item) const override
	 {
		 return item->type == type;
	 }
 };

 template <typename T> class betterFilter
 {
 public: 
	 vector<T*> filter(vector<T*> items, Specification<T> &spec)
	 {
		 vector<T*> res;
		 for (auto el : items)
		 {
			 if (spec.is_found(el))
			 {
				 res.push_back(el);
			 }
		 }
		 return res;
	 }
 };

 template<typename T> class bettterOfBetterFilter 
 {
 public:
	 vector<T*> filter(vector<T*> items, Specification<T> &spec) 
	 {
		 vector<T*> res;
		 for (auto el : items)
		 {
			 if (spec.is_found(el))
			 {
				 res.push_back(el);
			 }
		 }
		 return res;
	 }
 };










 //Liskov principle
 class Rectangle
 {
 protected:
	 int width, height;
 public: 
	 Rectangle(int width, int height)
		 : width{ width }, height{ height } {}
	 virtual void set_width(int val)
	 {
		 width = val;
	 }
	 
	 virtual void set_height(int val)
	 {
		 height = val;
	 }
	 int get_width()
	 {
		 return width;
	 }

	 int area()
	 {
		 return width * height;
	 }
 };

 class Square : public Rectangle
 {
 public: 
	 void set_height(int val) override
	 {
		 this->height = this->width = val;
	 }

	 void set_width(int val) override
	 {
		 this->width =  this->height= val;
	 }

	 Square(int side)
		 : Rectangle(side, side) {}
 };

 void process(Rectangle& r)
 {

	 int w = r.get_width();
	 r.set_height(10);

	 cout << "Expected area: " << w * 10 << " , got: " << r.area() << endl;

 }






 // Interface Segregation principle
 struct Document
 {

 };

 class IPrinter
 {
 public:
	 virtual void print() = 0;
 };

 class IScanner
 {
 public:
	 virtual void scan() = 0;
 };

 class IFax
 {
 public:
	 virtual void fax() = 0;
 };

 class printer : public IPrinter
 {
	 void print() override
	 {

	 }
 };

 class IMachine : public IPrinter, public IScanner, public IFax {};

 class Machine : public IMachine
 {
	 IPrinter& printer;
	 Machine(IPrinter& printer)
		 :printer(printer) {}
	 void print() override
	 {

	 }

	 void scan() override
	 {

	 }

	 void fax() override
	 {

	 }
 };




 // Dependency inversion principle 
 class Account
 {
 public:
	 virtual void addTransaction(string& entity, int& val) = 0;
	 virtual pair<string, int> findTransaction(string& entity) = 0;
 };

 class savingAccount : public Account
 {

	 vector <pair<string, int>> transactions;
 public:

	 void addTransaction(string& entity, int& val) override
	 {
		 transactions.push_back(make_pair(entity, val));
	 }

	 pair <string, int> findTransaction(string& entity) override
	 {
		 for (auto el : transactions)
		 {
			 if (el.first == entity)
			 {
				 return el;
			 }
			 pair <string, int > notFound = make_pair("", NULL);
			 return notFound;
		 }

	 }
 };

 class currentAccount : public Account
 {

	 vector <pair<string, int>> transactions;
 public:

	 void addTransaction(string& entity, int& val) override
	 {
		 transactions.push_back(make_pair(entity, val));
	 }

	 pair <string, int> findTransaction(string& entity) override
	 {
		 for (auto el : transactions)
		 {
			 if (el.first == entity)
			 {
				 return el;
			 }
			 pair <string, int > notFound = make_pair("", NULL);
			 return notFound;
		 }

	 }
 };

 class Research
 {
 public:
	 Research(Account &acc, string &entity)
	 {
		 pair<string, int> res = acc.findTransaction(entity);
		 if (res.first != "" && res.second != NULL)
		 {
			 cout << res.first << "   " << res.second << endl;
		 }
		 else cout << "Not found" << endl;
	 }
 };

 

 //Builder pattern 
 // First attempt
 //class Item
 //{
 //public: 
	// virtual string name() = 0;
	// virtual double price() = 0;
	// virtual void function() = 0;
 //};
 //class Vehicle
 //{ 
 //public: 
	// virtual vector<Item> body() = 0;
	// virtual vector<Item> mechanics() = 0;
 //};

 //class car : public Vehicle
 //{
 //public: 
	// vector <Item> bodyItems; 
	// vector <Item> mechanicsItems;
 //public:
	// void add_body_item(Item &item)
	// {
	//	 bodyItems.push_back(item);
	// }
	// void add_mechanics_item(Item &item)
	// {
	//	 mechanicsItems.push_back(item);
	// }
	// vector<Item> body() override
	// {
	//	 return bodyItems;
	// }
	// vector<Item> mechanics() override
	// {
	//	 return mechanicsItems;
	// }
	// void print_body(vector<Item> items)
	// {
	//	 for (auto item : items)
	//	 {
	//		 cout << "Name: " << item.name() << endl;
	//		 cout << "Price: " << item.price() << endl;
	//	 }
	// }
	// void print_mech(vector<Item> items)
	// {
	//	 for (auto item : items)
	//	 {
	//		 cout << "Name: " << item.name() << endl;
	//		 cout << "Price: " << item.price() << endl;
	//	 }
	// }
 //};
 //
 //class door : public Item
 //{
 //public: 
	// bool state = false;

	// string name() override
	// {
	//	 return "Door";
	// }
	// double price() override
	// {
	//	 return 109.99;
	// }
	// void toggle_state(bool &state)
	// {
	//	 if (state == false)
	//	 {
	//		 state = true;
	//	 }
	//	 else
	//	 {
	//		 state = false;
	//	 }
	// }
	// void function() override 
	// {
	//	 toggle_state(state);
	// }
 //};
 //class engine : public Item
 //{
	// bool engine_is_on = false;
	// string name() override
	// {
	//	 return "Engine";
	// }
	// double price() override
	// {
	//	 return 2599.99;
	// }
	// void toggle_engine_state(bool &state)
	// {
	//	 if (state == false)
	//	 {
	//		 state = true;
	//	 }
	//	 else
	//	 {
	//		 state = false;
	//	 }
	// }
	// void function() override
	// {
	//	 toggle_engine_state(engine_is_on);
	// }
 //};


 //class carBuilder
 //{
 //public: 
	// car create_car_with_door_and_engine()
	// {
	//	car car_with_door_and_engine;
	//	door doo;
	//	engine eng;
	//	car_with_door_and_engine.add_body_item(doo);
	//	car_with_door_and_engine.add_mechanics_item(eng);
	//	return car_with_door_and_engine;
	// }
 //};
 //
 //second attempt


//Bread Abstract Class
class Bread 
 {
 public:
	 string name; 
	 int size; 

	 virtual Bread& getBread() = 0;
	 Bread(string name, int size)
		 : name(name), size(size) {}
	 Bread()
		 :name{ NULL }, size{ NULL } {}
 };

 //Burger Abstract Class
 class Burger 
 {
 public:
	 string type; 
	 int size; 

	 virtual Burger& getBurger() = 0;
	 Burger(string type, int size)
		 : type(type) ,size(size) {}
	 Burger()
		 :type{ NULL }, size{ NULL } {}
 };


 

//French Bread Concrete Class
 class frenchBread : public Bread 
 {
 public:
	 Bread& getBread() override
	 {
		 return *this;
	 }

	 frenchBread(int size)
		 :Bread("French Bread", size) {}
	 frenchBread()
		 :Bread(){}

 };
 class frenchBreadBuilder
 {
	 frenchBread *FrenchBread;
 public:

	 static frenchBreadBuilder create()
	 {
		 frenchBread* FrenchBread = new frenchBread;
		 frenchBreadBuilder br(FrenchBread);
		 return br;
	 }

	 frenchBreadBuilder(frenchBread *bread)
	 {
		 FrenchBread = bread;
	 }
	
	 frenchBreadBuilder with_name(string Name)
	 {
		 FrenchBread->name = Name;
		 return *this;
	 }
	 frenchBreadBuilder with_size(int Size)
	 {
		 FrenchBread->size= Size;
		 return *this;
	 }
 };

 //White Bread Concrete Class
 class whiteBread : public Bread 
 {
 public:
	 Bread& getBread() override
	 {
		 return *this;
	 }

	 whiteBread( int size)
		 : Bread("White Bread", size) {}
 };

 //Vegeterian Base Class
 class vegieBurger : public Burger
 {
 public:
	 Burger& getBurger () override
	 {
		 return *this;
	 }

	 vegieBurger (string name, int size)
	 : Burger(name, size) {}

 };

 //Green Burger Derived Class From Vegeterian Burger Base Class
 class greenBurger : public vegieBurger 
 {
 public:
	 greenBurger(int size)
		 : vegieBurger("Green Burger", size) {}

 };

 //Non Vegeterian Burger Base Class
 class nonVegieBurger : public Burger 
 {
 public:
	 Burger& getBurger()override
	 {
		 return *this;
	 }

	 nonVegieBurger(string name, int size)
		 : Burger(name, size) {}

 };

 //Chicken Burger Derived Class From Non Vegeterian Base Class
 class chickenBurger: public nonVegieBurger 
 {
	 chickenBurger(int size)
		 : nonVegieBurger("Chicken Burger", size) {}

 };

 //Beef Burger Derived Class From Non Vegeterian Class
 class beefBurger : public nonVegieBurger 
 {
	 beefBurger(int size)
		 : nonVegieBurger("Beef Burger", size) {}

 };

 //Sandwich interface
 class I_Sandwich
 {
 public:
	 virtual Bread& bread() = 0;
	 virtual Burger& burger() = 0;
 };

 // Sandwich Class Contracts The Sandwich Interface 
 class sandwich : public I_Sandwich  {
 public: 
	 Bread& bread1; 
	 Burger& burger1; 

	 sandwich(Bread& bread, Burger& burger)
		 :bread1(bread), burger1(burger){}

	 pair<Bread&, Burger&> getBreadAndBurger()
	 {
		 pair<Bread&, Burger&> result{bread1, burger1};
		 return result;
	 }

	 Bread& bread () override
	 {
		 return bread1.getBread();
	 }
	 
	 Burger& burger () override
	 {
		 return burger1.getBurger();
	 }
 };
 
int main()
{
	
	//product pr("pen", Color::blue, Size::small);
	//product pr1("paper", Color::green, Size::medium);
	//product pr2("bag", Color::green, Size::medium);
	//product pr3("ruler", Color::red, Size::small);
	//vector <product*> items{&pr,&pr1,&pr2,&pr3};


	//book b1("Shiko1", 100, BookType::Novel);
	//book b2("Shiko2", 50, BookType::SciFi);
	//book b3("Shiko3", 200, BookType::Technical);
	//book b4("Shiko4", 10, BookType::Novel);
	//book b5("Shiko5", 55, BookType::SciFi);
	//vector<book*> books{ &b1,&b2,&b3,&b4,&b5};

	//colorSpecification green(Color::green);
	//colorSpecification blue(Color::blue);
	//sizeSpecification medium(Size::medium);
	//AndSpecification<product> greenAndMedium(green,medium);
	//betterFilter<product> br; 
	//vector <product*> res1 = br.filter(items, greenAndMedium);

	//bettterOfBetterFilter<book> bro;
	//bookTypeSpecification<book> novel (BookType::Novel);
	//vector <book*> res = bro.filter(books, novel);


	//for (auto el : res)
	//{
	//	cout << el->name << " green" << endl;
	//}
	//
	//for (auto el : res1)
	//{
	//	cout << el->name << " green" << endl;
	//}
	//currentAccount acc;
	//string entity = "Zara"; 
	//string entity2 = "Zaraw"; 
	//int value = 1000;
	//acc.addTransaction(entity, value);
	//Research r(acc, entity2);
	//vector <int> sort{1,2,23,2,253,5235,22,1,12,3,44,0};
	//for (auto el : sort)
	//{
	//	cout << el << endl;
	//}
	//car ca  = build.create_car_with_door_and_engine();
	//ca.print_body(ca.body());
	//sandwich greenBurger;
	//greenBurger.is_a("French");
	greenBurger green(2);
	whiteBread white(1);
	sandwich greenBurgerWithWhiteBread(white, green);
	Bread& be = greenBurgerWithWhiteBread.bread();
	Burger& ge = greenBurgerWithWhiteBread.burger();
	frenchBreadBuilder br = frenchBreadBuilder::create().with_name("French Burger").with_size(2);
	pair<Bread&, Burger&> res = greenBurgerWithWhiteBread.getBreadAndBurger();

	system("pause");
	return 0; 

}
