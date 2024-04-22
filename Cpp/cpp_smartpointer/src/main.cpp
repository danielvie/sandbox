#include <iostream>

// smartpointer class
template <typename T>
class SmartPointer {
	private:
		T* ptr;
		int* ref_count;

	public:
		SmartPointer() : ptr(nullptr), ref_count(new int(0)) {}
		SmartPointer(T* p) : ptr(p), ref_count(new int(1)) {}

		SmartPointer(const SmartPointer<T>& sp) : ptr(sp.ptr), ref_count(sp.ref_count) {
			++(*ref_count);
		}

		SmartPointer<T>& operator=(const SmartPointer<T>& sp) {
			if (this != &sp) {
				if (--(*ref_count) == 0) {
					delete ptr;
					delete ref_count;
				}
				ptr = sp.ptr;
				ref_count = sp.ref_count;
				++(*ref_count);
			}
			return *this;
		}

		~SmartPointer() {
			if (--(*ref_count) == 0) {
				delete ptr;
				delete ref_count;
			}
		}

		T& operator*() const {
			return *ptr;
		}

		T* operator->() const {
			return ptr;
		}

		int use_count() const {
			return *ref_count;
		}
};


class MyClass {
private:
    int m_value;
public:
    MyClass(int val) : m_value(val) {}
	~MyClass() {
		std::cout << "destroy with value " << m_value << std::endl;
	}
    void print() {
        std::cout << "Value is: " << m_value << std::endl;
    }
};

int main() {
    SmartPointer<MyClass> sp1(new MyClass(42));
    SmartPointer<MyClass> sp2 = sp1;
    SmartPointer<MyClass> sp3(new MyClass(100));

    std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    std::cout << "sp3 use count: " << sp3.use_count() << std::endl;

    // sp1->print();
    // (*sp2).print();

    // sp1 = sp3;

    // std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    // std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    // std::cout << "sp3 use count: " << sp3.use_count() << std::endl;

    // sp2 = sp3;

    // std::cout << "sp1 use count: " << sp1.use_count() << std::endl;
    // std::cout << "sp2 use count: " << sp2.use_count() << std::endl;
    // std::cout << "sp3 use count: " << sp3.use_count() << std::endl;

    return 0;
}