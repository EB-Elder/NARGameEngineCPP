#pragma once
// Pour les cas ou il nous faut faire des for-each en reverse
	// specifiquement pour les vector ici
template <typename V>
struct reverse_wrapper
{
	V& vec;										// rappel: on peut declarer un champ comme reference
	reverse_wrapper(V& _vec) : vec(_vec) {}	// mais celui-ci doit etre initialise par le constructeur

	// on redefini les meta-fonctions d'iterator begin() et end() 
	// en les remplacant par un reverse_iterator
	typename V::reverse_iterator begin() { return vec.rbegin(); }
	typename V::reverse_iterator end() { return vec.rend(); }
};

// Cette fonction permet au compilateur de deduire le type T du parametre
// car c'est ce type que l'on doit passer a notre struct reverse_wrapper 
template <typename T>
reverse_wrapper<T> make_reverse(T& v) {
	return reverse_wrapper<T>(v);
}