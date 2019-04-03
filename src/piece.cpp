// Copyright 2019 Alan Victor Baumgartner

#include "piece.hpp"

bool Piece::compare(Piece * lhs, Piece * rhs) {
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

void Piece::Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir) {
    pos_ = *pos_dir * pos_;
    color_ = *color_dir * color_;
}

