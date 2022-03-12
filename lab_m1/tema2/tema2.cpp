#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/tema2_camera.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

int directieGlonte = 0, directiePlayer = 0;
float fata = RADIANS(0.0f), spate = RADIANS(180.0f), stanga = RADIANS(90.0f), dreapta = RADIANS(270.0f), directie;

//bool unlockS = true, unlockW = true;

int lab[10][10] = { {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
					{1, 2, 0, 0, 0, 0, 0, 0, 1, 1},
					{1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
					{1, 0, 0, 2, 0, 1, 1, 2, 0, 1},
					{1, 0, 1, 1, 0, 0, 0, 0, 1, 1},
					{1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
					{0, 2, 0, 0, 0, 1, 0, 0, 1, 1},
					{1, 1, 0, 1, 1, 1, 1, 0, 0, 1},
					{1, 1, 0, 0, 2, 2, 0, 1, 1, 1},
					{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

int lab1[10][10] = { {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
					{1, 0, 1, 1, 0, 0, 0, 0, 1, 1},
					{1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
					{1, 0, 2, 0, 0, 1, 1, 0, 0, 0},
					{1, 1, 0, 1, 2, 0, 0, 0, 1, 1},
					{1, 1, 1, 1, 2, 1, 0, 1, 1, 1},
					{1, 0, 2, 0, 0, 1, 0, 2, 0, 1},
					{1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
					{1, 1, 2, 0, 0, 0, 0, 0, 2, 1},
					{1, 1, 1, 1, 1, 1, 1, 1, 0, 1} };

int lab2[10][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
					{1, 1, 1, 1, 0, 0, 0, 0, 1, 1},
					{1, 0, 0, 1, 2, 1, 1, 1, 1, 1},
					{1, 0, 2, 0, 0, 1, 1, 2, 1, 1},
					{1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
					{1, 0, 0, 1, 0, 1, 0, 1, 1, 1},
					{1, 0, 2, 0, 2, 1, 0, 0, 1, 1},
					{1, 1, 0, 1, 1, 1, 1, 2, 0, 0},
					{1, 0, 0, 0, 0, 2, 0, 1, 1, 1},
					{1, 0, 1, 1, 1, 1, 1, 1, 1, 1} };

int lab3[10][10] = { {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
					{0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
					{1, 1, 1, 1, 0, 1, 1, 1, 2, 1},
					{1, 1, 0, 2, 0, 1, 1, 0, 0, 1},
					{1, 1, 0, 1, 0, 2, 0, 0, 1, 1},
					{1, 0, 0, 0, 0, 1, 0, 1, 1, 1},
					{1, 2, 1, 0, 1, 1, 1, 0, 1, 1},
					{1, 0, 0, 2, 0, 0, 0, 0, 0, 1},
					{1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
					{1, 2, 1, 1, 1, 1, 1, 1, 1, 1} };

int lab4[10][10] = { {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
					{1, 2, 0, 0, 0, 1, 0, 0, 0, 1},
					{1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
					{1, 0, 0, 0, 2, 1, 1, 2, 0, 1},
					{1, 2, 1, 1, 0, 0, 1, 0, 1, 1},
					{1, 0, 0, 1, 0, 1, 1, 2, 1, 1},
					{1, 1, 0, 2, 0, 1, 1, 0, 1, 1},
					{1, 1, 0, 1, 1, 1, 1, 2, 0, 1},
					{1, 0, 2, 0, 0, 0, 1, 1, 0, 1},
					{1, 0, 1, 1, 1, 1, 1, 1, 0, 1} };


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
	renderCameraTarget = false;
	projectionType = true;

	directie = fata;

	right = 10.f;
	left = .01f;
	bottom = .01f;
	top = 10.f;
	fov = 40.f;

	srand(time(NULL));
	nr_labirint = rand() % 5;

	camera = new implemente::Camera();
	//camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// TODO(student): After you implement the changing of the projection
	// parameters, remove hardcodings of these parameters
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, Z_NEAR, Z_FAR);


	if (nr_labirint == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (lab[i][j] == 0) {
					coords.push_back(primulNivel[i][j]);
					if (i == 0 || j == 0)
						exits.push_back(primulNivel[i][j]);
				}
				if (lab[i][j] == 2) {
					enemies.push_back(Enemie(Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.35f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.2f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						0));
				}
				if (lab[i][j] == 1)
					walls.push_back(primulNivel[i][j]);
			}
		}
	}

	if (nr_labirint == 1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (lab1[i][j] == 0) {
					coords.push_back(primulNivel[i][j]);
					if (i == 0 || j == 0)
						exits.push_back(primulNivel[i][j]);
				}
				if (lab1[i][j] == 2) {
					enemies.push_back(Enemie(Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.35f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.2f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						0));
				}
				if (lab1[i][j] == 1)
					walls.push_back(primulNivel[i][j]);
			}
		}
	}

	if (nr_labirint == 2) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (lab2[i][j] == 0) {
					coords.push_back(primulNivel[i][j]);
					if (i == 0 || j == 0 || i == 9 || j == 9)
						exits.push_back(primulNivel[i][j]);
				}
				if (lab2[i][j] == 2) {
					enemies.push_back(Enemie(Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.35f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.2f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						0));
				}
				if (lab2[i][j] == 1)
					walls.push_back(primulNivel[i][j]);
			}
		}
	}

	if (nr_labirint == 3) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (lab3[i][j] == 0) {
					coords.push_back(primulNivel[i][j]);
					if (i == 0 || j == 0)
						exits.push_back(primulNivel[i][j]);
				}
				if (lab3[i][j] == 2) {
					enemies.push_back(Enemie(Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.35f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.2f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						0));
				}
				if (lab3[i][j] == 1)
					walls.push_back(primulNivel[i][j]);
			}
		}
	}

	if (nr_labirint == 4) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (lab4[i][j] == 0) {
					coords.push_back(primulNivel[i][j]);
					if (i == 0 || j == 0)
						exits.push_back(primulNivel[i][j]);
				}
				if (lab4[i][j] == 2) {
					enemies.push_back(Enemie(Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.35f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y + 0.2f, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						Coordonate(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z),
						0));
				}
				if (lab4[i][j] == 1)
					walls.push_back(primulNivel[i][j]);
			}
		}
	}


	//srand(time(NULL));
	int poz_rand = rand() % coords.size();
	playerCoords = coords[poz_rand];

	player.cap = Coordonate(playerCoords.x, playerCoords.y + 0.35f, playerCoords.z);
	player.trunchi = Coordonate(playerCoords.x, playerCoords.y + 0.2f, playerCoords.z);
	player.picioare = Coordonate(playerCoords.x, playerCoords.y, playerCoords.z);
	player.umarStang = Coordonate(playerCoords.x - 0.15f, playerCoords.y + 0.25f, playerCoords.z);
	player.umarDrept = Coordonate(playerCoords.x + 0.15f, playerCoords.y + 0.25f, playerCoords.z);
	player.bratStang = Coordonate(playerCoords.x - 0.15f, playerCoords.y + 0.15f, playerCoords.z);
	player.bratDrept = Coordonate(playerCoords.x + 0.15f, playerCoords.y + 0.15f, playerCoords.z);

	//coordsCameraX = playerCoords.x;
	//camera->Set(glm::vec3(playerCoords.x, playerCoords.y, playerCoords.z), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(0, playerCoords.y + 1, 3), glm::vec3(0, playerCoords.y + 1, 2), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
}


