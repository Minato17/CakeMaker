#include<iostream>
#include<string>
#include<list>
#include<fstream>
#include<windows.h>
#include<conio.h>

using namespace std;


class Cake
{
	string name;
public:
	Cake(string n)
	{
		name = n;
	}
	string getName()
	{
		return name;
	}

};

class RecipeCake
{
	string name;
	int time;
public:
	RecipeCake(string n, int t)
	{
		name = n;
		time = t;
	}
	string getName()
	{
		return name;
	}
	int getTime()
	{
		return time;
	}
};

class CakeMaker
{
public:
	CakeMaker();
	Cake *takeCommand(RecipeCake* recipe) {
		Cake *c;
		c = new Cake(recipe->getName());
		Sleep(recipe->getTime() * 1000);
		return c;
	}

};

class CarouselOfCakes
{
	Cake* storage[12];
	unsigned int maxCapacity = 12;
	unsigned int lowCapacity = 3;
	unsigned int n;
public:
	CarouselOfCakes()
	{
		fstream coc;
		coc.open("Carusel.txt", ios::in | ios::out | ios::app);
		string c;
		int i = 0;
		coc.seekg(0);
		while (getline(coc, c))
		{
			storage[i] = new Cake(c);
			i++;
		}
		n = i;
	}
	bool ifCake()
	{
		if (n <= lowCapacity)
			return true;
		else
			return false;
	}
	Cake* getCake(string name)
	{
		int i;
		string c;
		fstream coc;
		coc.open("Carusel.txt", ios::in | ios::out | ios::app);
		fstream b;
		b.open("Car.txt", ios::in | ios::out | ios::app);
		for (i = 0; i < n; i++)
		{
			if (storage[i]->getName() == name)
			{
				b.seekg(0);
				coc.seekg(0);
				while (getline(coc, c))
				{
					if (c == name)
						getline(coc, c);
					else
						b << c << endl;
				}
				coc.close();
				b.close();
				remove("Carusel.txt");
				rename("Car.txt", "Carusel.txt");
				return storage[i];
			}
		}
	}
	int getCurrentCapacity()
	{
		return n;
	}
	void getCakesFromCarousel()
	{
		int i = 0;
		for (i = 0; i < n; i++)
		{
			cout << "                                        " << i + 1 << "." << storage[i]->getName() << endl;
		}
	}

};

class CommandTaker
{
	RecipeCake* carouselRecipe = NULL;
	CakeMaker* cakeMaker = NULL;
	CarouselOfCakes* carousel = new CarouselOfCakes();
	void refillCarousel()
	{
		fstream coc;
		CakeMaker* cakeMaker = NULL;
		coc.open("Carusel.txt", ios::in | ios::out | ios::app);
		fstream pra;
		pra.open("Cakes.txt", ios::in | ios::out | ios::app);
		CarouselOfCakes* carousel = new CarouselOfCakes();
		RecipeCake* carouselRecipe = NULL;
		int i = carousel->getCurrentCapacity() - 1;
		string p;
		int t;
		pra.seekg(0);
		if (checkCarouselOfCakes())
		{
			while (i < 12)
			{
				getline(pra, p);
				pra >> t;
				pra.ignore();
				carouselRecipe = new RecipeCake(p, t);
				coc << cakeMaker->takeCommand(carouselRecipe)->getName() << endl;
				i++;
			}
		}
		pra.close();
		coc.close();
	}
	bool checkCarouselOfCakes()
	{
		CarouselOfCakes* carousel = new CarouselOfCakes();
		if (carousel->ifCake())
			return true;
		else
			return false;
	}
public:
	CommandTaker();
	Cake *takeCommand(RecipeCake* recipe)
	{
		CakeMaker* cakeMaker = NULL;
		CarouselOfCakes* carousel = NULL;
		refillCarousel();
		carousel = new CarouselOfCakes();
		if (carousel->getCake(recipe->getName())->getName() == recipe->getName())
		{
			return carousel->getCake(recipe->getName());
		}
		return cakeMaker->takeCommand(recipe);
	}
	Cake *takeCommand(RecipeCake* recipe, int nrOfCakes)
	{
		CakeMaker* cakeMaker = NULL;
		while (nrOfCakes != 1)
		{
			cakeMaker->takeCommand(recipe)->getName();
			nrOfCakes--;
		}
		return cakeMaker->takeCommand(recipe);
	}

