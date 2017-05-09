class Base {
public:
	// [build] error: templates may not be ‘virtual’
	template <class T> virtual void f(const T &) { 
		// 1
	}
};	

class Derivee : public Base {
public:
	// [build] error: templates may not be ‘virtual’
	template <class T> virtual void f(const T &) {
		// 2
	}
};

int main(int argc, char const *argv[])
{
	Base * p = new Derivee;

	p->f(3);	// Difficile !

	// Le compilateur ne peut pas savoir sur quoi pointera p au moment de l'exécution.
	// Ainsi pour être sûr que ce code fonctionne, doit-il instancier la fonction-membre
	// f pour toutes les classes dériviées de Base ? 
	// Plutôt que de répondre à cette qurstion gênante, C++ interdit tout simplement les member-templates virtuels.

	return 0;
}