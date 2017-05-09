#include <iostream>	// for std::cout

// Execution:
// $ ./fonctions-membres_template
// void Liste::ranger(const Organisateur&) [with Organisateur = TriDecroissant]
// virtual void TriDecroissant::trier(Liste&) const

// urls: 
// [1] - http://stackoverflow.com/questions/679021/how-to-find-the-name-of-the-current-function-at-runtime

class Liste {	// cette classe peut être ou ne pas être template
public:
	// ...
	template <class Organisateur>
	void ranger (const Organisateur & tri) { 
		// [1]
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		tri.trier(*this); 
	}
};

class Tri {
public:	
	virtual void trier(Liste & liste) const = 0;
};

class TriDecroissant : public Tri { 
public:
	virtual void trier(Liste & liste) const {
		// [1]
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

int main(int argc, char const *argv[])
{
	Liste maListe;
	// ...
	maListe.ranger( TriDecroissant() );

	return 0;
}