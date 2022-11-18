// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //

bool operator==(const WordLocation& lhs, const WordLocation& rhs) {
  if (lhs.word != rhs.word) return false;
  if (lhs.char_positions.size() != rhs.char_positions.size()) return false;
  for (size_t i = 0; i < lhs.char_positions.size(); ++i) {
    if (lhs.char_positions.at(i).character !=
        rhs.char_positions.at(i).character)
      return false;
    if (lhs.char_positions.at(i).row != rhs.char_positions.at(i).row)
      return false;
    if (lhs.char_positions.at(i).col != rhs.char_positions.at(i).col)
      return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

// TEST_CASE("LocationInBound") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
//                                         {'h', 'e', 'l', 'l', 'o'},
//                                         {'c', 'a', 'l', 'o', 'm'},
//                                         {'a', 'e', 't', 'a', 'u'},
//                                         {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
//   REQUIRE(wss.LocationInBounds(0, 0) == true);
//   REQUIRE(wss.LocationInBounds(0, 2) == true);
//   REQUIRE(wss.LocationInBounds(4, 0) == true);
//   REQUIRE(wss.LocationInBounds(-1, -1) == false);
//   REQUIRE(wss.LocationInBounds(-3, 0) == false);
//   REQUIRE(wss.LocationInBounds(0, -9) == false);
//   REQUIRE(wss.LocationInBounds(9, 0) == false);
//   REQUIRE(wss.LocationInBounds(10, 10) == false);
//   REQUIRE(wss.LocationInBounds(0, 9) == false);
//   REQUIRE(wss.LocationInBounds(5, 5) == false);
// }

// TEST_CASE("constructor") {
//   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
//                                         {'h', 'e', 'l', 'l', 'o'},
//                                         {'c', 'a', 'l', 'o', 'm'},
//                                         {'a', 'e', 't', 'a', 'u'},
//                                         {'t', 'e', 't', 'o', 'u'}};
//   WordSearchSolver wss(puzzle);
// }

TEST_CASE("tests") {
  // clang-format off
  CharPositions a{}, b{}, c{}, d{}, e{}, 
                f{}, g{}, h{}, i{}, j{}, 
                k{}, l{}, m{}, n{}, o{}, 
                p{}, q{}, r{}, s{}, t{}, 
                u{}, v{}, w{}, x{}, y{};
                
  a.character = 'a'; a.row = 0; a.col = 0;
  b.character = 'b'; b.row = 0; b.col = 1;
  c.character = 'c'; c.row = 0; c.col = 2;
  d.character = 'd'; d.row = 0; d.col = 3;
  e.character = 'e'; e.row = 0; e.col = 4;

  f.character = 'f'; f.row = 1; f.col = 0;
  g.character = 'g'; g.row = 1; g.col = 1;
  h.character = 'h'; h.row = 1; h.col = 2;
  i.character = 'i'; i.row = 1; i.col = 3;
  j.character = 'j'; j.row = 1; j.col = 4;

  k.character = 'k'; k.row = 2; k.col = 0;
  l.character = 'l'; l.row = 2; l.col = 1;
  m.character = 'm'; m.row = 2; m.col = 2; 
  n.character = 'n'; n.row = 2; n.col = 3;
  o.character = 'o'; o.row = 2; o.col = 4;

  p.character = 'p'; p.row = 3; p.col = 0; 
  q.character = 'q'; q.row = 3; q.col = 1;
  r.character = 'r'; r.row = 3; r.col = 2;
  s.character = 's'; s.row = 3; s.col = 3;
  t.character = 't'; t.row = 3; t.col = 4;

  u.character = 'u'; u.row = 4; u.col = 0; 
  v.character = 'v'; v.row = 4; v.col = 1; 
  w.character = 'w'; w.row = 4; w.col = 2;
  x.character = 'x'; x.row = 4; x.col = 3;
  y.character = 'y'; y.row = 4; y.col = 4;
  // clang-format on

  std::vector<std::vector<char>> puzzle{{'a', 'b', 'c', 'd', 'e'},
                                        {'f', 'g', 'h', 'i', 'j'},
                                        {'k', 'l', 'm', 'n', 'o'},
                                        {'p', 'q', 'r', 's', 't'},
                                        {'u', 'v', 'w', 'x', 'y'}};
  WordSearchSolver wss(puzzle);

  // overall test
  REQUIRE(wss.FindWord("hello") == WordLocation{});
  REQUIRE(wss.FindWord("abcde").word == "abcde");
  REQUIRE(wss.FindWord("klmno").word == "klmno");
  REQUIRE(wss.FindWord("klmno").char_positions.at(0).row == 2);
  REQUIRE(wss.FindWord("klmno").char_positions.at(1).col == 1);

  // agm  right diag match
  std::string word_agm = "agm";
  WordLocation agm{};
  agm.word = word_agm;
  agm.char_positions = {a, g, m};
  REQUIRE(wss.FindWord(word_agm) == agm);
  REQUIRE(wss.FindWord(word_agm, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agm, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_agm, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_agm, CheckDirection::kRightDiag) == agm);

  // msy right diag match
  std::string word_msy = "msy";
  WordLocation msy{};
  msy.word = word_msy;
  msy.char_positions = {m, s, y};
  REQUIRE(wss.FindWord(word_msy) == msy);
  REQUIRE(wss.FindWord(word_msy, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_msy, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_msy, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_msy, CheckDirection::kRightDiag) == msy);

  // ghij  horizontal match
  std::string word_ghij = "ghij";
  WordLocation ghij{};
  ghij.word = word_ghij;
  ghij.char_positions = {g, h, i, j};
  REQUIRE(wss.FindWord(word_ghij) == ghij);
  REQUIRE(wss.FindWord(word_ghij, CheckDirection::kHorizontal) == ghij);
  REQUIRE(wss.FindWord(word_ghij, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_ghij, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_ghij, CheckDirection::kRightDiag) ==
          WordLocation{});

  // uv  horizontal match
  std::string word_uv = "uv";
  WordLocation uv{};
  uv.word = word_uv;
  uv.char_positions = {u, v};
  REQUIRE(wss.FindWord(word_uv) == uv);
  REQUIRE(wss.FindWord(word_uv, CheckDirection::kHorizontal) == uv);
  REQUIRE(wss.FindWord(word_uv, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_uv, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_uv, CheckDirection::kRightDiag) == WordLocation{});

  // qu  vertical match
  std::string word_qu = "qu";
  WordLocation qu{};
  qu.word = word_qu;
  qu.char_positions = {q, u};
  REQUIRE(wss.FindWord(word_qu) == qu);
  REQUIRE(wss.FindWord(word_qu, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(word_qu, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_qu, CheckDirection::kLeftDiag) == qu);
  REQUIRE(wss.FindWord(word_qu, CheckDirection::kRightDiag) == WordLocation{});

  // eim  left diag match
  std::string word_eim = "eim";
  WordLocation eim{};
  eim.word = word_eim;
  eim.char_positions = {e, i, m};
  REQUIRE(wss.FindWord(word_eim) == eim);
  REQUIRE(wss.FindWord(word_eim, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_eim, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_eim, CheckDirection::kLeftDiag) == eim);
  REQUIRE(wss.FindWord(word_eim, CheckDirection::kRightDiag) == WordLocation{});

  // ejo  vertical match
  std::string word_ejo = "ejo";
  WordLocation ejo{};
  ejo.word = word_ejo;
  ejo.char_positions = {e, j, o};
  REQUIRE(wss.FindWord(word_ejo) == ejo);
  REQUIRE(wss.FindWord(word_ejo, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_ejo, CheckDirection::kVertical) == ejo);
  REQUIRE(wss.FindWord(word_ejo, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_ejo, CheckDirection::kRightDiag) == WordLocation{});

  // agcde  horizontal no match
  std::string word_agcde = "agcde";
  WordLocation agcde{};
  agcde.word = word_agcde;
  agcde.char_positions = {a, g, c, d, e};
  REQUIRE(wss.FindWord(word_agcde) == WordLocation{});
  REQUIRE(wss.FindWord(word_agcde, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agcde, CheckDirection::kVertical) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agcde, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agcde, CheckDirection::kRightDiag) ==
          WordLocation{});

  // gas  right diag no match
  std::string word_gas = "gas";
  WordLocation gas{};
  gas.word = word_gas;
  gas.char_positions = {g, a, s};
  REQUIRE(wss.FindWord(word_gas) == WordLocation{});
  REQUIRE(wss.FindWord(word_gas, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_gas, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_gas, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_gas, CheckDirection::kRightDiag) == WordLocation{});

  // mrx  vertical no match
  std::string word_mrx = "mrx";
  WordLocation mrx{};
  mrx.word = word_mrx;
  mrx.char_positions = {m, r, x};
  REQUIRE(wss.FindWord(word_mrx) == WordLocation{});
  REQUIRE(wss.FindWord(word_mrx, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_mrx, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_mrx, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_mrx, CheckDirection::kRightDiag) == WordLocation{});

  // abcde  horizontal match
  std::string word_abcde = "abcde";
  WordLocation abcde{};
  abcde.word = word_abcde;
  abcde.char_positions = {a, b, c, d, e};
  REQUIRE(wss.FindWord(word_abcde) == abcde);
  REQUIRE(wss.FindWord(word_abcde, CheckDirection::kHorizontal) == abcde);
  REQUIRE(wss.FindWord(word_abcde, CheckDirection::kVertical) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_abcde, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_abcde, CheckDirection::kRightDiag) ==
          WordLocation{});

  // uvwxy  horizontal match
  std::string word_uvwxy = "uvwxy";
  WordLocation uvwxy{};
  uvwxy.word = word_uvwxy;
  uvwxy.char_positions = {u, v, w, x, y};
  REQUIRE(wss.FindWord(word_uvwxy) == uvwxy);
  REQUIRE(wss.FindWord(word_uvwxy, CheckDirection::kHorizontal) == uvwxy);
  REQUIRE(wss.FindWord(word_uvwxy, CheckDirection::kVertical) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_uvwxy, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_uvwxy, CheckDirection::kRightDiag) ==
          WordLocation{});

  // afkpu  vertical match
  std::string word_afkpu = "afkpu";
  WordLocation afkpu{};
  afkpu.word = word_afkpu;
  afkpu.char_positions = {a, f, k, p, u};
  REQUIRE(wss.FindWord(word_afkpu) == afkpu);
  REQUIRE(wss.FindWord(word_afkpu, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_afkpu, CheckDirection::kVertical) == afkpu);
  REQUIRE(wss.FindWord(word_afkpu, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_afkpu, CheckDirection::kRightDiag) ==
          WordLocation{});

  // ejoty  vertical match
  std::string word_ejoty = "ejoty";
  WordLocation ejoty{};
  ejoty.word = word_ejoty;
  ejoty.char_positions = {e, j, o, t, y};
  REQUIRE(wss.FindWord(word_ejoty) == ejoty);
  REQUIRE(wss.FindWord(word_ejoty, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_ejoty, CheckDirection::kVertical) == ejoty);
  REQUIRE(wss.FindWord(word_ejoty, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_ejoty, CheckDirection::kRightDiag) ==
          WordLocation{});

  // agmsy  right diag match
  std::string word_agmsy = "agmsy";
  WordLocation agmsy{};
  agmsy.word = word_agmsy;
  agmsy.char_positions = {a, g, m, s, y};
  REQUIRE(wss.FindWord(word_agmsy) == agmsy);
  REQUIRE(wss.FindWord(word_agmsy, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agmsy, CheckDirection::kVertical) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agmsy, CheckDirection::kLeftDiag) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_agmsy, CheckDirection::kRightDiag) == agmsy);

  // eimqu  left diag match
  std::string word_eimqu = "eimqu";
  WordLocation eimqu{};
  eimqu.word = word_eimqu;
  eimqu.char_positions = {e, i, m, q, u};
  REQUIRE(wss.FindWord(word_eimqu) == eimqu);
  REQUIRE(wss.FindWord(word_eimqu, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_eimqu, CheckDirection::kVertical) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_eimqu, CheckDirection::kLeftDiag) == eimqu);
  REQUIRE(wss.FindWord(word_eimqu, CheckDirection::kRightDiag) ==
          WordLocation{});

  // ags
  std::string word_ags = "ags";
  WordLocation ags{};
  ags.word = word_ags;
  ags.char_positions = {a, g, s};
  REQUIRE(wss.FindWord(word_ags) == WordLocation{});
  REQUIRE(wss.FindWord(word_ags, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_ags, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_ags, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_ags, CheckDirection::kRightDiag) == WordLocation{});

  // hmp left diag no match
  std::string word_hmp = "hmp";
  WordLocation hmp{};
  hmp.word = word_hmp;
  hmp.char_positions = {h, m, p};
  REQUIRE(wss.FindWord(word_hmp) == WordLocation{});
  REQUIRE(wss.FindWord(word_hmp, CheckDirection::kHorizontal) ==
          WordLocation{});
  REQUIRE(wss.FindWord(word_hmp, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(word_hmp, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(word_hmp, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("chage the board size") {
  std::vector<std::vector<char>> puzzle{{'a', 'b', 'c', 'd', 'e', 'm'},
                                        {'f', 'g', 'h', 'n', 'j', 'l'},
                                        {'k', 'l', 'm', 'n', 's', 'k'},
                                        {'p', 'q', 'r', 's', 't', 'q'},
                                        {'u', 'v', 'w', 'x', 'y', 'a'},
                                        {'m', 'c', 'd', 't', 'p', 'f'},
                                        {'c', 'j', 'k', 't', 'y', 'u'}};
  WordSearchSolver wss(puzzle);

  // nnxs
  std::string nnsx = "nnsx";
  // clang-format off
  REQUIRE(wss.FindWord(nnsx).char_positions.at(0).character == 'n');
  REQUIRE(wss.FindWord(nnsx).char_positions.at(1).character == 'n');
  REQUIRE(wss.FindWord(nnsx).char_positions.at(2).character == 's');
  REQUIRE(wss.FindWord(nnsx).char_positions.at(1).col == 3);
  REQUIRE(wss.FindWord(nnsx).char_positions.at(1).row == 2);
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).word == nnsx);
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).char_positions.at(0).character == 'n');
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).char_positions.at(1).character == 'n');
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).char_positions.at(2).character == 's');
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).char_positions.at(1).col == 3);
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kVertical).char_positions.at(1).row == 2);
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(nnsx, CheckDirection::kRightDiag) == WordLocation{});

  // no match
  REQUIRE(wss.FindWord("dtf") == WordLocation{});
  REQUIRE(wss.FindWord("dtf", CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord("dtf", CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord("dtf", CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord("dtf", CheckDirection::kRightDiag) == WordLocation{});

  // afu
  std::string afu = "afu";
  REQUIRE(wss.FindWord(afu).char_positions.at(0).character == 'a');
  REQUIRE(wss.FindWord(afu).char_positions.at(1).character == 'f');
  REQUIRE(wss.FindWord(afu).char_positions.at(2).character == 'u');
  REQUIRE(wss.FindWord(afu).char_positions.at(1).col == 5);
  REQUIRE(wss.FindWord(afu).char_positions.at(1).row == 5);
  REQUIRE(wss.FindWord(afu, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(afu, CheckDirection::kVertical).word == afu);
  REQUIRE(wss.FindWord(afu, CheckDirection::kVertical)
              .char_positions.at(0)
              .character == 'a');
  REQUIRE(wss.FindWord(afu, CheckDirection::kVertical)
              .char_positions.at(1)
              .character == 'f');
  REQUIRE(wss.FindWord(afu, CheckDirection::kVertical)
              .char_positions.at(2)
              .character == 'u');
  REQUIRE(
      wss.FindWord(afu, CheckDirection::kVertical).char_positions.at(1).col ==
      5);
  REQUIRE(
      wss.FindWord(afu, CheckDirection::kVertical).char_positions.at(1).row ==
      5);
  REQUIRE(wss.FindWord(afu, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(afu, CheckDirection::kRightDiag) == WordLocation{});

  // swc
  std::string swc = "swc";
  // clang-format off
  REQUIRE(wss.FindWord(swc).char_positions.at(0).character == 's');
  REQUIRE(wss.FindWord(swc).char_positions.at(1).character == 'w');
  REQUIRE(wss.FindWord(swc).char_positions.at(2).character == 'c');
  REQUIRE(wss.FindWord(swc).char_positions.at(1).col == 2);
  REQUIRE(wss.FindWord(swc).char_positions.at(1).row == 4);
  REQUIRE(wss.FindWord(swc, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).word == swc);
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).char_positions.at(0).character == 's');
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).char_positions.at(1).character == 'w');
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).char_positions.at(2).character == 'c');
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).char_positions.at(1).col == 2);
  REQUIRE(wss.FindWord(swc, CheckDirection::kLeftDiag).char_positions.at(1).row == 4);
  REQUIRE(wss.FindWord(swc, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(swc, CheckDirection::kRightDiag) == WordLocation{});
  // clang-format on
}
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'t', 't', 'k', 'r', 'd', 'i', 'o', 'q', 's', 'h', 't', 'x', 'f', 'o', 'd', 'v', 'e', 'o'},
         {'m', 'g', 't', 'd', 'h', 'h', 'l', 'h', 'f', 'l', 'h', 'c', 'f', 'c', 'w', 's', 'u', 'b'},
         {'a', 'k', 'r', 's', 's', 'm', 's', 'z', 'a', 'x', 'v', 'h', 'l', 'j', 'p', 'g', 'm', 'w'},
         {'n', 'x', 'g', 't', 'k', 'n', 'v', 's', 'r', 't', 'k', 'l', 'w', 'm', 'y', 'o', 'g', 'q'},
         {'c', 'y', 'r', 'f', 'w', 'o', 'm', 'j', 'x', 'd', 'q', 'l', 'z', 'f', 'l', 'h', 'y', 'v'},
         {'u', 'w', 'p', 'o', 'r', 'z', 'z', 'o', 'l', 'z', 'e', 's', 'r', 'g', 's', 'j', 'n', 'q'},
         {'x', 'b', 'c', 'x', 'e', 'u', 'k', 'e', 'z', 'v', 'l', 'a', 't', 'i', 'y', 'i', 'w', 'p'},
         {'i', 'x', 'f', 'v', 'x', 'j', 'p', 'o', 's', 'i', 'z', 'f', 'a', 'z', 'h', 'c', 'y', 'l'},
         {'y', 'i', 'r', 'y', 'e', 'f', 'a', 'x', 'p', 'y', 'h', 'n', 'n', 'p', 'm', 't', 'n', 'j'},
         {'e', 'c', 'a', 'w', 'm', 'b', 'e', 'n', 'a', 'l', 'r', 'y', 'y', 's', 'j', 's', 'q', 'n'},
         {'x', 'q', 'm', 'o', 'o', 't', 'b', 'd', 'l', 'n', 'y', 'y', 'z', 'f', 'a', 'b', 'b', 'p'},
         {'c', 'f', 'e', 'f', 's', 'x', 'f', 't', 'p', 'o', 'l', 'f', 'd', 'i', 'x', 'r', 'y', 'n'},
         {'l', 'z', 't', 'w', 'o', 't', 'w', 'n', 'y', 'y', 'q', 'c', 'n', 'v', 'h', 'r', 'a', 'c'},
         {'r', 'h', 'v', 'g', 'w', 'g', 'o', 'b', 'q', 'l', 't', 'o', 'b', 'e', 'p', 'w', 'c', 'd'},
         {'p', 'a', 't', 'o', 'y', 'j', 's', 'o', 'e', 'b', 'h', 'g', 'd', 'y', 'o', 'a', 'f', 'm'},
         {'g', 'v', 'n', 'y', 'i', 'g', 'o', 'j', 'm', 'd', 'f', 'q', 'j', 'x', 'q', 'c', 'n', 'r'},
         {'l', 'f', 'f', 's', 'g', 'o', 'y', 'k', 'n', 'o', 'k', 'u', 'a', 't', 'r', 'o', 't', 'z'},
         {'w', 'i', 'j', 'l', 'n', 'q', 'b', 'w', 'n', 'u', 'y', 'a', 'l', 'm', 'h', 's', 'e', 'o'},
         {'g', 'e', 'a', 'v', 't', 'm', 'r', 'v', 'h', 'i', 'j', 'b', 'i', 'i', 'l', 't', 't', 'y'},
         {'l', 'u', 'x', 'z', 'q', 'v', 'b', 'b', 'j', 'j', 'v', 'p', 'z', 'c', 'u', 'z', 'z', 'p'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'y';
  c1.row = 14;
  c1.col = 4;
  c2.character = 'g';
  c2.row = 15;
  c2.col = 5;
  c3.character = 'y';
  c3.row = 16;
  c3.col = 6;
  c4.character = 'w';
  c4.row = 17;
  c4.col = 7;
  c5.character = 'h';
  c5.row = 18;
  c5.col = 8;
  WordLocation wl;
  wl.word = "ygywh";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == wl);
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'e', 'o', 'v', 'g', 'a', 'p', 'q', 's', 'i', 'g', 'o', 'j', 'w', 'k', 'p', 'u', 'z', 'x'},
         {'a', 'j', 'f', 'h', 'r', 'k', 'f', 'e', 'j', 'n', 'e', 'h', 'u', 'i', 'y', 's', 'q', 'y'},
         {'j', 'h', 's', 't', 'p', 'g', 'e', 'l', 't', 't', 'f', 's', 's', 'h', 'e', 'x', 'r', 'v'},
         {'j', 'y', 'b', 'u', 'l', 'f', 'c', 'i', 'p', 'c', 'a', 'f', 'a', 'j', 'm', 'v', 'c', 'd'},
         {'b', 'g', 'o', 'u', 'b', 'w', 'p', 't', 'd', 't', 's', 'w', 'q', 'b', 'w', 'r', 'y', 'i'},
         {'y', 'c', 'q', 'n', 'e', 's', 's', 'e', 'b', 'h', 'b', 'f', 'k', 'd', 'n', 'b', 'z', 'o'},
         {'x', 'o', 'j', 'c', 'j', 'b', 'z', 'b', 'e', 'v', 'u', 'e', 'f', 's', 'g', 'x', 'f', 'k'},
         {'r', 'a', 'r', 's', 'h', 's', 'z', 'r', 'x', 'm', 's', 'x', 'c', 'r', 'n', 'l', 'u', 'z'},
         {'o', 'v', 'a', 't', 's', 'x', 'x', 'a', 'p', 'g', 'z', 'x', 'q', 'r', 'x', 'h', 'l', 'e'},
         {'a', 'l', 'x', 'x', 'z', 's', 'w', 'c', 'j', 'k', 'n', 'f', 'j', 'c', 'c', 'l', 'x', 'v'},
         {'i', 'w', 'x', 'a', 'c', 'w', 'z', 'v', 'n', 'w', 'c', 'z', 'c', 'e', 'm', 'b', 'e', 'l'},
         {'t', 'a', 'n', 'f', 'm', 'd', 'm', 'x', 'h', 'p', 'j', 'g', 'm', 't', 'e', 'j', 't', 'j'},
         {'h', 's', 'e', 'v', 'q', 'g', 'w', 'u', 'n', 'i', 'w', 'r', 'v', 'r', 't', 'l', 'y', 'g'},
         {'o', 'l', 'f', 'x', 'c', 'o', 'd', 'q', 'k', 'j', 'b', 'd', 's', 'i', 'y', 'w', 'd', 'q'},
         {'f', 'b', 'l', 's', 'l', 'j', 'l', 'h', 'a', 'e', 'u', 'b', 'm', 'k', 'o', 's', 'h', 'q'},
         {'i', 'm', 'i', 's', 'x', 'j', 'y', 'q', 'r', 'y', 'm', 'x', 'o', 't', 'y', 'b', 'l', 'm'},
         {'k', 'y', 'v', 'n', 'f', 'p', 'o', 'r', 'z', 'e', 'l', 'i', 'w', 'u', 'w', 'e', 'o', 't'},
         {'n', 'o', 'j', 'e', 'm', 'y', 'b', 'd', 'r', 'c', 'g', 'f', 'o', 'r', 'f', 'j', 'g', 'k'},
         {'a', 'w', 'e', 'b', 'a', 'p', 'j', 'w', 'l', 'h', 'a', 'a', 'a', 'p', 'q', 'm', 't', 'd'},
         {'m', 'x', 'g', 'd', 'b', 'm', 'k', 'p', 'f', 's', 'a', 'n', 'c', 'c', 'l', 'g', 'd', 'n'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'h';
  c1.row = 1;
  c1.col = 3;
  c2.character = 'r';
  c2.row = 1;
  c2.col = 4;
  c3.character = 'k';
  c3.row = 1;
  c3.col = 5;
  c4.character = 'f';
  c4.row = 1;
  c4.col = 6;
  c5.character = 'e';
  c5.row = 1;
  c5.col = 7;
  WordLocation wl;
  wl.word = "hrkfe";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'y', 'm', 'y', 'r', 'z', 'p', 'l', 'b', 'i', 'j', 'q', 'n', 'a', 'y', 'w', 'c', 'u', 'v'},
         {'y', 'y', 'a', 'm', 'o', 'w', 'r', 's', 'f', 'l', 'd', 'k', 'p', 'd', 'x', 'o', 'u', 'y'},
         {'f', 'g', 'b', 'p', 'r', 's', 'd', 's', 'q', 'b', 'w', 'm', 'y', 'u', 'k', 'y', 'h', 'b'},
         {'u', 'a', 'v', 'c', 'l', 'y', 'm', 'b', 'b', 'l', 'p', 'y', 'j', 'w', 'e', 'n', 'l', 'v'},
         {'f', 'q', 'p', 'x', 's', 'm', 'm', 'q', 'i', 'y', 'p', 'r', 'z', 'l', 's', 'v', 'n', 'd'},
         {'v', 'a', 'e', 'x', 'n', 'v', 'x', 'x', 't', 'b', 'm', 'f', 'y', 'r', 'v', 'q', 'q', 'n'},
         {'e', 'c', 'g', 'm', 'd', 'v', 'e', 'c', 'i', 'y', 'z', 'w', 'b', 'v', 'y', 'i', 'u', 'l'},
         {'f', 'r', 'k', 'z', 'u', 'w', 'g', 'u', 'p', 'b', 'k', 'i', 'r', 'q', 'k', 'z', 'd', 'p'},
         {'u', 'j', 's', 'e', 'h', 't', 'a', 'i', 'o', 'a', 's', 'k', 'o', 'y', 'b', 'y', 'z', 'x'},
         {'x', 'f', 's', 'm', 'i', 'e', 'u', 'b', 'v', 'h', 'a', 'a', 'w', 'w', 'j', 'q', 'b', 'q'},
         {'k', 'd', 'a', 'a', 'g', 'v', 'l', 'u', 'v', 'o', 's', 'u', 'm', 'r', 'b', 'g', 'e', 'j'},
         {'k', 'a', 'n', 'h', 'h', 'n', 'h', 'g', 'm', 'q', 'w', 'n', 'i', 'i', 's', 'l', 'j', 'y'},
         {'g', 'w', 's', 'b', 'k', 'n', 'v', 'y', 'g', 'w', 'e', 'k', 'h', 'r', 'n', 'u', 'y', 'u'},
         {'k', 'g', 'c', 'w', 'y', 'b', 'l', 'h', 'j', 'd', 's', 'u', 'e', 'y', 'q', 'y', 'z', 'b'},
         {'n', 'w', 'b', 'u', 'u', 'g', 'g', 'd', 'z', 't', 'y', 'x', 'q', 'k', 'f', 's', 'g', 'e'},
         {'t', 't', 'n', 'f', 'y', 'f', 'z', 'c', 'f', 'q', 'd', 'g', 't', 'q', 'e', 'u', 'm', 'y'},
         {'c', 't', 'b', 'b', 'm', 'b', 'b', 'e', 'l', 'g', 'x', 't', 'm', 's', 'm', 'z', 'x', 'l'},
         {'g', 'z', 'n', 'l', 'p', 's', 't', 'k', 'j', 'x', 'g', 'x', 'v', 'l', 'q', 'z', 'o', 'f'},
         {'a', 'p', 'j', 'm', 'y', 'i', 'f', 'm', 'b', 'u', 'm', 'a', 'f', 's', 'z', 'u', 'g', 'q'},
         {'n', 'z', 'a', 'y', 'x', 'j', 'v', 'u', 'u', 'o', 't', 'i', 'v', 'w', 'a', 'e', 'k', 'a'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'q';
  c1.row = 9;
  c1.col = 15;
  c2.character = 'g';
  c2.row = 10;
  c2.col = 15;
  c3.character = 'l';
  c3.row = 11;
  c3.col = 15;
  c4.character = 'u';
  c4.row = 12;
  c4.col = 15;
  c5.character = 'y';
  c5.row = 13;
  c5.col = 15;
  WordLocation wl;
  wl.word = "qgluy";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'d', 'l', 'u', 'w', 't', 'h', 'i', 'y', 'q', 'k', 'h', 'g', 'a', 'l', 's', 'u', 'y', 'x'},
         {'x', 'l', 'n', 's', 'e', 'q', 'h', 'q', 'i', 'o', 'd', 'd', 'm', 'h', 'q', 'g', 'f', 'k'},
         {'q', 'n', 'k', 'i', 'z', 's', 'p', 'z', 'f', 'j', 'u', 'g', 'i', 'r', 't', 'w', 'l', 'x'},
         {'o', 't', 'o', 'x', 'h', 'r', 'c', 'v', 'a', 's', 'e', 'f', 'e', 'u', 'v', 'r', 'c', 'u'},
         {'l', 't', 'u', 'q', 'e', 'q', 'w', 'n', 'j', 'r', 'l', 'u', 'p', 'z', 'n', 'f', 'y', 'w'},
         {'w', 'c', 'u', 'z', 'x', 'y', 'g', 'd', 'u', 'b', 'w', 'y', 'w', 'h', 's', 's', 'y', 'y'},
         {'k', 'w', 'n', 't', 'o', 'y', 'n', 'f', 'a', 'd', 'k', 'a', 'b', 'i', 'f', 'v', 'j', 'c'},
         {'v', 'q', 'h', 'p', 'r', 'e', 'o', 'p', 'n', 'i', 'j', 'l', 'g', 't', 'k', 'u', 'm', 'a'},
         {'u', 'c', 'h', 'u', 'h', 't', 'v', 'i', 'b', 'a', 'g', 'l', 'e', 'b', 'd', 'n', 't', 'w'},
         {'t', 'h', 'm', 'h', 'p', 'v', 'u', 'x', 'r', 'e', 't', 'd', 'g', 'o', 'h', 'n', 'i', 'o'},
         {'g', 'f', 'x', 'k', 'h', 'f', 'x', 'n', 'i', 'a', 'b', 'b', 'y', 'u', 'i', 'k', 'b', 'z'},
         {'i', 'w', 'z', 'z', 'c', 's', 'e', 'l', 'g', 'm', 'a', 'r', 'a', 'j', 'y', 'z', 't', 'g'},
         {'g', 's', 't', 'p', 'u', 'u', 'q', 's', 'r', 'b', 'd', 'u', 'a', 'n', 'q', 'z', 'o', 'v'},
         {'u', 'u', 'i', 'a', 'g', 'i', 't', 'j', 'r', 's', 'k', 'm', 'y', 't', 'e', 't', 'i', 'y'},
         {'q', 'y', 'r', 'h', 'b', 'w', 'd', 'c', 'l', 'u', 'd', 'z', 'r', 'x', 't', 'z', 'a', 'c'},
         {'j', 't', 'n', 'b', 'l', 'z', 'n', 'l', 's', 's', 'h', 'a', 's', 'x', 'b', 'j', 'g', 'c'},
         {'f', 'j', 'g', 's', 'f', 'm', 'r', 'y', 'j', 'n', 'z', 'l', 'r', 'j', 'f', 'e', 'k', 's'},
         {'d', 'z', 'g', 'y', 't', 'n', 'y', 'm', 'm', 'b', 'v', 'u', 'g', 'd', 'd', 'm', 'v', 'l'},
         {'y', 'p', 'l', 'k', 'e', 'l', 'v', 'v', 'u', 'a', 'z', 'g', 'v', 'e', 'h', 'b', 'e', 'b'},
         {'q', 'd', 'n', 'c', 'g', 'k', 'w', 'm', 'p', 'b', 'b', 'n', 'o', 'b', 'e', 'a', 'l', 'i'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 's';
  c1.row = 15;
  c1.col = 12;
  c2.character = 'j';
  c2.row = 16;
  c2.col = 13;
  c3.character = 'd';
  c3.row = 17;
  c3.col = 14;
  c4.character = 'b';
  c4.row = 18;
  c4.col = 15;
  c5.character = 'l';
  c5.row = 19;
  c5.col = 16;
  WordLocation wl;
  wl.word = "sjdbl";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == wl);
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'d', 'r', 'r', 'e', 'i', 'y', 'i', 'i', 'q', 'y', 'u', 'p', 'u', 'b', 's', 'a', 'l', 'h'},
         {'v', 'd', 'c', 'p', 'k', 'c', 't', 'l', 'v', 'e', 'q', 'y', 'q', 'w', 's', 'h', 'a', 'a'},
         {'h', 'k', 'l', 'x', 'k', 'f', 'm', 'e', 'i', 'g', 'f', 'v', 'p', 'c', 'y', 's', 'r', 'j'},
         {'w', 'm', 'w', 't', 'r', 'o', 's', 'j', 'k', 'm', 'q', 'm', 'o', 'x', 'w', 'z', 'w', 'j'},
         {'g', 'k', 'n', 'p', 't', 'u', 'm', 'i', 'z', 'l', 'c', 's', 'w', 'z', 'f', 'u', 's', 'y'},
         {'i', 'm', 'j', 'v', 'a', 'z', 'j', 'p', 'y', 'g', 'q', 'u', 'r', 'x', 'e', 'e', 'o', 'x'},
         {'b', 'a', 'i', 'a', 'n', 'k', 's', 'j', 'l', 'z', 'f', 'g', 'z', 'q', 'u', 'i', 'l', 'v'},
         {'h', 'u', 'm', 'h', 'c', 'c', 'd', 't', 'z', 'k', 'a', 'p', 'j', 'b', 'q', 'r', 'd', 'd'},
         {'e', 'v', 'p', 'r', 'x', 'u', 'x', 'w', 'k', 's', 'f', 'x', 'p', 'o', 'u', 'b', 'y', 'w'},
         {'d', 'b', 's', 'f', 'n', 'u', 'u', 'x', 'x', 'm', 'q', 'a', 's', 'u', 'x', 'j', 'o', 'u'},
         {'d', 'l', 't', 'q', 'f', 'a', 'n', 'u', 'q', 'h', 'v', 'q', 'g', 'b', 'u', 'a', 'g', 'h'},
         {'u', 'c', 'e', 'r', 'p', 'x', 't', 'j', 'r', 'q', 's', 'h', 'n', 'x', 't', 'i', 'n', 'y'},
         {'i', 'd', 'v', 'a', 'm', 's', 'r', 's', 't', 'l', 's', 'b', 'u', 'o', 'e', 'b', 'f', 'v'},
         {'y', 'y', 'g', 'r', 'r', 'y', 'z', 'g', 'v', 's', 'o', 'l', 's', 'y', 'o', 'p', 'a', 'a'},
         {'i', 'r', 't', 'b', 'e', 'n', 'd', 'b', 'c', 'j', 'c', 'j', 'g', 'a', 'k', 'm', 'r', 'd'},
         {'m', 'q', 'j', 'h', 'k', 'x', 's', 'f', 'x', 'i', 'u', 'x', 'j', 'c', 'r', 'e', 'g', 'x'},
         {'t', 'l', 'y', 'x', 'u', 'a', 'h', 'c', 'a', 't', 'o', 'u', 'w', 'c', 'k', 'f', 'j', 'x'},
         {'e', 'e', 'e', 'b', 'o', 'y', 'a', 'x', 'd', 'r', 'd', 'j', 'p', 'z', 'u', 'n', 'w', 'q'},
         {'o', 'f', 's', 'q', 'y', 'i', 'k', 'w', 'k', 'x', 'b', 'v', 'w', 'h', 'b', 'a', 'k', 'q'},
         {'y', 'l', 'p', 'd', 'c', 'v', 'm', 't', 'u', 'i', 'j', 'q', 'y', 'z', 'y', 's', 'p', 'w'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'p';
  c1.row = 2;
  c1.col = 12;
  c2.character = 'c';
  c2.row = 2;
  c2.col = 13;
  c3.character = 'y';
  c3.row = 2;
  c3.col = 14;
  c4.character = 's';
  c4.row = 2;
  c4.col = 15;
  c5.character = 'r';
  c5.row = 2;
  c5.col = 16;
  WordLocation wl;
  wl.word = "pcysr";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'r', 'c', 'r', 'g', 'a', 'y', 'g', 'm', 'r', 'h', 'i', 'e', 'j', 'q', 'd', 'f', 'p', 'j'},
         {'m', 'd', 'w', 'e', 'p', 'f', 'l', 'f', 'x', 'n', 'd', 'r', 'g', 'w', 'w', 'a', 'e', 'w'},
         {'y', 'k', 'i', 'r', 'r', 'q', 'y', 'c', 'j', 'b', 'h', 'y', 'k', 't', 'b', 'j', 'y', 's'},
         {'q', 'l', 'x', 'n', 'z', 'c', 'f', 'h', 'a', 'd', 'h', 'e', 'z', 'h', 'p', 'j', 'z', 'i'},
         {'a', 'z', 'l', 'l', 'a', 'u', 'j', 'n', 'o', 'm', 'w', 'm', 'g', 'm', 'x', 'f', 'c', 'y'},
         {'h', 'j', 'i', 'h', 'm', 'p', 'n', 'l', 'z', 'e', 'u', 'a', 'n', 'w', 'z', 'a', 'h', 'z'},
         {'u', 's', 'o', 'k', 'g', 'm', 'y', 'm', 'z', 'w', 'r', 'd', 'w', 'a', 'm', 'e', 'j', 'y'},
         {'w', 'z', 'j', 'v', 'd', 'f', 'x', 's', 'e', 'w', 'u', 'l', 'x', 'p', 'g', 'm', 'b', 'm'},
         {'y', 'a', 'b', 'z', 'y', 'u', 'c', 'u', 'v', 'q', 'b', 'g', 'o', 'z', 'f', 'z', 'w', 'l'},
         {'f', 't', 'd', 'j', 'p', 'y', 'w', 'o', 'p', 'c', 'a', 'q', 'r', 'b', 's', 's', 'c', 'q'},
         {'m', 'h', 'n', 'j', 'x', 'o', 'q', 'm', 'p', 'x', 'n', 'l', 'i', 's', 'e', 'o', 'd', 'v'},
         {'m', 'c', 'j', 'd', 'e', 'm', 'v', 'x', 'p', 'o', 'p', 't', 'e', 'c', 'a', 't', 'l', 'a'},
         {'j', 'd', 'o', 'y', 'd', 'b', 'l', 'l', 'w', 'p', 'b', 'z', 'm', 'p', 'b', 'w', 's', 'i'},
         {'k', 'o', 'h', 'z', 'e', 'x', 's', 'k', 'b', 'v', 'e', 'm', 'v', 'n', 's', 'l', 'm', 'v'},
         {'m', 'z', 'i', 'i', 'r', 'k', 'k', 'd', 'z', 'n', 'b', 'u', 'x', 'l', 'k', 'f', 'm', 'o'},
         {'c', 'h', 'a', 'd', 'c', 'e', 'r', 'z', 's', 'l', 'm', 'g', 'g', 'y', 'f', 'r', 'j', 'w'},
         {'d', 't', 'c', 'e', 'i', 'd', 'y', 'g', 'r', 'k', 'n', 'f', 'a', 'p', 'm', 'b', 'u', 'q'},
         {'f', 'n', 'r', 'z', 'z', 'd', 'h', 'h', 'e', 'n', 'a', 'n', 'l', 'd', 'i', 'p', 'k', 'q'},
         {'v', 'k', 'y', 'm', 'v', 'l', 't', 'v', 'c', 'g', 'w', 'y', 'y', 'e', 'o', 's', 'd', 'p'},
         {'v', 'l', 'w', 'z', 'a', 'z', 'o', 'n', 'c', 'w', 'd', 'o', 'p', 'y', 'z', 'p', 'm', 'u'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'f';
  c1.row = 7;
  c1.col = 5;
  c2.character = 'c';
  c2.row = 8;
  c2.col = 6;
  c3.character = 'o';
  c3.row = 9;
  c3.col = 7;
  c4.character = 'p';
  c4.row = 10;
  c4.col = 8;
  c5.character = 'o';
  c5.row = 11;
  c5.col = 9;
  WordLocation wl;
  wl.word = "fcopo";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == wl);
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'u', 'f', 'l', 'n', 'r', 'f', 'r', 'p', 'm', 'g', 'i', 'z', 'k', 'n', 'x', 'o', 'r', 'w'},
         {'d', 'o', 'y', 'j', 'v', 'q', 'd', 'x', 'x', 'h', 'n', 'm', 'x', 'i', 'u', 'k', 'v', 'l'},
         {'p', 'p', 'd', 'd', 'v', 'n', 'c', 'f', 'a', 'b', 'u', 't', 'z', 'z', 'i', 'x', 'i', 'f'},
         {'o', 'n', 'c', 'n', 'x', 'p', 'c', 'w', 'z', 'w', 'h', 'v', 'j', 'w', 'm', 'm', 'c', 'h'},
         {'z', 'e', 'o', 'z', 'i', 'i', 'v', 'h', 'k', 'd', 'f', 'u', 'i', 'v', 'i', 'm', 'i', 'h'},
         {'b', 'k', 'd', 'b', 'i', 'm', 'y', 'u', 'l', 'k', 'g', 'n', 't', 'i', 't', 'h', 'j', 'b'},
         {'s', 'e', 'j', 'c', 'j', 'o', 'w', 'r', 'j', 'g', 'd', 't', 'p', 'h', 'g', 'v', 'i', 'q'},
         {'j', 'i', 'k', 'u', 'u', 't', 'j', 'n', 'b', 'd', 'u', 'm', 'g', 'o', 'r', 'p', 's', 'a'},
         {'f', 'r', 'u', 'q', 'z', 'z', 'k', 'p', 'g', 's', 'm', 'q', 'i', 'v', 'y', 't', 'q', 'u'},
         {'m', 'b', 'h', 'p', 'e', 'e', 'b', 'l', 's', 'u', 'c', 'n', 'x', 'i', 'e', 't', 'y', 'd'},
         {'s', 'k', 'u', 'z', 'c', 'g', 'r', 'l', 'c', 's', 'g', 'u', 'm', 'u', 'v', 'u', 'j', 'c'},
         {'a', 'm', 'p', 'u', 'h', 'r', 'h', 'g', 'b', 'l', 'z', 'c', 'p', 't', 'm', 'j', 'u', 'r'},
         {'s', 'm', 'e', 'u', 'e', 'k', 'q', 's', 'e', 'n', 'o', 'p', 'r', 'o', 'b', 'g', 'j', 'k'},
         {'y', 's', 'q', 'b', 'e', 'r', 'd', 'v', 'l', 'q', 'g', 'f', 'h', 'y', 'r', 'l', 'u', 'x'},
         {'x', 'm', 'q', 'b', 'a', 'e', 'q', 'r', 'v', 't', 'a', 'e', 'e', 'a', 'y', 'w', 'b', 'c'},
         {'o', 'f', 'z', 'z', 'v', 'g', 'g', 'e', 'e', 'a', 'r', 'b', 'x', 'o', 'n', 'p', 'r', 'p'},
         {'w', 'h', 'j', 'r', 'c', 'j', 'x', 'g', 'j', 'v', 'd', 'm', 'y', 't', 'r', 'x', 'u', 'o'},
         {'f', 'a', 's', 'k', 'a', 'l', 'n', 'a', 'z', 'a', 'r', 'q', 's', 'n', 'z', 'b', 'e', 'c'},
         {'m', 'b', 'k', 'v', 'x', 'p', 'j', 'x', 'i', 'b', 'u', 'c', 'p', 'c', 'd', 'k', 'o', 'f'},
         {'x', 'b', 'h', 'x', 'd', 'z', 'p', 'v', 'm', 'r', 'w', 'r', 'v', 'i', 'u', 'f', 'f', 'r'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'l';
  c1.row = 13;
  c1.col = 8;
  c2.character = 'v';
  c2.row = 14;
  c2.col = 8;
  c3.character = 'e';
  c3.row = 15;
  c3.col = 8;
  c4.character = 'j';
  c4.row = 16;
  c4.col = 8;
  c5.character = 'z';
  c5.row = 17;
  c5.col = 8;
  WordLocation wl;
  wl.word = "lvejz";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'f', 'q', 'u', 'x', 's', 'm', 'b', 'd', 'k', 's', 'k', 'y', 'r', 'q', 'r', 'w', 'r', 'j'},
         {'w', 'o', 's', 'u', 'a', 'i', 'y', 'u', 'v', 't', 'y', 'g', 'v', 'g', 'x', 'p', 'd', 'p'},
         {'e', 'e', 't', 'o', 'y', 'f', 'o', 's', 'y', 'f', 'o', 'p', 'p', 'k', 'f', 'j', 'g', 'f'},
         {'u', 'g', 'c', 'p', 'c', 'a', 'w', 'x', 'g', 't', 'o', 'l', 'k', 's', 's', 'f', 'g', 'q'},
         {'l', 'v', 'i', 'l', 'c', 'y', 'a', 'r', 'l', 'f', 'd', 'r', 'm', 'x', 'a', 'o', 'm', 'c'},
         {'r', 'i', 'z', 'z', 'd', 'n', 'l', 'o', 'g', 'd', 't', 'o', 'v', 'g', 'l', 'g', 'r', 'o'},
         {'e', 'r', 'f', 'r', 'y', 'i', 'l', 'n', 'h', 'l', 'd', 'u', 'n', 'u', 'e', 'o', 'w', 'i'},
         {'b', 'j', 'w', 'j', 'o', 'r', 'a', 'j', 'y', 'l', 'r', 'p', 'z', 'y', 'j', 'h', 'p', 'j'},
         {'r', 'a', 'w', 'z', 'n', 'a', 'v', 'a', 'w', 'z', 'o', 'u', 'j', 's', 'd', 'h', 'd', 'r'},
         {'z', 'd', 'd', 'x', 'r', 'w', 'm', 's', 'u', 'v', 'z', 'm', 'f', 'r', 'o', 'd', 's', 'c'},
         {'f', 'n', 'e', 'c', 'o', 'v', 'w', 'y', 'n', 'c', 'h', 's', 't', 'g', 'y', 'y', 'd', 'p'},
         {'v', 's', 'h', 'r', 'p', 'j', 'd', 'w', 'c', 's', 'a', 'u', 'w', 'f', 'j', 'a', 'j', 'z'},
         {'v', 'i', 'z', 'k', 'k', 'h', 'f', 'f', 'n', 'd', 'e', 't', 'u', 'b', 'l', 'd', 's', 'c'},
         {'o', 'y', 'z', 'q', 's', 'z', 'm', 'o', 'g', 'x', 'q', 'q', 'x', 'm', 'y', 'w', 'y', 'k'},
         {'f', 'd', 'p', 't', 'i', 'v', 'o', 'c', 'w', 'z', 'i', 'r', 'b', 'w', 'p', 'c', 'n', 'h'},
         {'b', 'b', 'x', 'k', 'z', 'n', 'a', 'y', 'b', 'a', 'u', 'a', 'k', 'c', 'f', 'b', 'v', 'o'},
         {'x', 'j', 's', 'v', 'k', 'a', 'o', 'n', 'z', 'f', 'q', 'o', 'o', 't', 'p', 'l', 'd', 'o'},
         {'b', 'f', 'm', 'c', 'f', 'j', 'e', 'r', 'l', 'k', 'v', 'i', 'a', 'u', 't', 's', 'p', 'f'},
         {'v', 'g', 'u', 'w', 'l', 'k', 'k', 'a', 'g', 'z', 'n', 'l', 'q', 'o', 'r', 'e', 'r', 'y'},
         {'p', 'v', 's', 'c', 'h', 'n', 'm', 'h', 'h', 'f', 'c', 'y', 'm', 'z', 'e', 'h', 'v', 's'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'r';
  c1.row = 0;
  c1.col = 16;
  c2.character = 'd';
  c2.row = 1;
  c2.col = 16;
  c3.character = 'g';
  c3.row = 2;
  c3.col = 16;
  c4.character = 'g';
  c4.row = 3;
  c4.col = 16;
  c5.character = 'm';
  c5.row = 4;
  c5.col = 16;
  WordLocation wl;
  wl.word = "rdggm";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'y', 'e', 'j', 'x', 'g', 'f', 'a', 'r', 'e', 'n', 'l', 'z', 'l', 'j', 'p', 't', 'g', 's'},
         {'n', 'w', 'i', 'r', 'w', 'o', 'n', 's', 'g', 'q', 'a', 'm', 'e', 'a', 's', 'p', 'y', 'a'},
         {'u', 'a', 's', 'y', 'n', 'd', 'z', 'b', 'o', 'o', 'u', 'u', 'h', 'k', 's', 'r', 'b', 'o'},
         {'f', 'q', 'j', 'n', 'i', 'l', 'z', 'n', 'm', 'u', 'c', 'm', 'u', 'z', 'm', 'm', 'x', 'c'},
         {'r', 'x', 'd', 'g', 'n', 'z', 'c', 'w', 'l', 'v', 'n', 'p', 'l', 'v', 'f', 'u', 'i', 'o'},
         {'g', 'i', 'd', 'u', 'e', 'h', 'g', 'y', 'g', 'u', 'n', 'g', 'y', 'e', 'f', 'd', 'k', 's'},
         {'d', 'p', 'r', 'o', 'k', 'e', 'd', 'x', 'z', 'l', 's', 'k', 'b', 'a', 's', 'e', 'w', 'y'},
         {'n', 'c', 'w', 'w', 'y', 'l', 'e', 'x', 'q', 'j', 'a', 'c', 'd', 'f', 'r', 'u', 'u', 'd'},
         {'b', 'z', 'b', 'c', 'm', 'v', 'm', 'n', 'x', 'g', 't', 't', 'e', 'h', 'v', 'd', 'f', 'v'},
         {'o', 'j', 's', 'g', 's', 'v', 'j', 'x', 'a', 'a', 'u', 'w', 'g', 'v', 'w', 'h', 'z', 'i'},
         {'e', 'm', 'y', 'b', 'u', 'r', 'u', 'z', 'a', 'r', 'e', 'f', 'm', 's', 'o', 'h', 'z', 'i'},
         {'c', 'k', 'g', 'c', 'm', 'c', 'z', 's', 'x', 'x', 'b', 'y', 'h', 'f', 'k', 'f', 'g', 'f'},
         {'x', 'c', 'g', 'x', 't', 'k', 'f', 'i', 'e', 't', 'p', 'f', 'e', 'r', 'r', 'm', 'v', 'e'},
         {'o', 'u', 'w', 'l', 'r', 'y', 'j', 'z', 'd', 'w', 'g', 'm', 'd', 'd', 'o', 'l', 'd', 'k'},
         {'v', 'i', 's', 'b', 'd', 'h', 'j', 'h', 'a', 'a', 't', 'v', 'e', 'h', 's', 'd', 'u', 'j'},
         {'d', 'g', 'k', 'i', 'e', 't', 'u', 'j', 'w', 'l', 'u', 'b', 'v', 'r', 'l', 'n', 's', 'r'},
         {'w', 'd', 'a', 'y', 'e', 'u', 'v', 'k', 'd', 'n', 'n', 'a', 'z', 's', 'i', 'l', 'b', 'o'},
         {'e', 'v', 'x', 'd', 'i', 'r', 'e', 'd', 'i', 's', 's', 'c', 'j', 'q', 'g', 'j', 'o', 'm'},
         {'f', 'k', 'w', 'l', 'z', 'm', 'n', 'y', 'e', 'x', 'k', 'h', 'l', 'o', 'd', 'i', 'r', 'l'},
         {'z', 'y', 'r', 'j', 's', 'j', 'l', 'd', 'a', 'r', 'm', 'q', 'd', 'u', 'c', 'c', 'h', 'c'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'w';
  c1.row = 13;
  c1.col = 9;
  c2.character = 'a';
  c2.row = 14;
  c2.col = 9;
  c3.character = 'l';
  c3.row = 15;
  c3.col = 9;
  c4.character = 'n';
  c4.row = 16;
  c4.col = 9;
  c5.character = 's';
  c5.row = 17;
  c5.col = 9;
  WordLocation wl;
  wl.word = "walns";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'t', 'y', 'd', 'g', 'd', 'i', 'c', 'l', 'c', 'n', 'y', 'q', 'q', 'h', 'e', 'g', 'd', 'r'},
         {'l', 'h', 'f', 'v', 'z', 'e', 'p', 'k', 'b', 'r', 'v', 'q', 'j', 'p', 'o', 'o', 'x', 't'},
         {'w', 'b', 'e', 'a', 'o', 'e', 'q', 'h', 'o', 'x', 'p', 'r', 'o', 'd', 'a', 'v', 'a', 'z'},
         {'z', 'p', 'j', 'a', 'g', 'h', 's', 'r', 'w', 'i', 'g', 'v', 'd', 'c', 'w', 'k', 'f', 'n'},
         {'o', 'v', 'w', 'c', 'u', 'l', 'v', 'i', 'q', 'w', 'd', 'q', 'x', 'f', 'f', 'j', 'f', 'n'},
         {'q', 'a', 'f', 'o', 'i', 'l', 'l', 'o', 'p', 'h', 'y', 'u', 'w', 'm', 's', 's', 'r', 'm'},
         {'g', 'm', 'x', 'w', 'k', 'c', 'n', 'i', 'h', 'u', 'r', 'p', 'i', 'j', 'r', 'p', 'x', 'b'},
         {'c', 'i', 'p', 'r', 'r', 'n', 'o', 'o', 'c', 'i', 'i', 't', 'w', 'o', 'h', 'v', 'l', 's'},
         {'a', 'a', 'c', 'j', 'u', 't', 'y', 'c', 'c', 'r', 't', 'b', 't', 'v', 'j', 'i', 'p', 'a'},
         {'w', 'd', 'q', 'a', 'n', 'z', 't', 'l', 'n', 'c', 'h', 'a', 'u', 'h', 'a', 'y', 'q', 'v'},
         {'r', 'r', 'z', 'v', 'i', 't', 'y', 'd', 'q', 'h', 'm', 'f', 'k', 'k', 'k', 'a', 'k', 'x'},
         {'b', 'f', 'j', 'r', 'h', 's', 'r', 'e', 'z', 'u', 'c', 'r', 'p', 'w', 'k', 'q', 't', 'v'},
         {'l', 's', 'y', 'c', 'b', 'k', 'h', 'l', 'u', 's', 'o', 'g', 'r', 'r', 'l', 'c', 'i', 'v'},
         {'u', 'a', 'z', 'v', 'u', 'b', 'n', 'l', 'z', 'z', 'd', 't', 'u', 'p', 'n', 't', 't', 'o'},
         {'f', 'c', 'a', 'c', 'w', 'q', 'k', 'o', 'h', 'w', 'q', 'q', 'r', 'l', 's', 'q', 'i', 'o'},
         {'t', 'v', 'b', 'v', 'x', 'e', 'o', 't', 'v', 'b', 'o', 'q', 'r', 'u', 't', 't', 'y', 'p'},
         {'j', 'i', 'f', 't', 'e', 'y', 'l', 'x', 'l', 'd', 'p', 't', 't', 'l', 'r', 'u', 'g', 'o'},
         {'a', 'w', 'h', 'w', 'z', 'w', 'o', 'q', 's', 'h', 'k', 'q', 'z', 'v', 'a', 'g', 'o', 'f'},
         {'e', 'b', 'e', 'p', 'e', 'w', 'j', 'z', 'h', 'a', 't', 'p', 'q', 'w', 'n', 'x', 'u', 'm'},
         {'v', 'i', 'e', 'n', 's', 'q', 'd', 'r', 'o', 'g', 'x', 'e', 'l', 'c', 'g', 'r', 't', 'k'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'g';
  c1.row = 3;
  c1.col = 10;
  c2.character = 'd';
  c2.row = 4;
  c2.col = 10;
  c3.character = 'y';
  c3.row = 5;
  c3.col = 10;
  c4.character = 'r';
  c4.row = 6;
  c4.col = 10;
  c5.character = 'i';
  c5.row = 7;
  c5.col = 10;
  WordLocation wl;
  wl.word = "gdyri";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'s', 'h', 'x', 'b', 'q', 'j', 'u', 't', 'l', 'c', 'a', 'x', 'a', 'm', 't', 'a', 'u', 'o'},
         {'d', 'a', 'm', 'c', 'd', 'u', 'v', 'p', 'j', 'u', 'p', 'l', 't', 'j', 's', 'q', 'l', 'i'},
         {'b', 'h', 'd', 'm', 'j', 'g', 'l', 'k', 's', 'h', 'm', 'o', 'v', 'r', 'p', 'k', 't', 'u'},
         {'g', 'q', 'l', 'r', 'k', 'a', 'd', 'e', 'm', 'v', 'w', 'z', 'g', 'y', 'g', 'j', 'm', 's'},
         {'r', 'y', 'c', 'j', 'f', 'o', 'a', 'c', 'h', 'r', 'm', 'a', 'l', 'u', 'r', 'x', 'm', 'd'},
         {'z', 'p', 'j', 'n', 'k', 'g', 'm', 's', 'g', 'v', 'e', 's', 'n', 'v', 'q', 'r', 'h', 'x'},
         {'h', 'h', 'a', 'o', 'y', 'o', 'q', 'l', 'j', 'h', 'i', 'v', 'n', 'i', 'm', 'y', 'x', 'y'},
         {'e', 'k', 'r', 'k', 'h', 'v', 'f', 'w', 'q', 'v', 'p', 'x', 'v', 'w', 'e', 'v', 'm', 'e'},
         {'l', 'c', 'q', 'w', 'm', 'a', 'r', 'z', 'k', 'f', 'x', 'i', 'e', 'e', 'u', 'v', 'q', 'b'},
         {'q', 'v', 'z', 'i', 't', 'o', 'g', 'o', 'm', 'm', 'j', 'y', 'r', 'w', 'a', 'j', 't', 'm'},
         {'j', 'm', 'l', 'u', 's', 'l', 'c', 'w', 'p', 'w', 't', 'h', 'z', 'l', 'd', 'a', 't', 'w'},
         {'o', 'z', 'k', 'a', 'o', 'v', 'y', 'h', 'r', 'a', 'q', 'k', 'n', 'b', 'x', 'a', 'x', 'r'},
         {'n', 'z', 'p', 'e', 'x', 'i', 'm', 'y', 't', 'p', 'y', 'm', 'l', 'o', 'o', 'x', 'o', 'c'},
         {'s', 'o', 'j', 'j', 'r', 'b', 'w', 'g', 'c', 'v', 'g', 'a', 'm', 'w', 'b', 'b', 'a', 'b'},
         {'l', 'm', 'z', 'e', 'b', 'a', 's', 'o', 'o', 'g', 'l', 'f', 'k', 'd', 'v', 't', 'p', 'm'},
         {'u', 'l', 'u', 'z', 'i', 'b', 'z', 'u', 'x', 'a', 'x', 'x', 'd', 'i', 'm', 'd', 'o', 'n'},
         {'f', 'g', 'c', 't', 'p', 'p', 'a', 'z', 't', 'y', 'v', 'k', 'k', 'p', 'v', 'f', 'o', 'd'},
         {'i', 'p', 'z', 'h', 's', 'y', 'g', 'v', 'g', 's', 'a', 'w', 'i', 'f', 'c', 'm', 'b', 't'},
         {'b', 'b', 't', 'w', 'z', 'o', 'g', 'm', 'f', 'd', 't', 'w', 'i', 'd', 'l', 'j', 'm', 'd'},
         {'h', 's', 'z', 'p', 'n', 'z', 'l', 'x', 'h', 'o', 'j', 'i', 'h', 'm', 'j', 'c', 'l', 'l'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'm';
  c1.row = 3;
  c1.col = 16;
  c2.character = 'x';
  c2.row = 4;
  c2.col = 15;
  c3.character = 'q';
  c3.row = 5;
  c3.col = 14;
  c4.character = 'i';
  c4.row = 6;
  c4.col = 13;
  c5.character = 'v';
  c5.row = 7;
  c5.col = 12;
  WordLocation wl;
  wl.word = "mxqiv";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'j', 'y', 'g', 't', 'y', 'k', 'g', 'u', 't', 'p', 'o', 'g', 'e', 'y', 'h', 's', 'a', 'q'},
         {'i', 'p', 'r', 'u', 'z', 'o', 'd', 't', 'c', 'c', 'j', 'k', 'x', 'v', 'k', 'g', 'o', 'k'},
         {'s', 'w', 'e', 'n', 'l', 'v', 'u', 's', 't', 'b', 'k', 'w', 't', 's', 'n', 'k', 'o', 'm'},
         {'b', 't', 'h', 'd', 'w', 't', 'q', 't', 'q', 'a', 'b', 'g', 'l', 'u', 'c', 'r', 'h', 'q'},
         {'m', 'b', 'i', 'i', 'e', 'u', 'e', 'y', 'o', 't', 'k', 'd', 'i', 'l', 'w', 'p', 'r', 's'},
         {'k', 'h', 'o', 'a', 'j', 'p', 'i', 'u', 'l', 'l', 'o', 't', 'd', 'a', 'w', 'n', 'k', 'b'},
         {'h', 'o', 'z', 'x', 'i', 'l', 'a', 's', 'x', 'z', 'h', 'q', 't', 'u', 'z', 'h', 'w', 'i'},
         {'z', 'f', 'f', 'k', 's', 't', 'f', 'v', 'v', 'c', 'k', 'g', 'd', 'r', 'w', 'e', 'q', 'g'},
         {'p', 'r', 'y', 'o', 'q', 'i', 'g', 'l', 'c', 'f', 'v', 'a', 'o', 'u', 'f', 't', 'g', 'z'},
         {'m', 'm', 'w', 'j', 'q', 'g', 'p', 'v', 'z', 'm', 'z', 'q', 's', 'q', 'j', 't', 'h', 'z'},
         {'b', 'n', 'k', 'd', 't', 'f', 'd', 'j', 'b', 'l', 'c', 'k', 'k', 'q', 'y', 'h', 'z', 'o'},
         {'p', 'r', 'j', 'p', 'd', 'k', 'f', 'x', 'a', 'o', 'q', 'j', 'p', 'r', 'x', 'b', 'w', 's'},
         {'j', 'c', 'b', 'm', 'n', 'd', 'w', 'z', 'v', 'w', 'g', 'w', 'm', 'w', 'n', 'x', 'n', 's'},
         {'h', 'u', 'q', 'k', 'i', 'i', 't', 'z', 'c', 's', 'c', 'y', 'k', 'l', 'a', 'l', 'a', 'p'},
         {'q', 'y', 'p', 'n', 'v', 'v', 'k', 'j', 't', 'z', 'h', 'g', 's', 'q', 'a', 'k', 'c', 'k'},
         {'s', 'y', 'l', 'u', 'q', 'o', 't', 'd', 'b', 'v', 'q', 'd', 'l', 'j', 'c', 'a', 'w', 'z'},
         {'x', 'i', 'i', 'r', 'i', 'r', 'z', 'a', 'i', 'c', 'k', 'm', 'o', 'c', 'k', 'a', 'z', 'd'},
         {'q', 'u', 'g', 't', 'p', 'w', 'x', 'c', 'f', 'b', 'c', 'e', 'c', 'c', 'm', 'm', 'v', 'u'},
         {'e', 'u', 'u', 'o', 'y', 'g', 'a', 'n', 'l', 'n', 'p', 'k', 'q', 'h', 'e', 'w', 'a', 'v'},
         {'u', 'z', 'y', 'c', 'c', 'c', 'g', 'e', 'e', 'u', 'r', 'z', 'p', 'x', 'w', 'l', 'n', 'u'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'u';
  c1.row = 5;
  c1.col = 7;
  c2.character = 's';
  c2.row = 6;
  c2.col = 7;
  c3.character = 'v';
  c3.row = 7;
  c3.col = 7;
  c4.character = 'l';
  c4.row = 8;
  c4.col = 7;
  c5.character = 'v';
  c5.row = 9;
  c5.col = 7;
  WordLocation wl;
  wl.word = "usvlv";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'b', 'h', 'h', 'q', 's', 'x', 'c', 'b', 'o', 'd', 'c', 'f', 'c', 'd', 'o', 'f', 'y', 'd'},
         {'x', 'k', 'm', 'k', 'm', 'h', 'f', 'z', 'b', 'x', 'v', 'o', 's', 'y', 'x', 'c', 'q', 'q'},
         {'z', 'u', 'r', 'q', 'x', 'v', 'v', 'z', 'y', 'j', 'g', 'y', 'o', 'd', 'j', 'a', 'q', 'v'},
         {'i', 'v', 'x', 'l', 's', 's', 'a', 'n', 's', 'z', 'r', 'j', 'r', 's', 'd', 'k', 'i', 'b'},
         {'f', 'd', 'c', 'f', 'o', 'j', 'e', 'd', 'o', 'n', 'd', 'g', 'k', 'l', 'd', 'h', 'z', 'w'},
         {'b', 'b', 'l', 'u', 'a', 'c', 'f', 's', 'u', 'i', 'e', 'f', 'l', 'k', 'i', 'q', 'r', 'z'},
         {'z', 'v', 'e', 'p', 'k', 'h', 'w', 'x', 'v', 'z', 'g', 'u', 'x', 'k', 'v', 'k', 'e', 'x'},
         {'o', 'l', 'r', 'j', 't', 'w', 'q', 'h', 'i', 'a', 'x', 'z', 'z', 'y', 'v', 'd', 'n', 'h'},
         {'n', 'l', 'e', 'k', 'l', 'n', 'g', 'k', 'x', 'd', 'v', 'd', 'a', 'j', 'o', 'u', 'u', 'j'},
         {'q', 'k', 'q', 'y', 'l', 'p', 'z', 'm', 'n', 'w', 's', 'd', 'e', 'f', 'o', 'k', 'r', 'b'},
         {'x', 'x', 'm', 'w', 'c', 'h', 'z', 'e', 'q', 'n', 'y', 'n', 'z', 'q', 'x', 'r', 'q', 'i'},
         {'h', 'q', 'x', 'w', 'm', 'p', 'b', 'q', 'w', 'q', 'd', 'n', 'r', 'c', 'm', 'f', 'z', 'q'},
         {'m', 'y', 'u', 'f', 'o', 'v', 's', 'n', 'l', 'p', 'e', 'c', 'a', 'n', 's', 'z', 'm', 'g'},
         {'o', 'n', 'z', 'k', 'd', 'c', 'z', 'x', 'e', 'n', 'c', 'f', 'd', 'r', 'g', 'z', 'w', 'u'},
         {'u', 'q', 'j', 'g', 'h', 'p', 'k', 'h', 'f', 'e', 'i', 'r', 'k', 'w', 'g', 'j', 'i', 'm'},
         {'n', 'j', 'j', 'u', 'w', 'n', 'z', 'b', 'g', 'f', 'b', 'e', 'b', 'v', 'u', 'm', 'b', 'c'},
         {'e', 'n', 'l', 'l', 'r', 'u', 'c', 'c', 's', 'i', 'n', 'b', 'w', 'b', 'k', 'h', 'v', 'j'},
         {'v', 'w', 'k', 'd', 'c', 'n', 'i', 'f', 'j', 'c', 's', 'm', 'g', 'y', 'a', 'u', 'j', 'r'},
         {'q', 'n', 'v', 'i', 'x', 'j', 'l', 'u', 'm', 'y', 'b', 'j', 'h', 'y', 'f', 't', 'c', 'j'},
         {'j', 'k', 'p', 'u', 'o', 'j', 'g', 'x', 'h', 'i', 'r', 's', 'c', 'h', 'f', 'z', 'r', 'c'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'v';
  c1.row = 7;
  c1.col = 14;
  c2.character = 'j';
  c2.row = 8;
  c2.col = 13;
  c3.character = 'e';
  c3.row = 9;
  c3.col = 12;
  c4.character = 'n';
  c4.row = 10;
  c4.col = 11;
  c5.character = 'd';
  c5.row = 11;
  c5.col = 10;
  WordLocation wl;
  wl.word = "vjend";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'n', 'o', 'r', 'n', 'u', 'k', 'i', 'i', 'g', 'y', 'b', 'k', 'q', 'u', 'j', 't', 'v', 'm'},
         {'j', 'p', 'r', 'j', 'h', 'o', 't', 'n', 'j', 'c', 'u', 'y', 'i', 'h', 'm', 'z', 'w', 'i'},
         {'j', 'e', 'q', 's', 'f', 's', 'c', 'v', 'o', 'o', 'q', 'k', 'a', 'z', 'b', 't', 'l', 'i'},
         {'h', 'g', 'y', 't', 'l', 's', 'r', 't', 'b', 'g', 's', 'y', 'o', 'e', 'e', 'f', 'w', 'j'},
         {'z', 'a', 'g', 'n', 'o', 'x', 'z', 'r', 'y', 'a', 'k', 'j', 'j', 'u', 'q', 'j', 'p', 'b'},
         {'d', 'i', 'u', 'e', 'q', 'o', 'e', 'f', 's', 'l', 'm', 'q', 'w', 'n', 't', 'd', 'a', 'h'},
         {'a', 'a', 'a', 'y', 'a', 'n', 'k', 'l', 'j', 'a', 'w', 'y', 'b', 'z', 'g', 'v', 'g', 'x'},
         {'j', 'm', 'e', 'e', 'x', 's', 'w', 'w', 'f', 'p', 'z', 'h', 'z', 'b', 'j', 'z', 'b', 'm'},
         {'m', 'l', 'z', 'v', 'l', 'w', 'v', 'm', 'x', 'e', 'j', 'f', 'd', 'v', 'u', 'j', 'z', 't'},
         {'b', 'v', 'p', 'i', 'n', 'o', 'r', 'm', 'r', 'b', 'n', 't', 'p', 'c', 'g', 'o', 'z', 's'},
         {'m', 'v', 'g', 'm', 'z', 's', 't', 'e', 'n', 'n', 'n', 'm', 'h', 'o', 'j', 'y', 'y', 'y'},
         {'p', 'p', 'k', 'g', 's', 'a', 'b', 'h', 'c', 'i', 'y', 'b', 'a', 'm', 'y', 'i', 'a', 'z'},
         {'a', 'u', 'd', 'n', 'j', 'q', 'b', 's', 'e', 'n', 'r', 'e', 'l', 'g', 'u', 'y', 'm', 'o'},
         {'y', 'q', 'y', 'c', 'y', 'y', 'd', 'a', 'k', 'c', 'i', 'n', 'd', 'l', 'h', 'h', 'a', 's'},
         {'x', 'e', 'l', 'e', 't', 'e', 'i', 'e', 'k', 'e', 'e', 'y', 't', 'e', 'o', 't', 'g', 'o'},
         {'r', 'm', 'o', 'd', 'q', 'z', 'q', 't', 'm', 'z', 'a', 'm', 's', 'a', 'q', 'f', 'e', 'j'},
         {'j', 'm', 'q', 'v', 't', 'w', 'v', 'o', 'b', 'k', 'h', 'j', 'a', 'y', 'v', 'p', 'b', 'n'},
         {'q', 'u', 'h', 'c', 't', 'j', 'o', 'l', 'j', 'h', 's', 'n', 's', 'b', 'c', 'k', 'w', 'v'},
         {'h', 's', 'j', 'k', 'e', 's', 't', 'e', 's', 'r', 'v', 't', 'g', 'l', 'p', 'p', 'n', 'j'},
         {'z', 'e', 'w', 'k', 'l', 'p', 'y', 'f', 'q', 'c', 'q', 'p', 'z', 'x', 'j', 'k', 'j', 'p'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'n';
  c1.row = 13;
  c1.col = 11;
  c2.character = 'y';
  c2.row = 14;
  c2.col = 11;
  c3.character = 'm';
  c3.row = 15;
  c3.col = 11;
  c4.character = 'j';
  c4.row = 16;
  c4.col = 11;
  c5.character = 'n';
  c5.row = 17;
  c5.col = 11;
  WordLocation wl;
  wl.word = "nymjn";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'y', 'w', 'e', 't', 'w', 'g', 'c', 'k', 'g', 'j', 'b', 'u', 'm', 'v', 'z', 'u', 'j', 'e'},
         {'v', 'q', 'd', 'h', 'q', 'x', 'p', 'a', 'm', 'n', 'm', 'w', 'a', 'l', 's', 'f', 'e', 'r'},
         {'n', 'i', 'b', 'u', 'u', 'e', 'q', 'g', 'c', 'p', 'a', 'l', 'v', 'y', 'e', 'y', 'f', 'u'},
         {'x', 'w', 'u', 'j', 'j', 'i', 'h', 'l', 't', 'a', 's', 'a', 'r', 'g', 'k', 'u', 'a', 'e'},
         {'a', 's', 'n', 'c', 'j', 'p', 'o', 'e', 'n', 'u', 'e', 'u', 'o', 'b', 'q', 'k', 'm', 'z'},
         {'u', 'u', 'n', 'o', 'w', 'f', 'q', 'p', 'l', 'c', 'l', 'n', 'h', 'l', 'h', 'u', 'q', 'q'},
         {'j', 'g', 'u', 'z', 'a', 'a', 't', 'q', 'b', 'k', 'c', 'q', 'l', 'w', 'm', 'y', 'm', 'i'},
         {'e', 'c', 'z', 'r', 'h', 'k', 'h', 'o', 'x', 'o', 'k', 'n', 'f', 'v', 't', 'b', 'u', 't'},
         {'c', 'o', 'l', 'f', 'a', 'n', 'x', 'l', 'k', 'j', 'k', 'w', 't', 'q', 'b', 's', 'h', 'i'},
         {'c', 'o', 'y', 'c', 'd', 'k', 'p', 'k', 'f', 'l', 'l', 'c', 'e', 'p', 's', 's', 'x', 's'},
         {'f', 'u', 'd', 'r', 'g', 'p', 'q', 'z', 'f', 'r', 's', 'p', 'b', 'w', 'd', 'b', 'y', 'i'},
         {'l', 'q', 's', 'q', 'b', 'g', 'u', 'h', 'x', 'm', 'z', 'u', 'e', 'h', 'r', 'k', 'y', 'z'},
         {'z', 'o', 'y', 'h', 'h', 's', 'w', 'k', 'r', 'z', 'l', 'p', 'k', 'w', 'h', 'c', 'p', 'i'},
         {'k', 'l', 'q', 'i', 'y', 'r', 'e', 'c', 'y', 'x', 'm', 'z', 'y', 'o', 'n', 'x', 'v', 'x'},
         {'r', 'r', 'h', 'i', 's', 'v', 'a', 'c', 'r', 'h', 'h', 'i', 's', 'r', 'u', 'k', 'b', 'u'},
         {'b', 'i', 'w', 'c', 'h', 'l', 'b', 'g', 'b', 'q', 'f', 'w', 'n', 'w', 'p', 'x', 'h', 'j'},
         {'s', 'h', 'm', 'l', 'q', 't', 'w', 'i', 'm', 'q', 'u', 'q', 'k', 'w', 'y', 'i', 'a', 'h'},
         {'v', 'b', 'n', 'w', 'r', 's', 'u', 'h', 'p', 'l', 'e', 'w', 'v', 'y', 'f', 'h', 'j', 'x'},
         {'c', 'f', 'i', 'q', 'x', 'c', 'g', 'j', 'a', 'g', 'u', 'a', 'o', 'p', 'd', 'd', 'o', 'x'},
         {'w', 'i', 'e', 'n', 'u', 'k', 'l', 'p', 'i', 'q', 'y', 't', 'n', 'c', 'b', 'v', 's', 'a'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'c';
  c1.row = 14;
  c1.col = 7;
  c2.character = 'g';
  c2.row = 15;
  c2.col = 7;
  c3.character = 'i';
  c3.row = 16;
  c3.col = 7;
  c4.character = 'h';
  c4.row = 17;
  c4.col = 7;
  c5.character = 'j';
  c5.row = 18;
  c5.col = 7;
  WordLocation wl;
  wl.word = "cgihj";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'f', 'n', 'k', 'i', 'g', 'n', 'p', 'c', 'l', 'z', 'c', 'n', 'f', 'l', 'j', 'v', 'y', 'm'},
         {'v', 'v', 'r', 'c', 'i', 'h', 'j', 'n', 'l', 'r', 'v', 's', 'a', 'c', 'f', 'n', 'k', 'n'},
         {'a', 'z', 'q', 'n', 'a', 's', 'a', 'f', 'f', 'k', 'd', 'f', 'w', 'a', 'a', 'p', 'f', 'k'},
         {'w', 'o', 'x', 'j', 'f', 'u', 'b', 'i', 'w', 'i', 'v', 'i', 'w', 'x', 'j', 'o', 'k', 'j'},
         {'g', 'l', 'r', 'n', 'v', 'w', 's', 't', 'w', 'u', 'j', 'd', 'g', 'h', 'r', 'e', 'r', 'z'},
         {'a', 's', 'h', 'x', 'd', 'e', 'h', 'z', 'b', 'r', 'n', 'l', 'a', 'v', 'w', 't', 'k', 't'},
         {'p', 'c', 'n', 'o', 'y', 'w', 'r', 'e', 'f', 'j', 'k', 'w', 'k', 'l', 'r', 't', 'k', 'u'},
         {'x', 'r', 'v', 'a', 'k', 'k', 'l', 'n', 'f', 'k', 'g', 'p', 'd', 'y', 't', 'q', 'm', 't'},
         {'o', 'd', 'x', 'u', 'o', 'i', 's', 'a', 'v', 'l', 't', 'h', 'f', 's', 'y', 'c', 's', 'l'},
         {'m', 'g', 'y', 't', 's', 'e', 'k', 'v', 'c', 'd', 'o', 'q', 'w', 'e', 'u', 'w', 'a', 'k'},
         {'g', 't', 'l', 'b', 'g', 'e', 'i', 'm', 'z', 'i', 'q', 't', 't', 'd', 'b', 'r', 'w', 't'},
         {'y', 'h', 'r', 'c', 'm', 'f', 't', 'l', 'j', 'n', 'h', 'm', 'z', 'n', 'h', 'k', 'q', 'n'},
         {'r', 'y', 'z', 'q', 'g', 'q', 'j', 'c', 'v', 'n', 't', 'r', 'g', 't', 'a', 'x', 'w', 'n'},
         {'e', 'p', 'a', 'q', 'e', 'h', 'c', 'd', 'w', 'j', 'o', 'm', 'w', 'h', 'k', 'y', 'x', 's'},
         {'q', 'i', 'u', 'l', 'v', 'q', 'e', 'e', 'j', 'f', 'b', 'f', 'u', 'g', 'w', 'w', 'w', 'a'},
         {'d', 'y', 'g', 'b', 'j', 'w', 'n', 'f', 'd', 'z', 'f', 'c', 't', 'v', 'k', 'q', 'g', 'i'},
         {'g', 'n', 'm', 'p', 'u', 'p', 'x', 'q', 'v', 't', 'm', 't', 'w', 'r', 't', 'c', 's', 'c'},
         {'a', 'h', 'k', 'd', 'i', 'p', 'f', 'b', 'l', 'r', 'r', 't', 'z', 'x', 'i', 'n', 'p', 'c'},
         {'d', 'o', 'u', 'a', 'h', 'g', 'u', 'f', 'x', 'p', 'j', 'r', 'u', 'j', 'a', 'e', 'm', 'i'},
         {'v', 't', 'k', 'i', 'l', 'b', 'c', 'm', 'b', 'm', 'a', 's', 'r', 'd', 'g', 'l', 'd', 'p'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'v';
  c1.row = 19;
  c1.col = 0;
  c2.character = 't';
  c2.row = 19;
  c2.col = 1;
  c3.character = 'k';
  c3.row = 19;
  c3.col = 2;
  c4.character = 'i';
  c4.row = 19;
  c4.col = 3;
  c5.character = 'l';
  c5.row = 19;
  c5.col = 4;
  WordLocation wl;
  wl.word = "vtkil";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'y', 'p', 'd', 'v', 'q', 'u', 'l', 'n', 'r', 'd', 'r', 'e', 'd', 'v', 'b', 'x', 'e', 't'},
         {'k', 'v', 'i', 'j', 'q', 'w', 'h', 'y', 'r', 'b', 'i', 'z', 'o', 'h', 'q', 't', 'c', 'j'},
         {'o', 'p', 'w', 'h', 'u', 'q', 'n', 'x', 'l', 'p', 'u', 'r', 'i', 'h', 'o', 's', 's', 'e'},
         {'q', 'a', 'e', 'i', 'd', 'n', 'j', 't', 'w', 'c', 'n', 'a', 'l', 'b', 'p', 'j', 'k', 'k'},
         {'z', 'y', 'j', 'n', 'p', 'e', 'g', 'z', 'n', 'v', 'r', 'f', 'b', 'j', 'h', 'g', 't', 'm'},
         {'v', 'f', 'g', 'r', 'h', 't', 'r', 'u', 'w', 'i', 'd', 'i', 'u', 'f', 'g', 'e', 's', 'x'},
         {'k', 'y', 'w', 'x', 'v', 'p', 'e', 'z', 'z', 'o', 'f', 'u', 'a', 'a', 'z', 'i', 't', 'g'},
         {'d', 'm', 'c', 'z', 'u', 'i', 'i', 'r', 'n', 'q', 'v', 'h', 'q', 'f', 'h', 'm', 'e', 'f'},
         {'e', 'k', 'e', 'f', 'y', 'l', 'z', 'b', 'n', 'z', 'j', 'g', 'h', 'n', 'u', 'k', 'o', 'q'},
         {'u', 'y', 'h', 'j', 'p', 'c', 'q', 'h', 'j', 'z', 't', 'p', 'g', 'z', 'a', 'k', 'e', 'a'},
         {'x', 'e', 'b', 'k', 'f', 'n', 's', 'm', 'c', 'm', 'y', 'q', 'f', 's', 'r', 'm', 'b', 'g'},
         {'r', 't', 'p', 'c', 'v', 'i', 's', 'b', 'k', 'u', 'o', 'o', 'u', 'l', 'u', 'y', 'w', 'z'},
         {'l', 'q', 'o', 'p', 'f', 'm', 'f', 'k', 'h', 'w', 'w', 'i', 'e', 'p', 'e', 't', 's', 'z'},
         {'e', 'm', 'a', 'o', 'g', 'o', 'e', 'a', 'a', 'b', 'a', 'y', 'a', 'n', 'q', 'q', 'c', 'v'},
         {'f', 'k', 'f', 'm', 'i', 'e', 'w', 'p', 't', 'a', 'i', 'n', 'z', 'o', 'z', 'c', 'e', 'f'},
         {'q', 'l', 'i', 's', 'm', 'k', 's', 'o', 'y', 'j', 'f', 'a', 'g', 'k', 'm', 'm', 'y', 'v'},
         {'s', 'u', 'k', 'n', 'v', 'u', 'b', 'u', 'l', 'c', 'y', 'p', 'k', 'r', 'c', 's', 'j', 'o'},
         {'e', 'e', 'd', 'c', 'p', 'i', 'f', 'v', 'u', 'r', 'h', 's', 'o', 'b', 'm', 'a', 'p', 'h'},
         {'v', 's', 'e', 'i', 'w', 'c', 'z', 'g', 't', 'c', 'a', 'f', 'q', 'f', 'l', 't', 'h', 'a'},
         {'d', 'o', 'v', 'x', 'i', 'f', 'r', 'w', 'g', 'e', 'x', 'x', 'n', 'u', 'r', 't', 'c', 'o'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'n';
  c1.row = 3;
  c1.col = 5;
  c2.character = 'e';
  c2.row = 4;
  c2.col = 5;
  c3.character = 't';
  c3.row = 5;
  c3.col = 5;
  c4.character = 'p';
  c4.row = 6;
  c4.col = 5;
  c5.character = 'i';
  c5.row = 7;
  c5.col = 5;
  WordLocation wl;
  wl.word = "netpi";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'c', 'o', 'h', 'a', 'i', 's', 'h', 'p', 'p', 'b', 'l', 'x', 'q', 'g', 'n', 'd', 'a', 'a'},
         {'m', 'l', 'a', 'k', 'u', 'p', 'c', 'g', 'f', 'g', 'z', 'u', 'q', 'c', 'k', 'x', 'e', 'u'},
         {'s', 'o', 'j', 'h', 'r', 'x', 'g', 'j', 'd', 'u', 'm', 'f', 'w', 'b', 's', 'x', 'l', 'm'},
         {'o', 'n', 't', 't', 'v', 'u', 'p', 'n', 'y', 'z', 'm', 'd', 'w', 'g', 't', 'f', 'q', 'm'},
         {'c', 'w', 'v', 'h', 's', 'j', 'o', 'p', 'k', 'g', 'o', 'x', 'v', 'c', 'k', 'o', 'y', 'h'},
         {'i', 'p', 'w', 'j', 'r', 'j', 'o', 'n', 'p', 'h', 'u', 'h', 't', 'x', 'e', 'q', 'g', 'w'},
         {'z', 'v', 'n', 'k', 'd', 'b', 'h', 'y', 'g', 'u', 'm', 'e', 'd', 'x', 'v', 'c', 'g', 'm'},
         {'l', 'w', 'z', 'c', 'd', 'u', 'k', 'y', 't', 'q', 'o', 'b', 'o', 'n', 'w', 'c', 'z', 'a'},
         {'f', 'j', 'a', 'l', 'f', 'n', 'r', 'k', 'm', 'n', 'm', 'u', 'z', 'z', 'q', 'b', 'e', 'v'},
         {'x', 'q', 'v', 's', 'g', 'j', 't', 'w', 'y', 's', 'a', 'a', 'u', 'g', 'j', 'u', 't', 'q'},
         {'j', 'l', 'a', 'x', 'a', 'n', 'r', 'b', 'm', 'j', 'c', 's', 'e', 'b', 'i', 'b', 't', 'o'},
         {'k', 'n', 'n', 'l', 'f', 'n', 'l', 'z', 't', 'u', 'v', 'p', 'k', 'f', 'a', 'm', 'c', 'c'},
         {'z', 'w', 'd', 'o', 'f', 'i', 'g', 'm', 'j', 'r', 'n', 'd', 'f', 'a', 'q', 's', 'l', 'x'},
         {'i', 'w', 'y', 'b', 's', 't', 'q', 'e', 'y', 's', 'q', 'd', 'u', 's', 'z', 'a', 'i', 'e'},
         {'i', 'q', 's', 'r', 'h', 'i', 'w', 'p', 'i', 'o', 'j', 'v', 'l', 'r', 'r', 'l', 'v', 'l'},
         {'f', 'n', 'p', 'f', 'g', 'h', 'i', 'c', 'z', 'h', 'e', 'j', 'o', 'm', 'a', 'i', 'g', 'j'},
         {'q', 'e', 'y', 'a', 't', 'i', 'v', 'g', 'b', 'm', 's', 'w', 'z', 'x', 'k', 'o', 'e', 's'},
         {'w', 'n', 'w', 'x', 'w', 'b', 'j', 'm', 'p', 'j', 'v', 'x', 'u', 'n', 'c', 't', 'o', 'x'},
         {'d', 'j', 'd', 'e', 'y', 'x', 'd', 'x', 'u', 'n', 'o', 'b', 'h', 'm', 'q', 'd', 'l', 'm'},
         {'g', 'u', 'b', 'y', 'f', 'y', 'v', 'a', 'l', 'z', 'v', 'b', 'w', 'y', 'l', 'c', 'e', 'l'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'h';
  c1.row = 0;
  c1.col = 6;
  c2.character = 'p';
  c2.row = 0;
  c2.col = 7;
  c3.character = 'p';
  c3.row = 0;
  c3.col = 8;
  c4.character = 'b';
  c4.row = 0;
  c4.col = 9;
  c5.character = 'l';
  c5.row = 0;
  c5.col = 10;
  WordLocation wl;
  wl.word = "hppbl";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'c', 't', 'x', 'x', 'g', 'g', 'm', 'i', 'l', 'y', 'a', 'q', 'j', 'i', 'd', 'h', 'm', 'c'},
         {'p', 'h', 'q', 'a', 'm', 's', 'j', 's', 'z', 'y', 'j', 'c', 'k', 'l', 'x', 'j', 'i', 'e'},
         {'q', 'v', 'm', 'b', 'v', 'o', 't', 'g', 'x', 'w', 'o', 'j', 'b', 'd', 's', 't', 'd', 'f'},
         {'l', 'p', 'x', 'm', 'n', 'g', 'o', 'z', 'u', 'l', 'l', 'e', 'p', 'b', 'z', 'e', 'e', 'x'},
         {'u', 'a', 'd', 'r', 'y', 't', 'c', 'b', 'y', 'v', 'w', 'e', 'c', 'h', 't', 'b', 'v', 'g'},
         {'j', 'j', 'i', 'd', 'v', 't', 'i', 'm', 'w', 'j', 's', 'c', 'i', 'n', 'c', 'o', 'g', 'd'},
         {'h', 'l', 'e', 'i', 'g', 'b', 'm', 'k', 'k', 'f', 'l', 'g', 'n', 'u', 'r', 'v', 'a', 'o'},
         {'q', 'k', 'd', 'm', 'v', 'v', 'p', 'e', 'k', 't', 'u', 't', 'w', 'd', 'e', 'd', 'l', 'm'},
         {'g', 'x', 'w', 's', 'e', 'j', 'y', 's', 'f', 's', 'p', 'f', 'g', 'g', 'p', 'l', 'u', 'n'},
         {'j', 'j', 'r', 't', 'f', 'l', 'o', 'd', 'o', 'u', 'g', 'c', 'g', 'm', 'z', 'e', 'h', 'e'},
         {'p', 'f', 'y', 'v', 'z', 'n', 'c', 'i', 't', 'u', 't', 'o', 'h', 'c', 'z', 'a', 'w', 'g'},
         {'l', 'm', 'k', 'b', 'h', 's', 'd', 'p', 'h', 'f', 'u', 'o', 'l', 'l', 'v', 'j', 'g', 'v'},
         {'w', 'j', 'd', 's', 'd', 'w', 'i', 'k', 'z', 'j', 'k', 'x', 'q', 'x', 'j', 'c', 'a', 's'},
         {'u', 'g', 'i', 'b', 'l', 'e', 'r', 'y', 'p', 'n', 'h', 'w', 'k', 'd', 'h', 'n', 'v', 'k'},
         {'l', 'd', 'w', 'm', 'n', 'i', 'j', 'f', 'h', 'v', 'h', 'h', 'p', 'b', 'p', 'x', 'f', 'c'},
         {'d', 'w', 'a', 't', 'l', 'h', 'r', 'v', 'n', 'a', 'k', 'i', 'k', 'w', 'o', 'i', 'k', 'd'},
         {'s', 'w', 'i', 'z', 'r', 'p', 'i', 'i', 's', 'y', 'i', 'z', 'c', 'l', 'w', 'd', 'g', 'j'},
         {'k', 'x', 'f', 'x', 'x', 'p', 'i', 'j', 'n', 'y', 't', 'y', 'b', 'l', 'u', 'j', 'm', 'n'},
         {'a', 'v', 'x', 'u', 'v', 'f', 'u', 'x', 'r', 's', 'a', 'z', 'b', 'n', 'x', 'i', 'm', 'w'},
         {'a', 'w', 'i', 'n', 'u', 'd', 'n', 'v', 'p', 'j', 'g', 'b', 'y', 'i', 'y', 'w', 'd', 't'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'a';
  c1.row = 10;
  c1.col = 15;
  c2.character = 'j';
  c2.row = 11;
  c2.col = 15;
  c3.character = 'c';
  c3.row = 12;
  c3.col = 15;
  c4.character = 'n';
  c4.row = 13;
  c4.col = 15;
  c5.character = 'x';
  c5.row = 14;
  c5.col = 15;
  WordLocation wl;
  wl.word = "ajcnx";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}

