#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


// Абстрактный класс аппаратного устройства
class Car abstract
{
protected:
	string producer;

public:
	string GetProducer()
	{
		return this->producer;
	}
	void SetProducer(string producer)
	{
		this->producer = producer;
	}
 // Метод создания клона объекта
	virtual Car* Clone() abstract;
};

class Body : public Car
{
	string color;
public:
	string GetColor()
	{
		return this->color;
	}
	void SetColor(string color)
	{
		this->color = color;
	}
	Car* Clone() override
	{
		Body* body = new Body;
		*body = *this;
		return body;
	}
};

class Engine : public Car
{
	int power;
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string type)
	{
		this->type = type;
	}
	int GetAmount()
	{
		return this->power;
	}
	void SetAmount(int Power)
	{
		this->power = Power;
	}
	Car* Clone() override
	{
		Engine * engine = new Engine;
		*engine = *this;
		return engine;
	}
};

class Fuel : public Car
{
	int Amount;
	string type;
public:
	string GetType()
	{
		return this->type;
	}
	void SetType(string type)
	{
		this->type = type;
	}
	int GetAmount()
	{
		return this->Amount;
	}
	void SetAmount(int Amount)
	{
		this->Amount = Amount;
	}
	Car* Clone() override
	{
		Fuel * fuel = new Fuel;
		*fuel = *this;
		return fuel;
	}
};

class Gears : public Car
{
	int Amount;
public:
	int GetAmount()
	{
		return this->Amount;
	}
	void SetAmount(int Amount)
	{
		this->Amount = Amount;
	}
	Car* Clone() override
	{
		Gears * gears = new Gears;
		*gears = *this;
		return gears;
	}
};

/*
 Прототип (Prototype) порождающий шаблон проектирования, который предназначен для создания объекта
 через клонирование другого объекта вместо создания посредством конструктора.
Паттерн используется чтобы:
-	избежать дополнительных усилий по созданию объекта стандартным путем (использование ключевого слова new,
	когда создается не только сам объект, но и вся иерархия предков объекта),
	когда это непозволительно дорого для приложения.
-	избежать наследования создателя объекта (object creator) в клиентском приложении, как это делает паттерн abstract factory.
*/

class Prototype abstract
{
public:
	 virtual Prototype* Clone() abstract;
};

class OwnCar: public Prototype
{
	Body* body;
	Gears* gears;
	vector<Engine*> engine;
	vector<Fuel*> fuel;
public:
	Body* GetBody()
	{
		return this->body;
	}
	void SetBody(Body* Body)
	{
		this->body = Body;
	}
	Gears* GetGears()
	{
		return this->gears;
	}
	void SetGears(Gears* Gears)
	{
		this->gears = Gears;
	}
	vector<Engine*>& GetEngine()
	{
		return engine;
	}
	void AddEngine(Engine * m)
	{
		engine.push_back(m);
	}
	vector<Fuel*>& GetFuel()
	{
		return fuel;
	}
	void AddFuel(Fuel * fuel)
	{
		this->fuel.push_back(fuel);
	}
	Prototype* Clone() override
	{
		OwnCar *car = new OwnCar;
		car->body = this->body != nullptr ? (Body*)this->body->Clone(): nullptr;
		car->gears = this->gears != nullptr ? (Gears*)this->gears->Clone() : nullptr;
		for(Engine* m : this->engine)
		{
			if (m != nullptr)
			{
				car->AddEngine((Engine*)m->Clone());
			}
		}
		for (Fuel* h : this->fuel)
		{
			if (h != nullptr)
			{
				car->AddFuel((Fuel*)h->Clone());
			}
		}		
		return car;
	}
};

//	Класс палитры типичных конфигураций
class carPrototypes
{
	// Словарь, в котором хранятся прототипы конфигураций
	map<string, OwnCar*> carprototypes;
public:
	carPrototypes()
	{
		// инициализация палитры прототипами конфигураций
		InitializecarPrototypes();
	}


	// Доступ к прототипу конфигурации по его имени
	OwnCar* operator[](string key)
	{
		return  carprototypes[key];
	}
	void InitializecarPrototypes()
	{
		carprototypes["Racing"] = CreateRacingConfig();
		carprototypes["Carrier"] = CreateCarrierConfig();
		carprototypes["City"] = CreateCityConfig();
	}

	OwnCar* CreateRacingConfig()
	{
		OwnCar* config = new OwnCar();

		Body* body = new Body();
		body->SetColor("Red");
		config->SetBody(body);

		Gears* gears = new Gears();
		gears->SetAmount(7);
		config->SetGears(gears);

		Fuel* fuel = new Fuel();
		fuel->SetType("Petrol");
		fuel->SetAmount(147);
		config->AddFuel(fuel);

		Engine* engine = new Engine();
		engine->SetType("Rotary");
		config->AddEngine(engine);

		return config;
	}

	OwnCar* CreateCarrierConfig()
	{
		OwnCar* config = new OwnCar();

		Body* body = new Body();
		body->SetColor("White");
		config->SetBody(body);

		Gears* gears = new Gears();
		gears->SetAmount(5);
		config->SetGears(gears);

		Fuel* fuel = new Fuel();
		fuel->SetType("Petrol");
		fuel->SetAmount(1300);
		config->AddFuel(fuel);

		Engine* engine = new Engine();
		engine->SetType("Combustion");
		config->AddEngine(engine);

		return config;
	}

	OwnCar* CreateCityConfig()
	{
		OwnCar* config = new OwnCar();

		Body* body = new Body();
		body->SetColor("Black");
		config->SetBody(body);

		Gears* gears = new Gears();
		gears->SetAmount(6);
		config->SetGears(gears);

		Fuel* fuel = new Fuel();
		fuel->SetType("Gas");
		fuel->SetAmount(50);
		config->AddFuel(fuel);

		Engine* engine = new Engine();
		engine->SetType("Combustion");
		config->AddEngine(engine);

		return config;
	}
};

void Printcar(OwnCar *car)
{
	cout << "Car configuration: " << endl;
	cout << "Body: " << car->GetBody()->GetColor() << endl;
	cout << "Engine: ";
	for(Engine *m : car->GetEngine())
	{
		cout << m->GetType() << "\n";
	}
	cout << "Fuels: ";
	for(Fuel *h : car->GetFuel())
	{
		cout << h->GetType() << "  " << h->GetAmount() << " L\n";
	}
	
	if (car->GetGears() != nullptr)
	{
		cout << "Gears: ";
		cout << car->GetGears()->GetAmount() << "\n";
	}
}

int main()
{
	// Ввести имя прототипа конфигурации
	cout << "Enter config prototype name(City, Racing, Carrier)\n> ";
	string prototypeName;
	cin >> prototypeName;
	carPrototypes car;
	// Получение прототипа конфигурации из палитры по его имени
	OwnCar *prototype = car[prototypeName];
	if (prototype != nullptr)
	{
		// Создание конфигурации на основе выбранного прототипа
		OwnCar *car = dynamic_cast<OwnCar*>(prototype->Clone());
		// Вывод состава конфигурации на консоль
		Printcar(car);
	}
	else
	{
		cout << "Error: incorrect config name";
	}

	system("pause");
}