void Tema2::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
	if ((healthbar > 0) && (totalTime > 0) && (winning >= 0)) {

		if (isWinning() == true) {
			cout << "YOU WON!!!" << endl;
			winning = -1;
		}

		totalTime -= 0.0001f;
		deseneazaLabirint();

		pozitioneazaPlayer();

		for (int i = 0; i < enemies.size(); i++) {
			if (player.trunchi.x > enemies[i].trunchi.x - 0.1f && player.trunchi.x < enemies[i].trunchi.x + 0.1f && player.trunchi.y > enemies[i].trunchi.y - 0.1f && player.trunchi.y < enemies[i].trunchi.y + 0.1f
				&& player.trunchi.z > enemies[i].trunchi.z - 0.1f && player.trunchi.z < enemies[i].trunchi.z + 0.1f)
				healthbar--;
			for (int j = 0; j < gloante.size(); j++) {
				if (bulletHitAnEnemie(enemies[i], gloante[j]) == true) {
					gloante.erase(gloante.begin() + j);
					enemies.erase(enemies.begin() + i);
				}
			}
		}

		for (int i = 0; i < gloante.size(); i++) {
			if (bulletHitTheWall(gloante[i]) == true) {
				gloante.erase(gloante.begin() + i);
				//continue;
			}
			else if (gloante[i].viata <= 0) {
				gloante.erase(gloante.begin() + i);

			}
			else {
				gloante[i].viata -= 0.03f;
				if (gloante[i].directie == 0) {
					gloante[i].z -= 0.03f;
				}
				if (gloante[i].directie == 1) {
					gloante[i].z += 0.03f;
				}
				if (gloante[i].directie == 2) {
					gloante[i].x -= 0.03f;
				}
				if (gloante[i].directie == 3) {
					gloante[i].x += 0.03f;
				}
				glm::mat4 modelMatrix = glm::mat4(1);
				modelMatrix = glm::translate(modelMatrix, glm::vec3(gloante[i].x, gloante[i].y, gloante[i].z));
				modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
				RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
			}
		}

		for (int i = 0; i < enemies.size(); i++) {

			if (enemies[i].directie == 0) {
				if (enemies[i].initial.z - 0.4f < enemies[i].cap.z) {
					enemies[i].cap.z -= 0.01f;
					enemies[i].picioare.z -= 0.01f;
					enemies[i].trunchi.z -= 0.01f;
				}
				else enemies[i].directie = 1;
				//if (enemies[i].initial.z - 0.3f >= enemies[i].cap.z) enemies[i].directie = 2;
			}

			if (enemies[i].directie == 1) {
				if (enemies[i].initial.x + 0.4f > enemies[i].cap.x) {
					enemies[i].cap.x += 0.01f;
					enemies[i].picioare.x += 0.01f;
					enemies[i].trunchi.x += 0.01f;
				}
				else enemies[i].directie = 2;
			}
			if (enemies[i].directie == 2) {
				if (enemies[i].initial.z + 0.4f > enemies[i].cap.z) {
					enemies[i].cap.z += 0.01f;
					//enemies[i].cap.z += enemies[i].initial.z;
					enemies[i].picioare.z += 0.01f;
					enemies[i].trunchi.z += 0.01f;
				}
				else enemies[i].directie = 3;
			}
			if (enemies[i].directie == 3) {
				if (enemies[i].initial.x - 0.4f < enemies[i].cap.x) {
					enemies[i].cap.x -= 0.01f;
					enemies[i].picioare.x -= 0.01f;
					enemies[i].trunchi.x -= 0.01f;
				}
				else enemies[i].directie = 0;
			}
		}

		for (int i = 0; i < enemies.size(); i++) {
			pozitioneazaInamic(enemies[i]);
		}

		if (renderCameraTarget)
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
			modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
		}
	}
	else if ((healthbar == 0) || (totalTime == 0)) {
		cout << "GAME OVER" << endl;
		healthbar--;
		totalTime--;
	}
	else {
		healthbar--;
		totalTime--;
	};
}