	void getCakesFromCarousel()
	{
		CarouselOfCakes* carousel = NULL;
		carousel = new CarouselOfCakes();
		carousel->getCakesFromCarousel();
	}
};

class CommandPanel
{
	list<RecipeCake*>menu;
	CommandTaker* commandTaker = NULL;

public:
	CommandPanel()
	{
		fstream pra;
		pra.open("Cakes.txt", ios::in | ios::out | ios::app);
		string p;
		RecipeCake *c = NULL;
		int t;
		pra.seekg(0);
		while (getline(pra, p))
		{
			pra >> t;
			pra.ignore();
			c = new RecipeCake(p, t);
			menu.push_back(c);
		}
		pra.close();
	}

	void showProducts()
	{

		list<RecipeCake*>::iterator it;
		RecipeCake *c = NULL;
		int i = 1;
		for (it = menu.begin(); it != menu.end(); ++it)
		{
			cout << "                                        " << i << ". " << (*it)->getName() << endl;
			i++;
		}

	}
	void selectProduct(string name)
	{
		list<RecipeCake*>::iterator it;
		RecipeCake *c = NULL;
		string p;
		int nr = 0;
		for (it = menu.begin(); it != menu.end(); ++it)
		{
			if ((*it)->getName() == name)
			{
				c = new RecipeCake((*it)->getName(), (*it)->getTime());
				nr++;
			}
		}
		if (nr == 1)
			cout << "                                        Comanda dumneavoastra de  " << commandTaker->takeCommand(c)->getName() << " a fost finalizata" << endl;
		else
			cout << "                                        Nu producem aceasta prajitura\n";
	}
	void selectProduct(string name, int numberOfProducts)
	{
		list<RecipeCake*>::iterator it;
		RecipeCake *c = NULL;
		string p;
		int nr = 0;
		for (it = menu.begin(); it != menu.end(); ++it)
		{
			if ((*it)->getName() == name)
			{
				c = new RecipeCake((*it)->getName(), (*it)->getTime());
				nr++;
			}
		}
		if (nr == 1)
			cout << "                                        Comanda dumneavoastra de " << commandTaker->takeCommand(c, numberOfProducts)->getName() << " in numar de" << numberOfProducts << " a fost finalizata" << endl;
		else
			cout << "                                        Nu producem aceasta prajitura\n";
	}
	void showProductsInCarousel()
	{
		commandTaker->getCakesFromCarousel();
	}
};

int main()
{
	CommandPanel *c = NULL;
	c = new CommandPanel();
	string p;
	int n;
	unsigned int opt;
	do {
		system("cls");
		cout << "\n                                        1.Afisare prajituri posibile\n\n                                        2.Comanda\n\n                                        3.Prajituri din depozit\n\n                                        0.Iesire\n\n";
		do {
			cout << "                                        Optiunea dumneavoastra: ";
			cin >> opt;
			if (!(opt == 1 || opt == 2 || opt == 3 || opt == 0))
				cout << "                                        Optiune Incorecta!!!\n";
		} while (!(opt == 1 || opt == 2 || opt == 3 || opt == 0));
		cout << endl;
		switch (opt)
		{
		case 1:
			c->showProducts();
			break;
		case 2:
			cout << "                                        Ce doriti sa cumparati: ";
			cin.ignore();
			getline(cin, p);
			cout << "                                        Cate doriti: ";
			cin >> n;
			if (n == 1)
				c->selectProduct(p);
			else
				c->selectProduct(p, n);

			break;
		case 3:
			c->showProductsInCarousel();
			break;
		case 0:
			exit(0);
		}
		system("pause");
	} while (1);
	return 0;
}