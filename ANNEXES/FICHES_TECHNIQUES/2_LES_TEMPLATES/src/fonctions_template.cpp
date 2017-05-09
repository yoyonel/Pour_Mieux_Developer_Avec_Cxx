#include <iostream>	// for std::cout
#include <sstream>	// for std:ostringsteam

// urls:
// [1] http://stackoverflow.com/questions/3846296/how-to-overload-the-operator-in-two-different-ways-for-postfix-a-and-prefix
// [2] http://www.cplusplus.com/reference/sstream/ostringstream/ostringstream/
// [3] http://stackoverflow.com/questions/2125880/convert-float-to-stdstring-in-c
// [4] https://msdn.microsoft.com/fr-fr/library/1z2f6c2k.aspx
// [5] http://stackoverflow.com/questions/3044690/operator-stdstring-const

template <class T>	// la fonction qui suit est paramétrée avec T
void f(T & elem) { elem++; }

class Complexe {
	float _reel, _imaginaire;
public:
	Complexe(float reel, float imaginaire) : _reel(reel), _imaginaire(imaginaire) {};

	// [1] - overload de l'operator ++
	// 1ere méthode en prefix
	Complexe& operator++ ()	{	// prefix ++	
		// Do work on this.	(increment your object here)
		_reel++;
		_imaginaire++;
		return *this;
	}
	// 2nde méthode en suffixe
 	// You want to make the ++ operator work like the standard operators
    // The simple way to do this is to implement postfix in terms of prefix.
    //
	Complexe operator++ (int) {
		Complexe result(*this);	// make a copy for result
		++(*this);				// Now use the prefix version to do the work
		return result;			// return the copy (the old) value.
	}

	// [2] - ostringstream
	// [5] - opérateur std::string const
	operator std::string() const {
		std::ostringstream ss;
		ss << "(" << this->_reel << ", " << this->_imaginaire << ")";
		return ss.str();
	}

	// [5] - opérateur std::string const -> en général une mauvaise idée, 
	// 		 plutot utiliser operator<<(std::ostream&, ...)
	// [4] - Surcharge de l'opérateur << -> la fonction surchargée d'opérateur << 
	//		 doit être déclarée comme une fonction friend de la classe Complexe 
	//		 pour accéder ux données privées depuis un object Complexe.
	friend std::ostream& operator<< (std::ostream& os, const Complexe& c);
};

std::ostream& operator<< (std::ostream& os, const Complexe& c) 
{
	os << std::string(c);
	return os;
}

int main(int argc, char const *argv[])
{
	int e = 3;
	std::cout << "e=" << e << std::endl;
	f(e);	// à la compilation, la fonction void f<int> (int & elem)
			// est générée. A l'exécution, e est incrémenté.
	 std::cout << "f(e) -> e=" << e << std::endl;
	
	Complexe c (3, 2);
	std::cout << "c=" << c << std::endl;
	f(c);	// compilation : void f<Complexe> (Complexe & elem) créée
			// exécution : appel de Complexe::operator++ pour c
	std::cout << "f(c) -> c=" << std::string(c) << std::endl;

	return 0;
}