TEST_CASE("", "") {
  // clang-format off
    std::vector<std::vector<char>> puzzle = 
        {{'o', 'f', 'w', 'g', 'o', 'm', 'f', 'v', 'm', 'q', 'h', 'x', 'b', 'q', 'r', 'w', 'w', 'x'},
         {'o', 'w', 'm', 'k', 'w', 'v', 'l', 'q', 'y', 'w', 's', 'n', 'u', 'g', 's', 's', 'p', 'i'},
         {'f', 'u', 'd', 't', 'n', 'k', 'r', 'o', 'c', 'k', 'm', 'b', 'i', 'b', 'z', 'u', 'n', 'x'},
         {'r', 'y', 'n', 'p', 'v', 'f', 'c', 'r', 'm', 'w', 'l', 'd', 'e', 's', 'z', 'k', 'm', 'm'},
         {'w', 'f', 'd', 'z', 'p', 'r', 'c', 'x', 'u', 'b', 't', 'i', 'z', 'l', 'g', 'm', 'c', 'd'},
         {'s', 'h', 'w', 'g', 'd', 'i', 'l', 'k', 'c', 'k', 'u', 'o', 'z', 'q', 'v', 'c', 'r', 'n'},
         {'v', 't', 'k', 'q', 'v', 'g', 'y', 'w', 't', 'e', 'i', 'x', 'k', 'c', 'e', 'g', 'i', 'k'},
         {'q', 't', 'w', 't', 'g', 'q', 'j', 'f', 'i', 'f', 'h', 'a', 's', 'e', 'v', 'e', 'u', 's'},
         {'m', 's', 'o', 'f', 'z', 'x', 'd', 'j', 'b', 'j', 'r', 'm', 'v', 'k', 'h', 'r', 'd', 'n'},
         {'j', 'm', 's', 's', 't', 'b', 'u', 'n', 'g', 'p', 'u', 'a', 'i', 'g', 'v', 'w', 'm', 'u'},
         {'v', 'r', 'f', 'x', 'a', 'w', 'l', 'y', 'g', 's', 'p', 'l', 'g', 'z', 'a', 'a', 't', 't'},
         {'e', 'n', 'j', 'm', 'c', 'd', 'm', 'm', 'j', 'j', 'j', 'x', 'd', 'g', 'o', 'i', 'f', 'r'},
         {'h', 'q', 'p', 'p', 'l', 'g', 'd', 't', 'h', 'd', 't', 'a', 'y', 'x', 'n', 'h', 'j', 's'},
         {'m', 'y', 'e', 'y', 'h', 'p', 'v', 'n', 'y', 'm', 'x', 'f', 'f', 'e', 'y', 'w', 'w', 'j'},
         {'c', 'z', 'c', 'm', 'e', 'x', 'o', 'c', 'v', 'e', 'm', 'g', 'w', 'y', 'g', 'c', 'y', 'q'},
         {'u', 'u', 'f', 's', 'i', 'c', 'z', 'n', 'j', 'x', 'j', 'h', 'g', 'n', 'g', 'i', 'b', 'm'},
         {'g', 'q', 'o', 'd', 'u', 'c', 'l', 's', 'd', 'u', 'u', 'b', 'm', 'q', 'x', 'r', 'k', 'f'},
         {'t', 'k', 's', 'e', 'h', 'd', 'l', 'o', 't', 't', 'y', 'u', 'f', 'g', 'm', 'w', 'l', 'g'},
         {'y', 'z', 'y', 'd', 't', 't', 'f', 'h', 'l', 'e', 'y', 'w', 'k', 't', 'g', 'e', 'y', 'n'},
         {'k', 'j', 'd', 'f', 'd', 'e', 'z', 'i', 'm', 'm', 'e', 'y', 'u', 'f', 'x', 't', 'i', 's'}};
  // clang-format on
  CharPositions c1, c2, c3, c4, c5;
  c1.character = 'b';
  c1.row = 4;
  c1.col = 9;
  c2.character = 'k';
  c2.row = 5;
  c2.col = 9;
  c3.character = 'e';
  c3.row = 6;
  c3.col = 9;
  c4.character = 'f';
  c4.row = 7;
  c4.col = 9;
  c5.character = 'j';
  c5.row = 8;
  c5.col = 9;
  WordLocation wl;
  wl.word = "bkefj";
  wl.char_positions = {c1, c2, c3, c4, c5};

  WordSearchSolver wss(puzzle);
  REQUIRE(wss.FindWord(wl.word) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});
  REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});
}