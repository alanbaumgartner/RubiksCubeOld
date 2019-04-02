// Copyright 2019 Alan Victor Baumgartner

#include <QApplication>
#include "gui.hpp"

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  

  Gui window;

  window.resize(567, 198);
  window.setWindowTitle("Rubiks Cube");
  window.show();
  
  return app.exec();
}