bool Tema2::playerTouchTheWall(Player player) {
	for (int i = 0; i < walls.size(); i++) {
		//if (glonte.x > coords[i].x - 0.5f && glonte.x < coords[i].x + 0.5f && glonte.y > coords[i].y - 0.5f && glonte.y < coords[i].y + 0.5f
		//	&& glonte.z > coords[i].z - 0.5f && glonte.z < coords[i].z + 0.5f)
		if (player.trunchi.x > walls[i].x - 0.5f && player.trunchi.x < walls[i].x + 0.5f && player.trunchi.y > walls[i].y - 0.5f && player.trunchi.y < walls[i].y + 0.5f
			&& player.trunchi.z > walls[i].z - 0.5f && player.trunchi.z < walls[i].z + 0.5f)
			//if (glonte.x == walls[i].x && glonte.z == walls[i].z)
			//cout << "glonte eliminat\n";
			return true;
	}
	return false;
}

bool Tema2::bulletHitTheWall(Glonte glonte) {
	for (int i = 0; i < walls.size(); i++) {
		//if (glonte.x > coords[i].x - 0.5f && glonte.x < coords[i].x + 0.5f && glonte.y > coords[i].y - 0.5f && glonte.y < coords[i].y + 0.5f
		//	&& glonte.z > coords[i].z - 0.5f && glonte.z < coords[i].z + 0.5f)
		if (glonte.x > walls[i].x - 0.5f && glonte.x < walls[i].x + 0.5f && glonte.y > walls[i].y - 0.5f && glonte.y < walls[i].y + 0.5f
			&& glonte.z > walls[i].z - 0.5f && glonte.z < walls[i].z + 0.5f)
			//if (glonte.x == walls[i].x && glonte.z == walls[i].z)
			//cout << "glonte eliminat\n";
			return true;
	}
	return false;
}

