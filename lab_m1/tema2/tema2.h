#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/tema2_camera.h"

#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

namespace m1
{
	class Tema2 : public gfxc::SimpleScene
	{

	public:
		/*
		struct ViewportSpace
		{
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};
		*/

		struct Coordonate
		{
			Coordonate() : x(0), y(0.5f), z(0) {}
			Coordonate(float x, float y, float z) : x(x), y(y), z(z) {}
			float x, y, z;
		};

		struct Player
		{
			Player() : cap(Coordonate()), picioare(Coordonate()), trunchi(Coordonate()), umarStang(Coordonate()), umarDrept(Coordonate()), bratStang(Coordonate()), bratDrept(Coordonate()), directie() {}
			Player(Coordonate cap, Coordonate trunchi, Coordonate picioare, Coordonate umarStang, Coordonate umarDrept, Coordonate bratStang, Coordonate bratDrept, int directie)
				: cap(cap), trunchi(trunchi), picioare(picioare), umarStang(umarStang), umarDrept(umarDrept), bratStang(bratStang), bratDrept(bratDrept), directie(directie) {}
			Coordonate cap, trunchi, picioare, umarStang, umarDrept, bratStang, bratDrept;
			int directie;
		};

		struct Enemie
		{
			Enemie() : cap(Coordonate()), picioare(Coordonate()), trunchi(Coordonate()), initial(Coordonate()), directie() {}
			Enemie(Coordonate cap, Coordonate trunchi, Coordonate picioare, Coordonate initial, int directie)
				: cap(cap), trunchi(trunchi), picioare(picioare), initial(initial), directie(directie) {}
			Coordonate cap, trunchi, picioare, initial;
			int directie;
		};

		struct Glonte
		{
			Glonte() : x(0), y(0), z(0), directie(), viata() {}
			Glonte(float x, float y, float z, int directie, float viata) : x(x), y(y), z(z), directie(directie), viata(viata) {}
			float x, y, z, viata;
			int directie;
		};

	public:
		Tema2();
		~Tema2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void pozitioneazaPlayer();
		void deseneazaLabirint();
		void pozitioneazaInamic(Enemie enemie);
		bool bulletHitTheWall(Glonte gloante);
		bool playerTouchTheWall(Player player);
		bool bulletHitAnEnemie(Enemie enemie, Glonte glonte);
		bool isWinning();

