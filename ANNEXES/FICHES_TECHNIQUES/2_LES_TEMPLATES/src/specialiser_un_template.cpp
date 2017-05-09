#include <iostream>	// for std::cout

// urls:
// [1] http://en.cppreference.com/w/cpp/language/template_specialization
// [2] http://en.cppreference.com/w/cpp/language/function_template

// primary template
template <class T>	// définition du cas général
void afficher(const T & obj) {
	std::cout << obj.name(); 	
}

// Le type int n'ayant pas de fonction-membre name, on définit:
// specialization for T = int
// [1] -  Explicit specializations of function templates
template<> 
void afficher(const int & obj) { 
	std::cout << obj; 
}

// --------------------------
// Explicit instantiation
// --------------------------
// A trailing template-argument can be left unspecified in an explicit instantiation 
// of a function template specialization or of a member function template specialization 
// if it can be deduced from the function parameter 
template<typename T>
void f(T s)
{
    std::cout << s << '\n';
}
 
// A trailing template-argument can be left unspecified in an explicit instantiation of a function template specialization 
// or of a member function template specialization if it can be deduced from the function parameter 
template void f<double>(double); // instantiates f<double>(double)
template void f<>(char); // instantiates f<char>(char), template argument deduced
template void f(int); // instantiates f<int>(int), template argument deduced

// Explicit instantiation definition of a function template with default arguments is not a use of the arguments, 
// and does not attempt to initialize them: 
char* p = 0;
template<class T> T g(T x = &p) { return x; }
template int g<int>(int);   // OK even though &p isn’t an int.


// --------------------------
// Implicit instanciation
// --------------------------
// When code refers to a function in context that requires the function definition to exist, 
// and this particular function has not been explicitly instantiated, implicit instantiation occurs. 
// The list of template arguments does not have to be supplied if it can be deduced from context 
namespace implicit_instanciation {
	template<typename T>
	void f(T s)
	{
	    std::cout << s << '\n';
	}

	void test() 
	{
		f<double>(1.1); // instantiates and calls f<double>(double)
    	f<>('a'); // instantiates and calls f<char>(char)
    	f(7); // instantiates and calls f<int>(int)
    	void (*ptr)(std::string) = f; // instantiates f<string>(string)
    	ptr("5");
	}
}
// Note: omitting <> entirely allows overload resolution to examine both template and non-template overloads. 

// --------------------------
// Template argument deduction
// --------------------------
namespace template_argument_deduction {
	template<typename To, typename From> To convert(From f);

	template<>
	int convert(double f) { return f; }
	template<>
	int convert(float f) { return f; }
	template<>
	char convert(double f) { return ' '; }
	 
	void g(double d) 
	{
	    int i = convert<int>(d); // calls convert<int,double>(double)
	    char c = convert<char>(d); // calls convert<char,double>(double)
	    int(*ptr)(float) = convert; // instantiates convert<int, float>(float)

	    std::cout << "int i = convert<int>(" << d << "); -> i=" << i << std::endl;
	    std::cout << "char c = convert<char>(" << d << "); -> c=" << c << std::endl;
	    std::cout << "int(*ptr)(float) = convert; ptr(" << d << ") = " << ptr(d) << std::endl;
	}

	void test()
	{
		g(4.2);
	}
}

// --------------------------
// Explicit template arguments
// --------------------------
namespace explicit_template_arguments {
	template<class ... Types> void f(Types ... values);

	template<>
	void f(int* ptr_i, float* f, int i) {}
	
	void g() {
  		f<int*, float*>(0, 0, 0); // Types = {int*, float*, int}
	}

}

// [2]
int main(int argc, char const *argv[])
{
	afficher(5);
	std::cout << std::endl;
	
	implicit_instanciation::test();
	template_argument_deduction::test();

	return 0;
}