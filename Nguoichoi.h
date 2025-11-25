#pragma once
#include "DoiTuongGame.h"
#include "solieu.h"
#include <graphics.h>
#include <string>
#include <cstdlib>
#include <cmath>

class NguoiChoi : public DoiTuongGame {
public:
    NguoiChoi() : DoiTuongGame(1, 1) {}

    void diChuyen(int dr, int dc, char map[SO_HANG_MAP][SO_COT_MAP + 1], int &diem) {
        int hangTiepTheo = viTri.hang + dr;
        int cotTiepTheo = viTri.cot + dc;

        if (hangTiepTheo >= 0 && hangTiepTheo < SO_HANG_MAP && cotTiepTheo >= 0 && cotTiepTheo < SO_COT_MAP && map[hangTiepTheo][cotTiepTheo] != '#') {
            viTri.hang = hangTiepTheo;
            viTri.cot = cotTiepTheo;
            if (map[viTri.hang][viTri.cot] == '.') {
                map[viTri.hang][viTri.cot] = ' ';
                diem += 10;
            }
        }
    }
    void ve(int toaDoX, int toaDoY) override {
        int x = viTri.cot * KICH_THUOC_O + toaDoX;
        int y = viTri.hang * KICH_THUOC_O + toaDoY;
        readimagefile("Hinhanh/pacman4.bmp", x, y, x + KICH_THUOC_O, y + KICH_THUOC_O);
    }
};