#pragma once

namespace gp1
{
	template<size_t S, typename T>
	struct Vec;

	template<typename T>
	struct Vec<1, T>
	{
		union
		{
			struct
			{
				T x;
			};

			struct
			{
				T r;
			};
		};
	};

	template<typename T>
	struct Vec<2, T>
	{
		union
		{
			struct
			{
				T x, y;
			};

			struct
			{
				T r, g;
			};
		};
	};

	template<typename T>
	struct Vec<3, T>
	{
		union
		{
			struct
			{
				T x, y, z;
			};

			struct
			{
				T r, g, b;
			};
		};
	};

	template<typename T>
	struct Vec<4, T>
	{
		union
		{
			struct
			{
				T x, y, z, w;
			};

			struct
			{
				T r, g, b, a;
			};
		};
	};

	typedef Vec<2, float> Vec2;
	typedef Vec<3, float> Vec3;
	typedef Vec<4, float> Vec4;


}
