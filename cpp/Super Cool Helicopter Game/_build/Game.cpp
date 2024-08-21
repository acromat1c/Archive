#include <raylib.h>
#include <math.h>
#include <fstream>

//Controlls
KeyboardKey Mod = KEY_LEFT_ALT;

KeyboardKey FullScreen = KEY_ENTER; // + Mod
KeyboardKey QuickExit = KEY_F12;

KeyboardKey MoveUp = KEY_W;
KeyboardKey MoveLeft = KEY_A;
KeyboardKey MoveDown = KEY_S;
KeyboardKey MoveRight = KEY_D;
MouseButton Fire1 = MOUSE_BUTTON_LEFT;
MouseButton Fire2 = MOUSE_BUTTON_RIGHT;
KeyboardKey Track = KEY_T;
KeyboardKey PauseGame = KEY_ESCAPE;

KeyboardKey GameShowHidden = KEY_P;

KeyboardKey ShowFramerate = KEY_U;
KeyboardKey MuteMusic = KEY_M;

// Developer Tools
KeyboardKey ToggleSpawn = KEY_I;
KeyboardKey GameOverTrigger = KEY_G; // + Mod

KeyboardKey EditorEnter = KEY_E; // + Mod      in settings

// in editor
KeyboardKey EditorCameraMove = KEY_TAB; MouseButton EditorCameraMoveMouse = MOUSE_BUTTON_MIDDLE;
KeyboardKey EditorCameraReset = KEY_R; // + Mod
KeyboardKey EditorSaveMap = KEY_S;

KeyboardKey EditorBrushSizeUp = KEY_Q;
KeyboardKey EditorBrushSizeDown = KEY_A;
KeyboardKey EditorGrid = KEY_G;
KeyboardKey EditorPreview = KEY_W;
KeyboardKey EditorShowPlayer = KEY_P;
KeyboardKey EditorShowHidden = KEY_V;

MouseButton EditorPlaceTile = MOUSE_BUTTON_RIGHT;
MouseButton EditorPlaceObject = MOUSE_BUTTON_LEFT;

KeyboardKey EditorDelete = KEY_Z;
KeyboardKey EditorCollision = KEY_C;
KeyboardKey EditorBulletCollision = KEY_K;
KeyboardKey EditorDrawObject = KEY_D;
KeyboardKey EditorDamage = KEY_Y;
KeyboardKey EditorEnemyCollision = KEY_U;
KeyboardKey EditorFreeze = KEY_F;
KeyboardKey EditorGlobal = KEY_T;
KeyboardKey EditorBlade = KEY_B;
KeyboardKey EditorPlayerRespawn = KEY_L; // + Mod
KeyboardKey EditorPlayerRespawnToggle = KEY_N; // + Mod
KeyboardKey EditorEnemyRespawn = KEY_L;
KeyboardKey EditorEnemyRespawnToggle = KEY_N;
KeyboardKey EditorReset = KEY_R;
KeyboardKey EditorRotateRight = KEY_O;
KeyboardKey EditorRotateLeft = KEY_I;
KeyboardKey EditorBoxLeft = KEY_LEFT;
KeyboardKey EditorBoxRight = KEY_RIGHT;
KeyboardKey EditorBoxDown = KEY_DOWN;
KeyboardKey EditorBoxUp = KEY_UP;

KeyboardKey EditorSelect1 = KEY_ONE; // + Mod for diferent effect
KeyboardKey EditorSelect2 = KEY_TWO; // + Mod for diferent effect
KeyboardKey EditorSelect3 = KEY_THREE; // + Mod for diferent effect
KeyboardKey EditorSelect4 = KEY_FOUR; // + Mod for diferent effect
KeyboardKey EditorSelect5 = KEY_FIVE; // + Mod for diferent effect
KeyboardKey EditorSelect6 = KEY_SIX; // + Mod for diferent effect
KeyboardKey EditorSelect7 = KEY_SEVEN; // + Mod for diferent effect
KeyboardKey EditorSelect8 = KEY_EIGHT; // + Mod for diferent effect
KeyboardKey EditorSelect9 = KEY_NINE; // + Mod for diferent effect
KeyboardKey EditorSelect0 = KEY_ZERO; // + Mod for diferent effect

bool CanUseEditor = true;

enum GameStateEnum { Play, Pause, LevelEditor, Start, GameOver };
GameStateEnum GameState = Start;

enum SelectedObjectEnum {TestHouse, Building, PlayerRespawn, EnemyRespawn, MapTemplate, P1, P2, P3, P4, P5,
						PlusHealth, PlusSpeed, PlusDamage, PlusBulletSpeed,PlusSteal, PlayerRespawnToggle, EnemyRespawnToggle,
						Desert, Grass, Water, Brick, Tree, Stone, Box, Blade, Delete, Freeze, Global, RotateRight, RotateLeft,
						BulletCollison, Collison, EnemyCollision, DrawObject, Damage};
SelectedObjectEnum SelectedObject;


float Objects[256][8];

float AnimationTimer = 0;
int MapTiles[512][512];
int TexturesLoaded = 0, SoundsLoaded = 0;
int WorldSize = 256 * 640;
const int NumberOfObjects = 1000;
float SavedTimer = 1.5, StartTimer = 0;
float CursorX, CursorY, EditorCursorX = 0, EditorCursorY = 0;
float BrushSize = 1, BoxWidth = 100, BoxHeight = 100;
int Kills;
float SoundLevel, MusicLevel;
Vector2 CursorWorld, CursorScreen, CursorDelta;
bool FilesLoaded = false, CursorTrack = false, ShowFPS = false, SnapToGrid = false, ShowHidden = true, 
Preview = false, ShowPlayer = true, Mute = false;
bool Desktop = false;
bool CursorReset = false;
Texture Textures[100];
Sound Sounds[100];
Camera2D GameCamera;



struct Files
{
	std::fstream Save, MapFile;

	float MapObjects[NumberOfObjects][16];

	void OpenMapFile()
	{
		MapFile.open("resources/Files/Map.txt");

		for (int i = 0; i < 511; i++)
		{
			for (int j = 0; j < 511; j++)
			{
				MapFile >> MapTiles[i][j];
			}
		}

		for (int i = 0; i < NumberOfObjects; i++)
		{
			MapFile >> MapObjects[i][0];// Freeze
			MapFile >> MapObjects[i][1]; // X
			MapFile >> MapObjects[i][2]; // Y
			MapFile >> MapObjects[i][3]; // Object
			MapFile >> MapObjects[i][4]; // Collision
			MapFile >> MapObjects[i][5]; // Draw
			MapFile >> MapObjects[i][6]; // Damage
			MapFile >> MapObjects[i][7]; // Damage number
			MapFile >> MapObjects[i][8]; // Bullet collision
			MapFile >> MapObjects[i][9]; // Box width
			MapFile >> MapObjects[i][10];// Box height
			MapFile >> MapObjects[i][11];// Enemy collision
			MapFile >> MapObjects[i][12];// Render Globaly
			MapFile >> MapObjects[i][13];// Rotate
			MapFile >> MapObjects[i][14];// Angle
			MapFile >> MapObjects[i][15];// Power up or Enemy Respawn
		}
		MapFile.close();
	}

	void SaveMapFile()
	{
		MapFile.open("resources/Files/Map.txt");

		for (int i = 0; i < 511; i++)
		{
			for (int j = 0; j < 511; j++)
			{
				MapFile << MapTiles[i][j] << std::endl;
			}
		}

		for (int i = 0; i < NumberOfObjects; i++)
		{
			MapFile << MapObjects[i][0] << std::endl;
			MapFile << MapObjects[i][1] << std::endl;
			MapFile << MapObjects[i][2] << std::endl;
			MapFile << MapObjects[i][3] << std::endl;
			MapFile << MapObjects[i][4] << std::endl;
			MapFile << MapObjects[i][5] << std::endl;
			MapFile << MapObjects[i][6] << std::endl;
			MapFile << MapObjects[i][7] << std::endl;
			MapFile << MapObjects[i][8] << std::endl;
			MapFile << MapObjects[i][9] << std::endl;
			MapFile << MapObjects[i][10] << std::endl;
			MapFile << MapObjects[i][11] << std::endl;
			MapFile << MapObjects[i][12] << std::endl;
			MapFile << MapObjects[i][13] << std::endl;
			MapFile << MapObjects[i][14] << std::endl;
			MapFile << MapObjects[i][15] << std::endl;
		}
		MapFile.close();
	}
};
Files ObjectFile;


struct OptionsScreen
{
	float Time;

	bool IsFullscreen;

	std::fstream OptionsFile;

	float CursorX, CursorY;

	void OpenOptionsFile()
	{
		OptionsFile.open("resources/Files/Settings.txt");
		OptionsFile >> SoundLevel;
		OptionsFile >> MusicLevel;
		OptionsFile >> IsFullscreen;
		OptionsFile.close();

		SoundLevel /= 100;
		MusicLevel /= 100;

		if (SoundLevel > 1)
		{
			SoundLevel = 0.5;
		}

		if (MusicLevel > 1)
		{
			MusicLevel = 0.5;
		}

		if (IsFullscreen)
		{
			ToggleFullscreen();
		}
	}

	void CloseOptionsFile()
	{
		SoundLevel *= 100;
		MusicLevel *= 100;

		OptionsFile.open("resources/Files/Settings.txt");
		OptionsFile << SoundLevel << std::endl;
		OptionsFile << MusicLevel << std::endl;
		OptionsFile << IsFullscreen << std::endl;
		OptionsFile.close();
	}

	void Controlls()
	{
		CursorX = GetMouseX();
		CursorY = GetMouseY();
	}

	void Logic()
	{
		if (CheckCollisionCircleRec(Vector2{CursorX, CursorY}, 1, 
			Rectangle{(float) GetScreenWidth() / 2 - 150, 200, 300, 100}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			GameState = Play;
		}

		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1, 
			Rectangle{ (float)GetScreenWidth() / 2 - 150, 350, 300, 50 }) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			SoundLevel = (CursorX - (GetScreenWidth() / 2 - 150)) / 300;

			if (SoundLevel > 1)
			{
				SoundLevel = 1;
			}
			else if (SoundLevel < 0)
			{
				SoundLevel = 0;
			}

			SetSoundVolume(Sounds[1], 0.6 * SoundLevel);
			SetSoundVolume(Sounds[2], 0.75 * SoundLevel);
			SetSoundVolume(Sounds[3], 1 * SoundLevel);
			SetSoundVolume(Sounds[4], 0.5 * SoundLevel);
		}

		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1, 
			Rectangle{ (float)GetScreenWidth() / 2 - 150, 450, 300, 50 }) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			MusicLevel = (CursorX - (GetScreenWidth() / 2 - 150)) / 300;

			if (MusicLevel > 1)
			{
				MusicLevel = 1;
			}
			else if (MusicLevel < 0)
			{
				MusicLevel = 0;
			}

			SetSoundVolume(Sounds[5], 0.75 * MusicLevel);
		}

		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1, 
			Rectangle{ (float)GetScreenWidth() / 2 - 150, 550, 300, 100 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ToggleFullscreen();
		}

		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1, 
			Rectangle{ (float)GetScreenWidth() / 2 - 150, 700, 300, 100 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			GameState = Start;

			CloseOptionsFile();
		}
	}

	void Draw()
	{
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
		
		for (int i = 10; i < GetScreenHeight(); i += 20)
		{	
			DrawRectangle(0, i, GetScreenWidth(), 10, DARKGREEN);
		}

		DrawRectangle(GetScreenWidth() / 2 - 150, 200, 300, 100, DARKGREEN);
		DrawText("Resume", GetScreenWidth() / 2 - MeasureText("Resume", 60) / 2, 230, 60, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 150, 350, 300, 50, DARKGREEN);
		DrawRectangle(GetScreenWidth() / 2 - 150, 350, SoundLevel * 300, 50, DARKBLUE);
		DrawText("Volum", GetScreenWidth() / 2 - MeasureText("Volum", 60) / 2, 350, 60, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 150, 450, 300, 50, DARKGREEN);
		DrawRectangle(GetScreenWidth() / 2 - 150, 450, MusicLevel * 300, 50, DARKBLUE);
		DrawText("Music", GetScreenWidth() / 2 - MeasureText("Music", 60) / 2, 450, 60, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 150, 550, 300, 100, DARKGREEN);
		DrawText("Fullscreen", GetScreenWidth() / 2 - MeasureText("Fullscreen", 55) / 2, 580, 55, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 150, 700, 300, 100, DARKGREEN);
		DrawText("Quit", GetScreenWidth() / 2 - MeasureText("Quit", 50) / 2, 730, 50, GREEN);

		DrawTexturePro(Textures[4], Rectangle{ 0,0,576, 576 },
			Rectangle{ CursorX, CursorY, 100, 100 }, Vector2{ 100 / 2, 100 / 2 }, 0, WHITE);
	}
};