void Tema2::deseneazaLabirint() {
	if (nr_labirint == 0) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				if (lab[i][j] == 1) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alDoileaNivel[i][j].x, alDoileaNivel[i][j].y, alDoileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alTreileaNivel[i][j].x, alTreileaNivel[i][j].y, alTreileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}
				}
		}
	}

	if (nr_labirint == 1) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				if (lab1[i][j] == 1) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alDoileaNivel[i][j].x, alDoileaNivel[i][j].y, alDoileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alTreileaNivel[i][j].x, alTreileaNivel[i][j].y, alTreileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}
				}
		}
	}

	if (nr_labirint == 2) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				if (lab2[i][j] == 1) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alDoileaNivel[i][j].x, alDoileaNivel[i][j].y, alDoileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alTreileaNivel[i][j].x, alTreileaNivel[i][j].y, alTreileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}
				}
		}
	}

	if (nr_labirint == 3) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				if (lab3[i][j] == 1) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alDoileaNivel[i][j].x, alDoileaNivel[i][j].y, alDoileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alTreileaNivel[i][j].x, alTreileaNivel[i][j].y, alTreileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}
				}
		}
	}

	if (nr_labirint == 4) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++)
				if (lab4[i][j] == 1) {
					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(primulNivel[i][j].x, primulNivel[i][j].y, primulNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alDoileaNivel[i][j].x, alDoileaNivel[i][j].y, alDoileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}

					{
						glm::mat4 modelMatrix = glm::mat4(1);
						modelMatrix = glm::translate(modelMatrix, glm::vec3(alTreileaNivel[i][j].x, alTreileaNivel[i][j].y, alTreileaNivel[i][j].z));
						//modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
						RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
					}
				}
		}
	}
}

void Tema2::pozitioneazaPlayer() {

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.picioare.x, player.picioare.y, player.picioare.z));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.trunchi.x, player.trunchi.y, player.trunchi.z));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.cap.x, player.cap.y, player.cap.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.umarDrept.x, player.umarDrept.y, player.umarDrept.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.umarStang.x, player.umarStang.y, player.umarStang.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.bratDrept.x, player.bratDrept.y, player.bratDrept.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.bratStang.x, player.bratStang.y, player.bratStang.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(0, 1, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}
}

void Tema2::pozitioneazaInamic(Enemie enemie) {

	/*
	player.cap = Coordonate(playerCoords.x, playerCoords.y + 0.35f, playerCoords.z);
	player.trunchi = Coordonate(playerCoords.x, playerCoords.y + 0.2f, playerCoords.z);
	player.picioare = Coordonate(playerCoords.x, playerCoords.y, playerCoords.z);
	*/

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(enemie.picioare.x, enemie.picioare.y, enemie.picioare.z));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(1, 0, 0));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(enemie.trunchi.x, enemie.trunchi.y, enemie.trunchi.z));
		//modelMatrix = glm::rotate(modelMatrix, RADIANS(90.0f), glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(enemie.cap.x, enemie.cap.y, enemie.cap.z));
		//modelMatrix = glm::rotate(modelMatrix, directie, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}
}

