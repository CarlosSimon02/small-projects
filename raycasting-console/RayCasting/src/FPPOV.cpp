#include "FPPOV.h"
#include "Utils.h"


bool FPPOV::OnUserCreate()
{
	ConstructConsole(srn::WIDTH, srn::HEIGHT, srn::FONTX, srn::FONTY);

	return true;
}

bool FPPOV::OnUserUpdate(float fElapsedTime)
{
	Fill(0, 0, srn::WIDTH, srn::HEIGHT, ' ');
	if (m_keys[VK_LEFT].bHeld) cam.dir -= (fElapsedTime*5.f);
	else if (m_keys[VK_RIGHT].bHeld) cam.dir += (fElapsedTime*5.f);
	else if (m_keys[VK_UP].bHeld)
	{
		cam.pos.x += (cosf(cam.dir) * fElapsedTime);
		cam.pos.y += (sinf(cam.dir) * fElapsedTime);
		if (map.getFig().c_str()[(int)cam.pos.x + (int)cam.pos.y * map.getDim().x] == 'O')
		{
			cam.pos.x -= (cosf(cam.dir) * fElapsedTime);
			cam.pos.y -= (sinf(cam.dir) * fElapsedTime);
		}
	}
	else if (m_keys[VK_DOWN].bHeld)
	{
		cam.pos.x -= (cosf(cam.dir) * fElapsedTime);
		cam.pos.y -= (sinf(cam.dir) * fElapsedTime);
		if (map.getFig().c_str()[(int)cam.pos.x + (int)cam.pos.y * map.getDim().x] == 'O')
		{
			cam.pos.x += (cosf(cam.dir) * fElapsedTime);
			cam.pos.y += (sinf(cam.dir) * fElapsedTime);
		}
	}


	for (int y = 0; y < srn::HEIGHT / 2; y++)
	{
		for (int x = 0; x < srn::WIDTH; x++)
		{
			m_bufScreen[x + (y + srn::HEIGHT / 2) * srn::WIDTH].Char.UnicodeChar = 0x2588;
			m_bufScreen[x + (y + srn::HEIGHT / 2) * srn::WIDTH].Attributes = COLOUR::FG_DARK_GREEN;
		}
	}

	for (int i = 0; i < srn::WIDTH; i++)
	{
		float rayAngle = (cam.dir - cam.FOV / 2.0f) + ((float)i / (float)srn::WIDTH * cam.FOV);
		float distanceToWall{};
		int side{};
		int projWallHeight{};
		bool hitWall = false;

		olc::vec2di rayPos{ (int)cam.pos.x, (int)cam.pos.y };

		olc::vec2df rayForIntersect{};
		olc::vec2df deltaDis{};
		deltaDis.x =  abs(1 / cosf(rayAngle));
		deltaDis.y =  abs(1 / sinf(rayAngle));

		rayForIntersect.x = (cosf(rayAngle) < 0) ? (cam.pos.x - rayPos.x)*deltaDis.x : (rayPos.x + 1 - cam.pos.x)*deltaDis.x;
		rayForIntersect.y = (sinf(rayAngle) < 0) ? (cam.pos.y - rayPos.y)*deltaDis.y : (rayPos.y + 1 - cam.pos.y)*deltaDis.y;

		olc::vec2di rayPosStep{};
		rayPosStep.x = (cosf(rayAngle) < 0) ? -1 : 1;
		rayPosStep.y = (sinf(rayAngle) < 0) ? -1 : 1;

		 
		while(!hitWall)
		{
			if (rayForIntersect.x < rayForIntersect.y)
			{
				rayPos.x += rayPosStep.x;
				rayForIntersect.x += deltaDis.x;
				side = 0;
			}

			else
			{
				rayPos.y += rayPosStep.y;
				rayForIntersect.y += deltaDis.y;
				side = 1;
			}


			if (rayPos.x < 0 || rayPos.x >= map.getDim().x || rayPos.y < 0 || rayPos.y >= map.getDim().y) break;

			else if (map.getFig().c_str()[rayPos.point(map.getDim().x)] == 'O')
			{
				distanceToWall = (side == 0) ? ((rayForIntersect.x - deltaDis.x) * cosf(rayAngle - cam.dir)) : ((rayForIntersect.y - deltaDis.y) * cosf(rayAngle - cam.dir));
				hitWall = true;
				projWallHeight = ((int)(map.getWallHeight() / distanceToWall) >srn::HEIGHT) ? srn::HEIGHT:(int)(map.getWallHeight() / distanceToWall);

				int ceiling = (srn::HEIGHT-1 < projWallHeight) ? 0 : (srn::HEIGHT/2 - projWallHeight/2);

				for (int j = 0; j < projWallHeight; j++)
				{
					wchar_t shade{};
					if (distanceToWall >= 0 && distanceToWall < 3) shade = 0x2588;
					else if (distanceToWall >= 3 && distanceToWall < 6) shade = 0x2593;
					else if (distanceToWall >= 6 && distanceToWall < 9) shade = 0x2592;
					else if (distanceToWall >= 9 && distanceToWall < 12) shade = 0x2591;
					else if (distanceToWall >= 12) shade = L' ';

					m_bufScreen[i + (j + ceiling) * srn::WIDTH].Char.UnicodeChar = shade;
					m_bufScreen[i + (j + ceiling) * srn::WIDTH].Attributes = COLOUR::FG_BLUE;
				}

			}
		}

	}

	return true;
}