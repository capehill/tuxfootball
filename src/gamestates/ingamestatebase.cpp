/***************************************************************************
 *   Copyright (C) 2003-2011 by Tux Football development team              *
 *   Authors: Christoph Brill <egore911@egore911.de>                       *
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

#include "ingamestatebase.h"

#include <iostream>
#include <SDL.h>

#include "gameengine.h"
#include "resources/surfacemanager.h"
#include "resources/fontmanager.h"
#include "logger/logger.h"

IngameStateBase::IngameStateBase(GameEngine &engine) :
				m_engine(engine)
{
	m_score = SurfaceManager::instance(m_engine.renderer())->load("graphics/score.png", false, true);
	m_nameFont = FontManager::instance(m_engine.renderer())->load("graphics/font_yellow.png", false, true);
	m_scoreFont = FontManager::instance(m_engine.renderer())->load("graphics/font_white.png", false, true);
}

IngameStateBase::~IngameStateBase()
{
	if(m_score) SurfaceManager::instance(m_engine.renderer())->release(m_score);
	if(m_nameFont) FontManager::instance(m_engine.renderer())->release(m_nameFont);
	if(m_scoreFont) FontManager::instance(m_engine.renderer())->release(m_scoreFont);
}

bool IngameStateBase::isGameInProgress() const
{
	return true;
}

void IngameStateBase::renderFrame()
{
	SDL_Rect score_pos, score_size;

	SDL_Renderer* renderer = m_engine.renderer();
	int renderer_width, renderer_height;
	SDL_GetRendererOutputSize(renderer, &renderer_width, &renderer_height);

	//
	// Draw Score background
	//
	if(m_score) {
		score_size.x = 0;
		score_size.y = 0;
		score_size.w = 298;
		score_size.h = 28;
		score_pos.x = renderer_width - score_size.w - 10;
		score_pos.y = 10;
		score_pos.w = 298;
		score_pos.h = 28;
		if(SDL_RenderCopy(renderer, m_score, &score_size, &score_pos) < 0) {
			ERROR("could not blit score : " << SDL_GetError());
		}
	}

	//
	// Draw Score
	//
	std::ostringstream homeScoreStr;
	std::ostringstream awayScoreStr;

	homeScoreStr << m_engine.score(GameEngine::HomeTeam);
	awayScoreStr << m_engine.score(GameEngine::AwayTeam);

	m_scoreFont->write(renderer, homeScoreStr.str().c_str(), renderer_width-228, 12);
	m_scoreFont->write(renderer, "-", renderer_width-207, 12);
	m_scoreFont->write(renderer, awayScoreStr.str().c_str(), renderer_width-193, 12);

	Team* homeTeam = m_engine.team(GameEngine::HomeTeam);
	Team* awayTeam = m_engine.team(GameEngine::AwayTeam);
	m_nameFont->write(renderer, homeTeam->shortname().c_str(), renderer_width-295, 12);
	m_nameFont->write(renderer, awayTeam->shortname().c_str(), renderer_width-160, 12);


	int scoreWidth = m_scoreFont->getTextWidth(homeScoreStr.str().c_str());
	scoreWidth = (scoreWidth < m_scoreFont->getTextWidth(awayScoreStr.str().c_str())) ? scoreWidth : m_scoreFont->getTextWidth(awayScoreStr.str().c_str());
	scoreWidth += 20;

	int sm = renderer_width/2;

	m_scoreFont->write(renderer, homeScoreStr.str().c_str(), sm - scoreWidth, renderer_height-34);
	m_scoreFont->write(renderer, awayScoreStr.str().c_str(), sm + 20, renderer_height-34);

	m_nameFont->write(renderer, homeTeam->name().c_str(), sm - scoreWidth - m_nameFont->getTextWidth(homeTeam->name().c_str())-20, renderer_height-34);
	m_nameFont->write(renderer, awayTeam->name().c_str(), sm+scoreWidth+20, renderer_height-34);

	//
	// Draw Time
	//
	uint timer = m_engine.timer();
	uint halfLength = m_engine.halfLength();
	std::ostringstream str3;
	int minutes = ((2700 * timer)/halfLength)%60;

	if(minutes<10) {
		str3 << ((2700 * timer)/halfLength)/60 << ":0" << ((2700 * timer)/halfLength)%60;
	} else {
		str3 << ((2700 * timer)/halfLength)/60 << ":" << ((2700 * timer)/halfLength)%60;
	}

	m_scoreFont->write(renderer, str3.str().c_str(), renderer_width - m_scoreFont->getTextWidth(str3.str().c_str()) - 22, 12);
}
