#pragma once

namespace gp1
{
	template<size_t x, size_t y, typename T>
	struct Matrix;

	template<typename T>
	struct Matrix<1, 1, T>
	{
		Matrix<1, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<1, 2, T>
	{
		Matrix<1, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<1, 3, T>
	{
		Matrix<1, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<1, 4, T>
	{
		Matrix<1, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<2, 1, T>
	{
		Matrix<2, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<2, 2, T>
	{
		Matrix<2, 2, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<2, 3, T>
	{
		Matrix<2, 3, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<2, 4, T>
	{
		Matrix<2, 4, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<3, 1, T>
	{
		Matrix<3, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<3, 2, T>
	{
		Matrix<3, 2, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<3, 3, T>
	{
		Matrix<3, 3, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<3, 4, T>
	{
		Matrix<3, 4, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<4, 1, T>
	{
		Matrix<4, 1, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<4, 2, T>
	{
		Matrix<4, 2, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<4, 3, T>
	{
		Matrix<4, 3, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};

	template<typename T>
	struct Matrix<4, 4, T>
	{
		Matrix<4, 4, T>(T a_x1) : x1(a_x1) {}

		T x1;
	};
}
