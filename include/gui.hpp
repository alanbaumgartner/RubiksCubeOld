// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <QWidget>
#include <QPushButton>
#include "color_object.hpp"
#include "cube.hpp"

class Gui : public QWidget {
 public:
  explicit Gui(QWidget *parent = 0);

 private:
  Cube * cube;
  QPushButton * buttons[50];
  ColorObject * sides[54];

  void rotate_cube(int index);
  void reset_cube();
  void randomize_cube();
  void update_cube();
  void set_color(int index, char color);
};
