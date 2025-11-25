#include "Giaodiengame.h"
#include "solieu.h"
#include <graphics.h>
#include <conio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;

void GiaoDienGame::veMap(const char map[SO_HANG_MAP][SO_COT_MAP + 1], int toaDoX, int toaDoY) {
    for (int r = 0; r < SO_HANG_MAP; r++) {
        for (int c = 0; c < SO_COT_MAP; c++) {
            int x = c * KICH_THUOC_O + toaDoX;
            int y = r * KICH_THUOC_O + toaDoY;
            char kyTu = map[r][c];
            if (kyTu == '#') {
                setcolor(BLUE);
                setfillstyle(SOLID_FILL, BLUE);
                rectangle(x, y, x + KICH_THUOC_O, y + KICH_THUOC_O);
                floodfill(x + 1, y + 1, BLUE);
            } else if (kyTu == '.') {
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                circle(x + KICH_THUOC_O / 2, y + KICH_THUOC_O / 2, KICH_THUOC_O / 6);
                floodfill(x + KICH_THUOC_O / 2, y + KICH_THUOC_O / 2, YELLOW);
            }
        }
    }
}

void GiaoDienGame::veThongTinGame(int mang, int diem, int toaDoX, int toaDoY, int game_width) {
    char mangText[20], diemText[100];
    sprintf(mangText, "Mang: %d", mang);
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(toaDoX, toaDoY - 30, mangText);

    sprintf(diemText, "Score: %d", diem);
    outtextxy(toaDoX + game_width - textwidth(diemText), toaDoY - 30, diemText);
}

void GiaoDienGame::veMenuChinh(int mucChon, bool nhacBat) {
    readimagefile("Hinhanh/background.bmp", 0, 0, 700, 700);
    readimagefile("Hinhanh/Pacman1.bmp", 100, 50, 600, 200);

    if (mucChon == 1) readimagefile("Hinhanh/play.bmp", 290, 240, 410, 360);
    else readimagefile("Hinhanh/play.bmp", 300, 250, 400, 350);

    if (mucChon == 2) readimagefile("Hinhanh/ranking.bmp", 290, 365, 410, 485);
    else readimagefile("Hinhanh/ranking.bmp", 300, 375, 400, 475);

    if (mucChon == 3) readimagefile("Hinhanh/exit.bmp", 290, 490, 410, 610);
    else readimagefile("Hinhanh/exit.bmp", 300, 500, 400, 600);

    if (nhacBat) readimagefile("Hinhanh/volumeon.bmp",25,565,75,615);
    else readimagefile("Hinhanh/volumeoff1.bmp",25,565,75,615);

    readimagefile("Hinhanh/help.bmp", 25, 625, 75, 675);
}

void GiaoDienGame::hienThiBangXepHang(const vector<DiemNguoiChoi>& danhSach) {
    cleardevice();
    setbkcolor(BLACK);
    int rongMH = getmaxx();

    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(LIGHTCYAN);
    char tieuDeBXH[] = "BANG XEP HANG TOP 5";
    outtextxy((rongMH - textwidth(tieuDeBXH)) / 2, 50, tieuDeBXH);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    int startY_BXH = 150;
    for (size_t i = 0; i < danhSach.size() && i < 5; i++) {
        string dongStr = to_string(i + 1) + ". " + danhSach[i].ten + " - " + to_string(danhSach[i].diem);
        char* dong = (char*)dongStr.c_str();
        outtextxy((rongMH - textwidth(dong)) / 2, startY_BXH + i * 40, dong);
    }
    setvisualpage(getactivepage());
}

void GiaoDienGame::hienThiLoi(const string& thongBao) {
    cleardevice();
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy((getmaxx() - textwidth((char*)thongBao.c_str())) / 2, getmaxy() / 2, (char*)thongBao.c_str());
    getch();
}

void GiaoDienGame::hienThiManHinhThang(const string& ten, int diem, const vector<DiemNguoiChoi>& bxh) {
    int rongMH = getmaxx(), caoMH = getmaxy();
    cleardevice();

    char msg[] = "YOU WIN!";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(YELLOW);
    outtextxy((rongMH - textwidth(msg)) / 2, caoMH / 2 - 80, msg);

    string tenTextStr = "Player: " + ten;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy((rongMH - textwidth((char*)tenTextStr.c_str())) / 2, caoMH / 2 + 20, (char*)tenTextStr.c_str());

    string diemTextStr = "Score: " + to_string(diem);
    setcolor(LIGHTGREEN);
    outtextxy((rongMH - textwidth((char*)diemTextStr.c_str())) / 2, caoMH / 2 + 50, (char*)diemTextStr.c_str());

    setvisualpage(getactivepage());
    getch();
    hienThiBangXepHang(bxh);
    getch();
}

