#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>
#define CSV_IO_NO_THREAD
#include "csv.h"
#include <unordered_map>

int main() {
  std::unordered_map<unsigned int, int> degrees;
  std::unordered_map<unsigned int, unsigned int> connects;
  std::unordered_map<unsigned int, std::pair<double, double>> vertices;
  io::CSVReader<2> inD("Degree.data");
  io::CSVReader<2> inC("Connectivity.data");
  io::CSVReader<3> inV("Vertices.data");
  double vertice_x, vertice_y,area = 0.,Area = 0.; // area is of single cell;Area is the Tesselaton area
  signed int connect;
  unsigned int i = 1, j = 1, n = 0, cell, degree, ignored;
  while (inV.read_row(ignored, vertice_x, vertice_y))
    vertices.insert(std::make_pair(i++, std::make_pair(vertice_x, vertice_y)));
  while (inD.read_row(cell, degree))
    degrees.insert(std::make_pair(cell, degree));
  while (inC.read_row(ignored, connect))
    connects.insert(std::make_pair(j++, std::fabs(connect)));
   for (auto it = degrees.begin(); it != degrees.end(); ++it) {
    std::vector<std::pair<double, double>>Vert; // Element containing all vertices of single cell.
    for (i = 1; i <= it->second; i++) {
      std::pair<double, double> xandy = vertices.find(connects.find(i + n)->second)->second;
      Vert.emplace_back(xandy); }
    for (int m = 0; m < it->second; m++) 
      area += (Vert[m].first) * (Vert[m + 1].second) -(Vert[m + 1].first) * (Vert[m].second);
    Area += std::fabs(area) / 2;area = 0;n += it->second;}
  std::cout << Area;
  return Area;
}
