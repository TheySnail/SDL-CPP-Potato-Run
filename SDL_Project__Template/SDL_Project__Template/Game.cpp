#include "Game.h"

#include <vector>

#include <SDL_ttf.h>
#include <SDL_mixer.h>

Game::Game()
{
	Initalise();
}

Game::~Game()
{

}

//vector functions
void CreateVectOfObstacles(SDL_Renderer* _renderer, std::vector<Obstacle*>& _ObstacleVect, int _speed)
{
	int xBuffer = 1280;//the positions they spawn in at, adjust for distance between

	/*Obstacle* obstacle= new Obstacle(false, _renderer, "Sprites/TempPlayer.bmp", 1280, 525, 100, 200, 1);*/

	for (int i = 0; i <3; i++)
	{
		Obstacle* obstacle = new Obstacle(false, false,_renderer, "Sprites/fork.bmp", 1280, 525, 100, 200, 1);

		_ObstacleVect.push_back(obstacle);//pushes copy of object into the back of the vector

		_ObstacleVect[i]->RepopulateObject(false, false, 1280 + (600 * i) + rand()%300, 525, 100, 200, _speed);

	}
}

void MoveVectObstacle(std::vector<Obstacle*> &_ObstacleVect)
{
	for (int i = 0; i < 3; i++)
	{
		_ObstacleVect[i]->ObjectScrollLeft();
		_ObstacleVect[i]->DrawObjectToScreen();
	}
}

SDL_Texture* RuleTxt(SDL_Renderer* _renderer,std::string _txt,TTF_Font* _font )
{
	SDL_Surface* text;

	SDL_Color colour = { 0,0,0 };//font colour

	text = TTF_RenderText_Solid(_font, _txt.c_str(), colour);

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	SDL_FreeSurface(text);

	return text_texture;
}

SDL_Rect QueryText(SDL_Texture* _tex, SDL_Rect _location)
{
	SDL_QueryTexture(_tex, 0, 0, &_location.w, &_location.h);
	_location.x = (1280 / 2) - (_location.w / 2); //x coordinate is the middle of the screen minus the middle of the text so its always in the middle
	return _location;
}

