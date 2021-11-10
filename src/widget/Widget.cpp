#include "Widget.h"
#include "Raster.h"

namespace OSDL {

Widget::Widget() : texture_(NULL), parent_(NULL), animation_(NULL), update_(false), is_alive_(true) {
    geometry_ = Geometry(0, 0, 0, 0, 0.0);
}

Widget::~Widget() {
    Clear();
    if (animation_ != NULL) {
        delete(animation_);
        animation_ = NULL;
    }
}

// TODO check return
void Widget::Move(const Geometry& pos) {
    geometry_ += pos;
}

void Widget::Move(int x, int y) {
    geometry_.x += x;
    geometry_.y += y;
}

void Widget::SetDimension(int w, int h) {
    geometry_.w = w;
    geometry_.h = h;
}

void Widget::SetPosition(const Geometry& pos) {
    geometry_.x = pos.x;
    geometry_.y = pos.y;
    geometry_.angle = pos.angle;
}

void Widget::Load() {

    if (!renderer_) {
        return;
    }

    if (!texture_ || update_) {
        update_ = false;
        renderer_->Update();
        Clear();
        Init();
    }

    if (animation_) {
        animation_->Animate();
        renderer_->Update();
        if (animation_->IsDone()) {
            delete(animation_);
            animation_ = NULL;
        }
    }

    PreRender();

    for (std::list<Widget*>::iterator i=widgets_.begin(); i!=widgets_.end();) {
        auto w = *i;
        if (w->is_alive_ && w != NULL) {
            w->Load();
            i++;
        } else if (!w->is_alive_) {
            i = RemoveChild(i);
        }
    }

}

// TODO check return
void Widget::Render(const Geometry* position) {

    if (!renderer_) {
        return;
    }

    Geometry pos = geometry_;
    if (position) {
        pos +=  *position;
    }
    SDL_Rect renderQuad = {pos.x, pos.y, geometry_.w, geometry_.h};
    SDL_RenderCopyEx(renderer_->Sdl(), texture_, NULL, &renderQuad, pos.angle, NULL, SDL_FLIP_NONE);

    for (auto& w : widgets_) {
        w->Render(&pos);
    }

}

void Widget::RenderTexture(Raster* root) {

    auto s = root->Render();
    texture_ = SDL_CreateTextureFromSurface(renderer_->Sdl(), s);
    if (!geometry_.w) geometry_.w = s->w;
    if (!geometry_.h) geometry_.h = s->h;
    SDL_FreeSurface(s);

}

void Widget::SetRenderer(Renderer* renderer) {
	renderer_ = renderer;
}

void Widget::SetParent(Widget* parent) {
    parent_ = parent;
}

void Widget::AddChild(Widget* child) {
    widgets_.push_back(child);
    child->SetParent(this);
    child->SetRenderer(renderer_);
}

std::list<Widget*>::iterator Widget::RemoveChild(std::list<Widget*>::iterator i) {
    delete(*i);
    i = widgets_.erase(i);
    return i ;
}

Geometry *Widget::GetPosition() {
    return &geometry_;
}

void Widget::Update() {
    update_ = true;
    renderer_->Update();
}

void Widget::Clear() {
    if (texture_ != NULL) {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void Widget::SetAnimation(Animation *animation) {
    if (animation != NULL) {
        animation_ = animation;
        animation_->SetWidget(this);
    }
}

void Widget::SetAlive(bool alive) {
    is_alive_ = alive;
}

bool Widget::IsAlive() {
    return is_alive_;
}

void Widget::SetWidgetName(std::string name) {
    el_name_ = name;
}

Widget* Widget::GetChildByName(std::string name) {
    for (auto &c : widgets_) {
        if (c->el_name_ == name) {
            return c;
        }
    }
    return NULL;
}

void Widget::Init() {}
void Widget::PreRender() {}

}