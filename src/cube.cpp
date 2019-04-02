// Copyright 2019 Alan Victor Baumgartner

#include "cube.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <rang.hpp>

Cube::Cube() {
  SetupPieces();

  std::string func_names[48] = {
    "U", "D", "L", "R", "F", "B",
    "UI", "DI", "LI", "RI", "FI", "BI",
    "U2", "D2", "L2", "R2", "F2", "B2",
    "u", "d", "l", "r", "f", "b",
    "ui", "di", "li", "ri", "fi", "bi",
    "u2", "d2", "l2", "r2", "f2", "b2",
    "M", "MI", "E", "EI", "S", "SI",
    "X", "XI", "Y", "YI", "Z", "ZI",
  };

  func_ptr funcs[48] = {
    &Cube::U, &Cube::D, &Cube::L, &Cube::R, &Cube::F, &Cube::B,
};

  func_map_.insert({0, "U", &Cube::U});
  func_map_.insert({1, "D", &Cube::D});
  func_map_.insert({2, "L", &Cube::L});
  func_map_.insert({3, "R", &Cube::R});
  func_map_.insert({4, "F", &Cube::F});
  func_map_.insert({5, "B", &Cube::B});

  func_map_.insert({6, "UI", &Cube::UI});
  func_map_.insert({7, "DI", &Cube::DI});
  func_map_.insert({8, "LI", &Cube::LI});
  func_map_.insert({9, "RI", &Cube::RI});
  func_map_.insert({10, "FI", &Cube::FI});
  func_map_.insert({11, "BI", &Cube::BI});

  func_map_.insert({12, "U2", &Cube::U2});
  func_map_.insert({13, "D2", &Cube::D2});
  func_map_.insert({14, "L2", &Cube::L2});
  func_map_.insert({15, "R2", &Cube::R2});
  func_map_.insert({16, "F2", &Cube::F2});
  func_map_.insert({17, "B2", &Cube::B2});

  func_map_.insert({18, "u", &Cube::u});
  func_map_.insert({19, "d", &Cube::d});
  func_map_.insert({20, "l", &Cube::l});
  func_map_.insert({21, "r", &Cube::r});
  func_map_.insert({22, "f", &Cube::f});
  func_map_.insert({23, "b", &Cube::b});

  func_map_.insert({24, "ui", &Cube::ui});
  func_map_.insert({25, "di", &Cube::di});
  func_map_.insert({26, "li", &Cube::li});
  func_map_.insert({27, "ri", &Cube::ri});
  func_map_.insert({28, "fi", &Cube::fi});
  func_map_.insert({29, "bi", &Cube::bi});

  func_map_.insert({30, "u2", &Cube::u2});
  func_map_.insert({31, "d2", &Cube::d2});
  func_map_.insert({32, "l2", &Cube::l2});
  func_map_.insert({33, "r2", &Cube::r2});
  func_map_.insert({34, "f2", &Cube::f2});
  func_map_.insert({35, "b2", &Cube::b2});

  func_map_.insert({36, "M", &Cube::M});
  func_map_.insert({37, "MI", &Cube::MI});
  func_map_.insert({38, "E", &Cube::E});
  func_map_.insert({39, "EI", &Cube::EI});
  func_map_.insert({40, "S", &Cube::S});
  func_map_.insert({41, "SI", &Cube::SI});

  func_map_.insert({42, "X", &Cube::X});
  func_map_.insert({43, "XI", &Cube::XI});
  func_map_.insert({44, "Y", &Cube::Y});
  func_map_.insert({45, "YI", &Cube::YI});
  func_map_.insert({46, "Z", &Cube::Z});
  func_map_.insert({47, "ZI", &Cube::ZI});

  srand(time(NULL));
}

Cube::~Cube() {
  for (int i = 0; i < 26; i++) {
    delete pieces_[i];
  }
}

