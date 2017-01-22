#include "Viewer.h"
#include "WinSingleton.h"

Viewer::Viewer(Model * _model)
{
	model = _model;
	window = WinSingleton::getInstance();
}

void Viewer::update()
{
	window->clear();
	std::vector<Layer>& layers = model->returnCurrentLevel()->getLayerList();
	for (int layer = 0; layer < layers.size(); layer++)
		for (int tile = 0; tile < layers[layer].tiles.size(); tile++)
			window->draw(layers[layer].tiles[tile]);
	window->display();
}
