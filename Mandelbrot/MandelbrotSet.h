#pragma once

#include <SFML\Graphics.hpp>
#include <complex>
#include "MandelbrotCache.h"

/*
Ensemble de Mandelbrot affichable à l'écran
*/
class MandelbrotSet : public sf::Drawable
{
private:
	sf::Image m_img;
	sf::Texture m_tex;
	sf::Sprite m_sprite;

	int m_w;
	int m_h;
	unsigned int m_lastIter;
	MandelbrotCache<float> m_cache;

	bool computeIter(unsigned int from, unsigned int to, std::complex<float>& point, std::complex<float> origin);

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	MandelbrotSet(unsigned int w, unsigned int iter);
	~MandelbrotSet();

	//calcule l'image à afficher
	void compute(unsigned int iter);

	//choisit la dimension de l'image créée
	void setDimension(unsigned int width);
};