void Cube::Print() {
  sort();
  std::string up = SideString(&UP, 1);
  std::string down = SideString(&DOWN, 1);
  std::string left = SideString(&LEFT, 0);
  std::string right = SideString(&RIGHT, 0);
  std::string front = SideString(&FRONT, 2);
  std::string back = SideString(&BACK, 2);

  for (int i = 0; i < 9; i+=3) {
    std::cout << "      ";
    PrintPiece(back.at(CWTURN(i, 2)));
    PrintPiece(back.at(CWTURN(i, 1)));
    PrintPiece(back.at(CWTURN(i, 0)));
    std::cout << std::endl;
  }

  for (int i = 0; i < 9; i+=3) {
    PrintPiece(left.at(CWTURN(i, 2)));
    PrintPiece(left.at(CWTURN(i, 1)));
    PrintPiece(left.at(CWTURN(i, 0)));

    PrintPiece(up.at(CWTURN(i, 2)));
    PrintPiece(up.at(CWTURN(i, 1)));
    PrintPiece(up.at(CWTURN(i, 0)));

    PrintPiece(right.at(CWTURN(i, 0)));
    PrintPiece(right.at(CWTURN(i, 1)));
    PrintPiece(right.at(CWTURN(i, 2)));

    PrintPiece(down.at(CWTURN(i, 2)));
    PrintPiece(down.at(CWTURN(i, 1)));
    PrintPiece(down.at(CWTURN(i, 0)));
    std::cout << std::endl;
  }

  for (int i = 0; i < 9; i+=3) {
    std::cout << "      ";
    PrintPiece(front.at(CCTURN(i, 0)));
    PrintPiece(front.at(CCTURN(i, 1)));
    PrintPiece(front.at(CCTURN(i, 2)));
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Cube::Play() {
  std::string t;
  Print();
  while (std::cin >> t) {
    if (t == "exit") {
      return;
    }
    if (t == "reset") {
      ResetPieces();
    }
    if (t == "random") {
      Randomize();
    }
    auto& ibn = func_map_.get<IndexByName>();
    auto found = ibn.find(t);
    if (found != ibn.end()) {
      (this->*found->func)();
    }
    Print();
  }
}

void Cube::Solve() {}

void Cube::U() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &UP)) {
      pieces_[i]->Rotate(&ROTATE_Y_CW, &ROTATE_COLOR_Y);
    }
  }
}

void Cube::D() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &DOWN)) {
      pieces_[i]->Rotate(&ROTATE_Y_CC, &ROTATE_COLOR_Y);
    }
  }
}

void Cube::L() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &LEFT)) {
      pieces_[i]->Rotate(&ROTATE_X_CW, &ROTATE_COLOR_X);
    }
  }
}

void Cube::R() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &RIGHT)) {
      pieces_[i]->Rotate(&ROTATE_X_CC, &ROTATE_COLOR_X);
    }
  }
}

void Cube::F() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &FRONT)) {
      pieces_[i]->Rotate(&ROTATE_Z_CW, &ROTATE_COLOR_Z);
    }
  }
}

void Cube::B() {
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], &BACK)) {
      pieces_[i]->Rotate(&ROTATE_Z_CC, &ROTATE_COLOR_Z);
    }
  }
}

void Cube::U2() {
  U();
  U();
}

void Cube::D2() {
  D();
  D();
}

void Cube::L2() {
  L();
  L();
}

void Cube::R2() {
  R();
  R();
}

void Cube::F2() {
  F();
  F();
}

void Cube::B2() {
  B();
  B();
}

void Cube::UI() {
  U();
  U();
  U();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], UP)) {
  //     pieces_[i]->Rotate(ROTATE_Y_CC);
  //   }
  // }
}

void Cube::DI() {
  D();
  D();
  D();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], DOWN)) {
  //     pieces_[i]->Rotate(ROTATE_Y_CW);
  //   }
  // }
}

void Cube::LI() {
  L();
  L();
  L();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], LEFT)) {
  //     pieces_[i]->Rotate(ROTATE_X_CC);
  //   }
  // }
}

void Cube::RI() {
  R();
  R();
  R();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], RIGHT)) {
  //     pieces_[i]->Rotate(ROTATE_X_CW);
  //   }
  // }
}

void Cube::FI() {
  F();
  F();
  F();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], FRONT)) {
  //     pieces_[i]->Rotate(ROTATE_Z_CC);
  //   }
  // }
}

void Cube::BI() {
  B();
  B();
  B();
  // for (int i = 0; i < 26; i++) {
  //   if (InPlane(pieces_[i], BACK)) {
  //     pieces_[i]->Rotate(ROTATE_Z_CW);
  //   }
  // }
}

void Cube::u() {
  U();
  EI();
}

void Cube::d() {
  D();
  E();
}

void Cube::l() {
  L();
  M();
}

void Cube::r() {
  R();
  MI();
}

void Cube::f() {
  F();
  S();
}

void Cube::b() {
  B();
  SI();
}

void Cube::u2() {
  U2();
  EI();
  EI();
}

void Cube::d2() {
  D2();
  E();
  E();
}

void Cube::l2() {
  L2();
  M();
  M();
}

void Cube::r2() {
  R2();
  MI();
  MI();
}

void Cube::f2() {
  F2();
  S();
  S();
}

