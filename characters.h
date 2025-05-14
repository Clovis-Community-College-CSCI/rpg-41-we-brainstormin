// Character Classes - for heroes and heroes
#include "/public/read.h"
#include <stdexcept>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <memory>
using namespace std;

class Actor {
	public:
		// Coordinates
		int x = 0, y = 0, z = 10;
		Actor(int new_x = 0, int new_y = 0, int new_z = 10) : x(new_x), y(new_y), z(new_z){}
		virtual ~Actor() {}
		virtual void take_damage(int x) = 0;
};

class Hero : public Actor {
	protected:
		string name = "Noob";
		int health = 100;
		int energy = 0; // Energy increases by 10, decreases once special is used
		int aura = 10; // Aura is the point/level system to advance to a higher dungeon/monster
		int moves = 0; // Counts number of moves to increase or reset Energy 
	public: 
		Hero() {}
		Hero(const string &new_name, int new_health) : name(new_name), health(new_health){}
		virtual void print() { cout << "Name: " << name << " Health: " << health << " Aura: " << aura << endl; }
		virtual void speak_a() const { cout << "They call me Bob." << endl; } // Attack speak
		virtual void speak_s() const { cout << "They call me THE Bob." << endl; } // Special speak
		virtual void take_damage(int x) { health -= x; if (health < 0) health = 0; }
		virtual void heal(int aid) {
			health += aid;
			if (health < 0) { health = 0; }
			if (health > 100) { health = 100; }
		}
		virtual void move() { 
			moves++; 
			set_energy(energy + 10);
		}
		virtual void attack(Actor &target) = 0;
		virtual void special(Actor &target) = 0;
		// Getters
		virtual string get_name() const { return name; }
		virtual int get_health() const { return health; }
		virtual int get_energy() const { return energy; }
		virtual int get_aura() const { return aura; } 
		virtual int get_moves() const { return moves; }
		// Setters
		virtual void set_name(const string &new_name) { name = new_name; }
		virtual void set_health(int new_health) { 
			if (new_health < 0) { health = 0; }
			else { health = new_health; } 
		}
		virtual void set_energy(int new_energy) { 
			if (new_energy < 0) { energy = 0; }
			else if (new_energy > 50) { energy = 50; }
			else { energy = new_energy; }
		}
		virtual void set_aura(int new_aura) { aura = new_aura; }
		virtual void set_moves(int new_moves) { moves = new_moves; }
};

