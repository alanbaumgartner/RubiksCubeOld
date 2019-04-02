// Copyright 2019 Alan Victor Baumgartner

#include <string>
#include "common.hpp"
#include "gui.hpp"

Gui::Gui(QWidget *parent)
    : QWidget(parent) {

    cube = new Cube();

    random = new QPushButton("Random", this); 
    random->setGeometry(187, 4 * 32 + 5, 64, 28);
    connect(random, &QPushButton::clicked, this, [this]{ randomize_cube(); });
    
    reset = new QPushButton("Reset", this);
    reset->setGeometry(187, 5 * 32 + 5, 64, 28);
    connect(reset, &QPushButton::clicked, this, [this]{ reset_cube(); });

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

    for (int i = 0; i < 36; i++) {
        std::string str = cube->get_func_name(i);
        QString qstr = QString::fromStdString(str);
        buttons[i] = new QPushButton(qstr, this); 
        buttons[i]->setGeometry((i % 6 * 52) + 255, (i / 6 * 32) + 5, 48, 28);
        connect(buttons[i], &QPushButton::clicked, this, [=]{ handle_button(i); });
    }
    update_cube();
}

void Gui::handle_button(int index) {
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
    QString qstr = "QLabel { background-color : ";
    switch (color) {
        case '1':
            qstr += "gray;}";
            break;
        case '2':
            qstr += "yellow;}";
            break;
        case '3':
            qstr += "orange;}";
            break;
        case '4':
            qstr += "red;}";
            break;
        case '5':
            qstr += "green;}";
            break;
        case '6':
            qstr += "blue;}";
            break;
    }
    sides[index]->setStyleSheet(qstr);
    sides[index]->update();
}