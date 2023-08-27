#include <iostream>
#include <vector>
#include <cassert>

class Node {
public:
      Node(int _row, int _col, int _val) {
            row = _row;
            col = _col;
            val = _val;
      }

      int row, col, val;
};


class SparseMatrix {
public:
      std::vector<Node> getSparseMatrix(std::vector<std::vector<int>> matrix) {
            std::vector<Node> res;

            for(int i = 0; i < matrix.size(); ++i) {
                  for(int j = 0; j < matrix[0].size(); ++j) {
                        if(matrix[i][j] != 0) {
                              res.push_back(Node(i, j, matrix[i][j]));
                        }
                  }
            }

            return res;
      }

      void showSparseMatrix(std::vector<Node> sparse_matrix) {
            int n = sparse_matrix.size();
            for(int i = 0; i < n; ++i) {
                  std::cout << '[' << sparse_matrix[i].row << ',' << sparse_matrix[i].col << ']' << ':' << sparse_matrix[i].val << std::endl;
            }
            std::cout << std::endl;
      }


      void showMatrix(std::vector<std::vector<int>> matrix) {
            for(int i = 0; i < matrix.size(); ++i) {
                  for(int j = 0; j < matrix[0].size(); ++j) {
                        std::cout << matrix[i][j] << ' ';
                  }
                  std::cout << std::endl;
            }
            std::cout << std::endl;
      }
};


std::vector<std::vector<int>> muliply_matrix(std::vector<std::vector<int>>& m1, std::vector<std::vector<int>>& m2) {
      int m = m1.size(), k = m1[0].size();
      int kk = m2.size(), n = m2[0].size();

      assert(k == kk);

      std::vector<std::vector<int>> res(m, std::vector<int>(n));

      for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                  for(int u = 0; u < k; ++u) {
                        res[i][j] += m1[i][u] * m2[u][j];
                  }
            }
      }

      return res;
}


int main() {
      std::vector<std::vector<int>> m1 = {
            {0, 1, 0, 0, 0},
            {0, 0, 0, 5, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {3, 0, 0, 0, 0}
      };

      SparseMatrix s;
      s.showSparseMatrix(s.getSparseMatrix(m1));

      std::vector<std::vector<int>> m2 = {
            {0,0,2},
            {1,0,0},
      };

      std::vector<std::vector<int>> m3 = {
            {0,1},
            {2,0},
            {0,1}
      };

      std::vector<std::vector<int>> res = muliply_matrix(m2, m3);
      s.showMatrix(res);
      s.showSparseMatrix(s.getSparseMatrix(res));

      return 0;
}
