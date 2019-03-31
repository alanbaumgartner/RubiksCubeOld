#include <QGridLayout>
#include <iostream>
#include <string>
#include "common.hpp"
#include "gui.hpp"

Gui::Gui(QWidget *parent)
    : QWidget(parent) {

    cube = new Cube();

    for (int i = 0; i < 9; i++) {
        sides[i] = new QLabel(this); 
        sides[i]->setStyleSheet("QLabel { background-color : red;}");
        sides[i]->setGeometry((i % 3 * 20) + 65, (i / 3 * 20) + 5, 16, 16);
    }

    for (int i = 0; i < 36; i++) {
        sides[i + 9] = new QLabel(this); 
        sides[i + 9]->setStyleSheet("QLabel { background-color : red;}");
        sides[i + 9]->setGeometry((i % 12 * 20) + 5, (i / 12 * 20) + 65, 16, 16);
    }

    for (int i = 0; i < 9; i++) {
        sides[i + 45] = new QLabel(this); 
        sides[i + 45]->setStyleSheet("QLabel { background-color : red;}");
        sides[i + 45]->setGeometry((i % 3 * 20) + 65, (i / 3 * 20) + 125, 16, 16);
    }

    for (int i = 0; i < 48; i++) {
        std::string str = cube->get_func_name(i);
        QString qstr = QString::fromStdString(str);
        buttons[i] = new QPushButton(qstr, this); 
        buttons[i]->setGeometry((i % 6 * 52) + 255, (i / 6 * 32) + 5, 48, 28);
        connect(buttons[i], &QPushButton::clicked, this, [=, this]{ handle_button(i); });
    }

    

}

void Gui::handle_button(int index) {
    cube->call_func_index(index);
    update_cube();
}

void Gui::update_cube() {
    std::string up = cube->SideString(&UP, 1);
    std::string down = cube->SideString(&DOWN, 1);
    std::string left = cube->SideString(&LEFT, 0);
    std::string right = cube->SideString(&RIGHT, 0);
    std::string front = cube->SideString(&FRONT, 2);
    std::string back = cube->SideString(&BACK, 2);

    for (int i = 0; i < 9; i+=3) {
        set_color(i, back.at(CWTURN(i % 9, 2)));
        set_color(i + 1, back.at(CWTURN(i % 9, 1)));
        set_color(i + 2, back.at(CWTURN(i % 9, 0)));
    }

    for (int i = 9; i < 45; i+=12) {
        set_color(i, left.at(CWTURN(i % 9, 2)));
        set_color(i + 1, left.at(CWTURN(i % 9, 1)));
        set_color(i + 2, left.at(CWTURN(i % 9, 0)));

        set_color(i + 3, up.at(CWTURN(i % 9, 2)));
        set_color(i + 4, up.at(CWTURN(i % 9, 1)));
        set_color(i + 5, up.at(CWTURN(i % 9, 0)));

        set_color(i + 6, right.at(CWTURN(i % 9, 0)));
        set_color(i + 7, right.at(CWTURN(i % 9, 1)));
        set_color(i + 8, right.at(CWTURN(i % 9, 2)));

        set_color(i + 9, down.at(CWTURN(i % 9, 2)));
        set_color(i + 10, down.at(CWTURN(i % 9, 1)));
        set_color(i + 11, down.at(CWTURN(i % 9, 0)));
    }

    for (int i = 45; i < 54; i+=3) {
        set_color(i, front.at(CCTURN(i % 9, 0)));
        set_color(i + 1, front.at(CCTURN(i % 9, 1)));
        set_color(i + 2, front.at(CCTURN(i % 9, 2)));
    }
}

void Gui::set_color(int index, char color) {
    switch (color) {
        case '1':
            sides[index]->setStyleSheet("QLabel { background-color : gray;}");
            sides[index]->update();
            break;
        case '2':
            sides[index]->setStyleSheet("QLabel { background-color : yellow;}");
            sides[index]->update();
            break;
        case '3':
            sides[index]->setStyleSheet("QLabel { background-color : orange;}");
            sides[index]->update();
            break;
        case '4':
            sides[index]->setStyleSheet("QLabel { background-color : red;}");
            sides[index]->update();
            break;
        case '5':
            sides[index]->setStyleSheet("QLabel { background-color : green;}");
            sides[index]->update();
            break;
        case '6':
            sides[index]->setStyleSheet("QLabel { background-color : blue;}");
            sides[index]->update();
            break;
    }
}