void Cube::b2() {
  B2();
  SI();
  SI();
}

void Cube::ui() {
  UI();
  E();
}

void Cube::di() {
  D();
  EI();
}

void Cube::li() {
  LI();
  MI();
}

void Cube::ri() {
  RI();
  M();
}

void Cube::fi() {
  FI();
  SI();
}

void Cube::bi() {
  BI();
  S();
}

void Cube::M() {
  LI();
  R();
  XI();
}

void Cube::MI() {
  M();
  M();
  M();
  // L();
  // RI();
  // X();
}

void Cube::E() {
  DI();
  U();
  YI();
}

void Cube::EI() {
  E();
  E();
  E();
  // D();
  // UI();
  // Y();
}

void Cube::S() {
  FI();
  B();
  Z();
}

void Cube::SI() {
  S();
  S();
  S();
  // F();
  // BI();
  // ZI();
}

void Cube::X() {
  for (int i = 0; i < 26; i++) {
      pieces_[i]->Rotate(&ROTATE_X_CC, &ROTATE_COLOR_X);
  }
}

void Cube::XI() {
  X();
  X();
  X();
  // for (int i = 0; i < 26; i++) {
  //     pieces_[i]->Rotate(ROTATE_X_CW);
  // }
}

void Cube::Y() {
  for (int i = 0; i < 26; i++) {
      pieces_[i]->Rotate(&ROTATE_Y_CW, &ROTATE_COLOR_Y);
  }
}

void Cube::YI() {
  Y();
  Y();
  Y();
  // for (int i = 0; i < 26; i++) {
  //     pieces_[i]->Rotate(ROTATE_Y_CC);
  // }
}

void Cube::Z() {
  for (int i = 0; i < 26; i++) {
      pieces_[i]->Rotate(&ROTATE_Z_CW, &ROTATE_COLOR_Z);
  }
}

void Cube::ZI() {
  Z();
  Z();
  Z();
  // for (int i = 0; i < 26; i++) {
  //     pieces_[i]->Rotate(ROTATE_Z_CC);
  // }
}

std::string Cube::get_colors() {
    sort();
    std::string up = SideString(&UP, 1);
    std::string down = SideString(&DOWN, 1);
    std::string left = SideString(&LEFT, 0);
    std::string right = SideString(&RIGHT, 0);
    std::string front = SideString(&FRONT, 2);
    std::string back = SideString(&BACK, 2);

    std::string colors = "";

    for (int i = 0; i < 9; i+=3) {
        colors += back.at(CWTURN(i % 9, 2));
        colors += back.at(CWTURN(i % 9, 1));
        colors +=  back.at(CWTURN(i % 9, 0));
    }

    for (int i = 9; i < 45; i+=12) {
        colors += left.at(CWTURN(i % 9, 2));
        colors += left.at(CWTURN(i % 9, 1));
        colors += left.at(CWTURN(i % 9, 0));

        colors += up.at(CWTURN(i % 9, 2));
        colors += up.at(CWTURN(i % 9, 1));
        colors += up.at(CWTURN(i % 9, 0));

        colors += right.at(CWTURN(i % 9, 0));
        colors += right.at(CWTURN(i % 9, 1));
        colors += right.at(CWTURN(i % 9, 2));

        colors += down.at(CWTURN(i % 9, 2));
        colors += down.at(CWTURN(i % 9, 1));
        colors += down.at(CWTURN(i % 9, 0));
    }

    for (int i = 45; i < 54; i+=3) {
        colors += front.at(CCTURN(i % 9, 0));
        colors += front.at(CCTURN(i % 9, 1));
        colors += front.at(CCTURN(i % 9, 2));
    }
    return colors;
}

void Cube::Randomize() {
  for (int i = 0; i < 999; i++) {
    call_func_index(rand() % 48);
  }
  std::sort(std::begin(pieces_), std::end(pieces_), Piece::compare);
}

double Cube::Score() {
  double score = SideScore(&UP, 1) + SideScore(&DOWN, 1) + SideScore(&LEFT, 0) + SideScore(&RIGHT, 0) + SideScore(&FRONT, 2) + SideScore(&BACK, 2);
  score = score/6;
  return score;
}

bool Cube::Solved() {
  return Score() == 1;
}

void Cube::sort() {
  std::sort(std::begin(pieces_), std::end(pieces_), Piece::compare);
}

std::string Cube::get_func_name(int index) {
  auto& ibi = func_map_.get<IndexByIndex>();
  auto found = ibi.find(index);
  if (found != ibi.end()) {
    return found->name;
  }
}

