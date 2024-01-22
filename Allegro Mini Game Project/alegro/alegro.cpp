#include<stdio.h>
#include<allegro5/allegro5.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_image.h>

int main() {


	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	ALLEGRO_MOUSE_STATE state;
	ALLEGRO_BITMAP* image;

	al_init();
	al_init_primitives_addon();
	al_init_image_addon();
	al_install_mouse();
	al_install_keyboard();
	image = al_load_bitmap("resim.bmp");

	display = al_create_display(600, 900);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	//bool running = true;
	int a = 150, b = 900;
	float degree = 0;

	int lx = 337.5, ly = 140;


	int imageWidth = 0;
	int imageHeight = 0;

	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_keyboard_event_source());



	bool running = true;

	while (running) {
		for (int y = 0; y < 150;) {
			for (int x = 0; x < 600;) {
				al_draw_rectangle(x, y, x + 75, y + 75, al_map_rgb(255, 255, 255), 3);
				x = x + 75;
			}
			y = y + 75;
		}

		for (int x = 450; x < 600;) {
			for (int y = 150; y < 900;) {
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






		//  al_draw_spline, al_map_rgb(255, 255, 0),5);
		al_draw_filled_circle(112.5, 412.5, 25, al_map_rgb(0, 255, 255));   //mavi daire
		al_draw_filled_circle(337.5, 112.5, 25, al_map_rgb(255, 0, 0));	//kırmızı daire
		al_draw_line(lx, ly, 337.5, 900, al_map_rgb(255, 0, 0), 4);
		//al_draw_filled_rectangle(a, b, a + 75, b - 75, al_map_rgb(255, 255, 0));

		imageWidth = al_get_bitmap_width(image);
		imageHeight = al_get_bitmap_height(image);

		al_draw_rotated_bitmap(image, imageWidth / 2, imageHeight / 2, a, b, degree * 3.14159 / 180, 0);

		al_flip_display();


		float x = 0, y = 0;
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);
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
		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			al_get_mouse_state(&state);

			if (state.buttons & 2) {
				degree += 90;
				if (degree <= 0)
					degree = 360;
			}
		}
		if (abs(lx - a) < 187.5 && abs(ly - b) < 760) {
			al_draw_line(335.5, 412, 337.5, 900, al_map_rgb(0, 0, 0), 4);
			if(degree==0)
				al_draw_line(335.5, 412, 507, 412, al_map_rgb(255, 255, 0), 4);
			if (degree == 270)
				al_draw_line(335.5, 412, 112.5, 412.5, al_map_rgb(255, 255, 0), 4);
			//if (degree == 360)
				//al_draw_line(335.5, 412, 507, 412, al_map_rgb(255, 255, 0), 4);
		}

	}

	
	al_flip_display();
	al_destroy_bitmap(image);
	al_destroy_display(display);
	al_uninstall_mouse();
	al_uninstall_keyboard();
	system("pause");
	return 0;
}