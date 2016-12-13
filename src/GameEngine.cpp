#include "GameEngine.h"
bool debug_mode;
int g_gl_width;
int g_gl_height;
GLFWwindow* g_window = NULL;
GLuint shader_programme;

GameEngine::GameEngine(){
	screenSize=glm::vec2(800,600);
	g_gl_width=screenSize.x;
	g_gl_height=screenSize.y;
	debug_mode=true;
	tools::debug("GameEngine created",tools::DBG_INFO);
	keyTools::init_keys();
	//printf("Key:%i\n",key_status.count;
}

void GameEngine::setWindowSize(int w,int h){
	this->screenSize=glm::vec2(w,h);
	g_gl_width=screenSize.x;
	g_gl_height=screenSize.y;
	tools::debug("New window size: "+std::to_string(w)+"x"+std::to_string(h),tools::DBG_INFO);
}

void GameEngine::initGl(){
	restart_gl_log ();
	start_gl ();
	glEnable (GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // set counter-clock-wise vertex order to mean the front
	glClearColor (0.2, 0.2, 0.2, 1.0); // grey background to help spot mistakes
	glViewport (0, 0, g_gl_width, g_gl_height);
	shader_programme = create_programme_from_files (VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
	cam=new Camera(&shader_programme,screenSize);
}

void GameEngine::run(){
	tools::debug("Engine is running",tools::DBG_INFO);
	paused=false;
	test=new Vehicle("mesh/sedan.obj",&shader_programme);
	addObj(test);
	addObj(new Object3D("mesh/car/car.obj",&shader_programme));
	test->setPos(-3.0f,0.0f,3.0f);
	cam->target=test;
	test->set_scale(0.25f,0.25f,0.25f);

	while(!glfwWindowShouldClose (g_window)){//bucle principal del motor de juegos
		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
		_update_fps_counter (g_window);

		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport (0, 0, g_gl_width, g_gl_height);
		glUseProgram (shader_programme);
		glfwPollEvents ();


		//si algun escenario ha sido cargado
		readGlobalKeys();//leer teclas "globales"
		if(scenario_loaded){
			if(!paused){
				readInGameKeys();//leer teclas de interaccion dentro del juego
			}
			for(int i=0;i<objects.size();i++){
				if(objects[i]->enabled){
					if(!paused){//si el juego está pausado...
						objects[i]->update();//actualizar el objeto (posicion,rotacion,etc)
							//printf("rotacion y:%f\n",test->rotation.y);
					}
					objects[i]->render();//renderizar cada objeto en la lista
				}
			}
		}
		cam->update();
		glfwSwapBuffers (g_window);
	}
	glfwTerminate();

	tools::debug("Engine is stopped",tools::DBG_INFO);
}

void GameEngine::loadScenario(std::string scenario_name){
	scenario_loaded=true;
}

void GameEngine::readInGameKeys(){

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_W)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.025,0.0f,0.0f);
		cam->zoom(-0.125f);
	}
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_S)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		cam->zoom(+0.125f);
		//test->move(-0.025,0.0f,0.0f);
	}
	
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_A)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.0f,0.0f,0.025);
		cam->rotate_around(0.125f);
	}

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_D)) {
		//tools::debug("UP",tools::DBG_KEY_PRESSED);
		//test->move(0.0f,0.0f,-0.025);
		cam->rotate_around(-0.125f);
	}

	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_UP)) {
		tools::debug("UP",tools::DBG_KEY_PRESSED);
		keyTools::press(K_UP_ARROW);
		test->move_forward();
	}
	else if ((keyTools::get_status(K_UP_ARROW)==1||keyTools::get_status(K_DOWN_ARROW)==1) && 
		(GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_UP)) || GLFW_RELEASE == glfwGetKey (g_window, GLFW_KEY_DOWN)) {
		//keyTools::release(K_UP_ARROW);
		//keyTools::press(K_UP_ARROW);
		test->decelerate();
	}

	if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_DOWN)){
		tools::debug("DOWN",tools::DBG_KEY_PRESSED);
		test->move_backward();
	}
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_LEFT)) {
		tools::debug("LEFT",tools::DBG_KEY_PRESSED);
		test->rotate(0.0f,-0.125f,0.0f);
	}
	if(GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_RIGHT)){
		tools::debug("RIGHT",tools::DBG_KEY_PRESSED);
		test->rotate(0.0f,+0.125f,0.0f);
	}
}

void GameEngine::readGlobalKeys(){
	//salir con ESC
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose (g_window, 1);
		tools::debug("ESC",tools::DBG_KEY_PRESSED);
		tools::debug("ESC pressed... quitting.",tools::DBG_INFO);
	}
	//limpiar pantalla
	if (GLFW_PRESS == glfwGetKey (g_window, GLFW_KEY_C)) {
		if (system("CLS")) system("clear");
	}
}

void GameEngine::addObj(Object3D *obj){
	objects.push_back(obj);
}