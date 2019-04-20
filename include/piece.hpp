// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include "common.hpp"

class Piece {
 public:
  Piece(Eigen::Vector3i pos, Eigen::Vector3i color) : pos_(pos), color_(color) {}

  void Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir);

  static bool compare(std::shared_ptr<Piece> lhs, std::shared_ptr<Piece> rhs);

  bool InPlane(const Eigen::Vector3i * plane);

  Eigen::Vector3i get_pos() const {
    return pos_;
  }

  Eigen::Vector3i get_color() const {
    return color_;
  }

 private:
  std::mutex lock_;
  Eigen::Vector3i pos_;
  Eigen::Vector3i color_;
};
