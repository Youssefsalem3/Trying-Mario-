#include <SFML/Graphics.hpp>
#include<iostream>;
#include <SFML/Audio.hpp>
#include<sstream>
using namespace std;
using namespace sf;
int main()
{
	//menu decleration
	Sprite Menu;
	Texture menu;
	menu.loadFromFile("menu.jpg");
	Menu.setTexture(menu);
	Menu.setPosition(400, 50);
	Menu.setScale(0.5, 0.5);
	int screen = 0;

	//tunnels
	Sprite tun1;
	Sprite tun2;
	Texture tunr;
	Texture tunl;
	tunr.loadFromFile("tuno.png");
	tunl.loadFromFile("tuno2.png");
	tun1.setPosition(850, 630);
	tun1.setTexture(tunl);
	tun1.setScale(0.17, 0.17);
	tun2.setPosition(2000, 630);
	tun2.setTexture(tunr);
	tun2.setScale(0.17, 0.17);



	//animation req
	int cntx = 0, cnty = 0;
	double velocityY = 0;
	int score = 0;
	bool grounded = false;
	int enemcnt = 0;
	bool alive = 1;
	bool aliveenm = 1;
	bool jumpy = 0;
	bool right = 0;


	//background making
	Texture bgg;
	bgg.loadFromFile("mbg.png");
	RectangleShape bg[30];
	for (int i = 0; i < 30; i++)
	{
		bg[i].setTexture(&bgg);
		bg[i].setSize(Vector2f(1280, 720));
		bg[i].setPosition(i * 1280, 0);
	}


	//ground
	Texture mudd;
	mudd.loadFromFile("mud.png");
	RectangleShape mud;
	mud.setTexture(&mudd);
	mud.setSize(Vector2f(1200, 28));
	mud.setPosition(0, 692);
	//ground 2
	RectangleShape mud2;
	mud2.setTexture(&mudd);
	mud2.setSize(Vector2f(20000, 28));
	mud2.setPosition(1350, 692);


	//mario creation
	Sprite mario;
	mario.setScale(0.5, 0.5);
	Texture marioo;
	marioo.loadFromFile("anime12.png");
	mario.setTexture(marioo);
	mario.setTextureRect(IntRect(0, 0, 97, 143));
	mario.setPosition(280, 626);



	//coins
	Sprite coin[11];
	Texture coinn;
	coinn.loadFromFile("coni.png");
	for (int i = 1; i <= 7; i++) {
		coin[i].setScale(0.075, 0.075);
		coin[i].setTexture(coinn);
		coin[i].setPosition(400 + (i * 100), 650);
	}
	//coins2
	Sprite coin2[11];
	for (int i = 1; i <= 7; i++) {
		coin2[i].setScale(0.075, 0.075);
		coin2[i].setTexture(coinn);
		coin2[i].setPosition(1400 + (i * 100), 650);
	}

	//sound track
	SoundBuffer bgk;
	bgk.loadFromFile("sbg.wav");
	Sound bggg;
	bggg.setBuffer(bgk);
	bggg.play();


	//setting jump sound 
	SoundBuffer jum;
	jum.loadFromFile("jump.wav");
	Sound jump;
	jump.setBuffer(jum);



	//coin sound
	SoundBuffer op;
	op.loadFromFile("sound.wav");
	Sound coinz;
	coinz.setBuffer(op);



	//scoring display
	Font opp;
	opp.loadFromFile("Font.ttf");
	Text score1;
	score1.setFont(opp);
	score1.setFillColor(Color::Red);
	score1.setStyle(Text::Bold);
	score1.setCharacterSize(20);
	score1.setPosition(1200, 30);
	score1.setString("Score:");
	Text score2;
	score2.setFont(opp);
	score2.setFillColor(Color::White);
	score2.setStyle(Text::Bold);
	score2.setCharacterSize(20);
	score2.setPosition(1300, 30);





	//lost display
	Text lost;
	lost.setFont(opp);
	lost.setFillColor(Color::Black);
	lost.setStyle(Text::Bold);
	lost.setCharacterSize(50);
	lost.setString("GAME OVER");

	//enemy
	Texture en;
	en.loadFromFile("enemy.png");
	Sprite enm;
	enm.setTexture(en);
	enm.setScale(0.09, 0.09);
	enm.setPosition(400, 650);
	Texture en2;
	en2.loadFromFile("enemy2.png");



	//obstacle 1
	RectangleShape obs1;
	//obs1.setFillColor(Color::Black);
	obs1.setSize(Vector2f(50, 50));
	obs1.setPosition(700, 650);
	obs1.setTexture(&mudd);



	//obstacle 2
	RectangleShape obs2;
	//obs2.setFillColor(Color::Black);
	obs2.setSize(Vector2f(50, 50));
	obs2.setPosition(200, 650);
	obs2.setTexture(&mudd);




	RenderWindow window(VideoMode(1280, 720), "Mario");
	View view(Vector2f(0, 0), Vector2f(1280, 720));


	window.setFramerateLimit(30);
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		//changing screen
		if (Mouse::isButtonPressed(Mouse::Left)) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (mousePos.x > 500 && mousePos.x < 950 && mousePos.y>100 && mousePos.y < 260) { screen = 1; }
		}




		//right motion
		if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
			right = 1;
			mario.move(3, 0);
			cnty = 2;
			cntx++;
			score1.move(3, 0);
			score2.move(3, 0);
			//boundries to avoid entering mud when falling
			if ((mud.getGlobalBounds().intersects(mario.getGlobalBounds()) || mud2.getGlobalBounds().intersects(mario.getGlobalBounds())) && mario.getPosition().y > 629) {
				mario.move(-3, 0);
			}
			if (((obs1.getGlobalBounds().intersects(mario.getGlobalBounds()) || obs2.getGlobalBounds().intersects(mario.getGlobalBounds()))) && mario.getPosition().y >= 600) {
				mario.move(-3, 0);
				score1.move(-3, 0);
				score2.move(-3, 0);
			}
			//borders
			if (mario.getPosition().x > 2200) {
				mario.move(-3, 0);
				score1.move(-3, 0);
				score2.move(-3, 0);
			}
			//left tunnel
			if (mario.getGlobalBounds().intersects(tun1.getGlobalBounds()) && mario.getPosition().y > 620 && mario.getPosition().x <= 850) {
				mario.setPosition(2100, 626); score1.setPosition(mario.getPosition().x + 920, 30); score2.setPosition(mario.getPosition().x + 1020, 30);
			}
			//left most tunnel
			if (mario.getGlobalBounds().intersects(tun2.getGlobalBounds())) {
				mario.move(-3, 0);
				score1.move(-3, 0);
				score2.move(-3, 0);
			}
		}

		//left motion
		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) {
			right = 0;
			mario.move(-3, 0);
			cnty = 1;
			cntx++;
			score1.move(-3, 0);
			score2.move(-3, 0);
			//boundries to avoid entering mud when falling
			if ((mud.getGlobalBounds().intersects(mario.getGlobalBounds()) || mud2.getGlobalBounds().intersects(mario.getGlobalBounds())) && mario.getPosition().y > 629) {
				mario.move(3, 0);
			}
			if (((obs1.getGlobalBounds().intersects(mario.getGlobalBounds()) || obs2.getGlobalBounds().intersects(mario.getGlobalBounds()))) && mario.getPosition().y >= 600) {
				mario.move(3, 0);
				score1.move(3, 0);
				score2.move(3, 0);
			}

			//borders
			if (mario.getPosition().x < 180) {
				mario.move(3, 0);
				score1.move(3, 0);
				score2.move(3, 0);
			}



			//left most tunnel
			if (mario.getGlobalBounds().intersects(tun1.getGlobalBounds())) {
				mario.move(3, 0);
				score1.move(3, 0);
				score2.move(3, 0);
			}
			//right tunnel
			if (mario.getGlobalBounds().intersects(tun2.getGlobalBounds()) && mario.getPosition().y > 620 && mario.getPosition().x < 2050) {
				mario.setPosition(800, 626); score1.setPosition(mario.getPosition().x + 920, 30); score2.setPosition(mario.getPosition().x + 1020, 30);
			}

		}




		//jumping
		if (((mud.getGlobalBounds().intersects(mario.getGlobalBounds()) || mud2.getGlobalBounds().intersects(mario.getGlobalBounds())) && mario.getPosition().y < 629) || ((mario.getGlobalBounds().intersects(obs1.getGlobalBounds())) && mario.getPosition().y < 585) || ((mario.getGlobalBounds().intersects(obs2.getGlobalBounds())) && mario.getPosition().y < 585) || mario.getGlobalBounds().intersects(tun1.getGlobalBounds()) && mario.getPosition().y <= 630 || mario.getGlobalBounds().intersects(tun2.getGlobalBounds()) && mario.getPosition().y <= 630) {
			grounded = true;
			velocityY = 0;
			jumpy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Key::Up)) {
				velocityY = 6;
				jump.play();
				jumpy = 1;

			}
		}
		else {
			grounded = false;
			velocityY -= 0.29;
		}







		//coins gathering
		for (int j = 1; j <= 7; j++) {
			if (mario.getGlobalBounds().intersects(coin[j].getGlobalBounds())) {
				coin[j].setPosition(-100, -100);

				score += 10;
				coinz.play();
			}
		}
		for (int j = 1; j <= 7; j++) {
			if (mario.getGlobalBounds().intersects(coin2[j].getGlobalBounds())) {
				coin2[j].setPosition(-100, -100);

				score += 10;
				coinz.play();
			}
		}






		//animation modifer
		cntx %= 3;
		if (jumpy == 0)
			mario.setTextureRect(IntRect(cntx * 97, cnty * 143, 97, 143));
		if (jumpy == 1 && right == 1)
			mario.setTextureRect(IntRect(1 * 97, 2 * 143, 97, 143));
		if (jumpy == 1 && right == 0)
			mario.setTextureRect(IntRect(1 * 97, 1 * 143, 97, 143));



		//camera modification

		view.setCenter(Vector2f(mario.getPosition().x , 360));

		//score formula
		stringstream strr;
		strr << score;
		score2.setString(strr.str());


		if (enm.getGlobalBounds().intersects(obs1.getGlobalBounds())) { enemcnt = 1; }
		if (enm.getGlobalBounds().intersects(obs2.getGlobalBounds())) { enemcnt = 0; }
		if (enemcnt == 1 && screen == 1) { enm.move(-3, 0); enm.setTexture(en2); }
		else if (enemcnt == 0 && screen == 1) { enm.move(3, 0); enm.setTexture(en); }




		window.clear();
		if (screen == 1) {
			window.setView(view);
			for (int i = 0; i < 4; i++) {
				window.draw(bg[i]);

			}
			//losing
			if (mario.getPosition().y > 720) { lost.setPosition(1200, 500); window.draw(lost); }
			if ((mario.getGlobalBounds().intersects(enm.getGlobalBounds())) && mario.getPosition().y > 620) { alive = 0; lost.setPosition(mario.getPosition().x, mario.getPosition().y - 100); window.draw(lost); }
			if ((mario.getGlobalBounds().intersects(enm.getGlobalBounds())) && mario.getPosition().y < 620) { enm.setPosition(-100, -100); aliveenm = 0; score += 10; }

			if (mario.getPosition().x >= 2200) { mario.move(-3, 0); score1.move(-3, 0); score2.move(-3, 0); }


			window.draw(mud);
			window.draw(mud2);
			if (alive)
				window.draw(mario);
			for (int i = 1; i <= 7; i++) {
				window.draw(coin[i]);
				window.draw(coin2[i]);
			}
			mario.move(0, -velocityY);
			window.draw(score1);
			window.draw(score2);
			if (aliveenm)
				window.draw(enm);
			window.draw(obs1);
			window.draw(obs2);
			window.draw(tun1);
			window.draw(tun2);
		}
		if (screen == 0)
			window.draw(Menu);
		window.display();
	}
}