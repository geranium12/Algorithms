#include <fstream>
#include <queue>
#include <vector>
#include <cmath>
#include <iomanip>

class Order {
private:
	int a;
	int b;
	long long d;
public:
	Order(const int& a, const int& b, const long& d) {
		this->a = a;
		this->b = b;
		this->d = d;
	}

	int getA() {
		return a;
	}

	int getB() {
		return b;
	}

	long long getD() {
		return d;
	}

	void setB(int b) {
		this->b = b;
	}

	void setD(long long d) {
		this->d = d;
	}

	friend std::ostream& operator<<(std::ostream& out, const Order& o) {
		out << o.a << " " << o.b << " " << o.d;
		return out;
	}
};

class OrderComparatorDeadlineA
{
public:
	int operator() (Order& o1, Order& o2) {
		int a1 = o1.getA();
		int a2 = o2.getA();
		long long d1 = o1.getD();
		long long d2 = o2.getD();
	
		if (d1 == d2) {
			return a1 < a2;
		}
		return d1 > d2;
	}
};

class OrderComparatorA 
{
public:
	int operator() (Order& o1, Order& o2) {
		int a1 = o1.getA();
		int a2 = o2.getA();
		return a1 < a2;
	}
};

typedef std::priority_queue<Order, std::vector<Order>, OrderComparatorDeadlineA> MinHeapDedlineA;
typedef std::priority_queue<Order, std::vector<Order>, OrderComparatorA> MaxHeapA;

int main() {
	std::ifstream fin("lazy.in");
	std::ofstream fout("lazy.out");

	int n;
	std::vector<Order> v;

	fin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		long long d;
		fin >> a >> b >> d;
		v.emplace_back(a, b, d);
	}
	
	MinHeapDedlineA min_heap{ OrderComparatorDeadlineA{}, std::move(v) };
	MaxHeapA max_heap{ OrderComparatorA{} };

	double price = 0;
	long long time, currentDeadline, payTime;
	time = currentDeadline = 0;

	Order orderMin = min_heap.top();
	min_heap.pop();
 	if (orderMin.getB() > orderMin.getD()) {
		price += (orderMin.getB() - orderMin.getD()) / (double)orderMin.getA();
	}
	else {
		orderMin.setD(orderMin.getB());
	}
	time = orderMin.getD();	

	max_heap.push(orderMin);

	while (!min_heap.empty()) {
		orderMin = min_heap.top();
		min_heap.pop();
		currentDeadline = orderMin.getD() - time;

		if (orderMin.getB() > currentDeadline) {
			payTime = orderMin.getB() - currentDeadline;
			time = orderMin.getD();

			while (!max_heap.empty() && payTime > 0) {
				Order orderMax = max_heap.top();
				if (orderMin.getA() >= orderMax.getA()) {
					break;
				}
				max_heap.pop();
				if (payTime >= orderMax.getD()) {
					price += (double)orderMax.getD() / orderMax.getA();
					payTime -= orderMax.getD();
				}
				else {
					price += (double)payTime / orderMax.getA();
					orderMax.setD(orderMax.getD() - payTime);
					max_heap.push(orderMax);
					payTime = 0;
				}
			}
			
			if (payTime > 0) {
				price += (double)payTime / orderMin.getA();
				orderMin.setD(orderMin.getB() - payTime);
			}
			else {
				orderMin.setD(orderMin.getB());
			}
			if (orderMin.getD() > 0) {
				max_heap.push(orderMin);
			}
		}
		else {
			time += orderMin.getB();
			orderMin.setD(orderMin.getB());
			max_heap.push(orderMin);

		}
	}

	fout << std::fixed << std::setprecision(2) << price << std::endl;
	return 0;
}