#pragma once
#include "solieu.h"
#include <vector>
#include <string>

class GiaoDienGame {
public:
    void veMap(const char map[SO_HANG_MAP][SO_COT_MAP + 1], int toaDoX, int toaDoY);
    void veThongTinGame(int mang, int diem, int toaDoX, int toaDoY, int game_width);
    void veMenuChinh(int mucChon, bool nhacBat);
    void hienThiHuongDan();
    void hienThiBangXepHang(const vector<DiemNguoiChoi>& danhSach);
    void hienThiManHinhThang(const string& ten, int diem, const vector<DiemNguoiChoi>& bxh);
    void hienThiManHinhThua(const string& ten, int diem, const vector<DiemNguoiChoi>& bxh);
    void hienThiLoi(const string& thongBao);
    string nhapTenNguoiChoi();
    int chonManChoi();
};
