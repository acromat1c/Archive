#include <raylib.h>

struct Ball
{
	int X, Y, SpeedX, SpeedY, Rad = 10;

	void Draw()
	{
		DrawCircle(X, Y, Rad, WHITE);
	}
};
struct Paddle
{
	int X, Y, Speed = 800, Height = 200, Width = 20, Score = 0;

	Rectangle GetRect()
	{
		return Rectangle{(float) X - Width / 2,(float) Y - Height / 2,(float) Width,(float) Height};
	}

	

	void Draw()
	{
		DrawRectangleRec(GetRect(), WHITE);
	}
};

struct AI
{
	bool AiActive = false;
	enum Direction {Up, Down, Stop};
	Direction Move;

	int AILogic(int BallY, int PaddleY)
	{
		if (AiActive && BallY <= (PaddleY + 50)  && BallY >= (PaddleY  - 50))
		{
			Move = Stop;
		}
		else if (AiActive && BallY < PaddleY)
		{
			Move = Down;
		}
		else if (AiActive && BallY > PaddleY)
		{
			Move = Up;
		}

		return Move;
	}
};

int main()
{
	char* winner = nullptr;
	bool winnerSide;
	bool RoundOver = false;
	bool PlayMusic = true;

	InitAudioDevice();

	InitWindow(1600, 900, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Sound Death = LoadSound("resources/Death_Sound.wav");
	SetSoundVolume(Death, 0.20);
	Sound GreenMan = LoadSound("resources/Darth_Sound.wav");
	SetSoundVolume(GreenMan, 1);
	Sound Hit = LoadSound("resources/hit.wav");
	SetSoundVolume(Hit, 0.50);
	Sound Music = LoadSound("resources/Super.wav");
	SetSoundVolume(Music, 0.50);

	Texture Yoda = LoadTexture("resources/Yoda_Image.png");
	Texture Darth = LoadTexture("resources/Darth_Image.png");

	AI Al;

	Ball ball;
	ball.X = GetScreenWidth() / 2;
	ball.Y = GetScreenHeight() / 2;
	ball.SpeedX = 600;
	ball.SpeedY = 0;

	Paddle left;
	left.X = 50;
	left.Y = GetScreenHeight() / 2;

	Paddle right;
	right.X = GetScreenWidth() - 50;
	right.Y = GetScreenHeight() / 2;

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_M))
		{
			switch (PlayMusic)
			{
			case true: PlayMusic = false;
				break;
			case false: PlayMusic = true;
				break;
			}
		}

		if (!IsSoundPlaying(Music) && PlayMusic)
		{
			PlaySound(Music);
		}
		else if (!PlayMusic)
		{
			StopSound(Music);
		}

		ball.X += ball.SpeedX * GetFrameTime();
		ball.Y += ball.SpeedY * GetFrameTime();

		if (ball.X >= GetScreenWidth() - 10)
		{
			winner = "Left Player Wins!";
			winnerSide = false;
		}
		else if (ball.X <= 0 + 10)
		{
			winnerSide = true;
			winner = "Right Player Wins!";

		}
		else if (ball.Y >= GetScreenHeight() - 10)
		{
			ball.Y = GetScreenHeight() - 10;
			ball.SpeedY *= -1;
		}
		else if (ball.Y <= 0 + 10)
		{
			ball.Y = 0 + 10;
			ball.SpeedY *= -1;
		}

		if (winner && !RoundOver && !winnerSide)
		{
			left.Score++;
			PlaySound(Death);
		}
		else if (winner && !RoundOver && winnerSide)
		{
			right.Score++;
			PlaySound(GreenMan);
		}

		if (IsKeyDown(KEY_W) && left.Y >= left.Height / 2)
		{
			left.Y -= left.Speed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_S) && left.Y <= GetScreenHeight() - left.Height / 2)
		{
			left.Y += left.Speed * GetFrameTime();
		}

		if (!RoundOver && Al.AILogic(ball.Y, right.Y) == Al.Down && right.Y >= right.Height / 2 || IsKeyDown(KEY_UP) && right.Y >= right.Height / 2)
		{
			right.Y -= right.Speed * GetFrameTime();
		}
		else if (!RoundOver && Al.AILogic(ball.Y, right.Y) == Al.Up && right.Y <= GetScreenHeight() - right.Height / 2 || IsKeyDown(KEY_DOWN) && right.Y <= GetScreenHeight() - right.Height / 2)
		{
			right.Y += right.Speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER))
		{
			ToggleFullscreen();
		}
		if (IsKeyPressed(KEY_ESCAPE))
		{
			WindowShouldClose();
		}
		if (IsKeyPressed(KEY_I))
		{
			switch (Al.AiActive)
			{
			case false: Al.AiActive = true;
				break;
			case true: Al.AiActive = false;
				break;
			}
		}

		if (CheckCollisionCircleRec(Vector2{(float) ball.X,(float) ball.Y }, ball.Rad, left.GetRect()))
		{
			if (ball.SpeedX < 0)
			{
				ball.SpeedX *= -1;
				ball.SpeedX += 50;
				ball.SpeedY = (((float)ball.Y - (float)left.Y) / ((float)left.Height / 2)) * ball.SpeedX;

				PlaySound(Hit);
			}	
		}
		else if (CheckCollisionCircleRec(Vector2{ (float)ball.X, (float)ball.Y }, ball.Rad, right.GetRect()))
		{
			if (ball.SpeedX > 0)
			{
				ball.SpeedX *= -1;
				ball.SpeedX += -50;
				ball.SpeedY = (((float)ball.Y - (float)right.Y) / ((float)right.Height / 2)) * (ball.SpeedX * -1);

				PlaySound(Hit);
			}
		}
		
		if (winner && IsKeyPressed(KEY_SPACE) || IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_SPACE))
		{
			ball.X = GetScreenWidth() / 2;
			ball.Y = GetScreenHeight() / 2;

			left.Y = GetScreenHeight() / 2;
			right.Y = GetScreenHeight() / 2;

			if (winner && !winnerSide)
			{
				ball.SpeedX = 600;
			}
			else
			{
				ball.SpeedX = -600;
			}
			ball.SpeedY = 0;

			winner = nullptr;
			RoundOver = false;
		}
		
		BeginDrawing();
			ClearBackground(BLACK);

			ball.Draw();
			left.Draw();
			right.Draw();

			int rightTextWidth = MeasureText(TextFormat("00%1", right.Score), 30);

			DrawText(TextFormat("%i", left.Score), 10, GetScreenHeight() - 30, 30, GREEN);
			DrawText(TextFormat("%i", right.Score), GetScreenWidth() - rightTextWidth - 10, GetScreenHeight() - 30, 30, GREEN);

			if (Al.AiActive)
			{
				DrawText("AI Active", GetScreenWidth() - 130, 40, 25, GREEN);
			}

			if (winner)
			{
			RoundOver = true;

			if (!winnerSide)
			{
				DrawTexture(Yoda, (GetScreenWidth() / 2) - (Yoda.width / 2), (GetScreenHeight() / 2) - (Yoda.height / 2) - 100, WHITE);
			} else if (winnerSide) {
				DrawTexture(Darth, (GetScreenWidth() / 2) - (Darth.width / 2), (GetScreenHeight() / 2) - (Darth.height / 2) - 100, WHITE);
			}
			float textWidth = MeasureText(winner, 60);
			DrawText(winner, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2, 60, GREEN);
			}
			DrawText("Pong", GetScreenWidth() - 80, 10, 25, GREEN);
			DrawFPS(10, 10);
		EndDrawing();
	}

	UnloadSound(Death);
	UnloadSound(GreenMan);
	UnloadSound(Hit);
	UnloadSound(Music);
	UnloadTexture(Yoda);
	UnloadTexture(Darth);
	
	CloseWindow();
	CloseAudioDevice();

	return 0;
}