int Game::Initalise()
{
	// try initialising SDL, log error and pause if fail
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << "\n";
		system("pause");
		return -1;
	}

	// try to create the window, log error and pause if fail
	window = SDL_CreateWindow("Potato Run", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if (window == NULL)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		system("pause");
		return -2;
	}

	// try to create the renderer, log error and pause if fail
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return -3;
	}



	TTF_Init();


	//font
	TTF_Font* font{ nullptr };
	font = TTF_OpenFont("CuteDino.ttf", 48);//init font
	if (!font)
	{
		std::cout << "Failure opening font : " << TTF_GetError() << std::endl;
	}

	bool MenuLoop = true; //menu control variable

	int Highscore = 0;
	
	GameObject* MenuBackground = new GameObject(renderer, "Sprites/backgroundall.bmp", 0, 0, 1280, 720);

	Button* StartButton = new Button(false, false,renderer, "Sprites/PlayButton.bmp", 570, 250, 150, 75);
	Button* QuitButton = new Button(false, false, renderer, "Sprites/QuitButton.bmp", 570, 550, 150, 75);
	Button* RuleButton = new Button(false, false, renderer, "Sprites/RulesButton.bmp", 570, 400, 150, 75);
	Button* BackButton = new Button(false, false, renderer, "Sprites/BackButton.bmp", 570, 475, 150, 75);

	SDL_Event MouseMove;

	//rule text 
	SDL_Texture* rule = RuleTxt(renderer, "Rules:", font);
	SDL_Rect dest = { 0,20,0,0 };
	dest = QueryText(rule, dest);

	SDL_Texture* line1 = RuleTxt(renderer, "In this game you are a potato ", font);
	SDL_Rect line1Dest = { 0,0,0,0 };
	line1Dest = QueryText(line1, line1Dest);
	line1Dest.y = 200;

	SDL_Texture* line2 = RuleTxt(renderer, "You need to jump over forks and avoid the seagulls.", font);
	SDL_Rect line2Dest = { 0,0,0,0 };
	line2Dest = QueryText(line2, line2Dest);
	line2Dest.y = 250;

	SDL_Texture* line3 = RuleTxt(renderer, "As you gain more score ", font);
	SDL_Rect line3Dest = { 0,0,0,0 };
	line3Dest = QueryText(line3, line3Dest);
	line3Dest.y = 300;

	SDL_Texture* line4 = RuleTxt(renderer, "the game will speed up getting harder. ", font);
	SDL_Rect line4Dest = { 0,0,0,0 };
	line4Dest = QueryText(line4, line4Dest);
	line4Dest.y = 350;

	SDL_Texture* line5 = RuleTxt(renderer, "Try and beat your high score, and have fun.", font);
	SDL_Rect line5Dest = { 0,0,0,0 };
	line5Dest = QueryText(line5, line5Dest);
	line5Dest.y = 400;

	GameObject* ruleBackground = new GameObject(renderer, "Sprites/rulebackground.bmp", 25, 175, 1230, 300);

	GameObject* RuleTitleBackground = new GameObject(renderer, "Sprites/rulebackground.bmp", 565, 10, 155, 70);

	while (MenuLoop)
	{
		
		while (SDL_PollEvent(&MouseMove) == true)
		{
			StartButton->MouseHandling(&MouseMove, "Sprites/PlayButton.bmp", "Sprites/PlayButtonHover.bmp");
			QuitButton->MouseHandling(&MouseMove, "Sprites/QuitButton.bmp", "Sprites/QuitButtonHover.bmp");
			RuleButton->MouseHandling(&MouseMove, "Sprites/RulesButton.bmp", "Sprites/RulesButtonHover.bmp");
		}
		SDL_RenderClear(renderer);

		//draws background
		MenuBackground->SpriteDrawToScreen();

		//draws buttons
		StartButton->SpriteDrawToScreen();
		QuitButton->SpriteDrawToScreen();
		RuleButton->SpriteDrawToScreen();

		SDL_RenderPresent(renderer);

		if (StartButton->GetState() == true)
		{
			GameLoop(renderer,font, Highscore);//runs gameloop
			StartButton->SetState(false);
		}


		while (RuleButton->GetState() == true)//rule menu treated as a menu in the menu
		{
			while (SDL_PollEvent(&MouseMove) == true)
			{
				BackButton->MouseHandling(&MouseMove, "Sprites/BackButton.bmp", "Sprites/BackButtonHover.bmp");
			}
			SDL_RenderClear(renderer);

			//draws menu and back button
			MenuBackground->SpriteDrawToScreen();
			BackButton->SpriteDrawToScreen();
			//draws border box to make it easier to read
			ruleBackground->SpriteDrawToScreen();
			RuleTitleBackground->SpriteDrawToScreen();

			//draws text
			SDL_RenderCopy(renderer, rule, 0, &dest);
			SDL_RenderCopy(renderer, line1, 0, &line1Dest);
			SDL_RenderCopy(renderer, line2, 0, &line2Dest);
			SDL_RenderCopy(renderer, line3, 0, &line3Dest);
			SDL_RenderCopy(renderer, line4, 0, &line4Dest);
			SDL_RenderCopy(renderer, line5, 0, &line5Dest);

			if (BackButton->GetState() == true)//if backbutton pressed break loop and return to normal menu
			{
				RuleButton->SetState(false);
				BackButton->SetState(false);
			}
			SDL_RenderPresent(renderer);
		}

		if (QuitButton->GetState() == true)
		{
			MenuLoop = false;
		}



	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_Quit();
	SDL_Quit();
	
	return 0;
}


