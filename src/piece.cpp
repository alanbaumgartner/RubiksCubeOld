// Copyright 2019 Alan Victor Baumgartner

#include "piece.hpp"

bool Piece::compare(std::shared_ptr<Piece> lhs, std::shared_ptr<Piece> rhs) {
    if (lhs->get_pos()(0) < rhs->get_pos()(0)) {
        return true;
    }

    if (lhs->get_pos()(0) == rhs->get_pos()(0)) {
        if (lhs->get_pos()(1) < rhs->get_pos()(1)) {
        return true;
        }
        if (lhs->get_pos()(1) == rhs->get_pos()(1)) {
        if (lhs->get_pos()(2) < rhs->get_pos()(2)) {
            return true;
        }
        }
    }
    return false;
}

void Piece::Rotate(const Eigen::Matrix3i * pos_dir, const Eigen::Matrix3i * color_dir) {
    lock_.lock();
    pos_ = *pos_dir * pos_;
    color_ = *color_dir * color_;
    lock_.unlock();
}

bool Piece::InPlane(const Eigen::Vector3i * plane) {
    return get_pos().dot(*plane) > 0;
}