bool Tema2::bulletHitAnEnemie(Enemie enemie, Glonte glonte) {
	//for (int i = 0; i < gloante.size(); i++) {
		//if (glonte.x > coords[i].x - 0.5f && glonte.x < coords[i].x + 0.5f && glonte.y > coords[i].y - 0.5f && glonte.y < coords[i].y + 0.5f
		//	&& glonte.z > coords[i].z - 0.5f && glonte.z < coords[i].z + 0.5f)
	if (enemie.trunchi.x > glonte.x - 0.1f && enemie.trunchi.x < glonte.x + 0.1f && enemie.trunchi.y > glonte.y - 0.1f && enemie.trunchi.y < glonte.y + 0.1f
		&& enemie.trunchi.z > glonte.z - 0.1f && enemie.trunchi.z < glonte.z + 0.1f)
		//if (glonte.x == walls[i].x && glonte.z == walls[i].z)
		//cout << "glonte eliminat\n";
		return true;
	//}
	return false;
}

bool Tema2::isWinning() {
	for (int i = 0; i < exits.size(); i++) {
		//if (player.picioare.x == exits[i].x && player.picioare.y == exits[i].y && player.picioare.z == exits[i].z)
		if (player.trunchi.x > exits[i].x - 0.5f && player.trunchi.x < exits[i].x + 0.5f && player.trunchi.y > exits[i].y - 0.5f && player.trunchi.y < exits[i].y + 0.5f
			&& player.trunchi.z > exits[i].z - 0.5f && player.trunchi.z < exits[i].z + 0.5f)
			return true;
	}
	return false;
}


