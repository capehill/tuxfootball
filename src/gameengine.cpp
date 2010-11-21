/***************************************************************************
                          gameengine.cpp  - Main game logic and initialisation
                             -------------------
    begin                : 18.04.2003
    copyright            : (C) 2003 by Jason Wood
    email                : jasonwood@blueyonder.co.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>
#ifdef HAVE_GETTEXT
#include <libintl.h>
#define _(String) gettext (String)
#else
#define _(String) (String)
#endif
	
#include "gameengine.h"
#include "surfacemanager.h"
#include "fontmanager.h"
#include "soundmanager.h"
#include "Font.hpp"
#include "controller.h"

#include "menu.h"
#include "videosettingsmenu.h"
#include "redefinekeysmenu.h"
#include "mainmenu.h"
#include "menuoptionlist.h"
#include "menubutton.h"
#include "menukeyselect.h"
#include "menulabel.h"

#include "mainmenustate.h"
#include "redefinekeysstate.h"
#include "matchstartstate.h"
#include "nationalanthemstate.h"
#include "firsthalfstate.h"
#include "halftimestate.h"
#include "secondhalfstate.h"
#include "fulltimestate.h"
#include "extratimestate.h"
#include "extratimefirsthalfstate.h"
#include "extratimehalftimestate.h"
#include "extratimesecondhalfstate.h"
#include "penaltyshootoutstate.h"
#include "matchabortedstate.h"
#include "matchfinishedstate.h"
#include "videomenustate.h"
#include "const.h"

Player *GameEngine::s_lastTouch=0;

void GameEngine::setLastTouch(Player *player)
{
	s_lastTouch = player;
}

Player *GameEngine::lastPlayerTouch()
{
	return s_lastTouch;
}

Team *GameEngine::lastTeamTouch()
{
	if(s_lastTouch == 0) return 0;
	return s_lastTouch->team();
}

Team *GameEngine::otherTeam(Team *team)
{
	if(team == m_awayTeam) return m_homeTeam;
	return m_awayTeam;
}


GameEngine::GameEngine(bool fullscreen) :
	m_frameSpeed(10),
	m_fullscreen(fullscreen)
{

	// Start audio.
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
		std::cout << "Warning - audio failed to start : " << Mix_GetError() << std::endl;
		m_audioOpen = false;
	} else {
		m_audioOpen = true;
	}

	m_sounds.push_back(SoundManager::instance()->load("sound/refwhistlelong.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/refwhistleshort.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/refwhistletwice.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/refwhistleend.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/crowdcheer.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/crowdboo.wav"));
	m_sounds.push_back(SoundManager::instance()->load("sound/crowdooh.wav"));

	m_quitKey = SDLK_ESCAPE;
	
	m_resX = 800;
	m_resY = 600;

	uint sdl_flags = SDL_SWSURFACE;
	if (m_fullscreen) sdl_flags |= SDL_FULLSCREEN;
	m_screen = SDL_SetVideoMode(m_resX, m_resY, 16, sdl_flags);
	#ifdef HAVE_CONFIG_H
	SDL_WM_SetCaption(PACKAGE_STRING, NULL);
	#else
	SDL_WM_SetCaption("tuxfootball", NULL);
	#endif
	if ( m_screen == NULL ) {
		m_finished = true;
		std::cerr << "Unable to set " << m_resX << "x" << m_resY << " video: " << SDL_GetError() << std::endl;
		m_pitch = NULL;
		m_ball = NULL;
		m_homeTeam = NULL;
		m_awayTeam = NULL;
		m_renderer = NULL;
		m_nameFont = NULL;
		m_scoreFont = NULL;
	} else {
		// Load Fonts
		std::string str = "graphics/24P_Arial_NeonBlue.png";
		m_nameFont = FontManager::instance()->load(m_screen->format, str, false, true);
		str = "graphics/24P_Arial_NeonYellow.png";
		m_scoreFont = FontManager::instance()->load(m_screen->format, str, false, true);

		// Write out text to show our starting progress
		m_scoreFont->write(m_screen, _("Starting Renderer"), 10, 10);
		SDL_Flip(m_screen);
		m_renderer = new Graphics(m_screen);

		m_scoreFont->write(m_screen, _("Loading Pitch"), 10, 40);
		SDL_Flip(m_screen);
		m_pitch = new Pitch(m_renderer);

		m_scoreFont->write(m_screen, _("Loading Ball"), 10, 70);
		SDL_Flip(m_screen);
		m_ball = new Ball(m_renderer, m_pitch);

		m_scoreFont->write(m_screen, _("Loading Team 1"), 10, 100);
		SDL_Flip(m_screen);
		m_homeTeam = new Team(this, "Blue Utd.", "team1", "graphics/homeplayermarker.png", m_pitch, m_ball, true);

		m_scoreFont->write(m_screen, _("Loading Team 2"), 10, 130);
		SDL_Flip(m_screen);
		m_awayTeam = new Team(this, "Red City", "team2", "graphics/awayplayermarker.png", m_pitch, m_ball, false);
	}

	SDL_Rect r = {m_resX/2, m_resY/2, m_pitch->width()-(m_resX), m_pitch->height()-(m_resY)};
	m_camera.setBoundingRect(r);
	r.x = 0;
	r.y = 0;
	r.w = m_resX;
	r.h = m_resY;
	m_camera.setScreenRect(r);

	m_homeController = new Controller(m_homeTeam, m_awayTeam, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_LSHIFT, SDLK_LCTRL, false, m_ball, m_pitch);
	m_awayController = new Controller(m_awayTeam, m_homeTeam, SDLK_k, SDLK_j, SDLK_h, SDLK_l, SDLK_f, SDLK_g, true, m_ball, m_pitch);

	m_menu = 0;
	m_logo = 0;
	m_halfLength = 6000;

	m_displayFPS = true;
	m_framesPerSecond = 60;

	m_gameStates.push_back( new MainMenuState(*this) );
	m_gameStates.push_back( new RedefineKeysState(*this) );
	m_gameStates.push_back( new VideoMenuState(*this) );
	m_gameStates.push_back( new MatchStartState(*this) );
	m_gameStates.push_back( new NationalAnthemState(*this) );
	m_gameStates.push_back( new FirstHalfState(*this) );
	m_gameStates.push_back( new HalfTimeState(*this) );
	m_gameStates.push_back( new SecondHalfState(*this) );
	m_gameStates.push_back( new FullTimeState(*this) );
	m_gameStates.push_back( new ExtraTimeState(*this) );
	m_gameStates.push_back( new ExtraTimeFirstHalfState(*this) );
	m_gameStates.push_back( new ExtraTimeHalfTimeState(*this) );
	m_gameStates.push_back( new ExtraTimeSecondHalfState(*this) );
	m_gameStates.push_back( new PenaltyShootoutState(*this) );
	m_gameStates.push_back( new MatchAbortedState(*this) );
	m_gameStates.push_back( new MatchFinishedState(*this) );
}

GameEngine::~GameEngine()
{
	if(m_pitch) delete m_pitch;
	if(m_homeTeam) delete m_homeTeam;
	if(m_awayTeam) delete m_awayTeam;
	
	if(m_homeController) delete m_homeController;
	if(m_awayController) delete m_awayController;
	if(m_renderer) delete m_renderer;

	if(m_nameFont) FontManager::instance()->release(m_nameFont);
	if(m_scoreFont) FontManager::instance()->release(m_scoreFont);

	std::vector<Mix_Chunk *>::iterator it = m_sounds.begin();
	while(it != m_sounds.end())
	{
		if(*it) SoundManager::instance()->release((*it));
		++it;
	}
	
	// Shutdown Audio.
	Mix_CloseAudio();

	std::vector<StateBase *>::iterator itt = m_gameStates.begin();
	while(itt != m_gameStates.end()) {
		delete(*itt);
		++itt;
	}
}

void GameEngine::gameLoop()
{
	static double totalFPSTime = 0;
	m_music = 0;
	
	int nextTime = SDL_GetTicks();
	m_camera.setPosition(Point3D(m_pitch->width()/2, m_pitch->height()-m_screen->h));
	
	m_finished = false;
	setState(TitleScreen);
	initialiseMatch();
	
	do {
		int startTime = SDL_GetTicks();
		int currentTime;

		// Make sure we wait for the next frame if we are going too fast... 
		while( (currentTime = SDL_GetTicks()) < nextTime ) {
			SDL_Delay(1);
		}
	
		// And make sure we catch up if we are going too slow.
		while(nextTime < currentTime) {
			iterateEngine();
			nextTime += m_frameSpeed;
			if(timerState() == Start) {
				m_timer++;
			}
		}

		drawFrame();
		startTime = SDL_GetTicks() - startTime;
		totalFPSTime = ((totalFPSTime * 9.0) + startTime)/10.0;
		if((int)totalFPSTime != 0) {
			m_framesPerSecond = (int)(1000.0 / totalFPSTime);
		}
	} while(!finished());
	if(m_music) Mix_FreeMusic(m_music);
}

void GameEngine::iterateEngine()
{
	m_gameStates[m_currentState]->updateLoop();
	
	if((m_menu) && (m_menu->finished())) {
		delete m_menu;
		m_menu = 0;
	}

	m_homeTeam->update();
	m_awayTeam->update();
	updateKeyboard();
	m_ball->applyKick();
	m_ball->move();
	if((m_homeTeam->controlState() == Player::KickOnly) && (m_ball->velocity().length() > 0.01)) {
		setSubMode(InPlay, false);
	}

	if(m_ballPrepared) {
		if(m_ball->velocity().length() < 0.01) {
			m_ball->setPosition(m_ballPreparedPosition);
			m_ball->setVelocity(Point3D());
			m_ballPrepared = false;
		}
	}

	m_camera.update();

	if(m_gameInProgress) {
		switch(m_subMode) {
			case InPlay :				
				if(m_pitch->crossesSideLine(Segment(m_ball->lastPosition(), m_ball->position()))) {
					setBallPreparedPosition(m_pitch->lastIntersection());
					setSubMode(ThrowIn, (GameEngine::lastTeamTouch() == m_awayTeam), false, m_pitch->lastIntersection());
				} else if(m_pitch->crossesGoalLine(Segment(m_ball->lastPosition(), m_ball->position()))) {
					if(m_pitch->entersGoal(Segment(m_ball->lastPosition(), m_ball->position()))) {
						if(m_pitch->inTopHalf(m_pitch->lastIntersection()) == m_homeTeam->topHalf()) {
							++m_awayScore;
							playSound(CrowdBoo);
						} else {
							playSound(CrowdCheer);
							++m_homeScore;
						}
						setSubMode(GoalCelebration, m_pitch->inTopHalf(m_pitch->lastIntersection()) == m_awayTeam->topHalf());
					} else if (m_pitch->inTopHalf(m_pitch->lastIntersection())==GameEngine::lastTeamTouch()->topHalf()) {
						setSubMode(Corner, (GameEngine::lastTeamTouch() == m_awayTeam), m_pitch->inLeftHalf(m_pitch->lastIntersection()));
					} else {
						playSound(CrowdOoh);
						setBallPreparedPosition(m_pitch->closestGoalKick(m_pitch->lastIntersection()));
						setSubMode(GoalKick, (GameEngine::lastTeamTouch() == m_awayTeam), m_pitch->inLeftHalf(m_pitch->lastIntersection()));
					}
				}
				break;
			case Corner :
				if(m_homeTeam->ready() && m_awayTeam->ready() && (!m_ballPrepared)) {
					if((m_homeTeam->controlState() != Player::KickOnly) || (m_awayTeam->controlState() != Player::KickOnly)) {
						m_homeTeam->setControlState(Player::KickOnly);
						m_awayTeam->setControlState(Player::KickOnly);
						playSound(RefWhistleShort);
					}
				}
				break;
			case GoalKick :
				if(m_homeTeam->ready() && m_awayTeam->ready() && (!m_ballPrepared)) {
					if((m_homeTeam->controlState() != Player::KickOnly) || (m_awayTeam->controlState() != Player::KickOnly)) {
						m_homeTeam->setControlState(Player::KickOnly);
						m_awayTeam->setControlState(Player::KickOnly);
						playSound(RefWhistleShort);
					}
				}
				break;
			case KickOff :
				if(m_homeTeam->ready() && m_awayTeam->ready() && (!m_ballPrepared)) {
					if((m_homeTeam->controlState() != Player::KickOnly) || (m_awayTeam->controlState() != Player::KickOnly)) {
						m_homeTeam->setControlState(Player::KickOnly);
						m_awayTeam->setControlState(Player::KickOnly);
						playSound(RefWhistleShort);
					}
				}
				break;
			case Penalty :
				setSubMode(InPlay, false);
				break;
			case FreeKick :
				setSubMode(InPlay, false);
				break;
			case ThrowIn :
				if(m_homeTeam->ready() && m_awayTeam->ready() && (!m_ballPrepared)) {
					if((m_homeTeam->controlState() != Player::KickOnly) || (m_awayTeam->controlState() != Player::KickOnly)) {
						m_homeTeam->setControlState(Player::KickOnly);
						m_awayTeam->setControlState(Player::KickOnly);
						playSound(RefWhistleShort);
					}
				}
				break;
			case GoalCelebration :
				setSubMode(KickOff, !m_subModeHome);
				break;
		} 
	}
}

void GameEngine::drawFrame()
{
	static int x = 0;
	SDL_Rect r, s;
	x+=2;
	
	int left = (int)m_camera.position().x() - m_resX/2;
	int top = (int)m_camera.position().y() - m_resY/2;

	m_pitch->draw(left, top);

	m_renderer->update();
	m_renderer->draw(left, top);

	if(m_gameInProgress) {
		//
		// Draw Score
		//
	
		std::ostringstream str1;
		std::ostringstream str2;
	
		str1 << m_homeScore;
		str2 << m_awayScore;	
	
		int scoreWidth = m_scoreFont->getTextWidth(str1.str().c_str());
		scoreWidth = (scoreWidth < m_scoreFont->getTextWidth(str2.str().c_str())) ? scoreWidth : m_scoreFont->getTextWidth(str2.str().c_str());
		scoreWidth += 20;

		int sm = m_screen->w/2;

		m_scoreFont->write(m_screen, str1.str().c_str(), sm - scoreWidth, m_screen->h-34);
		m_scoreFont->write(m_screen, str2.str().c_str(), sm + 20, m_screen->h-34);
	
		m_nameFont->write(m_screen, m_homeTeam->name().c_str(), 
			  sm - scoreWidth - m_nameFont->getTextWidth(m_homeTeam->name().c_str())-20, m_screen->h-34);
		m_nameFont->write(m_screen, m_awayTeam->name().c_str(), 
			  sm+scoreWidth+20, m_screen->h-34);

		//
		// Draw Time
		//
		std::ostringstream str3;
		int minutes = ((2700 * m_timer)/m_halfLength)%60;
	
		if(minutes<10) {
			str3 << ((2700 * m_timer)/m_halfLength)/60 << ":0" << ((2700 * m_timer)/m_halfLength)%60;
		} else {
			str3 << ((2700 * m_timer)/m_halfLength)/60 << ":" << ((2700 * m_timer)/m_halfLength)%60;
		}
		m_scoreFont->write(m_screen, str3.str().c_str(), 10, 10);
	}

	//
	// Draw frames per second
	// 
	if(m_displayFPS) {

		std::ostringstream str4;
		str4 << "FPS : " << m_framesPerSecond;
		m_scoreFont->write(m_screen, str4.str().c_str(), m_screen->w - 10 - m_scoreFont->getTextWidth(str4.str().c_str()), 10);
	}
	

	//
	// Draw Menu
	//
	if(m_menu) m_menu->draw();
	
	if(m_logo) {
		s.x = (m_screen->w - m_logo->w) / 2;
		s.y = 50;
		r.x = 0;
		r.y = 0;
		s.w = r.w = m_logo->w;
		s.h = r.h = m_logo->h;

		
		if(SDL_BlitSurface(m_logo, &r, m_screen, &s) < 0) {
			std::cerr << "Error - could not pitch tile : " << SDL_GetError() << std::endl;
		}
	}

	SDL_Flip(m_screen);
}

bool GameEngine::finished() 
{
	return m_finished;
}


void GameEngine::setTimer(TimerState state)
{
	m_timerState = state;
	
	if(state==Restart) {
		m_timer = 0;
		m_timerState = Start;
	}
}

GameEngine::TimerState GameEngine::timerState() const
{
	return m_timerState;
}

int GameEngine::timer() const
{
	return m_timer;
}

void GameEngine::setState(GameState state)
{
	if((m_currentState >= 0) && (m_currentState < m_gameStates.size()))
	{
		m_gameStates[m_currentState]->leaveState();
	}
	m_currentState=state;
	if((m_currentState >= 0) && (m_currentState < m_gameStates.size()))
	{
		m_gameStates[m_currentState]->enterState();
	}
	
	if((m_currentState==FirstHalf) || (m_currentState==SecondHalf) ||
	   (m_currentState==ExtraTimeFirstHalf) || (m_currentState==ExtraTimeSecondHalf)) {
		m_gameInProgress = true;
	} else {
		m_gameInProgress = false;
	}

	std::cout << "New state is " << m_currentState << std::endl;
}

void GameEngine::updateKeyboard()
{	
	SDL_Event event;
	static bool quitting = false;

	while(SDL_PollEvent(&event)) {		
		if(event.type == SDL_QUIT) m_finished = 1;
	}

	Uint8 *keys = SDL_GetKeyState(NULL);
	
	m_homeController->updateController(keys);
	m_awayController->updateController(keys);

	if(m_menu) {
		m_menu->update(keys);
	}

	if(keys[m_quitKey]) {
		quitting = true;
	} else {
		if(quitting) {
			setState(TitleScreen);
			quitting = false;
		}
	}
}

void GameEngine::setSubMode(SubMode mode, bool home, bool left, const Point3D &pos)
{
	m_subMode = mode;

	switch(mode) {
		case InPlay :
			m_homeTeam->setControlState(Player::Full);
			m_awayTeam->setControlState(Player::Full);
			setTimer(Start);
			break;
		case KickOff : 
			m_homeTeam->setupKickoff(home);
			m_awayTeam->setupKickoff(!home);
			setTimer(Stop);
			setBallPreparedPosition(m_pitch->centerSpot());
			break;
		case Corner :
			m_homeTeam->setupCorner(left, home);
			m_awayTeam->setupCorner(left, !home);
			setTimer(Stop);
			setBallPreparedPosition(m_pitch->cornerSpot(left, home ? m_awayTeam->topHalf() : m_homeTeam->topHalf()));
			playSound(RefWhistleTwice);
			break;
		case ThrowIn :		
			std::cout << "Prepare throwin" << std::endl;
			m_homeTeam->setupThrowIn(pos, home);
			m_awayTeam->setupThrowIn(pos, !home);
			setTimer(Stop);
			setBallPreparedPosition(pos);
			playSound(RefWhistleTwice);
			break;
		case GoalKick :
			std::cout << "FIXME : Goal Kicks are always on the floor at present." << std::endl;
			m_homeTeam->setupGoalKick(home, left, true);
			m_awayTeam->setupGoalKick(!home, left, true);
			setTimer(Stop);
			setBallPreparedPosition(m_pitch->goalKickSpot(left, home ? m_homeTeam->topHalf() : m_awayTeam->topHalf()));
			playSound(RefWhistleTwice);
			break;			
		case GoalCelebration :
			std::cout << "No goal celebration at present, go straight to kick off." << std::endl;
			playSound(RefWhistleTwice);
			break;
		default :
			std::cout << "Warning - setSubMode called for mode as yet unwritten" << std::endl;
	}
	
	m_subModeHome = home;
}

void GameEngine::setBallPreparedPosition(Point3D pos)
{
	m_ballPrepared = true;
	m_ballPreparedPosition = pos;
}

void GameEngine::setMenu(Menu *menu)
{
	if(m_menu) {
		delete m_menu;
		m_menu = 0;
	}
	m_menu = menu;
}

void GameEngine::setLogo(std::string logoImage)
{
	clearLogo();
	m_logo = SurfaceManager::instance()->load(m_screen->format, logoImage, false, true);
}

void GameEngine::clearLogo()
{
	if(m_logo) {
		SurfaceManager::instance()->release(m_logo);
		m_logo = 0;
	}
}

void GameEngine::setMusic(std::string musicFile)
{
	if(m_music) {
		Mix_FreeMusic(m_music);
		m_music = 0;
	}
	if(m_audioOpen) {
		int data_dirs = sizeof(data_dir)/sizeof(std::string);
		for (int i = 0; i < data_dirs; i++) {
			std::string filename = std::string(data_dir[i]);
			filename.append("/");
			filename.append(musicFile.c_str());
			m_music = Mix_LoadMUS(filename.c_str());
			if (m_music) break;
		}

		if(m_music == 0) {
			std::cout << "Warning - could not load Title music : " << Mix_GetError() << std::endl;
		} else {
			Mix_PlayMusic(m_music, -1);
		}
	}
}

void GameEngine::setCameraFollows(CameraFollows follows)
{
	switch(follows)
	{
	case CameraPattern :
		m_camera.setTarget(0);
		break;
	case CameraBall :
		m_camera.setTarget(m_ball);
		break;
	default :
		m_camera.setTarget(0);
	}
}

void GameEngine::initialiseMatch()
{
	m_ball->setPosition(m_pitch->centerSpot());
	m_ball->setVelocity(Point3D());
	m_camera.setDestination(Point3D(512, 1024));
	m_ballPrepared = false;
	setSubMode(InPlay, false);
	setTimer(Restart);
	setTimer(Stop);
	m_homeScore = 0;
	m_awayScore = 0;
}

Player *GameEngine::addPlayer(std::string skin, std::string playerMarker, Team *team, bool goalkeeper)
{
	Player *p = new Player(m_renderer, skin, playerMarker, m_pitch, team, m_ball, goalkeeper);

	m_playerList.push_back(PlayerContainer(p));
	
	return p;
}

void GameEngine::setHalfLength(uint halfLength)
{
	m_halfLength = halfLength;
	std::cout << "Half Length : " << m_halfLength;
}

uint GameEngine::halfLength() const
{
	return m_halfLength;
}

void GameEngine::setupHalfTime()
{
	m_homeTeam->setupHalfTime();
	m_awayTeam->setupHalfTime();
}

Menu *GameEngine::menu()
{
	return m_menu;
}

bool GameEngine::finished() const
{
	return m_finished;
}

void GameEngine::setFinished(bool finished)
{
	m_finished = finished;
}

Controller *GameEngine::controller(ControllerType controller)
{
	switch(controller) {
	case HomeController :
		return m_homeController;
	case AwayController :
		return m_awayController;
	}
	
	return 0;
}

SDL_Surface *GameEngine::screen()
{
	return m_screen;
}

Team *GameEngine::team(TeamTypes team)
{
	switch(team) {
	case HomeTeam :
		return m_homeTeam;
	case AwayTeam :
		return m_awayTeam;
	}
	return 0;
}

Mix_Chunk *GameEngine::gameSound(GameSounds sound)
{
	Mix_Chunk *result = 0;
	if((sound>=0) && (sound<= m_sounds.size())) {
		result = m_sounds[sound];
	}
	return result;
}

void GameEngine::playSound(GameSounds sound)
{
	if((sound>=0) && (sound<= m_sounds.size())) {
		if(m_sounds[sound]) {
			Mix_PlayChannel(-1, m_sounds[sound], 0);
		}
	}
}

uint GameEngine::score(TeamTypes team) const
{
	uint result = 0;
	switch(team)
	{
	case HomeTeam :
		result = m_homeScore;
	case AwayTeam :
		result = m_awayScore;
	}
	return result;
}

void GameEngine::setFullScreen(bool fullscreen)
{
	bool old = m_fullscreen;
	m_fullscreen = fullscreen;
	if (old != m_fullscreen)
	SDL_WM_ToggleFullScreen(m_screen);
}

bool GameEngine::fullScreen() const
{
	return m_fullscreen;
}
