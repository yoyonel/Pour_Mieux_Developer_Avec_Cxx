template <class T>	// la classe qui suit est paramétré avec T
class Liste {
	T * tab;	// T peut être un int, ou un float, ou un Animal ...
	void allouer(int taille);
public:
	void rajouterElement (T e) { 
		// ... 
	};
};

template <class T>
void Liste<T>::allouer(int taille) { 
	tab = new T[taille]; 
	// ... 
}

class Animal;

Liste<int>		tab1;	// tab1 est une liste d'entiers
Liste<Animal>	tab2;	// tab2 est une liste d'objects Animal
Liste<int>		tab3;	// tab3 est encore une liste d'entiers

int main() {
}