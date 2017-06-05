#pragma once

#include <SFML\Graphics.hpp>
#include <complex>
#include "MandelbrotCache.h"
#include "MandelbrotMath.h"

/*
Ensemble de Mandelbrot affichable à l'écran
T : sous-type de complexe
*/
template <typename T>
class MandelbrotSet : public sf::Drawable
{
protected:
	sf::Image m_img;
	MandelbrotCache<T> m_cache;

private:
	sf::Texture m_tex;
	sf::Sprite m_sprite;

	int m_w;
	int m_h;
	unsigned int m_lastIter;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	/*
	Effectue le calcul des points de l'ensemble
	virtual pour choisir mode de calcul
	*/
	virtual void doCompute(unsigned int iter);

	bool computeIter(unsigned int from, unsigned int to, std::complex<T>& point, const std::complex<T>& origin);

public:
	MandelbrotSet(unsigned int w, unsigned int iter);
	virtual ~MandelbrotSet();

	/*
	Calcule l'image à afficher
	*/
	void compute(unsigned int iter);

	//choisit la dimension de l'image créée
	void setDimension(unsigned int width);

	//calcule la prochaine itération
	void nextIteration(int offset = 1);

	//renvoie la dernière itération affichée
	unsigned int getLastIteration() const;

	int getWidth() const;
	int getHeight() const;
};



////////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
bool MandelbrotSet<T>::computeIter(unsigned int from, unsigned int to, std::complex<T>& point, const std::complex<T> &origin) {
	if (from >= to) {
		return isInSet(point);
	} //from < to
	point = nextOfMandelbrotSequence(point, origin);
	if (!isInSet(point)) {
		return false;
	} //point peut-être dans ensemble à une autre itération
	return computeIter(from + 1, to, point, origin);
}

template <typename T>
void MandelbrotSet<T>::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}


template <typename T>
MandelbrotSet<T>::MandelbrotSet(unsigned int w, unsigned int iter) : sf::Drawable(), m_img(), m_tex(), m_sprite(), m_lastIter(0)
{
	setDimension(w);
	compute(iter);
}


template <typename T>
MandelbrotSet<T>::~MandelbrotSet()
{
}

template <typename T>
void MandelbrotSet<T>::compute(unsigned int iter)
{
	m_img.create(m_w, m_h, sf::Color::White);

	//appel virtuel
	doCompute(iter);

	m_cache.setIter(iter); //maj de l'itération en cache
	m_lastIter = iter;

	m_tex.loadFromImage(m_img);
	m_sprite.setTexture(m_tex);
}

template <typename T>
void MandelbrotSet<T>::setDimension(unsigned int width)
{
	m_w = width;
	m_h = int((3.f / 4.f)*float(m_w));
	m_img.create(m_w, m_h, sf::Color::White);

	if (m_cache.getWidth() != width) {
		m_cache.resize(unsigned int(m_w), unsigned int(m_h));
	}
}

template <typename T>
void MandelbrotSet<T>::nextIteration(int offset)
{
	compute(m_lastIter + offset);
}

template <typename T>
unsigned int MandelbrotSet<T>::getLastIteration() const {
	return m_lastIter;
}

template <typename T>
void MandelbrotSet<T>::doCompute(unsigned int iter) {
	for (int i = 0; i < m_w; ++i) {
		for (int j = 0; j < m_h; ++j) {
			std::complex<T> origin = physicalToMath(std::complex<T>(T(i), T(j)), m_w, m_h);
			std::complex<T> p = 0;
			bool ok;
			if (m_cache.getIter() <= iter) { //cache utilisable
				p = m_cache(i, j);
				ok = computeIter(m_cache.getIter(), iter, p, origin);
			}
			else { //cache non utilisable
				ok = computeIter(0, iter, p, origin);
			}
			m_cache(i, j) = p;
			if (ok) {
				m_img.setPixel(i, j, sf::Color::Black);
			}
		}
	}
}


template <typename T>
int MandelbrotSet<T>::getWidth() const {
	return m_w;
}


template <typename T>
int MandelbrotSet<T>::getHeight() const {
	return m_h;
}
