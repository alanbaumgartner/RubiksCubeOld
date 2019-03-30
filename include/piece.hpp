// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <iostream>
#include "common.hpp"

class Piece {
 public:
  Piece();
  Piece(Eigen::Vector3i pos, Eigen::Vector3i color) : pos_(pos), color_(color) {}

  void Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir);

  static bool compare(Piece * lhs, Piece * rhs) {
    if (lhs->pos_(0) < rhs->pos_(0)) {
      return true;
    }

    if (lhs->pos_(0) == rhs->pos_(0)) {
      if (lhs->pos_(1) < rhs->pos_(1)) {
        return true;
      }
      if (lhs->pos_(1) == rhs->pos_(1)) {
        if (lhs->pos_(2) < rhs->pos_(2)) {
          return true;
        }
      }
    }
    return false;
  }

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
