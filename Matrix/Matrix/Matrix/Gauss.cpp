#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>


static void printMatrix(const std::vector<std::vector<double>>& matrix)
{
	for (const auto& row : matrix) {
		for (double elem : row) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}
}


std::vector<double> gauess(std::vector<std::vector<double>> matrix) {
	int n = matrix.size();

	for (int i = 0; i < n; ++i) {
		int maxRow = i;
		for (int k = i + 1; k < n; ++k) {
			if (std::abs(matrix[k][i]) > std::abs(matrix[maxRow][i])) {
				maxRow = k;
			}
		}
		std::swap(matrix[i], matrix[maxRow]);

		double div = matrix[i][i];
		for (int j = i; j <= n; ++j) {
			matrix[i][j] /= div;
		}

		for (int k = i + 1; k < n; ++k) {
			double factor = matrix[k][i];
			for (int j = i; j <= n; ++j) {
				matrix[k][j] -= factor * matrix[i][j];
			}
		}
	}

	std::vector<double> solution(n);
	for (int i = n - 1; i >= 0; --i) {
		solution[i] = matrix[i][n];
		for (int j = i + 1; j < n; ++j) {
			solution[i] -= matrix[i][j] * solution[j];
		}
	}

	return solution;
}

int main(void)
{

	setlocale(LC_ALL, "ru");

	std::vector<std::vector<double>> matrix = {
		{2, 1, -1, 8},
		{-3, -1, 2, -11},
		{-2, 1, 2, -3}
	};

	std::vector<double> solution = gauess(matrix);

	std::cout << "Решение системы: " << std::endl;
	for (int i = 0; i < solution.size(); ++i) {
		std::cout << "x" << i + 1 << " = " << solution[i] << std::endl;
	}

	return 0;
}






 
