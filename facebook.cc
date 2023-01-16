#include <iostream>
#include <cstdlib>
#include <set>
using namespace std;

class Person {
	const string username;
	mutable set<string> connections;
  public:
	Person() = delete; //No default constructor
	Person(string new_username) : username(new_username) {}
	string get_username() const {
		return username;
	}
	void add_connection(string other_name) const {
		auto [iter, inserted] = connections.insert(other_name);
		iter = iter; //Disable unused variable warning
		if (inserted) {} //Insert was successful
		else {} //Insert failed
	}
	const set<string> & get_connections() const {
		return connections;
	}
	bool is_added(string other_name) const {		//use this to check if target friend is already a friend
		auto iter = connections.find(other_name);
		return (iter != connections.end());
	}
	bool operator<(const Person &other) const {
		return username < other.username;
	}
};

void die() {
	cout << "BAD INPUT!\n";
	exit(1);
}

int main() {
	set<Person> all; //The entire social network
	cout << "Do you wish to implement:\n1. Facebook\n2. Twitter\n";
	int choice = 0;
	if (!(cin >> choice) || choice < 1 || choice > 2) die();
	bool facebook = (choice == 1);
	bool isIn = false;
	while (true) {
		cout << "Do you wish to:" << endl;
		cout << "1. Add person\n";
		cout << "2. Add " << (facebook ? "friend" : "follower") << endl;
		cout << "3. Print " << (facebook ? "friends" : "followers") << " of one person\n";
		cout << "4. Print entire social network of one person\n";
		cout << "5. Print all people in the social network\n";
		cout << "6. Quit\n";
		cin >> choice;
		if (choice == 6) exit(0);
		if (!cin or choice < 1 or choice > 6) die();

		if (choice == 1) { //Add person
			cout << "Enter name of person to add:\n";
			string name;
			cin >> name;

			//If they are not in the system yet, print:

			if (all.find(name) == all.end()) {				//If find reaches the end, it has not found anything. Neat
				Person user(name);
				all.insert(user);
				cout << name << " added to network.\n";
			}
			//If they were in the system already, print:
			else {
				cout << "Error: " << name << " in network already.\n";
			}
		} else if (choice == 2) { //Add friend/follower
			cout << "Enter name of person who will add a " << (facebook ? "friend" : "follower") << endl; //Yes I know this is backwards from how Twitter works
			string name;
			cin >> name;
			Person temp(name);

			//Check if they are in the system, if not:
			for (auto x : all) {
				if (x.get_username() == name) {
					isIn = true;
				}
			}
			if (!isIn) {
				cout << "Error: " << name << " is not in the network.\n";
				continue;
			}
			cout << "Enter name of the person to add: " << endl;
			string name2;
			cin >> name2;
			//Check if name2 is in the system, if not
			isIn = false;
			for (auto x : all) {
				if (x.get_username() == name2) {
					isIn = true;
				}
			}
			if (!isIn) {
				cout << "Error: " << name2 << " is not in the network.\n";
				continue;
			}

			if (facebook) { //Add bidirectional relationship
				for (auto &x : all) {
					if (x.get_username() == name) {
						if (x.is_added(name2)) {
							cout << "Error: " << name2 << " is added already.\n";
							continue;
						} else
							x.add_connection(name2);
					}
				}
				for (auto &x : all) {
					if (x.get_username() == name2) {
						if (x.is_added(name2)) {
							cout << "Error: " << name << " is added already.\n";
							continue;
						} else
							x.add_connection(name);
					}
				}
				//Add new Facebook friendship

			} else { //Twitter - name gains a follower in name2
				for (auto &x : all) {
					if (x.get_username() == name) {
						if (x.is_added(name2)) {
							cout << "Error: " << name2 << " is added already.\n";
							continue;
						} else
							x.add_connection(name2);
					}
				}
			}
		} else if (choice == 3) { //Print friends/followers one level deep
			if (facebook) cout << "Enter name of the person to print the friends of: " << endl;
			else cout << "Enter name of the person to print the followers of: " << endl;
			string name;
			cin >> name;

			//If trying to print the network of someone not in the system:
			isIn = false;
			for (auto x : all) {
				if (x.get_username() == name) {
					isIn = true;
				}
			}
			if (!isIn) {
				cout << "Error: " << name << " is not in the network.\n";
				continue;
			}
			for (string s : all.find(name) -> get_connections())
				cout << s << endl;
		} else if (choice == 4) { //Print all network of one person
			if (facebook) cout << "Enter name of the person to print the friends of: " << endl;
			else cout << "Enter name of the person to print the followers of: " << endl;
//			cout << "Enter name of the person to print the followers of: " << endl;
			string name;
			cin >> name;

			//If trying to print the network of someone not in the system:
			isIn = false;
			for (auto x : all) {
				if (x.get_username() == name) {
					isIn = true;
				}
			}
			if (!isIn) {
				cout << "Error: " << name << " is not in the network.\n";
				continue;
			}


			//Graph traversal - store vertexes processed and to be processed
			//Edges will be loaded from all each time based on name
			set<string> processed;
			set<string> to_process;
			//Start with one name in the to_process list...
			to_process.insert(name);
			while (to_process.size() > 0) {
				auto first = to_process.begin(); //Get first vertex to process
				string s = *first;
				auto iter = all.find(s);
				for (auto x : iter -> get_connections()) {
					if (processed.count(x) == 0) {
						to_process.insert(x);
					}
				}
				processed.insert(s);
				to_process.erase(iter -> get_username());
			}
			for (string s : processed) {//After we traverse the graph, print all the names in processed
				cout << s << endl;
			}
		} else { //Print everyone in the network
			for (Person a : all) {
				cout << a.get_username() << endl;
			}
		}
	}
}