OptionsScreen Options;

struct PlayerCharachter
{
	float X, PX, Y, PY, Rotation, RotorRotation = 0, RotationRad, 
		SpeedX, SpeedY, Speed = 1800, MaxSpeed = 600, Drag = 200, 
		Health, Score = 0, HealthMax = 500, DamageDelay, DamageDelayMax = 1, Size = 20, 
		bulletsound = 1, LifeSteal = 5,
		
		BulletX[500], BulletY[500], BulletRotation[500], BulletRotationRad[500], BulletPiercing[500],
		BulletSpeed0 = 2500, BulletSpeed1 = 1600, BulletTime[500], BulletOriginX[500], BulletOriginY[500], BulletLifeTime = 3,
		BulletFireTimer, BulletFireRate, BulletFireRate0 = 0.08, BulletFireRate1 = 0.85, BulletSize = 7, 
		Damage, Damage0 = 100, Damage1 = 140, BulletType[500];
	int Bullet = 0, BulletMax = 499, BulletTextureCoordinates[6] = { 79, 48, 18, 30, 36, 60};
	bool BulletCanFire, CanTakeDamage = true;

	void Reset()
	{
		HealthMax = 500;
		Health = HealthMax;
		Speed = 2200;
		MaxSpeed = 800;
		Damage0 = 100; 
		Damage1 = 140;
		LifeSteal = 5;
		BulletSpeed0 = 2500;
		BulletSpeed1 = 1600;
		BulletFireRate0 = 0.08;
		BulletFireRate1 = 0.85;
	}

	void Respawn()
	{
		X = WorldSize / 2;
		Y = WorldSize / 2;
		SpeedX = 0;
		SpeedY = 0;

		for (int i = 0; i < NumberOfObjects; i++)
		{
			if (ObjectFile.MapObjects[i][15] == 7)
			{
				ObjectFile.MapObjects[i][4] = 1;
				X = ObjectFile.MapObjects[i][1];
				Y = ObjectFile.MapObjects[i][2];
			}
		}
	}

	void BulletReset()
	{
		for (int i = 0; i <= BulletMax; i++)
		{
			BulletTime[i] = 3;
		}
	}
};

PlayerCharachter Player;

struct Enemy
{
	float X[200], PX[200], Y[200], PY[200], Health[200], Type[200], Speed0 = 300, Speed1 = 200, Speed2 = 150,
		MaxHealth0 = 300, MaxHealth1 = 180, MaxHealth2 = 1000, Damage0 = 100, Damage1 = 50, Damage2 = 200, Size = 75,
		wave = 10, waveMax = 199, waveTimer = 0, MinSpawn = 3000, MaxSpawn = 4000, Despawn = 4500, Respawnpoint = 0,

		BulletX[500], BulletY[500], BulletRotation[500], BulletRotationRad[500],
		BulletSpeed = 800, BulletTime[500], BulletOriginX[500], BulletOriginY[500], BulletLifeTime = 3,
		BulletFireTimer[500], BulletFireRate = 1, BulletSize = 5;

	int Bullet = 0, BulletMax = 499, BulletTextureCoordinates[6] = { 105, 63, 20, 24, 60, 72 };
	bool BulletCanFire[200], Respawn, Hit[200][500], Respawned= false;

	void Reset()
	{
		for (int i = 0; i < waveMax; i++)
		{
			Health[i] = -1;
		}
		for (int i = 0; i < BulletMax; i++)
		{
			BulletTime[i] = BulletLifeTime + 1;
		}

		wave = 10;
	}

	void Logic()
	{
		if (Respawn)
		{
			if (waveTimer < 10 && wave < waveMax)
			{
				waveTimer += GetFrameTime();
			}
			else
			{
				waveTimer = 0;
				wave += 1;
			}
		}

		for (int i = 0; i < BulletMax; i++)
		{
			if (BulletTime[i] <= BulletLifeTime)
			{
				BulletTime[i] += GetFrameTime();

				BulletX[i] = (cos(BulletRotationRad[i]) * (BulletSpeed * BulletTime[i])) + BulletOriginX[i];
				BulletY[i] = (sin(BulletRotationRad[i]) * (BulletSpeed * BulletTime[i])) + BulletOriginY[i];
			}
			if (Player.X > BulletX[i] - Player.Size &&
				Player.X < BulletX[i] + Player.Size &&
				Player.Y > BulletY[i] - Player.Size &&
				Player.Y < BulletY[i] + Player.Size &&
				BulletTime[i] < BulletLifeTime &&
				Player.CanTakeDamage == true)
			{
				if (CheckCollisionCircleRec(Vector2{ BulletX[i], BulletY[i] },
					BulletSize, Rectangle{ Player.X - Player.Size / 2, Player.Y - Player.Size / 2,
					Player.Size, Player.Size }))
				{
					Player.Health -= Damage1;
					Player.CanTakeDamage = false;

					BulletTime[i] = BulletLifeTime + 1;
				}
			}
			for (int j = 0; j < NumberOfObjects; j++)
			{
				if (ObjectFile.MapObjects[j][1] > BulletX[i] - 2000 &&
					ObjectFile.MapObjects[j][1] < BulletX[i] + 2000 &&
					ObjectFile.MapObjects[j][2] > BulletY[i] - 2000 &&
					ObjectFile.MapObjects[j][2] < BulletY[i] + 2000 &&
					ObjectFile.MapObjects[j][8] == 0)
				{
					if (ObjectFile.MapObjects[j][3] != 1)
					{
						if (CheckCollisionCircleRec(Vector2{ BulletX[i], BulletY[i] }, BulletSize,
							Rectangle{
								ObjectFile.MapObjects[j][1] - (Objects[(int)ObjectFile.MapObjects[j][3]][5] / 2),
								ObjectFile.MapObjects[j][2] - (Objects[(int)ObjectFile.MapObjects[j][3]][6] / 2),
								Objects[(int)ObjectFile.MapObjects[j][3]][5],
								Objects[(int)ObjectFile.MapObjects[j][3]][6] }))
						{
							BulletTime[i] = BulletLifeTime + 1;
						}
					}
					else
					{
						if (CheckCollisionCircleRec(Vector2{ BulletX[i], BulletY[i] }, 5,
							Rectangle{
								ObjectFile.MapObjects[j][1] - ObjectFile.MapObjects[j][9] / 2,
								ObjectFile.MapObjects[j][2] - ObjectFile.MapObjects[j][10] / 2,
								ObjectFile.MapObjects[j][9],
								ObjectFile.MapObjects[j][10] }))
						{
							BulletTime[i] = BulletLifeTime + 1;
						}
					}
				}
			}
		}

		for (int i = 0; i < wave; i++)
		{
			if (Health[i] <= 0 && StartTimer > 3)
			{
				if (Respawn == true)
				{
					Respawned = true;
					if (Respawnpoint >= NumberOfObjects) { Respawnpoint = 0; }
					for (int j = Respawnpoint; j < NumberOfObjects; j++)
					{
						if (j >= NumberOfObjects) { Respawnpoint = 0; }
						if (ObjectFile.MapObjects[j][15] == 6)
						{
							if (ObjectFile.MapObjects[j][1] > Player.X - MaxSpawn &&
								ObjectFile.MapObjects[j][1] < Player.X + MaxSpawn &&
								ObjectFile.MapObjects[j][2] > Player.Y - MaxSpawn &&
								ObjectFile.MapObjects[j][2] < Player.Y + MaxSpawn &&
								!(ObjectFile.MapObjects[j][1] > Player.X - MinSpawn &&
								ObjectFile.MapObjects[j][1] < Player.X + MinSpawn &&
								ObjectFile.MapObjects[j][2] > Player.Y - MinSpawn &&
								ObjectFile.MapObjects[j][2] < Player.Y + MinSpawn) &&
								ObjectFile.MapObjects[j][3] >= 10 || 
								ObjectFile.MapObjects[j][12] != 0)
							{
								ObjectFile.MapObjects[j][11] == 1;

								X[i] = ObjectFile.MapObjects[j][1];
								Y[i] = ObjectFile.MapObjects[j][2];

								Type[i] = rand() % 100;
								if (Type[i] < 30)
								{
									Type[i] = 0; Health[i] = MaxHealth0;
								}
								else if (Type[i] < 70)
								{
									Type[i] = 1; Health[i] = MaxHealth1;
								}
								else
								{
									Type[i] = 2; Health[i] = MaxHealth2;
								}
								Respawned = false;
							}
						}
						Respawnpoint = j + 1;
						if (Respawned) { continue; } break;
					}
				}
			}
			else
			{
				StartTimer += GetFrameTime();
			}

			if (Health[i] > 0)
			{
				if (Player.X > X[i] - 100 &&
					Player.X < X[i] + 100 &&
					Player.Y > Y[i] - 100 &&
					Player.Y < Y[i] + 100 &&
					Player.CanTakeDamage == true&&
					Type[i] == 0)
				{
					if (CheckCollisionCircleRec(Vector2{ X[i], Y[i] },
						Size, Rectangle{ Player.X - Player.Size / 2, Player.Y - Player.Size / 2,
						Player.Size, Player.Size }))
					{
						Player.Health -= Damage0;
						Player.CanTakeDamage = false;
					}
				}
				if (Player.X > X[i] - 100 &&
					Player.X < X[i] + 100 &&
					Player.Y > Y[i] - 100 &&
					Player.Y < Y[i] + 100 &&
					Player.CanTakeDamage == true&&
					Type[i] == 2)
				{
					if (CheckCollisionCircleRec(Vector2{ X[i], Y[i] },
						Size, Rectangle{ Player.X - Player.Size / 2, Player.Y - Player.Size / 2,
						Player.Size, Player.Size }))
					{
						Player.Health -= Damage2;
						Player.CanTakeDamage = false;
					}
				}

				int randFire = rand() % 4;

				if (Type[i] == 1 && BulletCanFire[i] && randFire == 1)
				{
					BulletRotationRad[Bullet] = atan2((X[i] - Player.X) * -1, (Y[i] - Player.Y));
					BulletRotationRad[Bullet] -= 6.28 / 4;
					BulletRotation[Bullet] = (((BulletRotationRad[Bullet] / 6.28) * 360) + 90);

					BulletOriginX[Bullet] = X[i];
					BulletOriginY[Bullet] = Y[i];
					BulletTime[Bullet] = 0;

					Bullet++;

					if (Bullet > BulletMax)
					{
						Bullet = 0;
					}

					BulletCanFire[i] = false;
					BulletFireTimer[i] = 0;
				}

				if (Type[i] == 1 && !BulletCanFire[i])
				{
					if (BulletFireTimer[i] > BulletFireRate)
					{
						BulletCanFire[i] = true;
					}
					else
					{
						BulletFireTimer[i] += GetFrameTime();
					}
				}

				if (Health[i] > 0)
				{
					for (int j = 0; j < Player.BulletMax; j++)
					{
						if (Player.BulletType[j] == 0) { Player.BulletSize = 7; Player.Damage = Player.Damage0; }
						else if (Player.BulletType[j] == 1) { Player.BulletSize = 100; Player.Damage = Player.Damage1; }
						if (Player.BulletX[j] > X[i] - Player.BulletSize - 100 &&
							Player.BulletX[j] < X[i] + Player.BulletSize + 100 &&
							Player.BulletY[j] > Y[i] - Player.BulletSize - 100 &&
							Player.BulletY[j] < Y[i] + Player.BulletSize + 100 &&
							Player.BulletTime[j] <= Player.BulletLifeTime)
						{
							if (CheckCollisionCircleRec(Vector2{ Player.BulletX[j], 
								Player.BulletY[j] }, Player.BulletSize,
								Rectangle { X[i] - Size / 2, Y[i] - Size / 2, Size, Size }))
							{
								if (Player.BulletPiercing[j] > 0 && Hit[i][j] == false)
								{
									Player.BulletPiercing[j]--;
								}
								else if (Hit[i][j] == false)
								{
									Player.BulletTime[j] = Player.BulletLifeTime + 1;
								}

								Health[i] -= (Player.Damage * (rand() % 50 + 50)) / 100;
								Hit[i][j] = true;

								if (Health[i] <= 0)
								{
									PlaySound(Sounds[2]);
									if (Player.Health < Player.HealthMax)
									{
										Player.Health += Player.LifeSteal;
										if (Player.Health > Player.HealthMax) { Player.Health = Player.HealthMax; }
									}
									Player.Score += 100;
								}
							}
						}
					}
				}

				if (Health[i] > 0)
				{
					if (X[i] > Player.X + Despawn || X[i] < Player.X - Despawn || Y[i] > Player.Y + Despawn || Y[i] < Player.Y - Despawn)
					{
						Health[i] = 0;
					}
				}

				switch ((int)Type[i])
				{
				case 0:
					if (X[i] < Player.X)
					{
						X[i] += Speed0 * GetFrameTime() + ((rand() % (int)Speed0) * GetFrameTime());
					}
					else if (X[i] > Player.X)
					{
						X[i] -= Speed0 * GetFrameTime() + ((rand() % (int)Speed0) * GetFrameTime());
					}
					if (Y[i] < Player.Y)
					{
						Y[i] += Speed0 * GetFrameTime() + ((rand() % (int)Speed0) * GetFrameTime());
					}
					else if (Y[i] > Player.Y)
					{
						Y[i] -= Speed0 * GetFrameTime() + ((rand() % (int)Speed0) * GetFrameTime());
					}
					break;
				case 1:
					if (X[i] < Player.X - 600 || X[i] - Player.X < 600 && X[i] > Player.X)
					{
						X[i] += Speed1 * GetFrameTime() + ((rand() % (int)Speed1) * GetFrameTime());
					}
					else if (X[i] > Player.X + 600 || X[i] - Player.X > 600 && X[i] < Player.X)
					{
						X[i] -= Speed1 * GetFrameTime() + ((rand() % (int)Speed1) * GetFrameTime());
					}
					if (Y[i] < Player.Y - 600 || Y[i] - Player.Y < 600 && Y[i] > Player.Y)
					{
						Y[i] += Speed1 * GetFrameTime() + ((rand() % (int)Speed1) * GetFrameTime());
					}
					else if (Y[i] > Player.Y + 600 || Y[i] - Player.Y > 600 && Y[i] < Player.Y)
					{
						Y[i] -= Speed1 * GetFrameTime() + ((rand() % (int)Speed1) * GetFrameTime());
					}
					break;
				case 2:
					if (X[i] < Player.X)
					{
						X[i] += Speed2 * GetFrameTime() + ((rand() % (int)Speed2) * GetFrameTime());
					}
					else if (X[i] > Player.X)
					{
						X[i] -= Speed2 * GetFrameTime() + ((rand() % (int)Speed2) * GetFrameTime());
					}
					if (Y[i] < Player.Y)
					{
						Y[i] += Speed2 * GetFrameTime() + ((rand() % (int)Speed2) * GetFrameTime());
					}
					else if (Y[i] > Player.Y)
					{
						Y[i] -= Speed2 * GetFrameTime() + ((rand() % (int)Speed2) * GetFrameTime());
					}
					break;
				}
				X[i] += ((rand() % (int)Speed0 * 2) - Speed0) * GetFrameTime();
				Y[i] += ((rand() % (int)Speed0 * 2) - Speed0) * GetFrameTime();
				if (Health[i] > 0)
				{
					for (int j = 0; j < NumberOfObjects; j++)
					{
						if (ObjectFile.MapObjects[j][1] > X[i] - Objects[(int)ObjectFile.MapObjects[j][3]][5] &&
							ObjectFile.MapObjects[j][1] < X[i] + Objects[(int)ObjectFile.MapObjects[j][3]][5] &&
							ObjectFile.MapObjects[j][2] > Y[i] - Objects[(int)ObjectFile.MapObjects[j][3]][6] &&
							ObjectFile.MapObjects[j][2] < Y[i] + Objects[(int)ObjectFile.MapObjects[j][3]][6] &&
							ObjectFile.MapObjects[j][3] >= 10 &&
							ObjectFile.MapObjects[j][11] == 0)
						{
							while (CheckCollisionCircleRec(Vector2{ X[i], Y[i] }, Size,
								Rectangle{
									ObjectFile.MapObjects[j][1] - (Objects[(int)ObjectFile.MapObjects[j][3]][5] / 2),
									ObjectFile.MapObjects[j][2] - (Objects[(int)ObjectFile.MapObjects[j][3]][6] / 2),
									Objects[(int)ObjectFile.MapObjects[j][3]][5],
									Objects[(int)ObjectFile.MapObjects[j][3]][6] }))
							{
								if (PX[i] > ObjectFile.MapObjects[j][1] + (Objects[(int)ObjectFile.MapObjects[j][3]][5] / 2))
								{
									X[i] += 1;
								}
								else if (PX[i] < ObjectFile.MapObjects[j][1] - (Objects[(int)ObjectFile.MapObjects[j][3]][5] / 2))
								{
									X[i] -= 1;
								}
								if (PY[i] > ObjectFile.MapObjects[j][2] + (Objects[(int)ObjectFile.MapObjects[j][3]][6] / 2))
								{
									Y[i] += 1;
								}
								else if (PY[i] < ObjectFile.MapObjects[j][2] - (Objects[(int)ObjectFile.MapObjects[j][3]][6] / 2))
								{
									Y[i] -= 1;
								}
							}
						}

						else if (ObjectFile.MapObjects[j][1] > X[i] - ObjectFile.MapObjects[j][9] &&
							ObjectFile.MapObjects[j][1] < X[i] + ObjectFile.MapObjects[j][9] &&
							ObjectFile.MapObjects[j][2] > Y[i] - ObjectFile.MapObjects[j][10] &&
							ObjectFile.MapObjects[j][2] < Y[i] + ObjectFile.MapObjects[j][10] &&
							ObjectFile.MapObjects[j][11] == 0)
						{
							while (CheckCollisionCircleRec(Vector2{ X[i], Y[i] }, Size,
								Rectangle{
									ObjectFile.MapObjects[j][1] - ObjectFile.MapObjects[j][9] / 2,
									ObjectFile.MapObjects[j][2] - ObjectFile.MapObjects[j][10] / 2,
									ObjectFile.MapObjects[j][9],
									ObjectFile.MapObjects[j][10] }))
							{
								if (PX[i] > ObjectFile.MapObjects[j][1] + ObjectFile.MapObjects[j][9] / 2)
								{
									X[i] += 1;
								}
								else if (PX[i] < ObjectFile.MapObjects[j][1] - ObjectFile.MapObjects[j][9] / 2)
								{
									X[i] -= 1;
								}
								if (PY[i] > ObjectFile.MapObjects[j][2] + ObjectFile.MapObjects[j][10] / 2)
								{
									Y[i] += 1;
								}
								else if (PY[i] < ObjectFile.MapObjects[j][2] - ObjectFile.MapObjects[j][10] / 2)
								{
									Y[i] -= 1;
								}
							}
						}
					}
				}
				PX[i] = X[i];
				PY[i] = Y[i];
			}
		}
	}
};

