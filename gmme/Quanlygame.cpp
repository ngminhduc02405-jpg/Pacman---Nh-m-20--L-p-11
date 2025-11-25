#include "Quanlygame.h"
#include "NguoiChoi.h"
#include "Ma.h"
#include "Giaodiengame.h"
#include "solieu.h"
#include <graphics.h>
#include <conio.h>
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
QuanLyGame::QuanLyGame() : diem(0), mang(3), nhacBat(true), tenNguoiChoi("Player") {
    danhSachMa.push_back(Ma(10, 10, 1));
    danhSachMa.push_back(Ma(10, 5, 2));
    danhSachMa.push_back(Ma(15, 5, 3));
    danhSachMa.push_back(Ma(15, 15, 4));
}

void QuanLyGame::taiManChoi(int man) {
    char (*source_map)[SO_COT_MAP + 1];
    switch (man) {
        case 1: source_map = man1; break;
        case 2: source_map = man2; break;
        case 3: source_map = man3; break;
        case 4: source_map = man4; break;
        case 5: source_map = man5; break;
        default: source_map = man1; break;
    }
    memcpy(map, source_map, sizeof(map));
}

bool QuanLyGame::kiemTraThang() {
    for (int r = 0; r < SO_HANG_MAP; r++) {
        for (int c = 0; c < SO_COT_MAP; c++) {
            if (map[r][c] == '.') return false;
        }
    }
    return true;
}
void QuanLyGame::taiBangXepHang() {
    bangXepHang.clear();
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        file.open("bxh.txt");
        DiemNguoiChoi ps;
        while (file >> ps.ten >> ps.diem) {
            bangXepHang.push_back(ps);
        }
        file.close();
    } catch (const ifstream::failure& e) {
    }
}
void QuanLyGame::luuBangXepHang() {
    taiBangXepHang();
    bool daTimThay = false;
    for (auto& nguoiChoiTrongBXH : bangXepHang) {
        if (nguoiChoiTrongBXH.ten == tenNguoiChoi) {
            if (diem > nguoiChoiTrongBXH.diem) {
                nguoiChoiTrongBXH.diem = diem;
            }
            daTimThay = true;
            break;
        }
    }
    if (!daTimThay) {
        bangXepHang.push_back({tenNguoiChoi, diem});
    }
    sort(bangXepHang.begin(), bangXepHang.end(), soSanhDiem);
    ofstream file;
    file.exceptions(ofstream::failbit | ofstream::badbit);
    try {
        file.open("bxh.txt");
        for (const auto& ps : bangXepHang) {
            file << ps.ten << " " << ps.diem << endl;
        }
        file.close();
        taiBangXepHang();
    } catch (const ofstream::failure& e) {
        giaoDien.hienThiLoi("Loi: Khong the luu diem!");
    }
}

