#ifndef DOITUONGGAME_H
#define DOITUONGGAME_H
#include "solieu.h"
#include <graphics.h>
class DoiTuongGame {
protected:
    ViTri viTri;
    ViTri viTriBatDau;

public:
    DoiTuongGame(int r, int c) : viTri{r, c}, viTriBatDau{r, c} {}
    virtual ~DoiTuongGame() {}

    void datLaiViTri() {
        viTri = viTriBatDau;
    }

    ViTri layViTri() const { return viTri; }

    virtual void ve(int toaDoX, int toaDoY) = 0;
};
#endif