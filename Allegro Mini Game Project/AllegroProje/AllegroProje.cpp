#include<stdio.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>
#include<Windows.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>

int level = 1;
bool keys[] = { false,false };
enum keys { SPACE, ESCAPE };
enum STATES { MENU, PLAYING, GAMEOVER, CONTINUE };

const int WIDTH = 600;
const int HEIGHT = 900;

void level1() {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_FONT* font18;
	ALLEGRO_BITMAP* laserbox;


	al_init();
	al_init_primitives_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	laserbox = al_load_bitmap("laserbox.bmp");

	display = al_create_display(WIDTH, HEIGHT);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_timer_event_source(timer));


	int states = MENU;
	bool running = true;
	int c1 = 262.5, c2 = 110, r = 25;
	int a = 225, b = 300, a1 = 225, b1 = WIDTH;
	int lx = 263, ly = 770, lx1 = 263, ly1 = 675;
	float x = 0, y = 0;
	font18 = al_load_font("arial.ttf", 18, 0);

	while (running) {


		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
		al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}


		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = false;
				break;
			}
		}



		if (states == MENU)
		{
			if (keys[SPACE])
				states = PLAYING;
		}
		else if (states == PLAYING)
		{
			if (keys[ESCAPE])
				states = GAMEOVER;
		}

		else if (states == GAMEOVER)
		{
			if (keys[SPACE])
				running = false;
		}

		if (states == MENU)
		{
			al_draw_bitmap(laserbox, 100, 200, 0);
			al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press space to play");
			al_flip_display();
		}
		else if (states == PLAYING)
		{
			
			for (int y = 0; y < 150;) {
				for (int x = 0; x < WIDTH;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					x = x + 75;
				}
				y = y + 75;
			}

			for (int y = 150; y < HEIGHT;) {
				al_draw_rectangle(0, y, 75, y + 75, al_map_rgb(255, 255, 255), 3);
				y = y + 75;
			}

			for (int y = 750; y < HEIGHT;) {
				for (int x = 75; x < WIDTH;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					x = x + 75;
				}
				y = y + 75;
			}

			for (int x = 450; x < WIDTH;) {
				for (int y = 150; y < HEIGHT;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					y = y + 75;
				}
				x = x + 75;

				al_draw_filled_circle(c1, c2, r, al_map_rgb(0, 255, 255));//blue circle
				al_draw_filled_circle(262.5, 787.5, 25, al_map_rgb(255, 0, 0));//red circle
				al_draw_line(lx, ly, lx1, ly1, al_map_rgb(255, 0, 0), 4);//laser
				al_draw_filled_rectangle(a, b, a + 75, b + 75, al_map_rgb(255, 225, 0)); //rec1
				al_draw_filled_rectangle(a1, b1, a1 + 75, b1 + 75, al_map_rgb(255, 225, 0)); //rec2

				al_flip_display();
			}

			float x = 0, y = 0;

			if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
				al_get_mouse_state(&state);

				if (state.buttons & 1) {
					if ((a || b == state.buttons & 1) && (a + 75 || b + 75 == state.buttons & 1)) {
						(a = +event.mouse.x, b = +event.mouse.y, al_set_mouse_xy(display, a, b)) || (a = +75 + event.mouse.x, b = +75 + event.mouse.y, al_set_mouse_xy(display, a + 75, b + 75));

						printf("Mouse position 1 : (%d, %d)\n", state.x, state.y);
						

						
					}
				}				
			}

			if (state.buttons & 2) {
				if ((a1 || b1 == state.buttons & 2) && (a1 + 75 || b1 + 75 == state.buttons & 2)) {
					(a1 = +event.mouse.x, b1 = +event.mouse.y, al_set_mouse_xy(display, a1, b1)) || (a1 = +75 + event.mouse.x, b1 = +75 + event.mouse.y, al_set_mouse_xy(display, a1 + 75, b1 + 75));

					printf("Mouse position 2 : (%d, %d)\n", state.x, state.y);	
				}
			}
			if (abs(lx - a1) >= 9 && abs(ly - b1) >= 100) {
				if (abs(lx - a1 - 75) >= 35 && abs(ly - b1 - 75) >= 100) {
					al_draw_line(lx, ly, lx1, ly1 - 375, al_map_rgb(255, 0, 0), 4);		

					if (abs(lx - a) >= 9 && abs(ly - b) >= 90) {
						if (abs(lx - a - 75) >= 40 && abs(ly - b - 75) >= 90) {
							al_draw_line(lx, ly, lx1, ly1 - 555.5, al_map_rgb(255, 0, 0), 4);
						}
					}
				}
				al_flip_display();

			}
			if (abs(lx - a1) >= 9 && abs(ly - b1) >= 100) {
				if (abs(lx - a1 - 75) >= 35 && abs(ly - b1 - 75) >= 100) {
					if (abs(lx - a) >= 9 && abs(ly - b) >= 90) {
						if (abs(lx - a - 75) >= 40 && abs(ly - b - 75) >= 90) {

							if (states == PLAYING) {
								al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press space to next level");
								al_flip_display();
								if (keys[SPACE]) {
									states = CONTINUE;
									printf("Loading");									
									running = false;
									level++;
								}
							}
							if (states == CONTINUE) {

								if (keys[SPACE]) {

								}

							}

							else if (states == CONTINUE) {



								if (keys[ESCAPE])
									states = GAMEOVER;
							}
						}
					}
				}
			}
		}
		else if (states == GAMEOVER)
		{
			al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press space to exit the game");
			al_flip_display();
		}
	}

	al_flip_display();
	al_destroy_display(display);
	al_uninstall_mouse();

}

