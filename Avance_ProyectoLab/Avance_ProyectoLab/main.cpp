#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <time.h>
#include <Windows.h>



using namespace std;
using namespace sf;

int main() {
	int vidas=3;
	int puntos = 0;
	Font *fuente1;
	Text *txt_puntos,*txt_p,*txt_vidas;
	txt_puntos = new Text();
	txt_vidas = new Text();

	txt_p = new Text();
	fuente1 = new Font();
	txt_puntos->setFont(*fuente1);
	txt_p->setFont(*fuente1);
	txt_vidas->setFont(*fuente1);

	txt_puntos->setString(to_string(vidas));
	txt_p->setString("Puntos :");
	txt_vidas->setString("Vidas :");
	txt_puntos->setCharacterSize(20);
	txt_vidas->setCharacterSize(17);
	txt_p->setCharacterSize(20);
	txt_puntos->setPosition(480, 0);
	
	txt_p->setPosition(400, 0);
	fuente1->loadFromFile("fuente.ttf");
	
	
	srand(time(0));

	RenderWindow app(VideoMode(520, 450), "Brick Breaker!");
	app.setFramerateLimit(60);

	Texture t1, t2, t3, t4,t5;
	t1.loadFromFile("images/block02.png");
	t2.loadFromFile("images/newbackground.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");
	t5.loadFromFile("images/vidas.png");
	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 440);
	Sprite sprite1,sprite2,sprite3;
	sprite1.setTexture(t5);
	sprite1.setPosition(40, 2);
	sprite2.setTexture(t5);
	sprite2.setPosition(60, 2);
	
	sprite3.setTexture(t5);
	sprite3.setPosition(80, 2);
	sprite1.setScale(15.f/726, 15.f/720);
	sprite2.setScale(15.f / 726, 15.f / 720);
	sprite3.setScale(15.f / 726, 15.f / 720);
	Sprite block[1000];

	//// COMIENZA LA MUSICA
	sf::Music music;

	if (!music.openFromFile("BGsong.wav"))
	{
		cout << "ERROR" << endl;
	}

	music.play();
	//// TERMINA LA MUSICA

	// LOS SOUND EFFECTS
	sf::SoundBuffer buffer;

	if (!buffer.loadFromFile("hit2.wav"))
	{
		cout << "ERROR" << endl;
	}

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(75);
	//sound.play();

	// TERMINA SOUND EFFECTS

	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block[n].setTexture(t1);
			block[n].setPosition(i * 43, j * 20);
			n++;
		}
	if (n == 18) {
		return NULL;
	}

	float dx = 6, dy = 5;
	float x = 300, y = 300;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		x += dx;
		for (int i = 0; i<n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				block[i].setPosition(-100, 0); dx = -dx;
				puntos = puntos + 1;
				sound.play();
			}

		y += dy;
		for (int i = 0; i<n; i++)
			if (FloatRect(x + 3, y + 3, 6, 6).intersects(block[i].getGlobalBounds()))
			{
				
				block[i].setPosition(-100, 0); dy = -dy;
				puntos = puntos + 1;
				sound.play();
			}

		if (x < 0 || x>520) {
			dx = -dx;
			
		}

		else if (y > 450) {
			
			vidas = vidas - 1;
			if (vidas == 0) {

				MessageBox(NULL, "Has perdido dale Ok para jugar de nuevo", "Perdiste!", MB_OK);
				vidas = 3;
				puntos = 0;
				

				
			}
			dy = -dy;
		}

		else if (y < 0) {
			dy = -dy;
		}

		float limit = 79.f;
		//RIGHT
		if (Keyboard::isKeyPressed(Keyboard::Right) && (sPaddle.getPosition().x + sPaddle.getLocalBounds().width  <520)) {
			
			
			
			sPaddle.move(6, 0);

		}
		
		
		

		
		
		
		
		
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			(sPaddle.getPosition().x + sPaddle.getLocalBounds().width / 12 > 12.f))

			//left
			if (Keyboard::isKeyPressed(Keyboard::Left)) sPaddle.move(-6, 0);

		if (FloatRect(x, y, 12, 12).intersects(sPaddle.getGlobalBounds())) {
			dy = -(rand() % 5 + 2);
		}

		sBall.setPosition(x, y);

		app.clear();
		app.draw(sBackground);
		if(vidas==3){
		app.draw(sprite1);
		app.draw(sprite2);
		app.draw(sprite3);
		
		}else if (vidas == 2) {
			app.draw(sprite1);
			app.draw(sprite2);
			//app.draw(sprite3);
			
		}
		else if (vidas == 1) {
			app.draw(sprite1);
			//app.draw(sprite2);
			//app.draw(sprite3);
			
		}

		app.draw(*txt_puntos);
		app.draw(*txt_vidas);
		
		app.draw(sBall);
		app.draw(sPaddle);
		app.draw(*txt_p);
		txt_puntos->setString(to_string(puntos));
		for (int i = 0; i<n; i++)
			app.draw(block[i]);
	
		app.display();
	}

	return 0;
}
