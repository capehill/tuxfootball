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

#ifndef TUXFOOTBALL_GAMEENGINE
#define TUXFOOTBALL_GAMEENGINE

#include "SDL.h"
#include "SDL_mixer.h"

#include "ball.h"
#include "pitch.h"
#include "team.h"
#include "camera.h"
#include "graphics.h"

#include <string>
#include <sstream>
#include <list>
#include <vector>

class Player;
class Menu;
class Controller;
class StateBase;

class GameEngine {
public:
	enum CameraFollows { CameraPattern, CameraBall };
	
	enum GameState {	TitleScreen=0,
				RedefineKeysScreen,
				VideoSettingsMenu,
				MatchStart,
				NationalAnthem,
				FirstHalf,
				HalfTime,
				SecondHalf,
				FullTime,
				ExtraTimeStart,
				ExtraTimeFirstHalf,
				ExtraTimeHalfTime,
				ExtraTimeSecondHalf,
				PenaltyShootout,
				MatchAborted,
				Finished};
				
	enum ControllerType {	HomeController,
				AwayController };

	enum TimerState {	Stop,
				Start,
				Restart};

	enum TeamTypes {	HomeTeam,
				AwayTeam };
				
	enum SubMode {		InPlay,
				Corner,
				GoalKick,
				KickOff,
				Penalty,
				FreeKick,
				ThrowIn,
				GoalCelebration};

	enum GameSounds {	RefWhistleLong = 0,
				RefWhistleShort,
				RefWhistleTwice,
				RefWhistleEnd,
				CrowdCheer,
				CrowdBoo,
				CrowdOoh };	
	
	GameEngine(bool fullscreen);
	~GameEngine();
	void gameLoop();
	static void setLastTouch(Player *player);
	Player *addPlayer(std::string skin, std::string playerMarker, Team *team, bool goalkeeper);
	
	static Player *lastPlayerTouch();
	static Team *lastTeamTouch();
	void setHalfLength(uint halfLength);
	uint halfLength() const;
	
	void setCameraFollows(CameraFollows follows);
	
	void setMenu(Menu *menu);
	Menu *menu();

	void setFinished(bool finished);
	bool finished() const;
	
	void setLogo(std::string logoImage);

	SDL_Surface *screen();

	/** clears the logo, if one exists. It is safe to call this when no logo exists. */
	void clearLogo();
	
	void setMusic(std::string musicFile);
	void setupHalfTime();

	void setState(GameState state);

	void setSubMode(SubMode mode, bool home, bool left=false, const Point3D &pos=Point3D());
	
	void setTimer(TimerState state);
	TimerState timerState() const;
	int timer() const;

	Team *team(TeamTypes team);
	uint score(TeamTypes team) const;

	Mix_Chunk *gameSound(GameSounds sound);
	void playSound(GameSounds sound);
	
	/** Returns the specified controller */
	Controller *controller(ControllerType controller);
	
	void initialiseMatch();

	void setFullScreen(bool fullscreen);
	bool fullScreen() const;
private: // attributes
	static Player *s_lastTouch;
	
	std::vector<StateBase *> m_gameStates;

	GameState m_currentState;
	SubMode m_subMode;
	bool m_subModeHome;
	/** True if we are playing a match, rather than in half time, or penalty shootout.
	 *  If this is true, we take account of corners and submodes. */
	bool m_gameInProgress;	
	/** Used for timings such as referee whistle, half length, etc.*/
	int m_timer;
	TimerState m_timerState;
	int m_frameSpeed;
	bool m_finished;
	SDL_Surface *m_screen;
	Pitch *m_pitch;
	Team *m_homeTeam;
	Team *m_awayTeam;
	Ball *m_ball;
	int m_homeScore;
	int m_awayScore;
	uint m_halfLength;

	SDL_Surface *m_nameFont;
	SDL_Surface *m_scoreFont;
	
	Camera m_camera;

	int m_resX;
	int m_resY;

	Controller *m_homeController;
	Controller *m_awayController;
	SDLKey m_quitKey;
	Graphics *m_renderer;
	bool m_ballPrepared;
	Point3D m_ballPreparedPosition;

	// Sound Effects
	std::vector<Mix_Chunk *> m_sounds;

	Mix_Music *m_music;

	std::list<PlayerContainer> m_playerList;
	
	Menu *m_menu;
	SDL_Surface *m_logo;

	/** Returns the team other than the one specified. E.g. if you pass it the home team, it returns the away team */
	Team *otherTeam(Team *team);

	/** Determines whether or not we display the Frames Per Second */
	bool m_displayFPS;
	int m_framesPerSecond;
	// True if audio has been successfully open
	bool m_audioOpen;

	// true if we are in fullscreen mode;
	bool m_fullscreen;
private: // methods
	void iterateEngine();
	void drawFrame();
	bool finished();
	void updateKeyboard();	
	void setBallPreparedPosition(Point3D pos);
};

#endif /* TUXFOOTBALL_GAMEENGINE */