	protected:
		implemente::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		Coordonate primulNivel[10][10] = { {Coordonate(-5, 0.5f, -5), Coordonate(-4, 0.5f, -5), Coordonate(-3, 0.5f, -5), Coordonate(-2, 0.5f, -5), Coordonate(-1, 0.5f, -5), Coordonate(0, 0.5f, -5), Coordonate(1, 0.5f, -5), Coordonate(2, 0.5f, -5), Coordonate(3, 0.5f, -5), Coordonate(4, 0.5f, -5)},
									{Coordonate(-5, 0.5f, -4), Coordonate(-4, 0.5f, -4), Coordonate(-3, 0.5f, -4), Coordonate(-2, 0.5f, -4), Coordonate(-1, 0.5f, -4), Coordonate(0, 0.5f, -4), Coordonate(1, 0.5f, -4), Coordonate(2, 0.5f, -4), Coordonate(3, 0.5f, -4), Coordonate(4, 0.5f, -4)},
									{Coordonate(-5, 0.5f, -3), Coordonate(-4, 0.5f, -3), Coordonate(-3, 0.5f, -3), Coordonate(-2, 0.5f, -3), Coordonate(-1, 0.5f, -3), Coordonate(0, 0.5f, -3), Coordonate(1, 0.5f, -3), Coordonate(2, 0.5f, -3), Coordonate(3, 0.5f, -3), Coordonate(4, 0.5f, -3)},
									{Coordonate(-5, 0.5f, -2), Coordonate(-4, 0.5f, -2), Coordonate(-3, 0.5f, -2), Coordonate(-2, 0.5f, -2), Coordonate(-1, 0.5f, -2), Coordonate(0, 0.5f, -2), Coordonate(1, 0.5f, -2), Coordonate(2, 0.5f, -2), Coordonate(3, 0.5f, -2), Coordonate(4, 0.5f, -2)},
									{Coordonate(-5, 0.5f, -1), Coordonate(-4, 0.5f, -1), Coordonate(-3, 0.5f, -1), Coordonate(-2, 0.5f, -1), Coordonate(-1, 0.5f, -1), Coordonate(0, 0.5f, -1), Coordonate(1, 0.5f, -1), Coordonate(2, 0.5f, -1), Coordonate(3, 0.5f, -1), Coordonate(4, 0.5f, -1)},
									{Coordonate(-5, 0.5f, 0), Coordonate(-4, 0.5f, 0), Coordonate(-3, 0.5f, 0), Coordonate(-2, 0.5f, 0), Coordonate(-1, 0.5f, 0), Coordonate(0, 0.5f, 0), Coordonate(1, 0.5f, 0), Coordonate(2, 0.5f, 0), Coordonate(3, 0.5f, 0), Coordonate(4, 0.5f, 0)},
									{Coordonate(-5, 0.5f, 1), Coordonate(-4, 0.5f, 1), Coordonate(-3, 0.5f, 1), Coordonate(-2, 0.5f, 1), Coordonate(-1, 0.5f, 1), Coordonate(0, 0.5f, 1), Coordonate(1, 0.5f, 1), Coordonate(2, 0.5f, 1), Coordonate(3, 0.5f, 1), Coordonate(4, 0.5f, 1)},
									{Coordonate(-5, 0.5f, 2), Coordonate(-4, 0.5f, 2), Coordonate(-3, 0.5f, 2), Coordonate(-2, 0.5f, 2), Coordonate(-1, 0.5f, 2), Coordonate(0, 0.5f, 2), Coordonate(1, 0.5f, 2), Coordonate(2, 0.5f, 2), Coordonate(3, 0.5f, 2), Coordonate(4, 0.5f, 2)},
									{Coordonate(-5, 0.5f, 3), Coordonate(-4, 0.5f, 3), Coordonate(-3, 0.5f, 3), Coordonate(-2, 0.5f, 3), Coordonate(-1, 0.5f, 3), Coordonate(0, 0.5f, 3), Coordonate(1, 0.5f, 3), Coordonate(2, 0.5f, 3), Coordonate(3, 0.5f, 3), Coordonate(4, 0.5f, 3)},
									{Coordonate(-5, 0.5f, 4), Coordonate(-4, 0.5f, 4), Coordonate(-3, 0.5f, 4), Coordonate(-2, 0.5f, 4), Coordonate(-1, 0.5f, 4), Coordonate(0, 0.5f, 4), Coordonate(1, 0.5f, 4), Coordonate(2, 0.5f, 4), Coordonate(3, 0.5f, 4), Coordonate(4, 0.5f, 4)} };

