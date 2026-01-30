#include "MEGEngine/primitive_shapes.h"

namespace MEGEngine {
	std::vector<Vertex> Cube::_vertices =
		{
			//                  Position                       /                  Normal                 /                 Colours                /           Texture Coords            //
			// top
			Vertex{Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},

			// front
			Vertex{Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},

			// right
			Vertex{Vec3(01.0, -01.0,  01.0), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(01.0, -01.0, -01.0), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(01.0,  01.0, -01.0), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(01.0,  01.0,  01.0), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},

			// back
			Vertex{Vec3( 1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},

			// left
			Vertex{Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f,  1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},

			// bottom
			Vertex{Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f, -1.0f, -1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3( 1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)},
			Vertex{Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f,  0.0f,  0.0f), Vec3(0.0f,  0.0f,  0.0f), Vec2(0.0f,  0.0f)}
		};

	std::vector<unsigned int> Cube::_indices =
	{
		// top
		0, 1, 2,
		2, 3, 0,

		// front
		4, 5, 6,
		6, 7, 4,

		// right
		8, 9, 10,
		10, 11, 8,

		// back
		12, 13, 14,
		14, 15, 12,

		// left
		16, 17, 18,
		18, 19, 16,

		// bottom
		20, 21, 22,
		22, 23, 20
	};


} // MEGEngine