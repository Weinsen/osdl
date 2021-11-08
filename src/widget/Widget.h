#ifndef SRC_WIDGET_WIDGET_H
#define SRC_WIDGET_WIDGET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <list>
#include "Animation.h"
#include "Geometry.h"
#include "Renderer.h"

namespace OSDL {

class Animation;
class Raster;
class Renderer;

class Widget {

protected:
	Animation* animation_;
	Geometry geometry_;
	SDL_Texture* texture_;
	Renderer* renderer_;
	std::list<Widget*> widgets_;
	Widget* parent_;
	std::string el_name_;
	bool update_;
	bool is_alive_;

	virtual std::list<Widget*>::iterator RemoveChild(std::list<Widget*>::iterator i);

public:
	Widget();
	virtual ~Widget();
	void Clear();
	void Update();
	void Move(const Geometry& pos);
	void Move(int x, int y);
	void SetDimension(int w, int h);
	void SetPosition(const Geometry& pos);
	void SetAnimation(Animation *animation);
	void Load();
	void Render(const Geometry* position = NULL);
	void RenderTexture(Raster* root);
	void SetParent(Widget* parent_);
	void SetRenderer(Renderer* renderer);
	void AddChild(Widget* child);
	void SetAlive(bool alive = true);
	void SetWidgetName(std::string name);
	Widget* GetChildByName(std::string name);
	Geometry *GetPosition();
	virtual void Init();
	virtual void PreRender();
};

}

#endif // SRC_WIDGET_WIDGET_H