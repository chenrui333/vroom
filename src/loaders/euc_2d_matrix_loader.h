/*
VROOM (Vehicle Routing Open-source Optimization Machine)
Copyright (C) 2015, Julien Coupey

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EUC_2D_MATRIX_LOADER_H
#define EUC_2D_MATRIX_LOADER_H
#include <vector>
#include <cmath>
#include "./matrix_loader.h"
#include "../structures/typedefs.h"
#include "../structures/matrix.h"

class euc_2d_matrix_loader : public matrix_loader<distance_t, double>{

public:
  virtual matrix<distance_t> load_matrix(const std::vector<std::pair<double, double>>& locations) override{
    unsigned n = locations.size();
    std::vector<distance_t> blank_line (n, 0);
    std::vector<std::vector<distance_t>> matrix_as_vector (n, blank_line);

    for(index_t i = 0; i < n; ++i){
      matrix_as_vector[i][i] = 0;
      for(index_t j = i + 1; j < n; ++j){
        double xd = locations[j].first - locations[i].first;
        double yd = locations[j].second - locations[i].second;
        distance_t dij = nint(std::sqrt(xd * xd + yd * yd));
        matrix_as_vector[i][j] = dij;
        matrix_as_vector[j][i] = dij;
      }
    }
    matrix<distance_t> m (matrix_as_vector);
    return m;
  }
};

#endif