		Coordonate alDoileaNivel[10][10] = { {Coordonate(-5, 1.5f, -5), Coordonate(-4, 1.5f, -5), Coordonate(-3, 1.5f, -5), Coordonate(-2, 1.5f, -5), Coordonate(-1, 1.5f, -5), Coordonate(0, 1.5f, -5), Coordonate(1, 1.5f, -5), Coordonate(2, 1.5f, -5), Coordonate(3, 1.5f, -5), Coordonate(4, 1.5f, -5)},
									{Coordonate(-5, 1.5f, -4), Coordonate(-4, 1.5f, -4), Coordonate(-3, 1.5f, -4), Coordonate(-2, 1.5f, -4), Coordonate(-1, 1.5f, -4), Coordonate(0, 1.5f, -4), Coordonate(1, 1.5f, -4), Coordonate(2, 1.5f, -4), Coordonate(3, 1.5f, -4), Coordonate(4, 1.5f, -4)},
									{Coordonate(-5, 1.5f, -3), Coordonate(-4, 1.5f, -3), Coordonate(-3, 1.5f, -3), Coordonate(-2, 1.5f, -3), Coordonate(-1, 1.5f, -3), Coordonate(0, 1.5f, -3), Coordonate(1, 1.5f, -3), Coordonate(2, 1.5f, -3), Coordonate(3, 1.5f, -3), Coordonate(4, 1.5f, -3)},
									{Coordonate(-5, 1.5f, -2), Coordonate(-4, 1.5f, -2), Coordonate(-3, 1.5f, -2), Coordonate(-2, 1.5f, -2), Coordonate(-1, 1.5f, -2), Coordonate(0, 1.5f, -2), Coordonate(1, 1.5f, -2), Coordonate(2, 1.5f, -2), Coordonate(3, 1.5f, -2), Coordonate(4, 1.5f, -2)},
									{Coordonate(-5, 1.5f, -1), Coordonate(-4, 1.5f, -1), Coordonate(-3, 1.5f, -1), Coordonate(-2, 1.5f, -1), Coordonate(-1, 1.5f, -1), Coordonate(0, 1.5f, -1), Coordonate(1, 1.5f, -1), Coordonate(2, 1.5f, -1), Coordonate(3, 1.5f, -1), Coordonate(4, 1.5f, -1)},
									{Coordonate(-5, 1.5f, 0), Coordonate(-4, 1.5f, 0), Coordonate(-3, 1.5f, 0), Coordonate(-2, 1.5f, 0), Coordonate(-1, 1.5f, 0), Coordonate(0, 1.5f, 0), Coordonate(1, 1.5f, 0), Coordonate(2, 1.5f, 0), Coordonate(3, 1.5f, 0), Coordonate(4, 1.5f, 0)},
									{Coordonate(-5, 1.5f, 1), Coordonate(-4, 1.5f, 1), Coordonate(-3, 1.5f, 1), Coordonate(-2, 1.5f, 1), Coordonate(-1, 1.5f, 1), Coordonate(0, 1.5f, 1), Coordonate(1, 1.5f, 1), Coordonate(2, 1.5f, 1), Coordonate(3, 1.5f, 1), Coordonate(4, 1.5f, 1)},
									{Coordonate(-5, 1.5f, 2), Coordonate(-4, 1.5f, 2), Coordonate(-3, 1.5f, 2), Coordonate(-2, 1.5f, 2), Coordonate(-1, 1.5f, 2), Coordonate(0, 1.5f, 2), Coordonate(1, 1.5f, 2), Coordonate(2, 1.5f, 2), Coordonate(3, 1.5f, 2), Coordonate(4, 1.5f, 2)},
									{Coordonate(-5, 1.5f, 3), Coordonate(-4, 1.5f, 3), Coordonate(-3, 1.5f, 3), Coordonate(-2, 1.5f, 3), Coordonate(-1, 1.5f, 3), Coordonate(0, 1.5f, 3), Coordonate(1, 1.5f, 3), Coordonate(2, 1.5f, 3), Coordonate(3, 1.5f, 3), Coordonate(4, 1.5f, 3)},
									{Coordonate(-5, 1.5f, 4), Coordonate(-4, 1.5f, 4), Coordonate(-3, 1.5f, 4), Coordonate(-2, 1.5f, 4), Coordonate(-1, 1.5f, 4), Coordonate(0, 1.5f, 4), Coordonate(1, 1.5f, 4), Coordonate(2, 1.5f, 4), Coordonate(3, 1.5f, 4), Coordonate(4, 1.5f, 4)} };

