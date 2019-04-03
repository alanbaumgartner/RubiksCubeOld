// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <iostream>
#include "common.hpp"

class Piece {
 public:
  Piece(Eigen::Vector3i pos, Eigen::Vector3i color) :
    pos_(pos), color_(color) {}

  void Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir);

  static bool compare(Piece * lhs, Piece * rhs);

  Eigen::Vector3i get_pos() {
    return pos_;
  }

  Eigen::Vector3i get_color() {
    return color_;
  }

 private:
  Eigen::Vector3i pos_;
  Eigen::Vector3i color_;
};