class Karen : public Hero { // The Mage - good attack, poor health, uses moderate energy 
	protected:
		int berate = 10; // Attack
		int degradation = 30; // Special
	public: 
		Karen() : Hero("Karen", 80) {}
		Karen(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void print() override {
			Hero::print();
			cout << "Berate: " << berate << " Degradation: " << degradation << endl;
		}
		void take_damage(int x) override { Hero::take_damage(x); }
		void speak_a() const override { cout << "Excuse ME? I NEED TO SPEAK TO YOUR MANAGER!" << endl; }
		void speak_s() const override { cout << "*&@%$* @$%!#$@ ^@!*# ! ! !" << endl; }
		void attack(Actor &target) {
			speak_a();
			target.take_damage(berate);
			move();
		}
		void special(Actor &target) {
			if (get_energy() >= 25) {
				speak_s();
				target.take_damage(degradation);
				set_energy(get_energy() - 25);
				move();
			} else { cout << "She doesn't think they're special enough for that yet." << endl; }
		}
};

class Cop : public Hero { // The Tank - strong attack, good health and takes less damage, uses lots of energy 
	protected:
		int pepper_spray = 20; // Attack
		int segway = 50; // Special
	public: 
		Cop() : Hero("Sergio", 100) {}
		Cop(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void print() override {
			Hero::print();
			cout << "Pepper Spray: " << pepper_spray << " Segway: " << segway << endl;
		}
		void take_damage(int x) override { Hero::take_damage(x/2); }
		void speak_a() const override { cout << "Cop cuties, cute while on duty. Navy blue booties..." << endl; }
		void speak_s() const override { cout << "SAFETY NEVER TAKES A HOLIDAY!!" << endl; }
		void attack(Actor &target) {
			speak_a();
			target.take_damage(pepper_spray);
			move();
		}
		void special(Actor &target) {
			if (get_energy() >= 50) {
				speak_s();
				target.take_damage(segway);
				set_energy(get_energy() - 50);
				move();
			} else { cout << "He doesn't think that's legal right now." << endl; }
		}
};

class Goth : public Hero { // The Assassin - good attack, good health, uses moderate energy
	protected: 
		int sparkle = 15; // Attack
		int mogging = 25; // Special
	public: 
		Goth() : Hero("Nessie", 100) {}
		Goth(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void print() override {
			Hero::print();
			cout << "Sparkle: " << sparkle << " Mogging: " << mogging << endl;
		}
		void take_damage(int x) override { Hero::take_damage(x); }
		void speak_a() const override { cout << "This is the skin of a killer...*sparkle* *sparkle*" << endl; }
		void speak_s() const override { cout << "I am not afraid of monsters. I am afraid of the mirror." << endl; }
		void attack(Actor &target) {
			speak_a();
			target.take_damage(sparkle);
			move();
		}
		void special(Actor &target) {
			if (get_energy() >= 30) {	
				speak_s();
				target.take_damage(mogging);
				set_energy(get_energy() - 30);
				move();
			} else { cout << "Nah. The world ain't ready for that." << endl; }
		}
};

class Unattended_Child : public Hero { // The Healer - weak attack but increases health, good health, uses low energy
	protected:
		int cry = 5;
		int snack = 20;
	public: 
		Unattended_Child() : Hero("Charlie", 100) {}
		Unattended_Child(const string &new_name, int new_health) : Hero(new_name, new_health) {}
		void print() override { 
			Hero::print();
			cout << "Cry: " << cry << " Snack: " << snack << endl;
		}
		void take_damage(int x) override { Hero::take_damage(x); }
		void speak_a() const override { cout << "HIIIIIIYAAAAAA! *he gave it his all*" << endl; }
		void speak_s() const override { cout << "Lala-la-la-la-laaa~" << endl; }
		void attack(Actor &target) {
			speak_a();
			target.take_damage(cry);
			move();
		}
		void special(Actor &target) override { cout << "The child's against violence." << endl; }
		void special(vector<Hero*> &party) {
			if (get_energy() >= 10) {
				speak_s();
				for (Hero* member : party) {
					member->heal(snack);
				}
				set_energy(get_energy() - 10);
				move();
			} else { cout << "Can't do that, we have child labor laws." << endl; }
		}
};


class Monster : public Actor {	
	protected:
        string name = "Gobwin";
        int health = 3;
    public:
        Monster() {}
		virtual ~Monster() {}
        Monster(const string &new_name, int new_health) : name(new_name), health(new_health){}
        virtual void print() { cout << "Name: " << name << " Health: " << health << endl; }
        virtual void speak() const { cout << "i dunno why i guard this dungeon" << endl; }
		virtual void take_damage(int x) { health -= x; if (health < 0) health = 0; }
		// Getters
		virtual string get_name() const { return name; }
        virtual int get_health() const { return health; }
        virtual char get_sym() const { return '~'; }
		// Setters
		virtual void set_name(const string &new_name) { name = new_name; }
        virtual void set_health(int new_health) { 
			if (new_health < 0) { health = 0; }
			else { health = new_health; }
		}
};

class Minivan_Mom : public Monster { // Level 1 Boss
	protected:
		int aDam = 5;
		int sDam = 15;
	public: 
		Minivan_Mom() : Monster("Miranda", 100) {}
		Minivan_Mom(const string &new_name, int new_health) : Monster(new_name, new_health) {}
		void print() override {
			Monster::print();
			cout << "She's a minvan mom." << endl;
		}
		void take_damage(int x) override { Monster::take_damage(x); }
		void speak() const override { cout << "No, this is MY parking space." << endl; }
		void attack(Hero &target) {
			speak(); 
			cout << "Miranda swung her Trader Joe's tote bag at " << target.get_name() << ", -" << aDam << endl;
			target.take_damage(aDam);
		}
		void special(Hero &target) {
			speak();
			cout << "Miranda tried to run over " << target.get_name() << " with a shopping cart, -" << sDam << "!" << endl;
			target.take_damage(sDam);
		}
		char get_sym() const override { return 'M'; }
};

class Leashed_Kids : public Monster { // Level 2 Boss 
	protected: 
		int aDam = 10;
		int sDam = 12;
	public:
		Leashed_Kids() : Monster("Kiddos", 100) {}
		Leashed_Kids(const string &new_name, int new_health) : Monster(new_name, new_health) {}
		void print() override {
			Monster::print();
			cout << "Just a bunch of fera kids on a leash.." << endl;
		}
		void take_damage(int x) override { Monster::take_damage(x); }
		void speak() const override { cout << "BABY SHARK DOO DOO DEE DOO DEE DOOO!" << endl; }
		void attack(Hero &target) {
			speak();
			cout << "One of the kids bit " << target.get_name() << ", -" << aDam << "!" << endl;
			target.take_damage(aDam);
		}
		void special(Hero &target) {
			speak();
			cout << "A kid turned into Bruce Lee and one punched " << target.get_name() << ", -" << sDam << "!" << endl;
			target.take_damage(sDam);
		}
		char get_sym() const override { return 'L'; }
};

class Sneaker_Head : public Monster { // Level 3 Boss
	protected: 
		int aDam = 10; 
		int sDam = 15;
	public:
		Sneaker_Head() : Monster("James", 100) {}
		Sneaker_Head(const string &new_name, int new_health) : Monster(new_name, new_health) {}
		void print() override {
			Monster::print();
			cout << "He's a persistent sneaker-head..." << endl;
		}
		void take_damage(int x) override { Monster::take_damage(x); }
		void speak() const override { cout << "What are those?" << endl; }
		void attack(Hero &target) {
			speak();
			cout << "James sold a shoe to " << target.get_name() << ", it's missing a pair, -" << aDam << endl;
			target.take_damage(aDam);
		}
		void special(Hero &target) {
			speak();
			cout << "James roasted " << target.get_name() << "'s white Vans and convinced 'em to buy a shoe, -" << sDam << "!" << endl;
			target.take_damage(sDam);
		}
		char get_sym() const override { return 'S'; }
};

class Vampires : public Monster { // Level 4 Boss
	protected:
		int aDam = 15;
		int sDam = 20;
	public: 
		Vampires() : Monster("Dracoolas", 100) {}
		Vampires(const string &new_name, int new_health) : Monster(new_name, new_health) {}
		void print() override {
			Monster::print();
			cout << "They're edgy vampirs...." << endl;
		}
		void take_damage(int x) override { Monster::take_damage(x); }
		void speak() const override { cout << "It's not a phase..." << endl; }
		void attack(Hero &target) {
			speak();
			cout << "One of them tried to hire " << target.get_name() << " into a cult, -" << aDam << "!" << endl;
			target.take_damage(aDam);
		}
		void special(Hero &target) {
			speak();
			cout << "One of them convinced " << target.get_name() << " he played Nosferatu in a Spongebob episode, -" << sDam << "!" << endl;
			target.take_damage(sDam);
		}
		char get_sym() const override { return 'V'; }
};

class Spirit : public Monster { // Level 5 FINAL Boss
	protected:
		int aDam = 20;
		int sDam = 25; 
	public: 
		Spirit() : Monster("The Spirit of Sierra Vista", 150) {}
		Spirit(const string &new_name, int new_health) : Monster (new_name, new_health) {}
		void print() override {
			Monster::print();
			cout << "Bruv, I think we need the ghost busters....." << endl;
		}
		void take_damage(int x) override { Monster::take_damage(x); }
		void speak() const override { cout << "Bleh blah bleh" << endl; }
		void attack(Hero &target) {
			speak();
			cout << "Who you gonna call? Not like you got friends lol. -" << aDam << "!" << endl;
			target.take_damage(aDam);
		}
		void special(Hero &target) {
			speak();
			cout << "Hibachi, Benihana, Teriyaki~ -" << sDam << "!" << endl;
			target.take_damage(sDam);
		}
		char get_sym() const override { return '&'; }
};