Enemy Spartan;

struct PowerUpStruct
{
	void Reset()
	{
		for (int i = 0; i < NumberOfObjects; i++)
		{
			if(ObjectFile.MapObjects[i][15] != 0 && ObjectFile.MapObjects[i][15] != 6 && ObjectFile.MapObjects[i][15] != 7)
			{
				ObjectFile.MapObjects[i][5] = 0;
			}
		}
	}
	void PickUp(int i)
	{
		if (ObjectFile.MapObjects[i][15] != 0 && ObjectFile.MapObjects[i][15] != 6 && ObjectFile.MapObjects[i][15] != 7)
		{
			if (ObjectFile.MapObjects[i][5] == 0)
			{
				if (CheckCollisionCircleRec(Vector2{ Player.X,Player.Y }, Player.Size, Rectangle{
								ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2),
								ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2),
								Objects[(int)ObjectFile.MapObjects[i][3]][5],
								Objects[(int)ObjectFile.MapObjects[i][3]][6] }))
				{
					switch ((int)ObjectFile.MapObjects[i][15])
					{
					case 1:
						Player.HealthMax += 50;
						Player.Health = Player.HealthMax;
						break;
					case 2:
						Player.MaxSpeed += 100;
						Player.Speed += 100;
						break;
					case 3:
						Player.BulletSpeed0 += 100;
						Player.BulletSpeed1 += 100;
						Player.BulletFireRate0 -= 0, 01;
						Player.BulletFireRate1 -= 0, 05;
						break;
					case 4:
						Player.Damage0 += 20;
						Player.Damage1 += 60;
						break;
					case 5:
						Player.LifeSteal += 5;
						break;
					}
					ObjectFile.MapObjects[i][5] = 1;
				}
			}
		}
	}
};
PowerUpStruct PowerUp;

void Reset()
{
	Player.Reset();
	Player.Respawn();
	StartTimer = 0;
	CursorReset = true;
	Spartan.Reset();
	PowerUp.Reset();
	Player.Score = 0;
	Player.BulletReset();

	GameState = Play;
}

struct StartScreenStruct
{
	float CursorX, CursorY;

	void Controlls()
	{
		CursorX = GetMouseX();
		CursorY = GetMouseY();
	}

	void Logic()
	{
		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1,
			Rectangle{ (float)GetScreenWidth() / 2 - 150,
			(float)GetScreenHeight() / 2 - 50 + 200, 300, 100 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Reset();
		}

		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1,
			Rectangle{ (float)GetScreenWidth() / 2 - 150,
			(float)GetScreenHeight() / 2 - 50 + 200 + 110, 300, 100 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Desktop = true;
		}
	}

	void Draw()
	{
		DrawTexturePro(Textures[5], Rectangle{ 0, 0, 1600, 900 },
			Rectangle{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, Vector2{ 0, 0 }, 0, WHITE);

		DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 50 + 200, 300, 100, DARKGREEN);
		DrawText("Play", GetScreenWidth() / 2 - MeasureText("Play", 60) / 2,
			GetScreenHeight() / 2 - 50 + 200 + 20, 60, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 150, GetScreenHeight() / 2 - 50 + 200 + 110, 300, 100, DARKGREEN);
		DrawText("Desktop", GetScreenWidth() / 2 - MeasureText("Desktop", 60) / 2,
			GetScreenHeight() / 2 - 50 + 200 + 110 + 20, 60, GREEN);

		DrawTexturePro(Textures[4], Rectangle{ 0,0,576, 576 },
			Rectangle{ CursorX, CursorY, 100, 100 }, Vector2{ 100 / 2, 100 / 2 }, 0, WHITE);
	}
};
StartScreenStruct StartScreen;

struct GameOverScreenStruckt
{
	float CursorX, CursorY;

	void Controlls()
	{
		CursorX = GetMouseX();
		CursorY = GetMouseY();
	}

	void Logic()
	{
		if (CheckCollisionCircleRec(Vector2{ CursorX, CursorY }, 1,
			Rectangle{ (float)GetScreenWidth() / 2 - 150,
			(float)GetScreenHeight() / 2 - 50 + 200, 300, 100 }) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			Reset();

			ResumeSound(Sounds[4]);
			ResumeSound(Sounds[5]);
		}

		
	}