void QuanLyGame::chayGame(int man) {
    diem = 0;
    mang = 3;
    taiManChoi(man);
    nguoiChoi.datLaiViTri();
    for(auto& ma : danhSachMa) ma.datLaiViTri();

    cleardevice();
    setbkcolor(BLACK);

    int game_width = SO_COT_MAP * KICH_THUOC_O;
    int game_height = SO_HANG_MAP * KICH_THUOC_O;
    int toaDoX = (getmaxx() - game_width) / 2;
    int toaDoY = (getmaxy() - game_height) / 2;
    int activePage = 0, frameCount = 0;
    bool nhacan = false;

    while (true) {
        setactivepage(activePage);
        cleardevice();

        giaoDien.veMap(map, toaDoX, toaDoY);
        nguoiChoi.ve(toaDoX, toaDoY);
        for(auto& ma : danhSachMa) ma.ve(toaDoX, toaDoY);
        giaoDien.veThongTinGame(mang, diem, toaDoX, toaDoY, game_width);

        if (kbhit()) {
            char ch = getch();
            if (!nhacan && nhacBat && (ch == 'w' || ch == 'W' || ch == 'a' || ch == 'A' || ch == 's' || ch == 'S' || ch == 'd' || ch == 'D')) {
                PlaySound(TEXT("Hinhanh/waka.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                nhacan = true;
            }
            if (ch == 'w' || ch == 'W') nguoiChoi.diChuyen(-1, 0, map, diem);
            else if (ch == 's' || ch == 'S') nguoiChoi.diChuyen(1, 0, map, diem);
            else if (ch == 'a' || ch == 'A') nguoiChoi.diChuyen(0, -1, map, diem);
            else if (ch == 'd' || ch == 'D') nguoiChoi.diChuyen(0, 1, map, diem);
            else if (ch == 'q' || ch == 'Q') break;
        }

        if (frameCount % 4 == 0) {
            for(auto& ma : danhSachMa) ma.diChuyen(nguoiChoi, map);
        }

        if (kiemTraThang()) {
            PlaySound(NULL, 0, 0);
            luuBangXepHang();
            giaoDien.hienThiManHinhThang(tenNguoiChoi, diem, bangXepHang);
            break;
        }

        bool daChet = false;
        for(const auto& ma : danhSachMa) {
            if (nguoiChoi.layViTri() == ma.layViTri()) {
                daChet = true;
                break;
            }
        }

        if (daChet) {
            if(nhacan){ PlaySound(NULL, 0, 0); nhacan = false; }
            mang--;
            if (mang <= 0) {
                if(nhacBat) { PlaySound(TEXT("Hinhanh/death.wav"), NULL, SND_FILENAME | SND_ASYNC); }
                luuBangXepHang();
                giaoDien.hienThiManHinhThua(tenNguoiChoi, diem, bangXepHang);
                break;
            } else {
                nguoiChoi.datLaiViTri();
                for(auto& ma : danhSachMa) ma.datLaiViTri();
                delay(1000);
            }
        }

        delay(100);
        setvisualpage(activePage);
        activePage = 1 - activePage;
        frameCount++;
    }
    PlaySound(NULL, 0, 0);
}
void QuanLyGame::chayMenu() {
    int x, y, mucChon = 0, page = 0;
    bool thoatMenu = false;
    clearmouseclick(WM_LBUTTONDOWN);

    while (!thoatMenu) {
        setactivepage(page);
        cleardevice();

        if (ismouseclick(WM_MOUSEMOVE)) {
            getmouseclick(WM_MOUSEMOVE, x, y);
            if ((y >= 250 && y <= 350) && (x >= 300 && x <= 400)) mucChon = 1;
            else if ((y >= 375 && y <= 475) && (x >= 300 && x <= 400)) mucChon = 2;
            else if ((y >= 500 && y <= 600) && (x >= 300 && x <= 400)) mucChon = 3;
            else mucChon = 0;
        }

        giaoDien.veMenuChinh(mucChon, nhacBat);
        setvisualpage(page);

        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if ((y >= 250 && y <= 350) && (x >= 300 && x <= 400)) { // Play
                if (nhacBat) { PlaySound(TEXT("Hinhanh/Hinhanh_Theme1.wav"), NULL, SND_FILENAME | SND_ASYNC); }
                tenNguoiChoi = giaoDien.nhapTenNguoiChoi();
                int man = giaoDien.chonManChoi();
                chayGame(man);
                clearmouseclick(WM_LBUTTONDOWN);
            } else if ((y >= 375 && y <= 475) && (x >= 300 && x <= 400)) { // Ranking
                taiBangXepHang();
                giaoDien.hienThiBangXepHang(bangXepHang);
                getch();
                clearmouseclick(WM_LBUTTONDOWN);
            } else if ((y >= 500 && y <= 600) && (x >= 300 && x <= 400)) { // Exit
                thoatMenu = true;
            } else if ((x >= 25 && x <= 75) && (y >= 565 && y <= 615)) { // Volume
                nhacBat = !nhacBat;
                if (!nhacBat) PlaySound(NULL, 0, 0);
                clearmouseclick(WM_LBUTTONDOWN);
            } else if ((x >= 25 && x <= 75) && (y >= 625 && y <= 675)) { // Help
                giaoDien.hienThiHuongDan();
            }
        }
        page = 1 - page;
        delay(10);
    }
}