void level2() {
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_BITMAP* image;
	ALLEGRO_FONT* font18;


	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	image = al_load_bitmap("resim.bmp");

	display = al_create_display(WIDTH, HEIGHT);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	int a = 150, b = HEIGHT;
	float degree = 0;

	int lx = 337.5, ly = 140;
	int states = PLAYING;

	int imageWidth = 0;
	int imageHeight = 0;

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());

	font18 = al_load_font("arial.ttf", 18, 0);

	bool running = true;

	while (running) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = true;
				break;

			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = true;
				break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_SPACE:
				keys[SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = false;
				break;
			}
		}

		if (states == PLAYING)
		{
			if (keys[ESCAPE])
				states = GAMEOVER;
		}
		else if (states == GAMEOVER)
		{
			if (keys[SPACE])
				running = false;
		}


		if (states == PLAYING)
		{


			for (int y = 0; y < 150;) {
				for (int x = 0; x < WIDTH;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					x = x + 75;
				}
				y = y + 75;
			}

			for (int x = 450; x < WIDTH;) {
				for (int y = 150; y < HEIGHT;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					y = y + 75;
				}
				x = x + 75;

			}
			for (int x = 0; x < 225;) {
				for (int y = 300; y < 375;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					y = y + 75;
				}
				x = x + 75;
			}
			for (int x = 0; x < 75;) {
				for (int y = 375; y < 475;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					y = y + 75;
				}
				x = x + 75;
			}
			for (int x = 75; x < 225;) {
				for (int y = 450; y < 525;) {
					al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
					y = y + 75;
				}
				x = x + 75;
			}	
			al_draw_filled_circle(112.5, 412.5, 25, al_map_rgb(0, 255, 255));   //mavi daire
			al_draw_filled_circle(337.5, 112.5, 25, al_map_rgb(255, 0, 0));	//kırmızı daire
			al_draw_line(lx, ly, 335.5, HEIGHT, al_map_rgb(255, 0, 0), 4);
		
			imageWidth = al_get_bitmap_width(image);
			imageHeight = al_get_bitmap_height(image);

			al_draw_rotated_bitmap(image, imageWidth / 2, imageHeight / 2, a, b, degree * 3.14159 / 180, 0);

			al_flip_display();


			float x = 0, y = 0;

			al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));

			if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				running = false;
			}

			if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
				al_get_mouse_state(&state);

				if (state.buttons & 1) {
					if ((a || b == state.buttons & 1) && (a + 75 || b - 75 == state.buttons & 1)) {
						(a = +event.mouse.x, b = +event.mouse.y, al_set_mouse_xy(display, a, b)) || (a = +75 + event.mouse.x, b = +75 + event.mouse.y, al_set_mouse_xy(display, a + 75, b - 75));

						printf("Mouse position : (%d, %d)\n", state.x, state.y); //son pozisyon çıktısı

					}

				}

			}
			al_clear_to_color(al_map_rgba_f(0, 0, 0, 1));
			if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				al_get_mouse_state(&state);

				if (state.buttons & 2) {
					degree -= 90;
					if (degree <= 0)
						degree = 360;



				}
			}
			if (abs(lx - a) < 187.5 && abs(ly - b) < 760) {
				al_draw_line(335.5, 412, 337.5, 900, al_map_rgb(0, 0, 0), 4);
				if (degree == 0)
					al_draw_line(335.5, 412, 507, 412, al_map_rgb(255, 255, 0), 4);
				if (degree == 270)
					al_draw_line(335.5, 412, 112.5, 412.5, al_map_rgb(255, 255, 0), 4);
			}	
		}
		else if (states == GAMEOVER)
		{
			al_draw_text(font18, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2, ALLEGRO_ALIGN_CENTRE, "Press space to exit the game");
			al_flip_display();
		}
	}

	al_flip_display();
	al_destroy_bitmap(image);
	al_destroy_display(display);
	al_uninstall_mouse();
	al_uninstall_keyboard();

}
int main() {

	if (level == 1) {
		level1();

	}
	if (level == 2) {
		level2();
	}
	system("pause");
	return 0;
}