void Tema2::FrameEnd()
{
	DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */




 /*if (playerTouchTheWall(player) == true) {
		 if (directie == fata) {
			 if (window->KeyHold(GLFW_KEY_W)) {
				 directieGlonte = 0;
			 }

			 if (window->KeyHold(GLFW_KEY_S)) {
				 directieGlonte = 1;
				 player.cap.z += deltaTime;
				 player.trunchi.z += deltaTime;
				 player.picioare.z += deltaTime;
				 player.umarStang.z += deltaTime;
				 player.umarDrept.z += deltaTime;
				 player.bratStang.z += deltaTime;
				 player.bratDrept.z += deltaTime;
			 }
			 if (window->KeyHold(GLFW_KEY_A)) {
				 //directie = RADIANS(90.0f);
				 directieGlonte = 2;
				 directie = stanga;
			 }
			 if (window->KeyHold(GLFW_KEY_D)) {
				 directieGlonte = 3;
				 directie = dreapta;
			 }
		 }

		 if (directie == spate) {
			 if (window->KeyHold(GLFW_KEY_S)) {
				 directieGlonte = 1;
			 }

			 if (window->KeyHold(GLFW_KEY_W)) {
				 directieGlonte = 0;
				 player.cap.z -= deltaTime;
				 player.trunchi.z -= deltaTime;
				 player.picioare.z -= deltaTime;
				 player.umarStang.z -= deltaTime;
				 player.umarDrept.z -= deltaTime;
				 player.bratStang.z -= deltaTime;
				 player.bratDrept.z -= deltaTime;
			 }
			 if (window->KeyHold(GLFW_KEY_D)) {
				 directieGlonte = 2;
				 directie = stanga;
			 }
			 if (window->KeyHold(GLFW_KEY_A)) {
				 directieGlonte = 3;
				 directie = dreapta;
			 }
		 }

		 if (directie == stanga) {
			 if (window->KeyHold(GLFW_KEY_D)) {
				 directieGlonte = 3;
			 }

			 if (window->KeyHold(GLFW_KEY_A)) {
				 directieGlonte = 2;
			 }
			 if (window->KeyHold(GLFW_KEY_W)) {
				 directieGlonte = 0;
				 directie = fata;
			 }
			 if (window->KeyHold(GLFW_KEY_S)) {
				 directieGlonte = 1;
				 directie = spate;
			 }
		 }

		 if (directie == dreapta) {
			 if (window->KeyHold(GLFW_KEY_D)) {
				 directieGlonte = 3;
			 }

			 if (window->KeyHold(GLFW_KEY_A)) {
				 directieGlonte = 2;
			 }
			 if (window->KeyHold(GLFW_KEY_S)) {
				 directieGlonte = 0;
				 directie = fata;
			 }
			 if (window->KeyHold(GLFW_KEY_W)) {
				 directieGlonte = 1;
				 directie = spate;
			 }
		 }
	 }
	 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_W)) {
		//if (playerTouchTheWall(player) == false) {
		directieGlonte = 0;
		player.cap.z -= deltaTime;
		player.trunchi.z -= deltaTime;
		player.picioare.z -= deltaTime;
		player.umarStang.z -= deltaTime;
		player.umarDrept.z -= deltaTime;
		player.bratStang.z -= deltaTime;
		player.bratDrept.z -= deltaTime;
		//}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		//if (playerTouchTheWall(player) == false) {
		directieGlonte = 1;
		player.cap.z += deltaTime;
		player.trunchi.z += deltaTime;
		player.picioare.z += deltaTime;
		player.umarStang.z += deltaTime;
		player.umarDrept.z += deltaTime;
		player.bratStang.z += deltaTime;
		player.bratDrept.z += deltaTime;
		//}
	}

	if (window->KeyHold(GLFW_KEY_D)) {
		//if (playerTouchTheWall(player) == false) {
		directieGlonte = 3;
		player.cap.x += deltaTime;
		player.trunchi.x += deltaTime;
		player.picioare.x += deltaTime;
		player.umarStang.x += deltaTime;
		player.umarDrept.x += deltaTime;
		player.bratStang.x += deltaTime;
		player.bratDrept.x += deltaTime;
		//}
	//	else directie = dreapta;
	}

	if (window->KeyHold(GLFW_KEY_A)) {
		//if (playerTouchTheWall(player) == false) {
		directieGlonte = 2;
		player.cap.x -= deltaTime;
		player.trunchi.x -= deltaTime;
		player.picioare.x -= deltaTime;
		player.umarStang.x -= deltaTime;
		player.umarDrept.x -= deltaTime;
		player.bratStang.x -= deltaTime;
		player.bratDrept.x -= deltaTime;
		//}
	}

	/*
		if (directie == fata) {

			if (window->KeyHold(GLFW_KEY_W)) {
				if (playerTouchTheWall(player) == false) {
					directieGlonte = 0;
					player.cap.z -= deltaTime;
					player.trunchi.z -= deltaTime;
					player.picioare.z -= deltaTime;
					player.umarStang.z -= deltaTime;
					player.umarDrept.z -= deltaTime;
					player.bratStang.z -= deltaTime;
					player.bratDrept.z -= deltaTime;
				} else directie = spate;
			}

			if (window->KeyHold(GLFW_KEY_S)) {
			//	if (playerTouchTheWall(player) == false) {
					directieGlonte = 1;
					player.cap.z += deltaTime;
					player.trunchi.z += deltaTime;
					player.picioare.z += deltaTime;
					player.umarStang.z += deltaTime;
					player.umarDrept.z += deltaTime;
					player.bratStang.z += deltaTime;
					player.bratDrept.z += deltaTime;
			//	}
			}
			if (window->KeyHold(GLFW_KEY_A)) {
				//directie = RADIANS(90.0f);
				directieGlonte = 2;
				directie = stanga;
			}
			if (window->KeyHold(GLFW_KEY_D)) {
				directieGlonte = 3;
				directie = dreapta;
			}
		}

		if (directie == spate) {
			if (window->KeyHold(GLFW_KEY_S)) {
				if (playerTouchTheWall(player) == false) {
					directieGlonte = 1;
					player.cap.z += deltaTime;
					player.trunchi.z += deltaTime;
					player.picioare.z += deltaTime;
					player.umarStang.z += deltaTime;
					player.umarDrept.z += deltaTime;
					player.bratStang.z += deltaTime;
					player.bratDrept.z += deltaTime;
				}
				else directie = fata;
			}

			if (window->KeyHold(GLFW_KEY_W)) {
				//if (playerTouchTheWall(player) == false) {
					directieGlonte = 0;
					player.cap.z -= deltaTime;
					player.trunchi.z -= deltaTime;
					player.picioare.z -= deltaTime;
					player.umarStang.z -= deltaTime;
					player.umarDrept.z -= deltaTime;
					player.bratStang.z -= deltaTime;
					player.bratDrept.z -= deltaTime;
				//}
			}
			if (window->KeyHold(GLFW_KEY_D)) {
				directieGlonte = 2;
				directie = stanga;
			}
			if (window->KeyHold(GLFW_KEY_A)) {
				directieGlonte = 3;
				directie = dreapta;
			}
		}

		if (directie == stanga) {
			if (window->KeyHold(GLFW_KEY_D)) {
				if (playerTouchTheWall(player) == false) {
					directieGlonte = 3;
					player.cap.x += deltaTime;
					player.trunchi.x += deltaTime;
					player.picioare.x += deltaTime;
					player.umarStang.x += deltaTime;
					player.umarDrept.x += deltaTime;
					player.bratStang.x += deltaTime;
					player.bratDrept.x += deltaTime;
				} else directie = dreapta;
			}

			if (window->KeyHold(GLFW_KEY_A)) {
			//	if (playerTouchTheWall(player) == false) {
					directieGlonte = 2;
					player.cap.x -= deltaTime;
					player.trunchi.x -= deltaTime;
					player.picioare.x -= deltaTime;
					player.umarStang.x -= deltaTime;
					player.umarDrept.x -= deltaTime;
					player.bratStang.x -= deltaTime;
					player.bratDrept.x -= deltaTime;
			//	}
			}
			if (window->KeyHold(GLFW_KEY_W)) {
				directieGlonte = 0;
				directie = fata;
			}
			if (window->KeyHold(GLFW_KEY_S)) {
				directieGlonte = 1;
				directie = spate;
			}
		}

		if (directie == dreapta) {
			if (window->KeyHold(GLFW_KEY_D)) {
				if (playerTouchTheWall(player) == false) {
					directieGlonte = 3;
					player.cap.x += deltaTime;
					player.trunchi.x += deltaTime;
					player.picioare.x += deltaTime;
					player.umarStang.x += deltaTime;
					player.umarDrept.x += deltaTime;
					player.bratStang.x += deltaTime;
					player.bratDrept.x += deltaTime;
				}
				else directie = stanga;
			}

			if (window->KeyHold(GLFW_KEY_A)) {
					directieGlonte = 2;
					player.cap.x -= deltaTime;
					player.trunchi.x -= deltaTime;
					player.picioare.x -= deltaTime;
					player.umarStang.x -= deltaTime;
					player.umarDrept.x -= deltaTime;
					player.bratStang.x -= deltaTime;
					player.bratDrept.x -= deltaTime;

			}
			if (window->KeyHold(GLFW_KEY_S)) {
				directieGlonte = 0;
				directie = fata;
			}
			if (window->KeyHold(GLFW_KEY_W)) {
				directieGlonte = 1;
				directie = spate;
			}
		}
		*/



	if (window->KeyHold(GLFW_KEY_LEFT_CONTROL)) {
		if (window->KeyHold(GLFW_KEY_SPACE)) {
			gloante.push_back(Glonte(player.trunchi.x, player.trunchi.y, player.trunchi.z, directieGlonte, 2.0f));
		}
	}

	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (window->KeyHold(GLFW_KEY_I)) {
			// TODO(student): Translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_J)) {
			// TODO(student): Translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_K)) {
			// TODO(student): Translate the camera backward
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_L)) {
			// TODO(student): Translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO(student): Translate the camera downward
			camera->TranslateUpward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO(student): Translate the camera upward
			camera->TranslateUpward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_F))
		{
			fov += deltaTime * cameraSpeed;

			if (projectionType)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}
		if (window->KeyHold(GLFW_KEY_G))
		{
			fov -= deltaTime * cameraSpeed;

			if (projectionType)
			{
				projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
			}
		}
	}

	// TODO(student): Change projection parameters. Declare any extra
	// variables you might need in the class header. Inspect this file
	// for any hardcoded projection arguments (can you find any?) and
	// replace them with those extra variables.
}


void Tema2::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	// TODO(student): Switch projections
	if (key == GLFW_KEY_O)
	{
		projectionType = false;
		projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
	}
	if (key == GLFW_KEY_P)
	{
		projectionType = true;
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
	}
}


void Tema2::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO(student): Rotate the camera in first-person mode around
			// OX and OY using `deltaX` and `deltaY`. Use the sensitivity
			// variables for setting up the rotation speed.
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO(student): Rotate the camera in third-person mode around
			// OX and OY using `deltaX` and `deltaY`. Use the sensitivity
			// variables for setting up the rotation speed.
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}
	}
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}