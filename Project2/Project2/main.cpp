#include <iostream>
#include <map>
#include <functional>

class asdf {
private:
	int a;
public:
	asdf(int i) : a(i) {};
	friend bool operator<(const asdf& first, const asdf& second) {
		return first.a < second.a;
	}
};


int main() {
	std::less<asdf> a;
	std::cout << a(asdf(1),asdf(3)) << std::endl;
	return 0;
}