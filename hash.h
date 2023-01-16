#include <vector>
#include <iostream>

class Hash {
	private:
		int mode = 0;
		int fixed_mod(int in) {
			if (in >= 0) return in % SIZE;
			else return (SIZE-((-in)%SIZE))%SIZE;
		}
		int find_next(int probes, int value) {
			int prime_mod = 999983;
			if (mode == 0) return probes;
			if (mode == 1) return probes*probes;
			if (mode == 2) return probes*(1 +(value % prime_mod));
			else return probes;
		}

		std::vector<T> data;
		std::vector<bool> is_empty;
		std::vector<bool> is_deleted;
	public:
		Hash(int new_mode) {
			mode = new_mode;
			data.resize(SIZE);
			is_empty.resize(SIZE);
			is_deleted.resize(SIZE);
			for (int i = 0; i < SIZE; i++) is_empty.at(i) = true;
			for (int i = 0; i < SIZE; i++) is_deleted.at(i) = false;
		}


		void insert(T new_data) {
			int address = fixed_mod(new_data);
			if (is_empty.at(address)) {
				data.at(address) = new_data;
				is_empty.at(address) = false;
				return;
			} else {
				int orig_address = address;
				while (true) {
					if (data.at(address) == new_data  && !is_empty.at(address)) return;
					if (is_empty.at(address)) {
						data.at(address) = new_data;
						is_empty.at(address) = false;
						is_deleted.at(address) = false;
						return;
					}
					for (int i = 0; i < SIZE, i++) {
						address = fixed_mod(address + 1);
						if (is_empty.at(address)) {
							date.at(address) = new_data;
							is_empty.at(address) = false;
							return;
						}

					}
				}
			}
			void remove(T old_data) {
				int address = fixed_mod(old_data);
				if (!search(old_data)) return;
				for (int i = 0; i < SIZE; i++) {
					if (data.at(fixed_mod(address+i)) == old_data && !is_empty.at(fixed_mod(address+i))) {
						is_empty.at(fixed_mod(address+i)) = true;
						is_deleted.at(fixed_mod(address+i)) = true;
						return;
					}
				}
			}
			bool search(T test_data) {
				int address = fixed_mod(test_data);
				for (int i = 0; i < SIZE; i++) {
					if (data.at(fixed_mod(address+find_next(i,test_data))) == test_data && !is_empty.at(fixed_mod(address+find_next(i,test_data)))) {
						return true;
					}
					if (is_empty.at(fixed_mod(address+find_next(i,test_data))) && !is_deleted.at(fixed_mod(address+find_next(i,test_data)))) {
						return false;
					}
				}
				return false;
			}
			void change(T old_data, T new_data) {
				if (search(old_data)) {
					remove(old_data);
					insert(new_data);
				}
				return;
			}
		};
