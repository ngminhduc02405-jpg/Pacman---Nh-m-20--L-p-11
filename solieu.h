#ifndef SOLIEU_H
#define SOLIEU_H
#pragma once
#include <string>
using namespace std;
const int KICH_THUOC_O = 32;
const int SO_HANG_MAP = 17;
const int SO_COT_MAP = 21;
const int SO_LUONG_MA = 4;
struct ViTri {
    int hang;
    int cot;

    bool operator==(const ViTri& other) const {
        return hang == other.hang && cot == other.cot;
    }
};
struct DiemNguoiChoi {
    string ten;
    int diem;
};

bool soSanhDiem(const DiemNguoiChoi& a, const DiemNguoiChoi& b);
#endif