	void Draw()
	{
		DrawTexturePro(Textures[8], Rectangle{ 0, 0, 442, 331 },
			Rectangle{ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, Vector2{ 0, 0 }, 0, WHITE);

		DrawRectangle(5, 5, 240, 30, BLACK);
		DrawText(TextFormat("Score %i", (int)Player.Score), 10, 10, 25, GREEN);

		DrawRectangle(GetScreenWidth() / 2 - 180, GetScreenHeight() / 2 - 50 + 200, 360, 100, DARKGREEN);
		DrawText("Try Again?", GetScreenWidth() / 2 - MeasureText("Try Again?", 60) / 2,
			GetScreenHeight() / 2 - 50 + 200 + 30, 60, GREEN);

		DrawTexturePro(Textures[4], Rectangle{ 0,0,576, 576 },
			Rectangle{ CursorX, CursorY, 100, 100 }, Vector2{ 100 / 2, 100 / 2 }, 0, WHITE);
	}
};
GameOverScreenStruckt GameOverScreen;

struct Map
{
	void DrawMap()
	{
		for (float i = 0; i < 511; i++)
		{
			for (float j = 0; j < 511; j++)
			{
				switch (GameState)
				{
				case Play:

					if (i * 320 > Player.X - 4000 && i * 320 < Player.X + 4000 &&
						j * 320 > Player.Y - 4000 && j * 320 < Player.Y + 4000)
					{
						switch (MapTiles[(int)i][(int)j])
						{
						case 0:
							DrawTexturePro(Textures[3], Rectangle{ 208,400,48,48 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 1:
							DrawTexturePro(Textures[3], Rectangle{ 32,48,48,48 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 2:

							if ((int)(AnimationTimer * 100) % 100 > 50)
							{
								DrawTexturePro(Textures[3], Rectangle{ 320,96,32,32 },
									Rectangle{ i * 320, j * 320, 320, 320 },
									Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							}
							else
							{
								DrawTexturePro(Textures[3], Rectangle{ 320,96,32,32 },
									Rectangle{ i * 320, j * 320, 320, 320 },
									Vector2{ 320 / 2, 320 / 2 }, 180, WHITE);
							}
							break;
						case 3:
							DrawTexturePro(Textures[3], Rectangle{ 194,225,26,23 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 4:
							DrawTexturePro(Textures[11], Rectangle{ 960,2068,64,64 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 5:
							DrawTexturePro(Textures[11], Rectangle{ 125,841,64,64 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						}
					}

					break;
				case LevelEditor:

					if (i * 320 > GameCamera.target.x - 18000 && i * 320 < GameCamera.target.x + 18000 &&
						j * 320 > GameCamera.target.y - 10000 && j * 320 < GameCamera.target.y + 10000)
					{
						switch (MapTiles[(int)i][(int)j])
						{
						case 0:
							DrawTexturePro(Textures[3], Rectangle{ 208,400,48,48 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 1:
							DrawTexturePro(Textures[3], Rectangle{ 32,48,48,48 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 2:
							DrawTexturePro(Textures[3], Rectangle{ 320,96,32,32 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 3:
							DrawTexturePro(Textures[3], Rectangle{ 194,225,26,23 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 4:
							DrawTexturePro(Textures[11], Rectangle{ 960,2068,64,64 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						case 5:
							DrawTexturePro(Textures[11], Rectangle{ 125,841,64,64 },
								Rectangle{ i * 320, j * 320, 320, 320 },
								Vector2{ 320 / 2, 320 / 2 }, 0, WHITE);
							break;
						}
						break;
					}
				}
			}
		}

		switch (GameState)
		{
		case Play:

			for (int i = 0; i < NumberOfObjects; i++)
			{
				if (ObjectFile.MapObjects[i][1] > Player.X - 4000 &&
					ObjectFile.MapObjects[i][1] < Player.X + 4000 &&
					ObjectFile.MapObjects[i][2] > Player.Y - 4000 &&
					ObjectFile.MapObjects[i][2] < Player.Y + 4000 &&
					ObjectFile.MapObjects[i][3] >= 10 ||
					ObjectFile.MapObjects[i][12] != 0)
				{
					if (ObjectFile.MapObjects[i][5] == 0 || !ShowHidden)
					{
						if (ObjectFile.MapObjects[i][13] != 0)
						{
							ObjectFile.MapObjects[i][14] += ObjectFile.MapObjects[i][13];
						}

						DrawTexturePro(Textures[(int)Objects[(int)ObjectFile.MapObjects[i][3]][8]],

							Rectangle{
							Objects[(int)ObjectFile.MapObjects[i][3]][1],
							Objects[(int)ObjectFile.MapObjects[i][3]][2],
							Objects[(int)ObjectFile.MapObjects[i][3]][3],
							Objects[(int)ObjectFile.MapObjects[i][3]][4] },

							Rectangle{
							ObjectFile.MapObjects[i][1],
							ObjectFile.MapObjects[i][2],
							Objects[(int)ObjectFile.MapObjects[i][3]][5],
							Objects[(int)ObjectFile.MapObjects[i][3]][6] },
							Vector2{
							Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2,
							Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2 },
							ObjectFile.MapObjects[i][14],
							WHITE);
					}
				}
				else if (ObjectFile.MapObjects[i][1] > Player.X - 4000 &&
					ObjectFile.MapObjects[i][1] < Player.X + 4000 &&
					ObjectFile.MapObjects[i][2] > Player.Y - 4000 &&
					ObjectFile.MapObjects[i][2] < Player.Y + 4000 &&
					ObjectFile.MapObjects[i][3] == 1)
				{
					if (ObjectFile.MapObjects[i][5] == 1 || !ShowHidden)
					{
						DrawRectangle(
							ObjectFile.MapObjects[i][1] - ObjectFile.MapObjects[i][9] / 2,
							ObjectFile.MapObjects[i][2] - ObjectFile.MapObjects[i][10] / 2,
							ObjectFile.MapObjects[i][9],
							ObjectFile.MapObjects[i][10],
							RED);
					}
				}
			}
			break;
		case LevelEditor:

			for (int i = 0; i < NumberOfObjects; i++)
			{
				if (ObjectFile.MapObjects[i][1] > GameCamera.target.x - 18000 && 
					ObjectFile.MapObjects[i][1] < GameCamera.target.x + 18000 &&
					ObjectFile.MapObjects[i][2] > GameCamera.target.y - 10000 && 
					ObjectFile.MapObjects[i][2] < GameCamera.target.y + 10000 &&
					ObjectFile.MapObjects[i][3] >= 10 ||
					ObjectFile.MapObjects[i][12] != 0 &&
					ObjectFile.MapObjects[i][3] >= 10)
				{
					if (ObjectFile.MapObjects[i][5] == 0 || ShowHidden)
					{
						DrawTexturePro(Textures[(int)Objects[(int)ObjectFile.MapObjects[i][3]][8]],

							Rectangle{
							Objects[(int)ObjectFile.MapObjects[i][3]][1],
							Objects[(int)ObjectFile.MapObjects[i][3]][2],
							Objects[(int)ObjectFile.MapObjects[i][3]][3],
							Objects[(int)ObjectFile.MapObjects[i][3]][4] },

							Rectangle{
							ObjectFile.MapObjects[i][1],
							ObjectFile.MapObjects[i][2],
							Objects[(int)ObjectFile.MapObjects[i][3]][5],
							Objects[(int)ObjectFile.MapObjects[i][3]][6] },
							Vector2{
							Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2,
							Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2 },
							Objects[(int)ObjectFile.MapObjects[i][3]][7],
							WHITE);
					}
						if (ObjectFile.MapObjects[i][4] != 0)
						{
							DrawText("Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2],
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][5] != 0)
						{
							DrawText("Draw",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 25,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][6] != 0)
						{
							DrawText(TextFormat("%d", (int)ObjectFile.MapObjects[i][7]),
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 50,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][8] != 0)
						{
							DrawText("Bullet Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 75,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][11] != 0)
						{
							DrawText("Enemy Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 100,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][0] != 0)
						{
							DrawText("Freeze",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 125,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][12] != 0)
						{
							DrawText("Global",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 150,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][13] != 0)
						{
							DrawText("Rotate",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 175,
								25, WHITE);
							DrawText(TextFormat("%d", (int)ObjectFile.MapObjects[i][13]),
								ObjectFile.MapObjects[i][1] + 100, ObjectFile.MapObjects[i][2] + 175,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][15] != 0)
						{
							switch ((int)ObjectFile.MapObjects[i][15])
							{
							case 1: DrawText("Plus Health", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 2: DrawText("Plus Speed", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 3: DrawText("Plus B Speed", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 4: DrawText("Plus Damage", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 5: DrawText("Plus Steal", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 6: DrawText("Enemy Respawn", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							case 7: DrawText("Player Respawn", ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 200, 25, WHITE); break;
							}
						}
					}
					else if (ObjectFile.MapObjects[i][1] > GameCamera.target.x - 18000 &&
							ObjectFile.MapObjects[i][1] < GameCamera.target.x + 18000 &&
							ObjectFile.MapObjects[i][2] > GameCamera.target.y - 10000 &&
							ObjectFile.MapObjects[i][2] < GameCamera.target.y + 10000 && 
							ObjectFile.MapObjects[i][3] == 1)
					{
					if (ObjectFile.MapObjects[i][5] == 1 || ShowHidden)
					{
						DrawRectangle(
							ObjectFile.MapObjects[i][1] - ObjectFile.MapObjects[i][9] / 2,
							ObjectFile.MapObjects[i][2] - ObjectFile.MapObjects[i][10] / 2,
							ObjectFile.MapObjects[i][9],
							ObjectFile.MapObjects[i][10],
							RED);
					}
						if (ObjectFile.MapObjects[i][4] != 0)
						{
							DrawText("Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2],
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][5] != 0)
						{
							DrawText("Draw",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 25,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][6] != 0)
						{
							DrawText(TextFormat("%d", (int)ObjectFile.MapObjects[i][7]),
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 50,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][11] != 0)
						{
							DrawText("Enemy Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 75,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][8] != 0)
						{
							DrawText("Bullet Collision",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 100,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][0] != 0)
						{
							DrawText("Freeze",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 125,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][12] != 0)
						{
							DrawText("Global",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 150,
								25, WHITE);
						}
						if (ObjectFile.MapObjects[i][12] != 0)
						{
							DrawText("Rotate",
								ObjectFile.MapObjects[i][1], ObjectFile.MapObjects[i][2] + 175,
								25, WHITE);
						}
				}
			}

			break;
		}
	}
};
Map Level;

bool CheckCollisionsEditor(int i)
{
	if (EditorCursorX > ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2) &&
		EditorCursorX < ObjectFile.MapObjects[i][1] + (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2) &&
		EditorCursorY > ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2) &&
		EditorCursorY < ObjectFile.MapObjects[i][2] + (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2)
		||
		EditorCursorX > ObjectFile.MapObjects[i][1] - ((ObjectFile.MapObjects[i][9] / 2) / BrushSize) &&
		EditorCursorX < ObjectFile.MapObjects[i][1] + ((ObjectFile.MapObjects[i][10] / 2) / BrushSize) &&
		EditorCursorY > ObjectFile.MapObjects[i][2] - ((ObjectFile.MapObjects[i][9] / 2) / BrushSize) &&
		EditorCursorY < ObjectFile.MapObjects[i][2] + ((ObjectFile.MapObjects[i][10] / 2) / BrushSize))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LoadResources()
{
	int i = 0;
	Textures[i] = LoadTexture("resources/0EnemyTexture.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/1ProjectileTexture.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/2Helicopter.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/3DesertTileset.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/4Cursor.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/5Helicopter.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/6Structures.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/7Prop.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/8Helicopter.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/9Enemy.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/10Enemy.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/11Map.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/12PowerUps.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/13Blade.png");
	i++; TexturesLoaded++;
	Textures[i] = LoadTexture("resources/14SpawnPoint.png");
	i = 0;

	Sounds[i] = LoadSound("resources/TestSound.wav");
	i++; SoundsLoaded++;
	Sounds[i] = LoadSound("resources/bullet.mp3");
	SetSoundVolume(Sounds[i], 0.6 * SoundLevel);
	i++; SoundsLoaded++;
	Sounds[i] = LoadSound("resources/death.mp3");
	SetSoundVolume(Sounds[i], 0.75 * SoundLevel);
	i++; SoundsLoaded++;
	Sounds[i] = LoadSound("resources/gameover.mp3");
	SetSoundVolume(Sounds[i], 1 * SoundLevel);
	i++; SoundsLoaded++;
	Sounds[i] = LoadSound("resources/helicopter.mp3");
	SetSoundVolume(Sounds[i], 0.5 * SoundLevel);
	i++; SoundsLoaded++;
	Sounds[i] = LoadSound("resources/music.mp3");
	SetSoundVolume(Sounds[i], 0.75 * MusicLevel);
	i++; SoundsLoaded++;
	i = 0;

	i = 10;
	Objects[i][1] = 352;	// X on texture
	Objects[i][2] = 1036;	// Y on texture
	Objects[i][3] = 64;		// Width on texture
	Objects[i][4] = 64;		// height on texture
	Objects[i][5] = 320;	// Object width
	Objects[i][6] = 320;	// Object height
	Objects[i][7] = 0;		// Object Rotation
	Objects[i][8] = 6;		// Texture
	i++;
	Objects[i][1] = 952;
	Objects[i][2] = 870;
	Objects[i][3] = 144;
	Objects[i][4] = 127;
	Objects[i][5] = 144 * 3;
	Objects[i][6] = 127 * 3;
	Objects[i][7] = 0;
	Objects[i][8] = 6;
	i++;
	Objects[i][1] = 73;
	Objects[i][2] = 273;
	Objects[i][3] = 62;
	Objects[i][4] = 62;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 0;
	Objects[i][2] = 0;
	Objects[i][3] = 6528;
	Objects[i][4] = 6400;
	Objects[i][5] = 6528 * 5;
	Objects[i][6] = 6400 * 5;
	Objects[i][7] = 0;
	Objects[i][8] = 11;
	i++;
	Objects[i][1] = 41;
	Objects[i][2] = 122;
	Objects[i][3] = 30;
	Objects[i][4] = 30;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 137;
	Objects[i][2] = 122;
	Objects[i][3] = 30;
	Objects[i][4] = 30;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 105;
	Objects[i][2] = 122;
	Objects[i][3] = 30;
	Objects[i][4] = 30;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 73;
	Objects[i][2] = 122;
	Objects[i][3] = 30;
	Objects[i][4] = 30;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 9;
	Objects[i][2] = 122;
	Objects[i][3] = 30;
	Objects[i][4] = 30;
	Objects[i][5] = 120;
	Objects[i][6] = 120;
	Objects[i][7] = 0;
	Objects[i][8] = 12;
	i++;
	Objects[i][1] = 21;
	Objects[i][2] = 8;
	Objects[i][3] = 109;
	Objects[i][4] = 109;
	Objects[i][5] = 350;
	Objects[i][6] = 350;
	Objects[i][7] = 0;
	Objects[i][8] = 13;
	i++;
	Objects[i][1] = 0;
	Objects[i][2] = 0;
	Objects[i][3] = 1000;
	Objects[i][4] = 1000;
	Objects[i][5] = 150;
	Objects[i][6] = 150;
	Objects[i][7] = 0;
	Objects[i][8] = 14;
	i++;
}
void UnloadResources()
{
	for (int i = 0; i <= TexturesLoaded; i++)
	{
		UnloadTexture(Textures[i]);
	}
	for (int i = 0; i <= SoundsLoaded; i++)
	{
		UnloadSound(Sounds[i]);
	}
}

void Controlls()
{
	if (IsKeyPressed(PauseGame))
	{
		switch (GameState)
		{
		case Play: GameState = Pause; PauseSound(Sounds[4]); PauseSound(Sounds[5]);
			break;
		case Pause: GameState = Play; ResumeSound(Sounds[5]); ResumeSound(Sounds[5]);
			break;
		}
	}

	if (IsKeyPressed(MuteMusic))
	{
		switch (Mute)
		{
		case true: Mute = false;
			break;
		case false: Mute = true;
			break;
		}
	}

	if (IsKeyDown(Mod) && IsKeyPressed(EditorEnter) && CanUseEditor)
	{
		switch (GameState)
		{
		case LevelEditor: GameState = Pause;
			break;
		case Pause: GameState = LevelEditor;
			break;
		}
	}

	if (IsKeyDown(Mod) && IsKeyPressed(FullScreen))
	{
		ToggleFullscreen();

		if (IsWindowFullscreen())
		{
			Options.IsFullscreen = true;
		}
		else
		{			
			Options.IsFullscreen = false;
		}
	}

	if (IsKeyPressed(ShowFramerate))
	{
		switch (ShowFPS)
		{
		case false: ShowFPS = true;
			break;
		case true: ShowFPS = false;
			break;
		}
	}

	switch (GameState)
	{
	case Play:

		if (IsKeyDown(Mod) && IsKeyPressed(ToggleSpawn))
		{
			switch (Spartan.Respawn)
			{
			case true:
				Spartan.Respawn = false;
				StartTimer = 0;
				break;
			case false:
				Spartan.Respawn = true;
				break;
			}
		}


		CursorDelta = GetMouseDelta();

		CursorX += CursorDelta.x;
		CursorY += CursorDelta.y;

		CursorWorld = GetScreenToWorld2D(Vector2{ CursorX , CursorY }, GameCamera);
		CursorScreen = GetWorldToScreen2D(Vector2{ CursorX, CursorY }, GameCamera);

		Player.RotationRad = atan2((CursorX - Player.X) * -1, (CursorY - Player.Y) * -1);
		Player.Rotation = (Player.RotationRad / 6.28) * -360;

		if (IsKeyDown(MoveDown) && !IsKeyDown(MoveUp))
		{
			Player.SpeedY += Player.Speed * GetFrameTime();
		}
		else if (IsKeyDown(MoveUp) && !IsKeyDown(MoveDown))
		{
			Player.SpeedY -= Player.Speed * GetFrameTime();
		}
		if (IsKeyDown(MoveRight) && !IsKeyDown(MoveLeft))
		{
			Player.SpeedX += Player.Speed * GetFrameTime();
		}
		else if (IsKeyDown(MoveLeft) && !IsKeyDown(MoveRight))
		{
			Player.SpeedX -= Player.Speed * GetFrameTime();
		}

		if (IsKeyPressed(Track))
		{
			switch (CursorTrack)
			{
			case false: CursorTrack = true;
				break;
			case true: CursorTrack = false;
				break;
			}
		}

		if (IsMouseButtonDown(Fire1))
		{
			if (Player.BulletCanFire)
			{
				if (Player.bulletsound > 0.25)
				{ 
					PlaySound(Sounds[1]);
				}
				
				Player.BulletType[Player.Bullet] = 0;
				Player.BulletRotation[Player.Bullet] = Player.Rotation;
				Player.BulletRotationRad[Player.Bullet] = ((Player.BulletRotation[Player.Bullet] - 90) / 360) * 6.28;

				Player.BulletOriginX[Player.Bullet] = Player.X;
				Player.BulletOriginY[Player.Bullet] = Player.Y;
				Player.BulletTime[Player.Bullet] = 0;
				Player.BulletPiercing[Player.Bullet] = 0;

				for (int i = 0; i < Spartan.wave; i++)
				{
					Spartan.Hit[i][Player.Bullet] = false;
				}

				Player.Bullet++;

				if (Player.Bullet > Player.BulletMax)
				{
					Player.Bullet = 0;
				}

				Player.BulletCanFire = false;
				Player.BulletFireTimer = 0;
				Player.BulletFireRate = Player.BulletFireRate0;
			}
		}
		if (IsMouseButtonPressed(Fire2))
		{
			if (Player.BulletCanFire)
			{
				if (Player.bulletsound > 0.25)
				{
					PlaySound(Sounds[1]);
				}

				Player.BulletType[Player.Bullet] = 1;
				Player.BulletRotation[Player.Bullet] = Player.Rotation;
				Player.BulletRotationRad[Player.Bullet] = ((Player.BulletRotation[Player.Bullet] - 90) / 360) * 6.28;

				Player.BulletOriginX[Player.Bullet] = Player.X;
				Player.BulletOriginY[Player.Bullet] = Player.Y;
				Player.BulletTime[Player.Bullet] = 0;
				Player.BulletPiercing[Player.Bullet] = 5;

				for (int i = 0; i < Spartan.wave; i++)
				{
					Spartan.Hit[i][Player.Bullet] = false;
				}

				Player.Bullet++;

				if (Player.Bullet > Player.BulletMax)
				{
					Player.Bullet = 0;
				}

				Player.BulletCanFire = false;
				Player.BulletFireTimer = 0;
				Player.BulletFireRate = Player.BulletFireRate1;
			}
		}

		if (IsKeyPressed(GameShowHidden))
		{
			switch (ShowHidden)
			{
			case false: ShowHidden = true;
				break;
			case true: ShowHidden = false;
				break;
			}
		}

		GameCamera.zoom += (float)GetMouseWheelMove() * 0.05;

		if (GameCamera.zoom < 0.5)
		{
			GameCamera.zoom = 0.5;
		}

		if (GameCamera.zoom > 1)
		{
			GameCamera.zoom = 1;
		}

		if (IsKeyPressed(GameOverTrigger) && IsKeyDown(Mod))
		{
			GameState = GameOver;
		}

		break;

	case Pause:

		Options.Controlls();
	
		break;

	case Start:

		StartScreen.Controlls();

		break;

	case GameOver:

		GameOverScreen.Controlls();

		break;

	case LevelEditor:

		EditorCursorX = GetScreenToWorld2D(GetMousePosition(), GameCamera).x;
		EditorCursorY = GetScreenToWorld2D(GetMousePosition(), GameCamera).y;

		if (SnapToGrid)
		{
			EditorCursorX = (floor(EditorCursorX / 10)) * 10;
			EditorCursorY = (floor(EditorCursorY / 10)) * 10;
		}

		GameCamera.zoom += (float)GetMouseWheelMove() * 0.05;

		if (GameCamera.zoom < 0.05)
		{
			GameCamera.zoom = 0.05;
		}
		if (GameCamera.zoom > 3)
		{
			GameCamera.zoom = 3;
		}

		if (IsMouseButtonDown(EditorCameraMoveMouse) || IsKeyDown(EditorCameraMove))
		{
			GameCamera.target.x -= GetMouseDelta().x / GameCamera.zoom;
			GameCamera.target.y -= GetMouseDelta().y / GameCamera.zoom;
		}

		if (!IsKeyDown(Mod) && IsKeyPressed(EditorCameraReset))
		{
			GameCamera.zoom = 1;
			GameCamera.target.x = Player.X;
			GameCamera.target.y = Player.Y;
		}

		if (IsKeyPressed(EditorBrushSizeUp))
		{
			BrushSize += 0.05;

			if (BrushSize > 1)
			{
				BrushSize = 1;
			}
		}
		if (IsKeyPressed(EditorBrushSizeDown))
		{
			BrushSize -= 0.05;

			if (BrushSize < 0.05)
			{
				BrushSize = 0.05;
			}
		}

		if (IsKeyDown(Mod) && IsKeyPressed(EditorSaveMap))
		{
			ObjectFile.SaveMapFile();
			SavedTimer = 0;
		}

		if (IsKeyPressed(EditorGrid))
		{
			switch (SnapToGrid)
			{
			case false: SnapToGrid = true;
				break;
			case true: SnapToGrid = false;
				break;
			}
		}

		if (IsKeyPressed(EditorShowHidden))
		{
			switch (ShowHidden)
			{
			case false: ShowHidden = true;
				break;
			case true: ShowHidden = false;
				break;
			}
		}

		if (IsKeyPressed(EditorPreview))
		{
			switch (Preview)
			{
			case false: Preview = true;
				break;
			case true: Preview = false;
				break;
			}
		}

		if (IsKeyPressed(EditorShowPlayer))
		{
			switch (ShowPlayer)
			{
			case false: ShowPlayer = true;
				break;
			case true: ShowPlayer = false;
				break;
			}
		}

		
		if (IsKeyPressed(EditorDelete))
		{
			SelectedObject = Delete;
		}
		else if (IsKeyPressed(EditorCollision))
		{
			SelectedObject = Collison;
		}
		else if (IsKeyPressed(EditorBulletCollision))
		{
			SelectedObject = BulletCollison;
		}
		else if (IsKeyPressed(EditorDrawObject))
		{
			SelectedObject = DrawObject;
		}
		else if (IsKeyPressed(EditorDamage))
		{
			SelectedObject = Damage;
		}
		else if (IsKeyPressed(EditorEnemyCollision))
		{
			SelectedObject = EnemyCollision;
		}
		else if (IsKeyPressed(EditorFreeze))
		{
			SelectedObject = Freeze;
		}
		else if (IsKeyPressed(EditorGlobal))
		{
			SelectedObject = Global;
		}
		else if (IsKeyPressed(EditorRotateRight))
		{
			SelectedObject = RotateRight;
		}
		else if (IsKeyPressed(EditorRotateLeft))
		{
			SelectedObject = RotateLeft;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorReset))
		{
			Spartan.Reset();
			Player.X = WorldSize / 2;
			Player.Y = WorldSize / 2;
			Player.SpeedX = 0;
			Player.SpeedY = 0;
			Player.BulletReset();
		}
		else if (IsKeyPressed(EditorBoxLeft) && SelectedObject == Box)
		{
			if (IsKeyDown(Mod))
			{
				BoxWidth -= 100;
			}
			else
			{
				BoxWidth -= 10;
			}
			if (BoxWidth < 10)
			{
				BoxWidth = 10;
			}
			else if (BoxWidth < 10)
			{
				BoxWidth = 10;
			}
		}
		else if (IsKeyPressed(EditorBoxRight) && SelectedObject == Box)
		{
			if (IsKeyDown(Mod))
			{
				BoxWidth += 100;
			}
			else
			{
				BoxWidth += 10;
			}
			if (BoxWidth > 3000)
			{
				BoxWidth = 3000;
			}
		}
		else if (IsKeyPressed(EditorBoxDown) && SelectedObject == Box)
		{
			if (IsKeyDown(Mod))
			{
				BoxHeight -= 100;
			}
			else
			{
				BoxHeight -= 10;
			}
			if (BoxHeight < 10)
			{
				BoxHeight = 10;
			}
		}
		else if (IsKeyPressed(EditorBoxUp) && SelectedObject == Box)
		{
			if (IsKeyDown(Mod))
			{
				BoxHeight += 100;
			}
			else
			{
				BoxHeight += 10;
			}
			if (BoxHeight > 3000)
			{
				BoxHeight = 3000;
			}
		}

		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect1))
		{
			SelectedObject = Desert;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect2))
		{
			SelectedObject = Grass;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect3))
		{
			SelectedObject = Water;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect4))
		{
			SelectedObject = Brick;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect5))
		{
			SelectedObject = Tree;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect6))
		{
			SelectedObject = Stone;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect7))
		{
			SelectedObject = PlusHealth;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect8))
		{
			SelectedObject = PlusSpeed;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect9))
		{
			SelectedObject = PlusBulletSpeed;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorSelect0))
		{
			SelectedObject = PlusDamage;
		}

		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect1))
		{
			SelectedObject = Box;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect2))
		{
			SelectedObject = TestHouse;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect3))
		{
			SelectedObject = Building;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect4))
		{
			SelectedObject = MapTemplate;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect5))
		{
			SelectedObject = PlusSteal;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect6))
		{
			SelectedObject = P1;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect7))
		{
			SelectedObject = P2;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect8))
		{
			SelectedObject = P3;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect9))
		{
			SelectedObject = P4;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorSelect0))
		{
			SelectedObject = P5;
		}
		else if (IsKeyPressed(EditorBlade))
		{
			SelectedObject = Blade;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorPlayerRespawn))
		{
			SelectedObject = PlayerRespawn;
		}
		else if (IsKeyDown(Mod) && IsKeyPressed(EditorPlayerRespawnToggle))
		{
			SelectedObject = PlayerRespawnToggle;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorEnemyRespawn))
		{
			SelectedObject = EnemyRespawn;
		}
		else if (!IsKeyDown(Mod) && IsKeyPressed(EditorEnemyRespawnToggle))
		{
			SelectedObject = EnemyRespawnToggle;
		}

		if (IsMouseButtonDown(EditorPlaceTile))
		{
				for (int i = 0; i < 511; i++)
				{
					for (int j = 0; j < 511; j++)
					{
						if (EditorCursorX > (i * 320) - ((320 / 2) / BrushSize) &&
							EditorCursorX < (i * 320) + ((320 / 2) / BrushSize) &&
							EditorCursorY > (j * 320) - ((320 / 2) / BrushSize) &&
							EditorCursorY < (j * 320) + ((320 / 2) / BrushSize))
						{
							switch (SelectedObject)
							{
							case Delete:
								for (int i = 0; i < NumberOfObjects; i++)
								{
									if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
									{
										ObjectFile.MapObjects[i][0] = 0;
										ObjectFile.MapObjects[i][1] = 0;
										ObjectFile.MapObjects[i][2] = 0;
										ObjectFile.MapObjects[i][3] = 0;
										ObjectFile.MapObjects[i][4] = 0;
										ObjectFile.MapObjects[i][5] = 0;
										ObjectFile.MapObjects[i][6] = 0;
										ObjectFile.MapObjects[i][7] = 0;
										ObjectFile.MapObjects[i][8] = 0;
										ObjectFile.MapObjects[i][9] = 0;
										ObjectFile.MapObjects[i][10] = 0;
										ObjectFile.MapObjects[i][11] = 0;
										ObjectFile.MapObjects[i][12] = 0;
										ObjectFile.MapObjects[i][13] = 0;
										ObjectFile.MapObjects[i][14] = 0;
										ObjectFile.MapObjects[i][15] = 0;
									}
								}
								break;
							case Desert:
								MapTiles[i][j] = 0;
								break;
							case Grass:
								MapTiles[i][j] = 1;
								break;
							case Water:
								MapTiles[i][j] = 2;
								break;
							case Brick:
								MapTiles[i][j] = 3;
								break;
							case Tree:
								MapTiles[i][j] = 4;
								break;
							case Stone:
								MapTiles[i][j] = 5;
								break;
							}
						}
					}
				}
		}
		if (IsMouseButtonPressed(EditorPlaceObject))
		{
			switch (SelectedObject)
			{
			case Delete:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						ObjectFile.MapObjects[i][0] = 0;
						ObjectFile.MapObjects[i][1] = 0;
						ObjectFile.MapObjects[i][2] = 0;
						ObjectFile.MapObjects[i][3] = 0;
						ObjectFile.MapObjects[i][4] = 0;
						ObjectFile.MapObjects[i][5] = 0;
						ObjectFile.MapObjects[i][6] = 0;
						ObjectFile.MapObjects[i][7] = 0;
						ObjectFile.MapObjects[i][8] = 0;
						ObjectFile.MapObjects[i][9] = 0;
						ObjectFile.MapObjects[i][10] = 0;
						ObjectFile.MapObjects[i][11] = 0;
						ObjectFile.MapObjects[i][12] = 0;
						ObjectFile.MapObjects[i][13] = 0;
						ObjectFile.MapObjects[i][14] = 0;
						ObjectFile.MapObjects[i][15] = 0;
					}
				}
				break;
			case Collison:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][4])
						{
						case 0:
							ObjectFile.MapObjects[i][4] = 1;
							ObjectFile.MapObjects[i][8] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][4] = 0;
							ObjectFile.MapObjects[i][8] = 0;
							break;
						}
					}
				}
			case EnemyCollision:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][11])
						{
						case 0:
							ObjectFile.MapObjects[i][11] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][11] = 0;
							break;
						}
					}
				}
				break;
			case DrawObject:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][5])
						{
						case 0:
							ObjectFile.MapObjects[i][5] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][5] = 0;
							break;
						}
					}
				}
				break;
			case Damage:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][6])
						{
						case 0:
							ObjectFile.MapObjects[i][6] = 1;
							ObjectFile.MapObjects[i][7] = BrushSize * 100;
							break;
						default:
							ObjectFile.MapObjects[i][6] = 0;
							ObjectFile.MapObjects[i][7] = 0;
							break;
						}
					}
				}
				break;
			case BulletCollison:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][8])
						{
						case 0:
							ObjectFile.MapObjects[i][8] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][8] = 0;
							break;
						}
					}
				}
				break;

			case Global:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][12])
						{
						case 0:
							ObjectFile.MapObjects[i][12] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][12] = 0;
							break;
						}
					}
				}
				break;

			case Freeze:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i))
					{
						switch ((int)ObjectFile.MapObjects[i][0])
						{
						case 0:
							ObjectFile.MapObjects[i][0] = 1;
							break;
						default:
							ObjectFile.MapObjects[i][0] = 0;
							break;
						}
					}
				}
				break;

			case RotateRight:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][13])
						{
						case 0:
							ObjectFile.MapObjects[i][13] = BrushSize * 10;
							break;
						default:
							ObjectFile.MapObjects[i][13] = 0;
							break;
						}
					}
				}
				break;

			case RotateLeft:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						switch ((int)ObjectFile.MapObjects[i][13])
						{
						case 0:
							ObjectFile.MapObjects[i][13] = BrushSize * 10 * -1;
							break;
						default:
							ObjectFile.MapObjects[i][13] = 0;
							break;
						}
					}
				}
				break;

			case PlusHealth:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 1;
						}
					}
				}
				break;
			case PlusSpeed:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 2;
						}
					}
				}
				break;
			case PlusBulletSpeed:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 3;
						}
					}
				}
				break;
			case PlusDamage:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 4;
						}
					}
				}
				break;
			case PlusSteal:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 5;
						}
					}
				}
				break;
			case PlayerRespawnToggle:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 7;
						}
					}
				}
				break;
			case EnemyRespawnToggle:
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (CheckCollisionsEditor(i) && ObjectFile.MapObjects[i][0] == 0)
					{
						if ((int)ObjectFile.MapObjects[i][15] != 0)
						{
							ObjectFile.MapObjects[i][15] = 0;
						}
						else
						{
							ObjectFile.MapObjects[i][15] = 6;
						}
					}
				}
				break;

			case Box:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 1;
						ObjectFile.MapObjects[i][9] = BoxWidth;
						ObjectFile.MapObjects[i][10] = BoxHeight;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case TestHouse:
				
				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 10;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case Building:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 11;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case EnemyRespawn:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 12;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case MapTemplate:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 13;

						i = NumberOfObjects + 1;
					}
				}
				break;

			case P1:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 14;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case P2:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 15;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case P3:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 16;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case P4:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 17;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case P5:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 18;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case Blade:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 19;

						i = NumberOfObjects + 1;
					}
				}
				break;
			case PlayerRespawn:

				for (int i = 0; i < NumberOfObjects; i++)
				{
					if (ObjectFile.MapObjects[i][3] == 0)
					{
						ObjectFile.MapObjects[i][1] = EditorCursorX;
						ObjectFile.MapObjects[i][2] = EditorCursorY;
						ObjectFile.MapObjects[i][3] = 20;

						i = NumberOfObjects + 1;
					}
				}
				break;
			}
		}

		break;
	}
}

