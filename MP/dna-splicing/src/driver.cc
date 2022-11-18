#include <iostream>

#include "dna_strand.hpp"

int main() {
  Node* first1 = new Node('c');
  Node* first2 = new Node('t');
  Node* first3 = new Node('g');
  Node* first4 = new Node('a');
  Node* first5 = new Node('a');
  Node* first6 = new Node('t');
  Node* first7 = new Node('t');
  Node* first8 = new Node('c');
  Node* first9 = new Node('g');
  first1->next = first2;
  first2->next = first3;
  first3->next = first4;
  first4->next = first5;
  first5->next = first6;
  first6->next = first7;
  first7->next = first8;
  first8->next = first9;
  DNAstrand list;
  list.Addhead(first1);
  list.Addtail(first9);
  list.Print();

  DNAstrand list2;
  Node* first21 = new Node('T');
  Node* first22 = new Node('G');
  Node* first23 = new Node('A');
  Node* first24 = new Node('T');
  Node* first25 = new Node('C');
  first21->next = first22;
  first22->next = first23;
  first23->next = first24;
  first24->next = first25;
  list2.Addhead(first21);
  list2.Addtail(first25);

  // Node* f = list.Find("ab");
  // std::cout << f->data << " " << f->next->data << " " << f->next->next->data
  //           << std::endl;

  list.SpliceIn("ctg", list2);
  list.Print();

  return 0;
}