void Cube::call_func_index(int index) {
  auto& ibi = func_map_.get<IndexByIndex>();
  auto found = ibi.find(index);
  if (found != ibi.end()) {
    (this->*found->func)();
  }
}

void Cube::call_func_string(std::string name) {
  auto& ibn = func_map_.get<IndexByName>();
  auto found = ibn.find(name);
  if (found != ibn.end()) {
    (this->*found->func)();
  }
}


bool Cube::InPlane(Piece * piece, const Eigen::Vector3i * plane) {
  return piece->get_pos().dot(*plane) > 0;
}

int Cube::populate_map(const Eigen::Vector3i * plane, int position) {
  std::map<int, int> vals;
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], plane)) {
      int color = pieces_[i]->get_color()(position);
      if (vals.find(color) == vals.end()) {
        vals[color] = 1;
      } else {
        int temp = ++vals[color];
        if (max < temp) {
          max = temp;
        }
      }
    }
  }
  return max;
}

void Cube::PrintPiece(char color) {
  switch (color) {
    case '1':
      std::cout << rang::fg::gray << char(254) << rang::fg::reset << " ";
      break;
    case '2':
      std::cout << rang::fg::yellow << char(254) << rang::fg::reset << " ";
      break;
    case '3':
      std::cout << rang::fg::magenta << char(254) << rang::fg::reset << " ";
      break;
    case '4':
      std::cout << rang::fg::red << char(254) << rang::fg::reset << " ";
      break;
    case '5':
      std::cout << rang::fg::green << char(254) << rang::fg::reset << " ";
      break;
    case '6':
      std::cout << rang::fg::blue << char(254) << rang::fg::reset << " ";
      break;
    default:
      break;
  }
}

void Cube::ResetPieces() {
  for (int i = 0; i < 26; i++) {
    delete pieces_[i];
  }
  SetupPieces();
}

double Cube::SideScore(const Eigen::Vector3i * side, int pos) {
  int max = populate_map(side, pos);
  return log(max)/log(9);
}

std::string Cube::SideString(const Eigen::Vector3i * side, int pos) {
  std::string list = "";
  for (int i = 0; i < 26; i++) {
    if (InPlane(pieces_[i], side)) {
      list += std::to_string(pieces_[i]->get_color()(pos));
    }
  }
  return list;
}

void Cube::SetupPieces() {
  pieces_[0] = new Piece(UP, WHITE);
  pieces_[1] = new Piece(UP + LEFT, WHITE + ORANGE);
  pieces_[2] = new Piece(UP + RIGHT, WHITE + RED);
  pieces_[3] = new Piece(UP + FRONT, WHITE + GREEN);
  pieces_[4] = new Piece(UP + BACK, WHITE + BLUE);
  pieces_[5] = new Piece(UP + LEFT + FRONT, WHITE + ORANGE + GREEN);
  pieces_[6] = new Piece(UP + LEFT + BACK, WHITE + ORANGE + BLUE);
  pieces_[7] = new Piece(UP + RIGHT + FRONT, WHITE + RED + GREEN);
  pieces_[8] = new Piece(UP + RIGHT + BACK, WHITE + RED + BLUE);
  pieces_[9] = new Piece(DOWN, YELLOW);
  pieces_[10] = new Piece(DOWN + LEFT, YELLOW + ORANGE);
  pieces_[11] = new Piece(DOWN + RIGHT, YELLOW + RED);
  pieces_[12] = new Piece(DOWN + FRONT, YELLOW + GREEN);
  pieces_[13] = new Piece(DOWN + BACK, YELLOW + BLUE);
  pieces_[14] = new Piece(DOWN + LEFT + FRONT, YELLOW + ORANGE + GREEN);
  pieces_[15] = new Piece(DOWN + LEFT + BACK, YELLOW + ORANGE + BLUE);
  pieces_[16] = new Piece(DOWN + RIGHT + FRONT, YELLOW + RED + GREEN);
  pieces_[17] = new Piece(DOWN + RIGHT + BACK, YELLOW + RED + BLUE);
  pieces_[18] = new Piece(LEFT, ORANGE);
  pieces_[19] = new Piece(RIGHT, RED);
  pieces_[20] = new Piece(FRONT, GREEN);
  pieces_[21] = new Piece(BACK, BLUE);
  pieces_[22] = new Piece(LEFT + FRONT, ORANGE + GREEN);
  pieces_[23] = new Piece(RIGHT + FRONT, RED + GREEN);
  pieces_[24] = new Piece(LEFT + BACK, ORANGE + BLUE);
  pieces_[25] = new Piece(RIGHT + BACK, RED + BLUE);
}
