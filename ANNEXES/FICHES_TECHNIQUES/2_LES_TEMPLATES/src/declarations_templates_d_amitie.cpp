#include <iostream>
#include <sstream>

// url: http://en.cppreference.com/w/cpp/language/friend

// 1) Designates a function or several functions as friends of this class 
namespace ns_test_1 {
	class X {
	public:
		X(char)	{ }
		~X() { }
		char * foo (int);
	};

	class Y {
	    int data; // private member
	    // the non-member function operator<< will have access to Y's private members
	    friend std::ostream& operator<<(std::ostream& out, const Y& o);
	    friend char* X::foo(int); // members of other classes can be friends too
	    friend X::X(char), X::~X(); // constructors and destructors can be friends
	};

	// friend declaration does not declare a member function
	// this operator<< still needs to be defined, as a non-member
	std::ostream& operator<<(std::ostream& out, const Y& y)
	{
	    return out << y.data; // can access private member Y::data
	}
}

// 2) (only allowed in non-local class definitions) Defines a non-member function, and makes it a friend of this class at the same time. 
// Such non-member function is always inline. 
namespace ns_test_2 {
	class X {
	    int a;
	    friend void friend_set(X& p, int i) {
	        p.a = i; // this is a non-member function
	    }
	public:
	    void member_set(int i) {
	        a = i; // this is a member function
	    }
	};
}

//
namespace ns_test_4 {
	class Y {};
	class A {
	    int data; // private data member
	    class B { }; // private nested type
	    enum { a = 100 }; // private enumerator
	    friend class X; // friend class forward declaration (elaborated class name)
	    friend Y; // friend class declaration (simple type specifier) (since c++11)
	};
	 
	class X : A::B // Error until C++11: the base-clause is not part of member declarations
	               // allowed in C++11
	{
	    A::B mx; // OK: A::B accessible to member of friend
	    class Y : A::B { // OK: A::B accessible to base-clause of nested member of friend
	    };
	    int v[A::a]; // OK: A::a accessible to member of friend
	};
}

// Notes:
// Friendship is not transitive (a friend of your friend is not your friend)
// Friendship is not inherited (your friend's children are not your friends)
namespace ns_test_friendship {
	class F {};
	int f();
	int main()
	{
	    extern int g();
	    
	    class Local { // Local class in the main() function
	        // friend int f(); // Error, no such function declared in main()
	        friend int g(); // OK, there is a declaration for g in main()
	        friend class F; // friends a local F (defined later)
	        friend class ns_test_friendship::F; // friends the global F
	    };
	    
	    class F {}; // local F

	    return 0;
	}
}

// Template friends
namespace ns_test_template_friends {
	// In this case, every specialization of the template becomes a friend, 
	// whether it is implicitly instantiated, partially specialized, or explicitly specialized. 
	namespace template_specialization_friendship {
		class A {
		    template<typename T>
		    friend class B; // every B<T> is a friend of A
		 
		    template<typename T>
		    friend void f(T) {} // every f<T> is a friend of A
		};
	}

	// Friend declarations cannot refer to partial specializations, 
	// but can refer to full specializations:
	namespace partial_full_specializations {
		template<class T> class A {}; // primary
		template<class T> class A<T*> {}; // partial
		template<> class A<int> {}; // full
		class X {
			// [build] error: partial specialization ‘ns_test_template_friends::A<T*>’ declared ‘friend’
		    // template<class T> friend class A<T*>; // error!

		    friend class A<int>; // OK
		};
	}

	// When a friend declaration refers to a full specialization of a function template, 
	// the keyword inline and default arguments cannot be used. 
	namespace no_inline_default {
		template<class T> void f(int);
		template<> void f<int>(int);
		 
		class X {
			// [build] error: default arguments are not allowed in declaration of friend template specialization ‘void f<int>(int)’
		    // friend void f<int>(int x = 1); // error: default args not allowed
		};
	}

