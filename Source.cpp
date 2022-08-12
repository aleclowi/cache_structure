#include "Cache.h"
#include<iostream>
#include<string>
bool length_comp(const std::string& left, const std::string& right) {
	return left.size() < right.size();
}
int main() {
	pic10b::cache<int, 3> intCache; // can store up to 3 values of int plus high and low
		try { // can we pop with nothing there?
		intCache.pop();
	}
	catch (const std::exception& e) { // apparently not...
		std::cerr << "exception thrown: " << e.what() << '\n';
	}
	std::cout << "current: ";
	for (int i : intCache) { // empty so does nothing
		std::cout << i << " ";
	}
	std::cout << '\n';
	intCache.insert(3); // insert 3 and look for high and low
	std::cout << "high and low: " << intCache.get_high() << " " <<
		intCache.get_low() << '\n';
	intCache.insert(4); // insert 4
	for (int i : intCache) { // print all the numbers
		std::cout << i << " ";
	}
	std::cout << '\n';
	// insert two more numbers, will pop the 3
	intCache.insert(27);
	intCache.insert(37);
	std::cout << "print all the numbers: ";
	for (auto itr = intCache.begin(),
		past_end = intCache.end(); itr != past_end; ++itr) {
		std::cout << *itr << " ";
	}
	std::cout << '\n';
	// pop the most distant (4)
	intCache.pop();
	std::cout << "After a pop: ";
	for (auto itr = intCache.begin(), past_end = intCache.end();
		itr != past_end; ++itr) { // print all the numbers
		std::cout << *itr << " ";
	}
	std::cout << '\n';
	std::cout << "recall highs and lows: " << intCache.get_high() <<
		" " << intCache.get_low() << '\n';
	auto intCache2 = intCache; // copy constructor
	std::cout << "element count: " << intCache2.size() << '\n';
	auto intCache3 = std::move(intCache); // move constructor
	std::cout << "element count: " << intCache3.size() << '\n';
	intCache = intCache3; // assignment operator
	std::cout << "element count: " << intCache.size() << '\n';
	pic10b::cache<std::string, 2, bool(*)(const std::string&, const
		std::string&)>
		stringCache(length_comp);
	stringCache.emplace(); // emtpy string added
	std::string hey = "hey";
	stringCache.insert(hey);
	stringCache.insert("howdy");
	stringCache.insert("salutations");
	stringCache.insert("greetings");
	stringCache.pop(); // now only stores "greetings"
	stringCache.emplace(4, '$'); // also stores "$$$$"
	std::cout << "printout of strings: ";
	print(stringCache); // prints the cache
	std::cout << '\n';
	std::cout << "size of a string: ";
	// in a world if auto didn't exist...
	pic10b::cache<std::string, 2,
		bool(*)(const std::string&, const std::string&)>::const_iterator its =
		stringCache.begin();
	std::cout << its->size() << '\n'; // can use arrow operator!
	std::cout << "highs and lows of the strings (lowest is empty): "
		<< stringCache.get_high() << " " << stringCache.get_low() << '\n';
	return 0;
}