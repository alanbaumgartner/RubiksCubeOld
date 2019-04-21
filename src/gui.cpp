// Copyright 2019 Alan Victor Baumgartner

#include <string>
#include <unordered_map>
#include "common.hpp"
#include "gui.hpp"

static std::unordered_map<char, QString> color_map = {
    {'1', "QLabel { background-color : gray; }"},
    {'2', "QLabel { background-color : yellow; }"},
    {'3', "QLabel { background-color : orange; }"},
    {'4', "QLabel { background-color : red; }"},
    {'5', "QLabel { background-color : green; }"},
    {'6', "QLabel { background-color : blue; }"},
};

Gui::Gui(QWidget *parent) : QWidget(parent) {

    cube = new Cube();

    buttons[48] = new QPushButton("Random", this);
    buttons[48]->setGeometry(187, 4 * 32 + 5, 64, 28);
    connect(buttons[48], &QPushButton::clicked, this, [=]{ randomize_cube(); });

    buttons[49] = new QPushButton("Reset", this);
    buttons[49]->setGeometry(187, 5 * 32 + 5, 64, 28);
    connect(buttons[49], &QPushButton::clicked, this, [=]{ reset_cube(); });

    int x_pos;
    int y_pos;
    for (int i = 0; i < 9; i++) {
        x_pos = i % 3 * 20;
        y_pos = i / 3 * 20;

        // Back Pieces.
        sides[i] = new QLabel(this);
        sides[i]->setGeometry(x_pos + 65, y_pos + 5, 16, 16);

        // Front Pieces.
        sides[i + 45] = new QLabel(this);
        sides[i + 45]->setGeometry(x_pos + 65, y_pos + 125, 16, 16);
    }

    for (int i = 0; i < 36; i++) {
        x_pos = (i % 12 * 20);
        y_pos = (i / 12 * 20);
        // Left, Up, Right, Down Pieces.
        sides[i + 9] = new QLabel(this);
        sides[i + 9]->setGeometry(x_pos + 5, y_pos + 65, 16, 16);
    }

    for (int i = 0; i < 36; i++) {
        x_pos = (i % 6 * 52);
        y_pos = (i / 6 * 32);
        std::string str = cube->get_func_name(i);
        QString qstr = QString::fromStdString(str);
        buttons[i] = new QPushButton(qstr, this);
        buttons[i]->setGeometry(x_pos + 255, y_pos + 5, 48, 28);
        connect(buttons[i], &QPushButton::clicked, this, [=]{ rotate_cube(i); });
    }

    update_cube();
}

void Gui::rotate_cube(int index) {
    cube->call_func_index(index);
    update_cube();
}

void Gui::reset_cube() {
    cube->ResetPieces();
    update_cube();
}

void Gui::randomize_cube() {
    cube->Randomize();
    update_cube();
}

void Gui::update_cube() {
    std::string colors = cube->get_colors();
    for (int i = 0; i < 54; i++) {
        set_color(i, colors.at(i));
    }
}

void Gui::set_color(int index, char color) {
    sides[index]->setStyleSheet(color_map[color]);
    sides[index]->update();
}
