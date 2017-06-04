#pragma once



/*bool near(float a, float b) {
	return  std::abs(b - a) <= 0.001f;
}*/



/*
Indique si le point est dans l'ensemble
T : sous-type de complexe
*/
template <typename T>
bool isInSet(std::complex<T> nb, unsigned int iter = 30) {
	if (nb.real() < (T)-2 || nb.real() >(T)1 || nb.imag() < (T)-1 || nb.imag() >(T)1) {
		return false;
	}
	return std::abs(Mandelbrot_n(iter, nb)) <= T(2);
}


/*
Renvoie le nombre suivant de la séquence de mandelbrot
T : type de complexe
*/
template <typename T>
T nextOfMandelbrotSequence(T prec, T point) {
	return (prec * prec) + point;
}

/*
Renvoie le rang n de la séquence de mandelbrot
T : type de complexe
*/
template <typename T>
T Mandelbrot_n(unsigned int n, T point) {
	if (n == 0) {
		return 0;
	}
	T prec = Mandelbrot_n(n - 1, point);
	return nextOfMandelbrotSequence(prec, point);
}


/*
point : point physique à transformer en point mathématique
w : largeur du monde physique
h : hauteur du monde physique
T : sous-type du complexe
*/
template <typename T>
std::complex<T> physicalToMath(std::complex<T> point, int w, int h) {
	T wUnit = w / T(3);
	T hUnit = h / T(2);
	point.real((point.real() / wUnit) - T(2));
	point.imag((point.imag() / hUnit) - T(1));
	return point;
}
