//1 commit
//2 commit
//Pull commit
//3 commit
//Merge commit
//Fetch commit
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace sf;
using namespace std;
int ts = 54;
Vector2i otstup(48, 24);
struct piece
{
	int x, y, col, row, kind, match;
	piece(){ match = 0;}
} grid[10][10];

void swap(piece p1, piece p2)
{
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	grid[p1.row][p1.col] = p1;
	grid[p2.row][p2.col] = p2;
}
bool startgame(){
	bool game = true;
	bool zap = true;
	bool zap2 = true;
	int x0, y0, x, y; int click = 0; Vector2i pos;
	bool isSwap = false, isMoving = false;

	Font font;
	font.loadFromFile("source/1.ttf");
	Text text("", font, 25);
	text.setFillColor(Color::Black);
	Text rec("", font, 25);
	rec.setFillColor(Color::Black);
	Text lasttime("", font, 25);
	lasttime.setFillColor(Color::Black);
	Text help("", font, 25);
	help.setFillColor(Color::Black);
	Text rule("", font, 25);
	rule.setFillColor(Color::Black);

	RenderWindow app(VideoMode(740, 480), "3in1",Style::Close);
	app.setFramerateLimit(60);

	Image el;
	el.loadFromFile("source/gems.png");
	el.createMaskFromColor(Color(255, 255, 255));
	Texture back, texel,ruletx;
	back.loadFromFile("source/background.png");
	ruletx.loadFromFile("source/rule.png");
	texel.loadFromImage(el);
	Sprite background(back), gems(texel), rules(ruletx);
	float currentFrame = 0;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;
	//Çàïîëíåíèå ñëó÷àéíûìè ýëåìåíòàìè
	for (int i = 1; i <= 8; i++)
	for (int j = 1; j <= 8; j++)
	{
		grid[i][j].kind =1+ rand() % 6;
		grid[i][j].col = j;
		grid[i][j].row = i;
		grid[i][j].x = j*ts;
		grid[i][j].y = i*ts;
	}

	while (app.isOpen())
	{
		if (game = true) gameTime = gameTimeClock.getElapsedTime().asSeconds();
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed || (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape))
				return(false);
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::R)
				return(true);
			if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Right)

			{
				switch (zap){
				case true:
				{
							 char buff[100];
							 ifstream Save("save.txt");
							 lasttime.setString(L"Ïîñëåäíåå\nâðåìÿ\n");
							 lasttime.setPosition(500, 100);
							 Save.getline(buff, 50);
							 rec.setString(buff);
							 rec.setPosition(500, 170);
							 rule.setString(L"Íàæàòèåì íà  ËÊÌ âûáåðèòå\n ýëåìåíò. Òàêæå âûáåðèòå\n ýëåìåíò ñòîÿùèé ðÿäîì.\nÂàøà çàäà÷à ñîñòàâèòü òðè\n èëè áîëüøå ýëåìåíòîâ â ðÿä\nÓäà÷íîé èãðû ");
							 rule.setPosition(45,20);
							 rules.setPosition(0, 0);
							 zap = false;
							 break; }
				case false:
				{			  rule.setString(L"");
							  rec.setString("");
							  lasttime.setString("");
							  zap = true;
							  break; }
				}
			}
			if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Middle)
			{
				ofstream Save("save.txt");
				Save << gameTime;
				zap2 = false;
				Save.close();
			}

			if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left)
			{
				if (!isSwap && !isMoving) click++;
				pos = Mouse::getPosition(app) - otstup;
			}
		}

		//Ìûøü
		if (click == 1)
		{
			x0 = pos.x / ts + 1;
			y0 = pos.y / ts + 1;
		}
		if (click == 2)
		{
			x = pos.x / ts + 1;
			y = pos.y / ts + 1;
			{
				if (abs(x - x0) + abs(y - y0) == 1)
				{
					swap(grid[y0][x0], grid[y][x]); isSwap = 1; click = 0;
				}

				else click = 1;
			}
		}

		//Ïîèñê ñîâïàäåíèé
		for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			if (grid[i][j].kind == grid[i + 1][j].kind)
			if (grid[i][j].kind == grid[i - 1][j].kind)
			for (int n = -1; n <= 1; n++) grid[i + n][j].match++;
			if (grid[i][j].kind == grid[i][j + 1].kind)
			if (grid[i][j].kind == grid[i][j - 1].kind)
			for (int n = -1; n <= 1; n++) grid[i][j + n].match++;
		}
		//Àíèìàöèÿ
		isMoving = false;
		for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			piece &p = grid[i][j];
			int dx, dy;
			for (int n = 0; n < 5; n++)
			{
				dx = p.x - p.col*ts;
				dy = p.y - p.row*ts;
				if (dx) p.x -= dx / abs(dx);
				if (dy) p.y -= dy / abs(dy);
			}
			if (dx || dy) isMoving = 1;
		}

		//Âîçâðàò ýë-òà îáðàòíî
		int score = 0;
		for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
			score += grid[i][j].match;
		if (isSwap && !isMoving)
		{
			if (!score) swap(grid[y0][x0], grid[y][x]); isSwap = 0;
		}

		//Îáíîâëåíèå ïîëÿ
		if (!isMoving)
		{
			for (int i = 8; i > 0; i--)
			for (int j = 1; j <= 8; j++)
			if (grid[i][j].match)
			for (int n = i; n > 0; n--)
			if (!grid[n][j].match) { swap(grid[n][j], grid[i][j]); break; };

			for (int j = 1; j <= 8; j++)
			for (int i = 8, n = 0; i > 0; i--)
			if (grid[i][j].match)
			{
				grid[i][j].kind = rand() % 7;
				grid[i][j].y = -ts*n++;
				grid[i][j].match = 0;
			}
		}
		app.draw(background);
		help.setString(L"ÏÊÌ-Ïðàâèëà\nÑÊÌ-Çàïèñü\nR-Ðåñòàðò");
		help.setPosition(500, 200);
		ostringstream gameTimeString;
		gameTimeString << gameTime;
		text.setString(L"Âðåìÿ èãðû \n" + gameTimeString.str());
		text.setPosition(500, 50);
		app.draw(help);
		app.draw(text);
		app.draw(rec);
		app.draw(lasttime);
		for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++)
		{
			piece p = grid[i][j];
			gems.setTextureRect(IntRect((p.kind) * 49, 0, 49, 49));
			gems.setPosition(p.x, p.y);
			gems.move(otstup.x - ts, otstup.y - ts);
			app.draw(gems);
		}
		if (!zap){
			app.draw(rules);
			app.draw(rule);
		};
		app.display();
	}
}
void rungame(){
	if (startgame()){ rungame(); }
}
int main()
{	srand(time(0));
	rungame();
	return 0;
}
	

