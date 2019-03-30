// Copyright 2019 Alan Victor Baumgartner

#pragma once

#include <string>
#include "piece.hpp"
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key_extractors.hpp>
#include <boost/multi_index/ordered_index.hpp>

class Cube {
 public:
  Cube();
  ~Cube();

  void Print();

  void Play();
  void Solve();

  void U();
  void D();
  void L();
  void R();
  void F();
  void B();

  void U2();
  void D2();
  void L2();
  void R2();
  void F2();
  void B2();

  void UI();
  void DI();
  void LI();
  void RI();
  void FI();
  void BI();

  void u();
  void d();
  void l();
  void r();
  void f();
  void b();

  void u2();
  void d2();
  void l2();
  void r2();
  void f2();
  void b2();

  void ui();
  void di();
  void li();
  void ri();
  void fi();
  void bi();

  void M();
  void MI();
  void E();
  void EI();
  void S();
  void SI();

  void X();
  void XI();
  void Y();
  void YI();
  void Z();
  void ZI();

  void Randomize();
  double Score();
  bool Solved();

  Piece ** get_pieces() {
    return pieces_;
  }

 private:
  typedef void (Cube::*func_ptr)();

  struct func_struct {
    int index;
    std::string name;
    func_ptr func;
  };

  struct IndexByIndex {};
  struct IndexByName {};

  using Container = boost::multi_index_container<
    func_struct,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique<
        boost::multi_index::tag<IndexByIndex>,
        boost::multi_index::member<func_struct, int, &func_struct::index>
      >,
      boost::multi_index::hashed_unique<
        boost::multi_index::tag<IndexByName>,
        boost::multi_index::member<func_struct, std::string, &func_struct::name>
      >
    >
  >;

  Container func_map_;

  Piece * pieces_[26];

  bool InPlane(Piece * piece, const Eigen::Vector3i * plane);
  int populate_map(const Eigen::Vector3i * plane, int position);

  void PrintPiece(char color);
  void ResetPieces();

  double SideScore(const Eigen::Vector3i * side, int pos);
  std::string SideString(const Eigen::Vector3i * side, int pos);

  void SetupPieces();
};
