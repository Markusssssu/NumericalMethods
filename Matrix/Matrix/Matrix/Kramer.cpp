#include<iostream>
#include<vector>


double daterminant(std::vector<std::vector<double>> matrix) {

	int n = matrix.size();
	if (n == 1) return matrix[0][0];

	double det = 0;
	for (int col = 0; col < n; ++col) {
		std::vector<std::vector<double>> submatrix(n - 1, std::vector<double>(n - 1));
		for (int i = 1; i < n; ++i) {
			int subcol = 0;
			for (int j = 0; j < n; ++j) {
				if (j == col) continue;
				submatrix[i - 1][subcol] = matrix[i][j];
				subcol++;
			}
		}
		det += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * daterminant(submatrix);
	}

	return det;
}


std::vector<double> cramer(std::vector<std::vector<double>> matrix) {
	int n = matrix.size();
	std::vector<double> solution(n);
	std::vector<std::vector<double>> A(n, std::vector<double>(n));
	std::vector<double> B(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			A[i][j] = matrix[i][j];
		}
		B[i] = matrix[i][n];
	}


	double detA = daterminant(A);
	if (detA == 0) {
		std::cout << "System not have one number";
		return solution;
	}
	for (int col = 0; col < n; ++col) {
		std::vector<std::vector<double>> temp = A;
		for (int row = 0; row < n; ++row) {
			temp[row][col] = B[row];
		}
		solution[col] = daterminant(temp) / detA;
	}
	return solution;
}


int main(void)
{
	std::vector<std::vector<double>> matrix = {
		   {2, 1, -1, 8},
		   {-3, -1, 2, -11},
		   {-2, 1, 2, -3}
	};

	std::vector<double> solution = cramer(matrix);

	std::cout << "Решение системы:" << std::endl;
	for (int i = 0; i < solution.size(); ++i) {
		std::cout << "x" << i + 1 << " = " << solution[i] << endl;
	}

	return 0;
}


