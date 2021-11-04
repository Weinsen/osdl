#include "Raster.h"

namespace OSDL {

Raster::Raster() {
    parent_ = NULL;
    mirror_ = false;
    geometry_ = Geometry(0, 0, 0, 0, 0.0);
    blendMode_ = SDL_BLENDMODE_BLEND;
}

Raster::~Raster() {
}

// TODO check return
void Raster::Move(const Geometry& pos) {
    geometry_ += pos;
}

void Raster::Move(int x, int y) {
    geometry_.x += x;
    geometry_.y += y;
}

void Raster::SetPosition(const Geometry& pos) {
    geometry_.x = pos.x;
    geometry_.y = pos.y;
    geometry_.angle = pos.angle;
}

void Raster::SetParent(Raster* parent) {
    parent_ = parent;
}

void Raster::AddChild(Raster* child) {
    childs_.push_back(child);
    child->SetParent(this);
}

void Raster::AddChild(Raster* child, Geometry& position) {
    childs_.push_back(child);
    child->SetParent(this);
    child->Move(position);
}

SDL_Surface* Raster::Render(const Geometry* position) {

    SDL_Surface* surface = Generate();
    Geometry pos = geometry_;
    if (position) {
        pos +=  *position;
    }
    // SDL_Rect r1{pos.x(), pos.y(), geometry_.w, geometry_.h};

    for (auto c : childs_) {
        SDL_Surface* c_s = c->Render(&pos);
        if (!c_s) {
            continue;
        }
        SDL_Rect r1, r2;
        if (mirror_) {
            int posx = geometry_.w - c_s->w - c->GetPosition()->x;
            r1 = SDL_Rect{posx, c->GetPosition()->y, c_s->w, c_s->h};
            r2 = SDL_Rect{0, 0, c_s->w, c_s->h};
        } else {
            r1 = SDL_Rect{c->GetPosition()->x, c->GetPosition()->y, c_s->w, c_s->h};
            r2 = SDL_Rect{0, 0, c_s->w, c_s->h};
        }
        SDL_SetSurfaceBlendMode(c_s, c->blendMode_);
        SDL_BlitSurface(c_s, &r2, surface, &r1);
        SDL_FreeSurface(c_s);
        c_s = NULL;
    }

    return surface;

}

Geometry *Raster::GetPosition() {
    return &geometry_;
}

void Raster::SetMirror(bool mirror) {
    mirror_ = mirror;
}

void Raster::SetBlendMode(SDL_BlendMode blendMode) {
    blendMode_ = blendMode;
}

SDL_Surface* Raster::CreateSurface(int w, int h) {
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        return SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    #else
        return SDL_CreateRGBSurface(0, w, h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    #endif
}


}


