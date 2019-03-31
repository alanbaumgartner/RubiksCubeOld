#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "cube.hpp"

class Gui : public QWidget {
    
  public:
    Gui(QWidget *parent = 0);

  private:
    Cube * cube;
    QPushButton * buttons[48];
    QLabel * sides[54];

    void handle_button(int index);
    void update_cube();
    void set_color(int index, char color);
};