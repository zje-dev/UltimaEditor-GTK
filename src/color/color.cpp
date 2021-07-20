#include "./color.h"
/*
void color_picker_window::select_color_0 (wxCommandEvent& event) {
	*current_color = 0;
}

void color_picker_window::select_color_1 (wxCommandEvent& event) {
	*current_color = 1;
}

void color_picker_window::select_color_2 (wxCommandEvent& event) {
	*current_color = 2;
}

void color_picker_window::select_color_3 (wxCommandEvent& event) {
	*current_color = 3;
}

void color_picker_window::select_color_4 (wxCommandEvent& event) {
	*current_color = 4;
}

void color_picker_window::select_color_5 (wxCommandEvent& event) {
	*current_color = 5;
}

void color_picker_window::select_color_6 (wxCommandEvent& event) {
	*current_color = 6;
}

void color_picker_window::select_color_7 (wxCommandEvent& event) {
	*current_color = 7;
}

void color_picker_window::select_color_8 (wxCommandEvent& event) {
	*current_color = 8;
}

void color_picker_window::select_color_9 (wxCommandEvent& event) {
	*current_color = 9;
}

void color_picker_window::select_color_10(wxCommandEvent& event) {
	*current_color = 10;
}

void color_picker_window::select_color_11(wxCommandEvent& event) {
	*current_color = 11;
}

void color_picker_window::select_color_12(wxCommandEvent& event) {
	*current_color = 12;
}

void color_picker_window::select_color_13(wxCommandEvent& event) {
	*current_color = 13;
}

void color_picker_window::select_color_14(wxCommandEvent& event) {
	*current_color = 14;
}

void color_picker_window::select_color_15(wxCommandEvent& event) {
	*current_color = 15;
}

color_picker_window::color_picker_window (int palette, int *color, bool fs) : wxFrame(NULL, wxID_ANY, "Color picker") {
	current_color = color;
	int ids_cga[4] = {
		cga_0,
		cga_1,
		cga_2,
		cga_3
	}, ids_tik[16] = {
		tik_0,
		tik_1,
		tik_2,
		tik_3,
		tik_4,
		tik_5,
		tik_6,
		tik_7,
		tik_8,
		tik_9,
		tik_10,
		tik_11,
		tik_12,
		tik_13,
		tik_14,
		tik_15
	};
	selects.push_back(&color_picker_window::select_color_0);
	selects.push_back(&color_picker_window::select_color_1);
	selects.push_back(&color_picker_window::select_color_2);
	selects.push_back(&color_picker_window::select_color_3);
	selects.push_back(&color_picker_window::select_color_4);
	selects.push_back(&color_picker_window::select_color_5);
	selects.push_back(&color_picker_window::select_color_6);
	selects.push_back(&color_picker_window::select_color_7);
	selects.push_back(&color_picker_window::select_color_8);
	selects.push_back(&color_picker_window::select_color_9);
	selects.push_back(&color_picker_window::select_color_10);
	selects.push_back(&color_picker_window::select_color_11);
	selects.push_back(&color_picker_window::select_color_12);
	selects.push_back(&color_picker_window::select_color_13);
	selects.push_back(&color_picker_window::select_color_14);
	selects.push_back(&color_picker_window::select_color_15);
	switch (palette) {
		case 0:
			SetClientSize(220, 90);
			for (int i = 0; i < 4; i++) {
				std::string img_path = "./img/cga/cga_"+std::to_string(i)+".xpm";
				new wxBitmapButton(this, ids_cga[i], wxBitmap(img_path.c_str(), wxBITMAP_TYPE_BMP), wxPoint(55 * i, 25), wxSize(50, 60));
				Bind(wxEVT_BUTTON, selects[i], this, ids_cga[i]);
			}
			new wxStaticText(this, wxID_ANY, "CGA Colors", wxPoint(65, 5));
			break;
		case 1:
			if (!fs) {
				SetClientSize(435, 150);
				new wxStaticText(this, wxID_ANY, "EGA Colors", wxPoint(185, 5));
				for (int i = 0; i < 16; i++) {
					std::string img_path = "./img/ega/ega_"+std::to_string(i)+".xpm";
					new wxBitmapButton(this, ids_tik[i], wxBitmap(img_path.c_str(), wxBITMAP_TYPE_BMP), wxPoint(55 * i - (i > 7 ? 440 : 0), (i > 7 ? 90 : 25)), wxSize(50, 60));
					Bind(wxEVT_BUTTON, selects[i], this, ids_tik[i]);
				}
			} else {
				SetClientSize(270, 210);
				new wxStaticText(this, wxID_ANY, "EGA Colors", wxPoint(125, 5));
				new wxBitmapButton(this, 29, wxBitmap("./img/tandy/t1k_0.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 25), wxSize(50, 60));
				new wxBitmapButton(this, 30, wxBitmap("./img/tandy/t1k_8.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 25), wxSize(50, 60));
				new wxBitmapButton(this, 31, wxBitmap("./img/tandy/t1k_7.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 25), wxSize(50, 60));
				new wxBitmapButton(this, 32, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 25), wxSize(50, 60));
				new wxBitmapButton(this, 33, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(220, 25), wxSize(50, 60));
				new wxBitmapButton(this, 34, wxBitmap("./img/tandy/t1k_2.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 90), wxSize(50, 60));
				new wxBitmapButton(this, 35, wxBitmap("./img/tandy/t1k_10.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 90), wxSize(50, 60));
				new wxBitmapButton(this, 36, wxBitmap("./img/tandy/t1k_6.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 90), wxSize(50, 60));
				new wxBitmapButton(this, 37, wxBitmap("./img/tandy/t1k_12.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 90), wxSize(50, 60));
				new wxBitmapButton(this, 38, wxBitmap("./img/tandy/t1k_11.xpm", wxBITMAP_TYPE_BMP), wxPoint(220, 90), wxSize(50, 60));
				new wxBitmapButton(this, 39, wxBitmap("./img/tandy/t1k_1.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 150), wxSize(50, 60));
				new wxBitmapButton(this, 40, wxBitmap("./img/tandy/t1k_9.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 150), wxSize(50, 60));
				new wxBitmapButton(this, 41, wxBitmap("./img/tandy/t1k_7.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 150), wxSize(50, 60));
				new wxBitmapButton(this, 42, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 150), wxSize(50, 60));
				for (int i = 0; i < 16; i++) {
					Bind(wxEVT_BUTTON, selects[i], this, ids_tik[i]);
				}
			}
			break;
		case 2:
			if (!fs) {
				SetClientSize(435, 150);
				new wxStaticText(this, wxID_ANY, "T1K Colors", wxPoint(185, 5));
				for (int i = 0; i < 16; i++) {
					std::string img_path = "./img/tandy/t1k_"+std::to_string(i)+".xpm";
					new wxBitmapButton(this, ids_tik[i], wxBitmap(img_path.c_str(), wxBITMAP_TYPE_BMP), wxPoint(55 * i - (i > 7 ? 440 : 0), (i > 7 ? 90 : 25)), wxSize(50, 60));
					Bind(wxEVT_BUTTON, selects[i], this, ids_tik[i]);
				}
			} else {
				SetClientSize(270, 210);
				new wxStaticText(this, wxID_ANY, "EGA Colors", wxPoint(125, 5));
				new wxBitmapButton(this, 29, wxBitmap("./img/tandy/t1k_0.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 25), wxSize(50, 60));
				new wxBitmapButton(this, 30, wxBitmap("./img/tandy/t1k_8.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 25), wxSize(50, 60));
				new wxBitmapButton(this, 31, wxBitmap("./img/tandy/t1k_7.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 25), wxSize(50, 60));
				new wxBitmapButton(this, 32, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 25), wxSize(50, 60));
				new wxBitmapButton(this, 33, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(220, 25), wxSize(50, 60));
				new wxBitmapButton(this, 34, wxBitmap("./img/tandy/t1k_2.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 90), wxSize(50, 60));
				new wxBitmapButton(this, 35, wxBitmap("./img/tandy/t1k_10.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 90), wxSize(50, 60));
				new wxBitmapButton(this, 36, wxBitmap("./img/tandy/t1k_14.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 90), wxSize(50, 60));
				new wxBitmapButton(this, 37, wxBitmap("./img/tandy/t1k_4.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 90), wxSize(50, 60));
				new wxBitmapButton(this, 38, wxBitmap("./img/tandy/t1k_11.xpm", wxBITMAP_TYPE_BMP), wxPoint(220, 90), wxSize(50, 60));
				new wxBitmapButton(this, 39, wxBitmap("./img/tandy/t1k_1.xpm", wxBITMAP_TYPE_BMP), wxPoint(0, 150), wxSize(50, 60));
				new wxBitmapButton(this, 40, wxBitmap("./img/tandy/t1k_9.xpm", wxBITMAP_TYPE_BMP), wxPoint(55, 150), wxSize(50, 60));
				new wxBitmapButton(this, 41, wxBitmap("./img/tandy/t1k_7.xpm", wxBITMAP_TYPE_BMP), wxPoint(110, 150), wxSize(50, 60));
				new wxBitmapButton(this, 42, wxBitmap("./img/tandy/t1k_15.xpm", wxBITMAP_TYPE_BMP), wxPoint(165, 150), wxSize(50, 60));
				for (int i = 0; i < 16; i++) {
					Bind(wxEVT_BUTTON, selects[i], this, ids_tik[i]);
				}
			}
			break;
	}
	Show();
}
*/