	// If a member of a class template A is declared to be a friend of a non-template class B, 
	// the corresponding member of every specialization of A becomes a friend of B. 
	// If A is explicitly specialized, as long as there is a member of the 
	// same name, same kind (type, function, class template, function template), same parameters/signature, 
	// it will be a friend of B. 
	namespace template_class_friend_to_a_non_template_class {
		template<typename T> // primary template
		struct A
		{
		    struct C {};
		    void f();
		    struct D {
		        void g();
		    };
		};
		 
		template<> // full specialization
		struct A<int>
		{
		    struct C {};
		    int f();
		    struct D {
		        void g();
		    };
		};
		 
		class B // non-template class
		{
		    template<class T>
		    friend struct A<T>::C; // A<int>::C is a friend, as well as all A<T>::C
		 
		    template<class T>
		    friend void A<T>::f(); // A<int>::f() is not a friend, because the
		                           // signatures do not match, but A<char>::f() is
		 
		    template<class T>
		    friend void A<T>::D::g(); // A<int>::D::g() is not a friend: it is not a member
		                              // of A, and A<int>::D is not a specialization of A<T>::D
		};
	}

	namespace template_friends_operators {
		namespace in_class_body {
			// A common use case for template friends is declaration of a non-member operator overload that acts on a class template, 
			// e.g. operator<<(std::ostream&, const Foo<T>&) for some user-defined Foo<T>
			// Such operator can be defined in the class body, 
			// which has the effect of generating a separate non-template operator<< for each T 
			// and makes that non-template operator<< a friend of its Foo<T> 
			template<typename T>
			class Foo {
			 public:
			    Foo(const T& val) : data(val) {}
			 private:
			    T data;
			 
			    // generates a non-template operator<< for this T
			    friend std::ostream& operator<<(std::ostream& os, const Foo& obj)
			    {
			        return os << obj.data;
			    }
			};
			 
			int main()
			{
			    Foo<double> obj(1.23);
			    std::cout << obj << '\n';

			    return 0;
			}
		}

		namespace before_the_class_body {
			template<typename T>
			class Foo; // forward declare to make function declaration possible
			 
			template<typename T> // declaration
			std::ostream& operator<<(std::ostream&, const Foo<T>&);
			 
			template<typename T>
			class Foo {
			 public:
			    Foo(const T& val) : data(val) {}
			 private:
			    T data;
			 
			    // refers to a full specialization for this particular T 
			    friend std::ostream& operator<< <> (std::ostream&, const Foo&);
			    // note: this relies on template argument deduction in declarations
			    // can also specify the template argument with operator<< <T>"
			};
			 
			// definition
			template<typename T>
			std::ostream& operator<<(std::ostream& os, const Foo<T>& obj)
			{
			    return os << obj.data;
			}
			 
			int main()
			{
			    Foo<double> obj(1.23);
			    std::cout << obj << '\n';

			    Foo<float> obj_2(1.23);
			    std::cout << obj_2 << '\n';
			    return 0;
			}			
		}

		namespace insertion_extraction_operators_as_nonmember_friend {
			class MyClass {
			    int i;
			 
			    friend std::ostream& operator<<(std::ostream& out, const MyClass& o);
			    friend std::istream& operator>>(std::istream& in, MyClass& o);
			 public:
			    MyClass(int i = 0) : i(i) {}
			};
			 
			std::ostream& operator<<(std::ostream& out, const MyClass& mc)
			{
			    return out << mc.i;
			}
			 
			// C++11
			std::istream& operator>>(std::istream& in, MyClass& mc)
			{
			    return in >> mc.i;
			}
			 
			int main()
			{
			    MyClass mc(7);
			    std::cout << mc << '\n';
			    std::istringstream("100") >> mc;
			    std::cout << mc << '\n';

			    return 0;
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	ns_test_friendship::main();
	ns_test_template_friends::template_friends_operators::in_class_body::main();
	ns_test_template_friends::template_friends_operators::before_the_class_body::main();
	ns_test_template_friends::template_friends_operators::insertion_extraction_operators_as_nonmember_friend::main();
	return 0;
}