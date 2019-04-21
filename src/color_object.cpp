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

Gui::Gui(QWidget * parent, std::string color) : QWidget(parent), color_(color) {
    setStyleSheet(color_map[QString::fromStdString(color)]);
}
