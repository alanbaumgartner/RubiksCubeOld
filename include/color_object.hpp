// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <QLabel>

class ColorObject : public QLabel {
 public:
  ColorObject(QWidget * parent = 0, std::string color);

 private:
  std::string color;
};
