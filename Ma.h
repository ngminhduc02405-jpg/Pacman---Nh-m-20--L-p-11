#pragma once
#include "DoiTuongGame.h"
#include "NguoiChoi.h"
#include "solieu.h"
#include <graphics.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

class Ma : public DoiTuongGame {
private:
    string duongDanAnh;

public:
    Ma(int r, int c, int id) : DoiTuongGame(r, c) {
        duongDanAnh = "Hinhanh/anh" + to_string(id) + ".bmp";
    }

    void diChuyen(const NguoiChoi& nguoiChoi, char map[SO_HANG_MAP][SO_COT_MAP + 1]) {
        int cacHuongDi[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int huongDiTotNhat = -1;
        ViTri viTriNguoiChoi = nguoiChoi.layViTri();

        if (rand() % 100 < 50) { // 50% di chuyển thông minh
            int khoangCachNhoNhat = 9999;
            for (int i = 0; i < 4; i++) {
                int hangTiepTheo = viTri.hang + cacHuongDi[i][0];
                int cotTiepTheo = viTri.cot + cacHuongDi[i][1];
                if (hangTiepTheo >= 0 && hangTiepTheo < SO_HANG_MAP && cotTiepTheo >= 0 && cotTiepTheo < SO_COT_MAP && map[hangTiepTheo][cotTiepTheo] != '#') {
                    int khoangCach = abs(hangTiepTheo - viTriNguoiChoi.hang) + abs(cotTiepTheo - viTriNguoiChoi.cot);
                    if (khoangCach < khoangCachNhoNhat) {
                        khoangCachNhoNhat = khoangCach;
                        huongDiTotNhat = i;
                    }
                }
            }
        } else {
            vector<int> huongHopLe;
            for (int i = 0; i < 4; i++) {
                int hangTiepTheo = viTri.hang + cacHuongDi[i][0];
                int cotTiepTheo = viTri.cot + cacHuongDi[i][1];
                if (hangTiepTheo >= 0 && hangTiepTheo < SO_HANG_MAP && cotTiepTheo >= 0 && cotTiepTheo < SO_COT_MAP && map[hangTiepTheo][cotTiepTheo] != '#') {
                    huongHopLe.push_back(i);
                }
            }
            if (!huongHopLe.empty()) {
                huongDiTotNhat = huongHopLe[rand() % huongHopLe.size()];
            }
        }

        if (huongDiTotNhat != -1) {
            viTri.hang += cacHuongDi[huongDiTotNhat][0];
            viTri.cot += cacHuongDi[huongDiTotNhat][1];
        }
    }

    void ve(int toaDoX, int toaDoY) override {
        int x = viTri.cot * KICH_THUOC_O + toaDoX;
        int y = viTri.hang * KICH_THUOC_O + toaDoY;
        readimagefile((char*)duongDanAnh.c_str(), x, y, x + KICH_THUOC_O, y + KICH_THUOC_O);
    }
};