		Coordonate alTreileaNivel[10][10] = { {Coordonate(-5, 2.5f, -5), Coordonate(-4, 2.5f, -5), Coordonate(-3, 2.5f, -5), Coordonate(-2, 2.5f, -5), Coordonate(-1, 2.5f, -5), Coordonate(0, 2.5f, -5), Coordonate(1, 2.5f, -5), Coordonate(2, 2.5f, -5), Coordonate(3, 2.5f, -5), Coordonate(4, 2.5f, -5)},
									{Coordonate(-5, 2.5f, -4), Coordonate(-4, 2.5f, -4), Coordonate(-3, 2.5f, -4), Coordonate(-2, 2.5f, -4), Coordonate(-1, 2.5f, -4), Coordonate(0, 2.5f, -4), Coordonate(1, 2.5f, -4), Coordonate(2, 2.5f, -4), Coordonate(3, 2.5f, -4), Coordonate(4, 2.5f, -4)},
									{Coordonate(-5, 2.5f, -3), Coordonate(-4, 2.5f, -3), Coordonate(-3, 2.5f, -3), Coordonate(-2, 2.5f, -3), Coordonate(-1, 2.5f, -3), Coordonate(0, 2.5f, -3), Coordonate(1, 2.5f, -3), Coordonate(2, 2.5f, -3), Coordonate(3, 2.5f, -3), Coordonate(4, 2.5f, -3)},
									{Coordonate(-5, 2.5f, -2), Coordonate(-4, 2.5f, -2), Coordonate(-3, 2.5f, -2), Coordonate(-2, 2.5f, -2), Coordonate(-1, 2.5f, -2), Coordonate(0, 2.5f, -2), Coordonate(1, 2.5f, -2), Coordonate(2, 2.5f, -2), Coordonate(3, 2.5f, -2), Coordonate(4, 2.5f, -2)},
									{Coordonate(-5, 2.5f, -1), Coordonate(-4, 2.5f, -1), Coordonate(-3, 2.5f, -1), Coordonate(-2, 2.5f, -1), Coordonate(-1, 2.5f, -1), Coordonate(0, 2.5f, -1), Coordonate(1, 2.5f, -1), Coordonate(2, 2.5f, -1), Coordonate(3, 2.5f, -1), Coordonate(4, 2.5f, -1)},
									{Coordonate(-5, 2.5f, 0), Coordonate(-4, 2.5f, 0), Coordonate(-3, 2.5f, 0), Coordonate(-2, 2.5f, 0), Coordonate(-1, 2.5f, 0), Coordonate(0, 2.5f, 0), Coordonate(1, 2.5f, 0), Coordonate(2, 2.5f, 0), Coordonate(3, 2.5f, 0), Coordonate(4, 2.5f, 0)},
									{Coordonate(-5, 2.5f, 1), Coordonate(-4, 2.5f, 1), Coordonate(-3, 2.5f, 1), Coordonate(-2, 2.5f, 1), Coordonate(-1, 2.5f, 1), Coordonate(0, 2.5f, 1), Coordonate(1, 2.5f, 1), Coordonate(2, 2.5f, 1), Coordonate(3, 2.5f, 1), Coordonate(4, 2.5f, 1)},
									{Coordonate(-5, 2.5f, 2), Coordonate(-4, 2.5f, 2), Coordonate(-3, 2.5f, 2), Coordonate(-2, 2.5f, 2), Coordonate(-1, 2.5f, 2), Coordonate(0, 2.5f, 2), Coordonate(1, 2.5f, 2), Coordonate(2, 2.5f, 2), Coordonate(3, 2.5f, 2), Coordonate(4, 2.5f, 2)},
									{Coordonate(-5, 2.5f, 3), Coordonate(-4, 2.5f, 3), Coordonate(-3, 2.5f, 3), Coordonate(-2, 2.5f, 3), Coordonate(-1, 2.5f, 3), Coordonate(0, 2.5f, 3), Coordonate(1, 2.5f, 3), Coordonate(2, 2.5f, 3), Coordonate(3, 2.5f, 3), Coordonate(4, 2.5f, 3)},
									{Coordonate(-5, 2.5f, 4), Coordonate(-4, 2.5f, 4), Coordonate(-3, 2.5f, 4), Coordonate(-2, 2.5f, 4), Coordonate(-1, 2.5f, 4), Coordonate(0, 2.5f, 4), Coordonate(1, 2.5f, 4), Coordonate(2, 2.5f, 4), Coordonate(3, 2.5f, 4), Coordonate(4, 2.5f, 4)} };
		// TODO(student): If you need any other class variables, define them here.
		bool projectionType;
		std::vector<Coordonate> coords, walls, exits;
		std::vector<Coordonate> enemiesCoords;
		std::vector<Enemie> enemies;
		std::vector<Glonte> gloante;
		Coordonate playerCoords = Coordonate();
		Player player;
		int healthbar = 5, totalTime = 10000, nr_labirint, winning = 0;

		GLfloat right;
		GLfloat left;
		GLfloat bottom;
		GLfloat top;
		GLfloat fov;
	};
}   // namespace m1

