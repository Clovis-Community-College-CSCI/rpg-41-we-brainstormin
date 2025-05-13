// Character Classes - for heroes, crooks,  and other characters
// Currently under construction, up for changing creative aspects 

#include "/public/read.h"
#include <stdexcept>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <memory>
using namespace std;

class Actor {
	int x = 0, y = 0, z = 10;
	Actor(int new_x = 0, int new_y = 0, int new_z = 10) : x(new_x), y(new_y), z(new_z){}
};

class Hero : public Actor {
	protected:
		string name = "Noob";
		int health = 100;
		int energy = 50;
		int aura = 10;
	public: 
		Hero() {}
		Hero(const string &new_name, int new_health) : name(new_name), health(new_health){}
		// Getters
		virtual string get_name() const { return name; }
		virtual int get_health() const { return health; }
		virtual int get_energy() const { return energy; }
		virtual int get_aura() const { return aura; } 
		// Setters
		virtual void set_name(const string &new_name) { name = new_name; }
		virtual void set_health(int new_health) { health = new_health; }
		virtual void set_energy(int new_energy) { energy = new_energy; }
		virtual void set_aura(int new_aura) { aura = new_aura; }
		virtual print() { cout << "Name: " << name << " Health: " << health << endl; }
		virtual void speak() const { cout << "They call me Bob." << endl; }
};

class Karen : public Hero { // The Mage - good attack, poor health, uses moderate energy 
	protected:
		int berate = 10;
		int degredation = 30;
	public: 
		Karen() : Hero() {
			set_name("Karen");
			set_health = 80;
		}
		Karen(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Hero::take_damage(0); }
		void speak() const override { cout << "*&@%$*@$%!#$@^@!*#" << endl; }
};

class Cop : public Hero { // The Tank - strong attack, good health and takes less damage, uses lots of energy 
	protected:
		int pepper_spray = 20;
		int segway = 50;
	public: 
		Cop() : Hero() {
			set_name("Sergio");
			set_health = 100;
		}
		Cop(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void take_damage(int x) override { health -= x / 2; Hero::take_damage(0); }
		void speak() const override { cout << "Cop cuties, cute while on duty. Navy blue booties..." << endl; }
};

class Goth : public Hero { // The Assassin - good attack, good health, uses moderate energy
	protected: 
		int poison = 15; 
		int mogging = 25;
	public: 
		Goth() : Hero() {
			set_name("Nessie");
			set_health = 100;
		}
		Goth(const string &new_name, int new_health) : Heo(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Hero::take_damage(0); }
		void speak() const override { cout << "This is the skin of a killer, Bella." << endl; }
};

class Unattended_Child : public Hero { // The Healer - weak attack but increases health, good health, uses low energy
	protected:
		int cry = 5;
		int candy = 20;
	public: 
		Unattended_Child() : Hero() {
			set_name("Charlie");
			set_health = 100;
		}
		Unattended_Child(const &new_name, int new_health) : Hero(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Hero::take_damage(0); }
		void speak() const override { cout << "Lala-la-la-la-laaa laalalalala" << endl; }
};


class Monster : public Actor {	
	protected:
        string name = "Gobwin";
        int health = 3;
    public:
        Monster() {}
        Monster(const string &new_name, int new_health) : name(new_name), health(new_health){}
        virtual string get_name() const { return name; }
        virtual int get_health() const { return health; }
        virtual void set_name(const string &new_name) { name = new_name; }
        virtual void set_health(int new_health) { health = new_health; }
        virtual print() { cout << "Name: " << name << " Health: " << health << endl; }
        virtual void speak() const { cout << "i dunno why i guard this dungeon" << endl; }
};

class Minivan_Mom : public Monster { // Level 1 Boss
	protected:
		int attack = 5;
		int special = 15;
	public: 
		Minivan_Mom() : Monster() {
			set_name("Miranda");
			set_health = 100;
		}
		Minivan_Mom(const &new_name, int new_health) : Monster(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Monster::take_damage(0); }
		void speak() const override { cout << "No, this is MY parking space." << endl; }
};

class Leashed_Kids : public Monster { // Level 2 Boss 
	protected: 
		int attack = 10;
		int special = 12;
	public:
		Leashes_Kids() : Monster() {
			set_name("Kiddos");
			set_health = 100;
		}
		Leashed_Kids(const &new_name, int new_health) : Monster(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Monster::take_damage(0); }
		void speak() const override { cout << "BABY SHARK DOO DOO DEE DOO DEE DOOO!" << endl; }
};

class Sneaker_Head : public Monster { // Level 3 Boss
	protected: 
		int attack = 10; 
		int special = 15;
	public:
		Sneaker_Head() : Monster() {
			set_name("James");
			set_health = 100;
		}
		Sneaker_Head(const &new_name, int new_health) : Monster(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Monster::take_damage(0); }
		void speak() const override { cout << "What are those?" << endl; }
};

class Vampires : public Monster { // Level 4 Boss
	protected:
		int attack = 15;
		int special = 20;
	public: 
		Vampires() : Monster() {
			set_name("Dracoolas");
			set_health = 100;
		}
		Vampires(const &new_name, int new_health) : Monster(new_name, new_health) {}
		void take_damage(int x) override { health -= x; Monster::take_damage(0); }
		void speak() const override { cout << "It's not a phase..." << endl; }
};

class Spirit : public Monster { // Level 5 FINAL Boss
	protected:
		int attack = 20;
		int special = 25; 
	public: 
		Spirit() : Monster() {
			set_name("The Spirit of Sierra Vista"); 
			set_health = 150;
		}
		Spirit(const &new_name, int new_health) : Monster (new_name, new_health) {}
		void take_damage(int x) override { health -= x; Monster::take_damage(0); }
		void speak() const override { cout << "Bleh blah bleh" << endl; }
};