void Logic()
{
	switch (GameState)
	{
	case Play:

		if (CursorReset)
		{
			CursorReset = false;
			CursorX = Player.X;
			CursorY = Player.Y;
		}

		if (Player.bulletsound < 0.25)
		{
			Player.bulletsound += GetFrameTime();
		}

		if (!IsSoundPlaying(Sounds[4]))
		{
			PlaySound(Sounds[4]);
		}

		if (!IsSoundPlaying(Sounds[5]) && !Mute)
		{
			PlaySound(Sounds[5]);
		}
		else if (Mute)
		{
			StopSound(Sounds[5]);
		}


		if (Player.Health <= 0)
		{
			PlaySound(Sounds[3]);
			GameState = GameOver;
			PauseSound(Sounds[4]);
			PauseSound(Sounds[5]);
		}

		SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);

		if (Player.SpeedX > 0 && !IsKeyDown(MoveLeft))
		{
			Player.SpeedX -= Player.Drag * GetFrameTime();
		}
		else if (Player.SpeedX < 0 && !IsKeyDown(MoveRight))
		{
			Player.SpeedX += Player.Drag * GetFrameTime();
		}
		if (Player.SpeedY < 0 && !IsKeyDown(MoveUp))
		{
			Player.SpeedY += Player.Drag * GetFrameTime();
		}
		else if (Player.SpeedY > 0 && !IsKeyDown(MoveDown))
		{
			Player.SpeedY -= Player.Drag * GetFrameTime();
		}

		if (Player.SpeedX > Player.MaxSpeed)
		{
			Player.SpeedX = Player.MaxSpeed;
		}
		else if (Player.SpeedX < Player.MaxSpeed * -1)
		{
			Player.SpeedX = Player.MaxSpeed * -1;
		}
		if (Player.SpeedY > Player.MaxSpeed)
		{
			Player.SpeedY = Player.MaxSpeed;
		}
		else if (Player.SpeedY < Player.MaxSpeed * -1)
		{
			Player.SpeedY = Player.MaxSpeed * -1;
		}

		if (Player.X < 4000)
		{
			Player.X = 4000;
			Player.SpeedX = 0;
		}
		else if (Player.X > WorldSize - 4000)
		{
			Player.X = WorldSize - 4000;
			Player.SpeedX = 0;
		}
		if (Player.Y < 4000)
		{
			Player.Y = 4000;
			Player.SpeedY = 0;
		}
		else if (Player.Y > WorldSize - 4000)
		{
			Player.Y = WorldSize - 4000;
			Player.SpeedY = 0;
		}

		for (int i = 0; i < NumberOfObjects; i++)
		{
			if (ObjectFile.MapObjects[i][1] > Player.X - Objects[(int)ObjectFile.MapObjects[i][3]][5] &&
				ObjectFile.MapObjects[i][1] < Player.X + Objects[(int)ObjectFile.MapObjects[i][3]][5] &&
				ObjectFile.MapObjects[i][2] > Player.Y - Objects[(int)ObjectFile.MapObjects[i][3]][6] &&
				ObjectFile.MapObjects[i][2] < Player.Y + Objects[(int)ObjectFile.MapObjects[i][3]][6] &&
				ObjectFile.MapObjects[i][3] >= 10)
			{
				PowerUp.PickUp(i);
				if (ObjectFile.MapObjects[i][6] != 0 && Player.CanTakeDamage)
				{
					switch ((int)ObjectFile.MapObjects[i][4])
					{
					case 0:
							if (CheckCollisionCircleRec(Vector2{ Player.X,Player.Y }, Player.Size, Rectangle{
								ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2),
								ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2),
								Objects[(int)ObjectFile.MapObjects[i][3]][5],
								Objects[(int)ObjectFile.MapObjects[i][3]][6] }))
							{
								Player.Health -= ObjectFile.MapObjects[i][7];
								Player.CanTakeDamage = false;
							}
						break;
					default:
						switch ((int)ObjectFile.MapObjects[i][13])
						{
						case 0:
							if (CheckCollisionPointRec(Vector2{ Player.X,Player.Y }, Rectangle{
								ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2),
								ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2),
								Objects[(int)ObjectFile.MapObjects[i][3]][5],
								Objects[(int)ObjectFile.MapObjects[i][3]][6] }))
							{
								Player.Health -= ObjectFile.MapObjects[i][7];
								Player.CanTakeDamage = false;
							}
							break;
						default:
							if (CheckCollisionPointCircle(Vector2{ Player.X,Player.Y }, Vector2{ ObjectFile.MapObjects[i][1],ObjectFile.MapObjects[i][2] }, (Objects[(int)ObjectFile.MapObjects[i][3]][6]) / 2))
							{
								Player.Health -= ObjectFile.MapObjects[i][7];
								Player.CanTakeDamage = false;
							}
						}
					}
				}
				if (ObjectFile.MapObjects[i][4] == 0)
				{
					while (CheckCollisionCircleRec(Vector2{ Player.X, Player.Y }, Player.Size,
						Rectangle{
							ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2),
							ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2),
							Objects[(int)ObjectFile.MapObjects[i][3]][5],
							Objects[(int)ObjectFile.MapObjects[i][3]][6] }))
					{
						if (Player.PX > ObjectFile.MapObjects[i][1] + (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2))
						{
							Player.SpeedX = 0;
							Player.X += 1;
							CursorX += 1;
						}
						else if (Player.PX < ObjectFile.MapObjects[i][1] - (Objects[(int)ObjectFile.MapObjects[i][3]][5] / 2))
						{
							Player.SpeedX = 0;
							Player.X -= 1;
							CursorX -= 1;
						}
						if (Player.PY > ObjectFile.MapObjects[i][2] + (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2))
						{
							Player.SpeedY = 0;
							Player.Y += 1;
							CursorY += 1;
						}
						else if (Player.PY < ObjectFile.MapObjects[i][2] - (Objects[(int)ObjectFile.MapObjects[i][3]][6] / 2))
						{
							Player.SpeedY = 0;
							Player.Y -= 1;
							CursorY -= 1;
						}
					}
				}
			}

			else if (ObjectFile.MapObjects[i][1] > Player.X - ObjectFile.MapObjects[i][9] &&
				ObjectFile.MapObjects[i][1] < Player.X + ObjectFile.MapObjects[i][9] &&
				ObjectFile.MapObjects[i][2] > Player.Y - ObjectFile.MapObjects[i][10] &&
				ObjectFile.MapObjects[i][2] < Player.Y + ObjectFile.MapObjects[i][10] &&
				ObjectFile.MapObjects[i][3] == 1 &&
				ObjectFile.MapObjects[i][4] == 0)
			{
				while (CheckCollisionCircleRec(Vector2{ Player.X, Player.Y }, Player.Size,
					Rectangle{
						ObjectFile.MapObjects[i][1] - ObjectFile.MapObjects[i][9] / 2,
						ObjectFile.MapObjects[i][2] - ObjectFile.MapObjects[i][10] / 2,
						ObjectFile.MapObjects[i][9],
						ObjectFile.MapObjects[i][10] }))
				{
					if (Player.PX > ObjectFile.MapObjects[i][1] + ObjectFile.MapObjects[i][9] / 2)
					{
						Player.SpeedX = 0;
						Player.X += 1;
						CursorX += 1;
					}
					else if (Player.PX < ObjectFile.MapObjects[i][1] - ObjectFile.MapObjects[i][9] / 2)
					{
						Player.SpeedX = 0;
						Player.X -= 1;
						CursorX -= 1;
					}
					if (Player.PY > ObjectFile.MapObjects[i][2] + ObjectFile.MapObjects[i][10] / 2)
					{
						Player.SpeedY = 0;
						Player.Y += 1;
						CursorY += 1;
					}
					else if (Player.PY < ObjectFile.MapObjects[i][2] - ObjectFile.MapObjects[i][10] / 2)
					{
						Player.SpeedY = 0;
						Player.Y -= 1;
						CursorY -= 1;
					}
				}
			}
		}

		Player.PX = Player.X;
		Player.PY = Player.Y;

		Player.X += Player.SpeedX * GetFrameTime();
		Player.Y += Player.SpeedY * GetFrameTime();



		if (!CursorTrack)
		{
			CursorX += Player.SpeedX * GetFrameTime();
			CursorY += Player.SpeedY * GetFrameTime();
		}

		if (CursorX > Player.X + 1500 / GameCamera.zoom)
		{
			CursorX = Player.X + 1500 / GameCamera.zoom;
		}
		if (CursorX < Player.X - 1500 / GameCamera.zoom)
		{
			CursorX = Player.X - 1500 / GameCamera.zoom;
		}
		if (CursorY > Player.Y + 800 / GameCamera.zoom)
		{
			CursorY = Player.Y + 800 / GameCamera.zoom;
		}
		if (CursorY < Player.Y - 800 / GameCamera.zoom)
		{
			CursorY = Player.Y - 800 / GameCamera.zoom;
		}

		if (!Player.BulletCanFire)
		{
			Player.BulletFireTimer += GetFrameTime();
		}
		if (Player.BulletFireTimer >= Player.BulletFireRate)
		{
			Player.BulletCanFire = true;
		}

		for (int i = 0; i < Player.BulletMax; i++)
		{
			if (Player.BulletTime[i] <= Player.BulletLifeTime)
			{
				Player.BulletTime[i] += GetFrameTime();

				if (Player.BulletType[i] == 0)
				{
					Player.BulletX[i] = (cos(Player.BulletRotationRad[i]) * (Player.BulletSpeed0 * Player.BulletTime[i]))
						+ Player.BulletOriginX[i];
					Player.BulletY[i] = (sin(Player.BulletRotationRad[i]) * (Player.BulletSpeed0 * Player.BulletTime[i]))
						+ Player.BulletOriginY[i];
				}
				else if (Player.BulletType[i] = 1)
				{
					Player.BulletX[i] = (cos(Player.BulletRotationRad[i]) * (Player.BulletSpeed1 * Player.BulletTime[i]))
						+ Player.BulletOriginX[i];
					Player.BulletY[i] = (sin(Player.BulletRotationRad[i]) * (Player.BulletSpeed1 * Player.BulletTime[i]))
						+ Player.BulletOriginY[i];
				}

				for (int j = 0; j < NumberOfObjects; j++)
				{
					if (ObjectFile.MapObjects[j][1] > Player.BulletX[i] - 2000 &&
						ObjectFile.MapObjects[j][1] < Player.BulletX[i] + 2000 &&
						ObjectFile.MapObjects[j][2] > Player.BulletY[i] - 2000 &&
						ObjectFile.MapObjects[j][2] < Player.BulletY[i] + 2000 &&
						ObjectFile.MapObjects[j][8] == 0)
					{
						if (ObjectFile.MapObjects[j][3] != 1)
						{
							if (CheckCollisionCircleRec(Vector2{ Player.BulletX[i], Player.BulletY[i] }, Player.BulletSize,
								Rectangle{
									ObjectFile.MapObjects[j][1] - (Objects[(int)ObjectFile.MapObjects[j][3]][5] / 2),
									ObjectFile.MapObjects[j][2] - (Objects[(int)ObjectFile.MapObjects[j][3]][6] / 2),
									Objects[(int)ObjectFile.MapObjects[j][3]][5],
									Objects[(int)ObjectFile.MapObjects[j][3]][6] }))
							{
								Player.BulletTime[i] = Player.BulletLifeTime + 1;
							}
						}
						else
						{
							if (CheckCollisionCircleRec(Vector2{ Player.BulletX[i], Player.BulletY[i] }, 5,
								Rectangle{
									ObjectFile.MapObjects[j][1] - ObjectFile.MapObjects[j][9] / 2,
									ObjectFile.MapObjects[j][2] - ObjectFile.MapObjects[j][10] / 2,
									ObjectFile.MapObjects[j][9],
									ObjectFile.MapObjects[j][10] }))
							{
								Player.BulletTime[i] = Player.BulletLifeTime + 1;
							}
						}
					}
				}
			}
		}

		if (Player.CanTakeDamage == false)
		{
			Player.DamageDelay += GetFrameTime();
			if (Player.DamageDelay >= Player.DamageDelayMax)
			{
				Player.DamageDelay = 0;
				Player.CanTakeDamage = true;
			}
		}

		Spartan.Logic();

		break;

	case Pause:

		Options.Logic();

		break;

	case Start:

		StartScreen.Logic();

		break;

	case GameOver:

		GameOverScreen.Logic();

		break;

	case LevelEditor:



		break;
	}
}