void GiaoDienGame::hienThiManHinhThua(const string& ten, int diem, const vector<DiemNguoiChoi>& bxh) {
    int rongMH = getmaxx(), caoMH = getmaxy();
    cleardevice();

    char msg[] = "YOU DIED";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(RED);
    outtextxy((rongMH - textwidth(msg)) / 2, caoMH / 2 - 80, msg);

    string tenTextStr = "Player: " + ten;
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy((rongMH - textwidth((char*)tenTextStr.c_str())) / 2, caoMH / 2 + 20, (char*)tenTextStr.c_str());

    string diemTextStr = "Score: " + to_string(diem);
    setcolor(YELLOW);
    outtextxy((rongMH - textwidth((char*)diemTextStr.c_str())) / 2, caoMH / 2 + 50, (char*)diemTextStr.c_str());

    setvisualpage(getactivepage());
    getch();
    hienThiBangXepHang(bxh);
    getch();
}

string GiaoDienGame::nhapTenNguoiChoi() {
    cleardevice();
    setbkcolor(BLACK);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    string tenNhap;
    int rongMH = getmaxx(), caoMH = getmaxy();
    bool hienConTro = true;
    int dem = 0;

    while (true) {
        cleardevice();
        const char* prompt = "Nhap ten nguoi choi:";
        outtextxy((rongMH - textwidth((char*)prompt)) / 2, caoMH / 2 - 50, (char*)prompt);
        outtextxy((rongMH - textwidth((char*)tenNhap.c_str())) / 2, caoMH / 2, (char*)tenNhap.c_str());

        if (hienConTro) {
            outtextxy((rongMH - textwidth((char*)tenNhap.c_str())) / 2 + textwidth((char*)tenNhap.c_str()) + 5, caoMH / 2, (char*)"|");
        }

        if (kbhit()) {
            char ch = getch();
            if (ch == 13 && !tenNhap.empty()) { // Enter
                break;
            } else if (ch == 8 && !tenNhap.empty()) { // Backspace
                tenNhap.pop_back();
            } else if (isprint(ch) && tenNhap.length() < 49) {
                tenNhap += ch;
            }
        }
        if (++dem >= 10) {
            hienConTro = !hienConTro;
            dem = 0;
        }
        delay(50);
    }
    return tenNhap;
}

int GiaoDienGame::chonManChoi() {
    int x, y;
    int mucChon = 0;
    int page = 0;
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_MOUSEMOVE);

    while (true) {
        setactivepage(page);
        cleardevice();
        setbkcolor(BLACK);
        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        setcolor(WHITE);
        outtextxy((getmaxx() - textwidth((char*)"Chon Cap Do")) / 2, 100, (char*)"Chon Cap Do");

        for (int i = 0; i < 5; i++) {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, (mucChon == i + 1) ? 3 : 2);
            setcolor((mucChon == i + 1) ? YELLOW : WHITE);
            string dongStr = to_string(i + 1) + " - Level " + to_string(i+1);
            outtextxy((getmaxx() - textwidth((char*)dongStr.c_str())) / 2, 180 + i * 40, (char*)dongStr.c_str());
        }

        setvisualpage(page);
        page = 1 - page;

        if (ismouseclick(WM_MOUSEMOVE)) {
            getmouseclick(WM_MOUSEMOVE, x, y);
            mucChon = 0;
            for (int i = 0; i < 5; i++) {
                int start_y = 180 + i * 40;
                if (y >= start_y && y <= start_y + textheight((char*)"A")) {
                    mucChon = i + 1;
                    break;
                }
            }
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            for (int i = 0; i < 5; i++) {
                int start_y = 180 + i * 40;
                if (y >= start_y && y <= start_y + textheight((char*)"A")) {
                    cleardevice();
                    return i + 1;
                }
            }
        }
        delay(20);
    }
}

void GiaoDienGame::hienThiHuongDan() {
    cleardevice();
    setbkcolor(BLACK);
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(LIGHTCYAN);
    outtextxy((getmaxx() - textwidth((char*)"HUONG DAN CHOI")) / 2, 100, (char*)"HUONG DAN CHOI");

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    outtextxy(150, 200, (char*)"- Su dung W, A, S, D de di chuyen.");
    outtextxy(150, 250, (char*)"- An phim Q de thoat khi dang choi.");
    outtextxy(150, 300, (char*)"- An het cac cham vang de chien thang.");

    setcolor(YELLOW);
    outtextxy((getmaxx() - textwidth((char*)"Nhan phim bat ky de quay lai Menu")) / 2, 400, (char*)"Nhan phim bat ky de quay lai Menu");

    setvisualpage(getactivepage());
    getch();
    clearmouseclick(WM_LBUTTONDOWN);
}