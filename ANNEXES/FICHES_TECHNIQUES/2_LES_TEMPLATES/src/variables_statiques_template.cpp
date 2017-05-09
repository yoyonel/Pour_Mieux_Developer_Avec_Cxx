#include <iostream>	// for std::cout

namespace ns_test_1 {
	template <class T>
	class Liste {
	public:
		static int nbInstances;
	};

	template <class T>
	int Liste<T>::nbInstances = 42;

	void use_static_template_variable()
	{
		std::cout << Liste<void>::nbInstances << std::endl;	// il faut quand même instancier un type pour la classe template
															// pour avoir accès à la variable statique	
	}
}

namespace ns_test_2 {
	template <class T>
	class Liste {
	public:
		static T nbInstances;
		static void init()
		{
			nbInstances = (T)(42.42);
		}
	};

	template <class T>
	T Liste<T>::nbInstances;
	void use_static_template_variable()
	{
		{
			Liste<int>::init();
			std::cout << Liste<int>::nbInstances << std::endl;
		}

		{
			Liste<double>::init();
			std::cout << Liste<double>::nbInstances << std::endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	ns_test_1::use_static_template_variable();
	ns_test_2::use_static_template_variable();
	return 0;
}