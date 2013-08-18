/***************************************************************************
 *   Copyright (C) 2003-2011 by Tux Football development team              *
 *   Authors: Jason Wood <jasonwood@blueyonder.co.uk>                      *
 *            Christoph Brill <egore911@egore911.de>                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "spriteobject.h"

#include <iostream>

#include "logger/logger.h"

SpriteObject::SpriteObject(SDL_Texture *surf, SDL_Texture *shadow, SDL_Texture *overlay,
				Point3D position, SDL_Rect offset, SDL_Rect shadowOffset, SDL_Rect overlayOffset)
{
	m_surface = surf;
	m_shadow = shadow;
	m_overlay = overlay;

	m_position = position;
	m_offset = offset;
	m_shadowOffset = shadowOffset;
	m_overlayOffset = overlayOffset;
}

SpriteObject::~SpriteObject()
{
}

void SpriteObject::draw(int left, int top, SDL_Renderer *renderer)
{
	SDL_Rect srcrect, dstrect;

	if (renderer==0 || m_surface==0)
		return;

	int sufrace_width, surface_height;
	SDL_QueryTexture(m_surface, NULL, NULL, &sufrace_width, &surface_height);

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = dstrect.w = sufrace_width;
	srcrect.h = dstrect.h = surface_height;

	dstrect.x = (int)(m_position.x() - left + m_offset.x);
	dstrect.y = (int)(m_position.y() - top + m_offset.y - m_position.z());

	if(SDL_RenderCopy(renderer, m_surface, &srcrect, &dstrect) < 0) {
		ERROR("could not draw SpriteObject to screen : " << SDL_GetError());
	}

}

void SpriteObject::drawShadow(int left, int top, SDL_Renderer *renderer)
{
	SDL_Rect srcrect, dstrect;

	if (renderer==0 || m_shadow==0)
		return;

	int shadow_width, shadow_height;
	SDL_QueryTexture(m_shadow, NULL, NULL, &shadow_width, &shadow_height);

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = dstrect.w = shadow_width;
	srcrect.h = dstrect.h = shadow_height;

	dstrect.x = (int)(m_position.x() - left + m_shadowOffset.x + m_position.z());
	dstrect.y = (int)(m_position.y() - top + m_shadowOffset.y - (m_position.z()*0.8));

	if(SDL_RenderCopy(renderer, m_shadow, &srcrect, &dstrect) < 0) {
		ERROR("could not blit SpriteObject shadow to screen : " << SDL_GetError());
	}
}

void SpriteObject::drawOverlay(int left, int top, SDL_Renderer *renderer)
{
	SDL_Rect srcrect, dstrect;

	if (renderer==0 || m_overlay==0)
		return;

	int overlay_width, overlay_height, renderer_width, renderer_height;
	SDL_QueryTexture(m_overlay, NULL, NULL, &overlay_width, &overlay_height);
	SDL_GetRendererOutputSize(renderer, &renderer_width, &renderer_height);

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = dstrect.w = overlay_width;
	srcrect.h = dstrect.h = overlay_height;

	dstrect.x = (int)(m_position.x() - left + m_overlayOffset.x);
	dstrect.y = (int)(m_position.y() - top + m_overlayOffset.y - m_position.z());

	// if overlay is off-screen, then draw it at the closest point on-screen that there is.
	if(dstrect.x<0) dstrect.x = 0;
	if(dstrect.x + srcrect.w > renderer_width) dstrect.x = renderer_width - srcrect.w;
	if(dstrect.y<0) dstrect.y = 0;
	if(dstrect.y + srcrect.h > renderer_height) dstrect.y = renderer_height - srcrect.h;

	if(SDL_RenderCopy(renderer, m_overlay, &srcrect, &dstrect) < 0) {
		ERROR("could not blit SpriteObject overlay to screen : " << SDL_GetError());
	}
}

void SpriteObject::setSurface(SDL_Texture *surf)
{
	m_surface = surf;
}

void SpriteObject::setOverlaySurface(SDL_Texture *surf)
{
	m_overlay = surf;
}

void SpriteObject::setShadowSurface(SDL_Texture *surf)
{
	m_shadow = surf;
}

void SpriteObject::setPosition(const Point3D &pos)
{
	m_position = pos;
}

Point3D SpriteObject::position()
{
	return m_position;
}
