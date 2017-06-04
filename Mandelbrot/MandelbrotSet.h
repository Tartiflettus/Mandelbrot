#pragma once

#include <SFML\Graphics.hpp>
#include <complex>

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

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	MandelbrotSet(unsigned int w, unsigned int iter);
	~MandelbrotSet();

	//calcule l'image à afficher
	void compute(unsigned int width, unsigned int iter);
};

