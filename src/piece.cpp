// Copyright 2019 Alan Victor Baumgartner

#include "piece.hpp"

Piece::Piece() {}

void Piece::Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir) {
    pos_ = *pos_dir * pos_;
    color_ = *color_dir * color_;
}