void Draw()
{

	AnimationTimer += GetFrameTime();
	if (AnimationTimer > 10)
	{
		AnimationTimer -= 10;
	}

	BeginDrawing();
	ClearBackground(BLACK);

	switch (GameState)
	{
	case Play:

		BeginMode2D(GameCamera);

		GameCamera.target = Vector2{ Player.X + (CursorX - Player.X) / 2, Player.Y + (CursorY - Player.Y) / 2 };

		Level.DrawMap();

		for (int i = 0; i < Player.BulletMax; i++)
		{
			if (Player.BulletTime[i] <= Player.BulletLifeTime)
			{
				if (Player.BulletType[i] == 0)
				{
					DrawTexturePro(Textures[1], Rectangle{ 79,
															48,
															18,
															30 },
						Rectangle{ Player.BulletX[i], Player.BulletY[i], 36,
															60 },
						Vector2{ 36 / 2,
						60 / 2 }, Player.BulletRotation[i], WHITE);
				}
				else if (Player.BulletType[i] == 1)
				{
					DrawTexturePro(Textures[1], Rectangle{ 42,
															109,
															9,
															9 },
						Rectangle{ Player.BulletX[i], Player.BulletY[i], 100,
															100 },
						Vector2{ 100 / 2,
						100 / 2 }, Player.BulletRotation[i], WHITE);
				}
			}
		}

		for (int i = 0; i < Spartan.BulletMax; i++)
		{
			if (Spartan.BulletTime[i] <= Spartan.BulletLifeTime)
			{
				DrawTexturePro(Textures[1], Rectangle{ (float)Spartan.BulletTextureCoordinates[0],
														(float)Spartan.BulletTextureCoordinates[1],
														(float)Spartan.BulletTextureCoordinates[2],
														(float)Spartan.BulletTextureCoordinates[3] },
					Rectangle{ Spartan.BulletX[i], Spartan.BulletY[i], (float)Spartan.BulletTextureCoordinates[4],
														(float)Spartan.BulletTextureCoordinates[5] },
					Vector2{ (float)Spartan.BulletTextureCoordinates[4] / 2,
					(float)Spartan.BulletTextureCoordinates[5] / 2 }, Spartan.BulletRotation[i], WHITE);
			}
		}

		for (int i = 0; i < 199; i++)
		{
			if (Spartan.Health[i] > 0)
			{
				switch ((int)Spartan.Type[i])
				{
				case 0:
					DrawTexturePro(Textures[9], Rectangle{ 0,0,900,863 },
						Rectangle{ Spartan.X[i], Spartan.Y[i], 150, 150 }, Vector2{ 150 / 2,  150 / 2 }, 0, WHITE);
					break;
				case 1:
					DrawTexturePro(Textures[10], Rectangle{ 0,0,320,707 },
						Rectangle{ Spartan.X[i], Spartan.Y[i], 150, 150 }, Vector2{ 150 / 2,  150 / 2 }, 0, WHITE);
					break;
				case 2:
					DrawTexturePro(Textures[9], Rectangle{ 0,0,900,863 },
						Rectangle{ Spartan.X[i], Spartan.Y[i], 150, 150 }, Vector2{ 150 / 2,  150 / 2 }, 0, GREEN);
					break;
				}
			}
		}

		DrawTexturePro(Textures[2], Rectangle{ 0,0,150,150 },
			Rectangle{ Player.X, Player.Y, 150, 150 }, Vector2{ 150 / 2,  150 / 2 - 12 }, Player.Rotation, WHITE);
		DrawTexturePro(Textures[7], Rectangle{ 0,0,150,150 },
			Rectangle{ Player.X, Player.Y, 150, 150 }, Vector2{ 150 / 2,  150 / 2 - 12 }, Player.Rotation + Player.RotorRotation, WHITE);

		Player.RotorRotation += 255 * 360 * GetFrameTime();

		if (Player.RotorRotation > 360)
		{
			Player.RotorRotation -= 360;
		}

		DrawTexturePro(Textures[4], Rectangle{ 0,0,576, 576 },
			Rectangle{ CursorX, CursorY, 100, 100 }, Vector2{ 100 / 2, 100 / 2 }, 0, WHITE);


		EndMode2D();

		DrawRectangle(5, 5, 240, 30, BLACK);
		DrawText(TextFormat("Score %i", (int)Player.Score), 10, 10, 25, GREEN);
		DrawRectangle(5,35,200,30,BLACK);
		DrawText(TextFormat("HP %i", (int) Player.Health), 10, 40, 25, GREEN);
		DrawRectangle(5, 65, 160, 30, BLACK);
		DrawText(TextFormat("Wave %i", (int)Spartan.wave), 10, 70, 25, GREEN);

		if (Spartan.Respawn == false)
		{
			DrawRectangle(5, 65, 160, 30, BLACK);
			DrawText("Respawn off", 10, 70, 25, GREEN);
		}
		if (!ShowHidden)
		{
			DrawRectangle(5, 100, 160, 30, BLACK);
			DrawText("Show Hidden", 10, 100, 25, GREEN);
		}

		break;

	case Pause:

		Options.Draw();

		break;

	case Start:

		StartScreen.Draw();

		break;

	case GameOver:

		GameOverScreen.Draw();

		break;

	case LevelEditor:

		BeginMode2D(GameCamera);

		Level.DrawMap();


		if (ShowPlayer)
		{
			for (int i = 0; i < 199; i++)
			{
				DrawCircle((int)Spartan.X[i], (int)Spartan.Y[i], (int)Spartan.Size, RED);
			}

			DrawTexturePro(Textures[2], Rectangle{ 0,0,150,150 },
				Rectangle{ Player.X, Player.Y, 150, 150 }, Vector2{ 150 / 2,  150 / 2 - 12 }, Player.Rotation, WHITE);
		}

		if (Preview)
		{
			switch (SelectedObject)
			{
			case Box:
				DrawRectangle(
						EditorCursorX - BoxWidth / 2,
						EditorCursorY - BoxHeight / 2,
						BoxWidth,
						BoxHeight,
						RED);
				break;
			case TestHouse:
				DrawTexturePro(Textures[(int)Objects[10][8]],

					Rectangle{
					Objects[10][1],
					Objects[10][2],
					Objects[10][3],
					Objects[10][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[10][5],
					Objects[10][6] },
					Vector2{
					Objects[10][5] / 2,
					Objects[10][6] / 2 },
					Objects[10][7],
					WHITE);
				break;
			case Building:
				DrawTexturePro(Textures[(int)Objects[11][8]],

					Rectangle{
					Objects[11][1],
					Objects[11][2],
					Objects[11][3],
					Objects[11][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[11][5],
					Objects[11][6] },
					Vector2{
					Objects[11][5] / 2,
					Objects[11][6] / 2 },
					Objects[11][7],
					WHITE);
				break;
			case EnemyRespawn:
				DrawTexturePro(Textures[(int)Objects[12][8]],

					Rectangle{
					Objects[12][1],
					Objects[12][2],
					Objects[12][3],
					Objects[12][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[12][5],
					Objects[12][6] },
					Vector2{
					Objects[12][5] / 2,
					Objects[12][6] / 2 },
					Objects[12][7],
					WHITE);
				break;
			case MapTemplate:
				DrawTexturePro(Textures[(int)Objects[13][8]],

					Rectangle{
					Objects[13][1],
					Objects[13][2],
					Objects[13][3],
					Objects[13][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[13][5],
					Objects[13][6] },
					Vector2{
					Objects[13][5] / 2,
					Objects[13][6] / 2 },
					Objects[13][7],
					WHITE);
				break;

			case P1:
				DrawTexturePro(Textures[(int)Objects[14][8]],

					Rectangle{
					Objects[14][1],
					Objects[14][2],
					Objects[14][3],
					Objects[14][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[14][5],
					Objects[14][6] },
					Vector2{
					Objects[14][5] / 2,
					Objects[14][6] / 2 },
					Objects[14][7],
					WHITE);
				break;
			case P2:
				DrawTexturePro(Textures[(int)Objects[15][8]],

					Rectangle{
					Objects[15][1],
					Objects[15][2],
					Objects[15][3],
					Objects[15][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[15][5],
					Objects[15][6] },
					Vector2{
					Objects[15][5] / 2,
					Objects[15][6] / 2 },
					Objects[15][7],
					WHITE);
				break;
			case P3:
				DrawTexturePro(Textures[(int)Objects[16][8]],

					Rectangle{
					Objects[16][1],
					Objects[16][2],
					Objects[16][3],
					Objects[16][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[16][5],
					Objects[16][6] },
					Vector2{
					Objects[16][5] / 2,
					Objects[16][6] / 2 },
					Objects[16][7],
					WHITE);
				break;
			case P4:
				DrawTexturePro(Textures[(int)Objects[17][8]],

					Rectangle{
					Objects[17][1],
					Objects[17][2],
					Objects[17][3],
					Objects[17][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[17][5],
					Objects[17][6] },
					Vector2{
					Objects[17][5] / 2,
					Objects[17][6] / 2 },
					Objects[17][7],
					WHITE);
				break;
			case P5:
				DrawTexturePro(Textures[(int)Objects[18][8]],

					Rectangle{
					Objects[18][1],
					Objects[18][2],
					Objects[18][3],
					Objects[18][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[18][5],
					Objects[18][6] },
					Vector2{
					Objects[18][5] / 2,
					Objects[18][6] / 2 },
					Objects[18][7],
					WHITE);
				break;
			case Blade:
				DrawTexturePro(Textures[(int)Objects[19][8]],

					Rectangle{
					Objects[19][1],
					Objects[19][2],
					Objects[19][3],
					Objects[19][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[19][5],
					Objects[19][6] },
					Vector2{
					Objects[19][5] / 2,
					Objects[19][6] / 2 },
					Objects[19][7],
					WHITE);
				break;
			case PlayerRespawn:
				DrawTexturePro(Textures[(int)Objects[20][8]],

					Rectangle{
					Objects[20][1],
					Objects[20][2],
					Objects[20][3],
					Objects[20][4] },

					Rectangle{
					EditorCursorX,
					EditorCursorY,
					Objects[20][5],
					Objects[20][6] },
					Vector2{
					Objects[20][5] / 2,
					Objects[20][6] / 2 },
					Objects[20][7],
					WHITE);
				break;
			}
		}

		DrawTexturePro(Textures[4], Rectangle{ 0,0,576, 576 },
			Rectangle{ EditorCursorX, EditorCursorY, 100 / GameCamera.zoom, 100 / GameCamera.zoom }, 
			Vector2{ (100 / GameCamera.zoom)/ 2, (100 / GameCamera.zoom) / 2 }, 0, WHITE);


		EndMode2D();

		DrawRectangle(0, 0, GetScreenWidth(), 40, BLACK);

		if (SnapToGrid)
		{
			DrawText("Grid", 500, 10, 25, GREEN);
		}
		if (!ShowHidden)
		{
			DrawText("Hidden", 600, 10, 25, GREEN);
		}
		if (!ShowPlayer)
		{
			DrawText("Units", 700, 10, 25, GREEN);
		}

		switch (SelectedObject)
		{
		case Delete:
			DrawText("Delete", 10, 10, 25, GREEN);
		break;
		case Collison:
			DrawText("Collison", 10, 10, 25, GREEN);
		break;
		case BulletCollison:
			DrawText("Bullet Collison", 10, 10, 25, GREEN);
		break;
		case EnemyCollision:
			DrawText("Enemy Collison", 10, 10, 25, GREEN);
		break;
		case DrawObject:
			DrawText("Draw", 10, 10, 25, GREEN);
		break;
		case Damage:
			DrawText("Damage", 10, 10, 25, GREEN);
		break;
		case Freeze:
			DrawText("Freeze", 10, 10, 25, GREEN);
		break;
		case Global:
			DrawText("Global", 10, 10, 25, GREEN);
		break;
		case RotateRight:
			DrawText("Rotate R", 10, 10, 25, GREEN);
		break;
		case RotateLeft:
			DrawText("Rotate L", 10, 10, 25, GREEN);
		break;
		case PlusHealth:
			DrawText("Plus Health", 10, 10, 25, GREEN);
		break;
		case PlusSpeed:
			DrawText("Plus Speed", 10, 10, 25, GREEN);
		break;
		case PlusBulletSpeed:
			DrawText("Plus B Speed", 10, 10, 25, GREEN);
		break;
		case PlusDamage:
			DrawText("Plus Damage", 10, 10, 25, GREEN);
		break;
		case PlusSteal:
			DrawText("Plus Steal", 10, 10, 25, GREEN);
		break;
		case EnemyRespawnToggle:
			DrawText("E Respawn Point", 10, 10, 25, GREEN);
		break;
		case PlayerRespawnToggle:
			DrawText("P Respawn Point", 10, 10, 25, GREEN);
		break;

		case Desert:
			DrawText("Desert", 10, 10, 25, GREEN);
			break;
		case Grass:
			DrawText("Grass", 10, 10, 25, GREEN);
			break;
		case Water:
			DrawText("Water", 10, 10, 25, GREEN);
			break;
		case Brick:
			DrawText("Brick", 10, 10, 25, GREEN);
		break;
		case Tree:
			DrawText("Tree", 10, 10, 25, GREEN);
		break;
		case Stone:
			DrawText("Stone", 10, 10, 25, GREEN);
		break;

		case Box:
			DrawText("Box", 10, 10, 25, GREEN);
			DrawText(TextFormat("%i", (int)BoxWidth), 300, 10, 25, GREEN);
			DrawText(TextFormat("%i", (int)BoxHeight), 400, 10, 25, GREEN);
			break;
		case TestHouse:
			DrawText("TestHouse", 10, 10, 25, GREEN);
		break;
		case Building:
			DrawText("Building", 10, 10, 25, GREEN);
		break;
		case EnemyRespawn:
			DrawText("EnemyRespawn", 10, 10, 25, GREEN);
		break;
		case MapTemplate:
			DrawText("MapTemplate", 10, 10, 25, GREEN);
		break;

		case P1:
			DrawText("P1", 10, 10, 25, GREEN);
			break;
		case P2:
			DrawText("P2", 10, 10, 25, GREEN);
			break;
		case P3:
			DrawText("P3", 10, 10, 25, GREEN);
			break;
		case P4:
			DrawText("P4", 10, 10, 25, GREEN);
			break;
		case P5:
			DrawText("P5", 10, 10, 25, GREEN);
			break;
		case Blade:
			DrawText("Blade", 10, 10, 25, GREEN);
			break;
		case PlayerRespawn:
			DrawText("PlayerRespawn", 10, 10, 25, GREEN);
			break;
		}

		if (SavedTimer < 1.25)
		{
			SavedTimer += GetFrameTime();

			DrawText("Saved", GetScreenWidth() - 60, 10, 25, GREEN);
		}

		DrawText(TextFormat("%i", (int)(BrushSize * 100)), 220, 10, 25, GREEN);

		break;
	}

	if (ShowFPS)
	{
		DrawRectangle(GetScreenWidth() - 105, 5, 100, 30, BLACK);
		DrawFPS(GetScreenWidth() - 90, 10);
	}

	EndDrawing();
}

int main()
{
	Spartan.Respawn = true;

	InitWindow(1600, 900, "Super Cool Helicopter Game");
	SetWindowState(FLAG_VSYNC_HINT);
	InitAudioDevice();
	Options.OpenOptionsFile();
	LoadResources();
	HideCursor();

	GameCamera.target = Vector2{ Player.X, Player.Y };
	GameCamera.offset = Vector2{(float) GetScreenWidth() / 2, (float) GetScreenHeight() / 2};
	GameCamera.zoom = 0.5;
	GameCamera.rotation = 0;

	SetExitKey(QuickExit);

	srand(time(0));

	ObjectFile.OpenMapFile();

	while (!WindowShouldClose() && !Desktop)
	{
		Controlls();
		Logic();
		Draw();
	}

	Options.CloseOptionsFile();

	EndMode2D();
	UnloadResources();
	CloseAudioDevice();
	CloseWindow();
}