//initialization and loop
int Game::GameLoop(SDL_Renderer* renderer, TTF_Font* _font, int &_HighScore)
{
	FrameRateCount = 0;
	int jumpStartFrame = -1;
	int fallStartFrame = -1;

	int fallTime = 25;
	int jumpTime = 25;

	//used for tracking what sprite the game should display the player as
	int SpriteCount = 1;

	int speed = 6; //speed of background and obstacles

	int score = 0;

	//creates background
	SpriteScroll* BackGroundFloor = new SpriteScroll (renderer, "Sprites/backgroundfloor.bmp",0,590,1280, 130,speed);
	SpriteScroll* BackGroundSky = new SpriteScroll(renderer, "Sprites/backgroundall.bmp",0,0, 1280, 720, 3);

	player* Player = new player(false,renderer, "Sprites/TempPlayer.bmp", 150, 525, 100, 100);

	//game over screen
	GameObject* HighScoreBackGround = new GameObject(renderer, "Sprites/rulebackground.bmp", 440, 290, 400, 170);
	GameObject* NoHighScoreBackGround = new GameObject(renderer, "Sprites/rulebackground.bmp", 370, 290, 540, 170);

	std::vector<Obstacle*> ObstacleVect;//creats obstacle vector
	ObstacleVect.reserve(10);//reserves space in the obstacle vector to ensure that nothing gets overwritten

	CreateVectOfObstacles(renderer, ObstacleVect,speed);



	//text for highscore screen
	SDL_Texture* HighScoreText = RuleTxt(renderer, "New High Score!", _font);
	SDL_Rect highScoreTxtDest = { 0,0,0,0 };
	highScoreTxtDest = QueryText(HighScoreText, highScoreTxtDest);
	highScoreTxtDest.y = 300;

	//text for highscore screen no new high score
	SDL_Texture* NoHighScoreText = RuleTxt(renderer, "Better Luck Next Time", _font);
	SDL_Rect NohighScoreTxtDest = { 0,0,0,0 };
	NohighScoreTxtDest = QueryText(NoHighScoreText, NohighScoreTxtDest);
	NohighScoreTxtDest.y = 300;

	SDL_Texture* failHighScoreisText = RuleTxt(renderer, "HighScore is:", _font);
	SDL_Rect failHighScoreisTextdest = { 0,0,0,0 };
	failHighScoreisTextdest = QueryText(failHighScoreisText, failHighScoreisTextdest);
	failHighScoreisTextdest.y = 350;

	//score
	std::vector <SDL_Texture*> TxtVector;

	initScoreTxt(renderer, TxtVector);

	//creates sound effect
	Sound ScoreIncrease;
	ScoreIncrease.LoadSound("Sound/ScoreIncrease.mp3");

	Sound JumpSound;
	JumpSound.LoadSound("Sound/JumpSound.mp3");

	Sound DeathSound;
	DeathSound.LoadSound("Sound/DeathSound.mp3");

	//music
	Mix_Music* BackgroundMusic = Mix_LoadMUS("Sound/BackgroundMusic.mp3");
	Mix_PlayMusic(BackgroundMusic, -1);

	Mix_VolumeMusic(32);//makes background music queiter

	bool ExitFlag = false;
	SDL_Event GameEvent;

	//game loop
	while (ExitFlag == false)
	{

		int current = SDL_GetTicks();//what current tick is it on


		while (SDL_PollEvent(&GameEvent))//polls the game even to check to see what the state is
		{
			if (GameEvent.type == SDL_QUIT)//if the event type is quit
			{
				ExitFlag = true;//stop game loop
			}

			if (GameEvent.type == SDL_KEYDOWN)//if event was a button press
			{
				switch (GameEvent.key.keysym.scancode)
				{
				case 44://scancode for space
					if (Player->getIsJumping() == false)
					{
						jumpStartFrame = FrameRateCount;//starts jump frames
						Player->setIsJumping(true);
						JumpSound.PlaySound();//plays jumping noise
					}
					break;

				default:
					break;
				}

			}
		}

		SDL_RenderClear(renderer);//first thing loop does is clear old screen


		//jumping 
		if (Player->getIsJumping())
		{
			if (FrameRateCount < jumpStartFrame + jumpTime && FrameRateCount > 25)//plus 15 is how long the jump should last for and the FrameRateCount > 15 just makes it so you cant jump immeaditly
			{
				Player->PlayerJump();
			}

			if (FrameRateCount == jumpStartFrame + 25)//when reaches apex of jump
			{
				fallStartFrame = FrameRateCount;//get the frame the character should start falling
			}

			if (FrameRateCount < fallStartFrame + fallTime && FrameRateCount > 30)//fall until the framerate is reaches the planned time
			{
				Player->PlayerFall();
			}

			if (FrameRateCount == fallStartFrame + fallTime)//the frame the jump ends the player can jump again
			{
				Player->setIsJumping(false);
			}
		}



		//moves background
		//sky
		BackGroundSky->ScrollLeft();
		BackGroundSky->DrawScrollToScreen();

		//floor like this so the floor can  be going same speed as the obstacles
		BackGroundFloor->ScrollLeft();
		BackGroundFloor->DrawScrollToScreen();



		//draws player to the screen
		if (FrameRateCount % 10 == 0)//every 10 frames
		{
			SpriteCount++;
			Player->UpdateSprite(SpriteCount);

			if (SpriteCount == 8)//needs to be withing 1 to 8 as sprite rotates 45 degrees per 10 frames 360/8 = 45
			{
				SpriteCount = 0;
			}
		}

		Player->SpriteDrawToScreen();


		if (ObstacleVect[0]->getOffScreen() == true)//the first one in the vector is always going to be the one about to go off screen
		{
			int flyControl = rand() % 4;

			if (flyControl != 0)// 3/4 of the time the obstacle will not be flying
			{
		//												gets position of last object adds a fixed buffer and a random buffer also random height 
				ObstacleVect[0]->RepopulateObject(false, false, ObstacleVect.back()->GetX() + 900+ (rand()%500), 520- (rand()%50), 100, 200, speed);//reuses the same object with different elements
				ObstacleVect[0]->UpdateSprite();//updates the sprite to the correct sprite
			}
			
			else // 1/4 it will be a flying obstacle
			{
				ObstacleVect[0]->RepopulateObject(false, true, ObstacleVect.back()->GetX() + 900 + (rand() % 500), 300, 200, 75, speed);
				ObstacleVect[0]->UpdateSprite();
			}
			
			ObstacleVect.push_back(ObstacleVect[0]);//creates copy of first object with new member values and sends it to the back of the vector

			ObstacleVect.erase(ObstacleVect.begin());//destroys the old 
		}
		
		if (Player->AaBbCollision(ObstacleVect) == true)
		{

			DeathSound.PlaySound();//plays death sound
			Player->UpdateImage("Sprites/potaodead.bmp");//updates to dead sprite
			Player->SpriteDrawToScreen();
			if (score > _HighScore)
			{
				_HighScore = score;
				
				std::vector <SDL_Texture*> highScoreVect;

				initScoreTxt(renderer, highScoreVect);//creates the vector of numbers used to show the high score
				HighScoreBackGround->SpriteDrawToScreen();
				SDL_RenderCopy(renderer, HighScoreText, 0, &highScoreTxtDest);//shows text for high score
				displayHighScore(renderer, highScoreVect, _HighScore,575,400);
			}

			else
			{
				std::vector <SDL_Texture*> highScoreVect;

				initScoreTxt(renderer, highScoreVect);//creates the vector of numbers used to show the high score
				NoHighScoreBackGround->SpriteDrawToScreen();
				SDL_RenderCopy(renderer, NoHighScoreText, 0, &NohighScoreTxtDest);//better luck next time text
				SDL_RenderCopy(renderer, failHighScoreisText, 0, &failHighScoreisTextdest);//highscore is text
				displayHighScore(renderer, highScoreVect, _HighScore, 575, 400);//shows teh high score
			}

			ExitFlag = true;//leave game loop
		}

		//obstacles
		MoveVectObstacle(ObstacleVect);
		
		displayScore(renderer, TxtVector, score);//calls score function

		SDL_RenderPresent(renderer);//last thing loop does is present new screen

		
		if (FrameRateCount % 2 == 0)//every 2 frames increase score
		{
			score++;
		}

		if (score % 100 == 0)//plays score increase sound every 100 score
		{
			ScoreIncrease.PlaySound();
		}

		if (score % 400 == 0)//every 400 score
		{
			speed++;
			for (int i = 0; i < ObstacleVect.size(); i++)
			{
				ObstacleVect[i]->increaseSpeed(speed);//updates the speed of obstacles when it changes
			}
			BackGroundFloor->UpdateSpeed(speed);
		}
		

		//framerate control

		int end = SDL_GetTicks();// the ticks it is at end of the frame

		float DelayAmount = 16.666f - (end - current);//how much time the frame took to compute

		if (DelayAmount > 1)//if the frame took more than 1 frame to compute it delays
		{
			SDL_Delay(int(DelayAmount));
		}

		FrameRateCount++;// adds one to the framerate count after every frame
	}

	SDL_Delay(4000);//wait

	/*delete Player;

	delete BackGroundFloor;
	delete BackGroundSky;

	for (int i = 0; i < ObstacleVect.size(); i++)
	{
		delete ObstacleVect[i];
	}

	for (int i = 0; i < TxtVector.size(); i++)
	{
		delete TxtVector[i];
	}*/


	/*Mix_FreeMusic();*/

	return 0;
}

