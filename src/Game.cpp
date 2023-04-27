#include "Game.h"

Game::Game(const std::string &name) : name(name){}

int Game::Run() {
    // Initialize glfw
    if (!glfwInit())
        return -1;
    // Create the window
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, name.c_str());

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::LogError("Failed to initialize GLAD");
        return -1;
    }

    window->Init();

    ResourceManager::LoadShader("res/shaders/batch_default.vert", "res/shaders/batch_default.frag", "default");
    ResourceManager::LoadTexture("res/textures/Zach.png", "zach");

    Camera camera = Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
    BatchRenderer renderer(&camera, ResourceManager::GetShader("default"));

    Scene main("main", &camera, &renderer);
    Zach zach(0.0f, 0.0f, 1.0f, 1.0f, 0, 1);
    zach.SetTexture(ResourceManager::GetTexture("zach"));
    main.AddEntity(&zach);

    SceneManager::AddScene(&main);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currFrame = 0.0f;

    float camSpeed = 4.0f;

    // Game loop
    while (window->IsOpen())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glClearColor(0.45f, 0.1f, 0.55f, 1.0f);

        // Calculate delta time
        currFrame = (float)glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;


        if (InputManager::GetKey(GLFW_KEY_D)) {
            camera.transform.Translate(camSpeed * deltaTime, 0.0f);
        }
        else if (InputManager::GetKey(GLFW_KEY_A)) {
            camera.transform.Translate(-camSpeed * deltaTime, 0.0f);
        }
        if (InputManager::GetKey(GLFW_KEY_W)) {
            camera.transform.Translate(0.0f, -camSpeed * deltaTime);
        }
        else if (InputManager::GetKey(GLFW_KEY_S)) {
            camera.transform.Translate(0.0f, camSpeed * deltaTime);
        }

        if (InputManager::GetKey(GLFW_KEY_LEFT_SHIFT)) {
            camera.transform.Scale(camSpeed * deltaTime, camSpeed * deltaTime);
        }
        else if (InputManager::GetKey(GLFW_KEY_SPACE)) {
            camera.transform.Scale(-camSpeed * deltaTime, -camSpeed * deltaTime);
        }

        if (InputManager::GetMouseButton(GLFW_MOUSE_BUTTON_1)) {
            // TODO: stack allocate
            glm::vec2 mousePos = InputManager::GetWorldMousePos(window->GetWidth(), window->GetHeight(), camera.right, camera.transform);
            Zach* z = new Zach(mousePos.x, mousePos.y, 1.0f, 1.0f, 0.0f);
            z->SetTexture(ResourceManager::GetTexture("zach"));
            main.AddEntity(z);
        }

        SceneManager::Update(deltaTime);
#ifdef _DEBUG
        renderer.drawCalls = 0;
#endif // _DEBUG
        SceneManager::Render();
#ifdef _DEBUG
        std::cout << "FPS: " << 1.0f / deltaTime << "\t" << "Draw Calls:" << renderer.drawCalls << '\n';
#endif // _DEBUG

        // Swap front and back buffers 
        window->SwapBuffers();
        // Update current frame inputs
        InputManager::Update();
        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    delete window;
    ResourceManager::FreeAll();
    return 0;
}

int Game::TEST_RUN() {
    // Initialize glfw
    if (!glfwInit())
        return -1;
    // Create the window
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, name.c_str());

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::LogError("Failed to initialize GLAD");
        return -1;
    }

    window->Init();

    ResourceManager::LoadShader("res/shaders/batch_default.vert", "res/shaders/batch_default.frag", "batch_default");
    ResourceManager::LoadTexture("res/textures/kirby.png", "kirby");
    ResourceManager::LoadTexture("res/textures/Guy.png", "guy");

    Camera camera =  Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

    BatchRenderer renderer(&camera, ResourceManager::GetShader("batch_default"));
    Texture* k = ResourceManager::GetTexture("kirby");
    
    Scene scene("main", &camera, &renderer);
    SceneManager::AddScene(&scene);


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float currFrame = 0.0f;

    float kirbySpeed = 8.0f;

    // Game loop
    while (window->IsOpen())
    {
        // Clear screen and set background color (Maybe move to window class)
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.45f, 0.1f, 0.55f, 1.0f);

        // Calculate delta time
        currFrame = (float)glfwGetTime();
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;
        std::cout << 60.0f / deltaTime << "\n";
#ifdef _DEBUG
        renderer.drawCalls = 0;
#endif // _DEBUG


        renderer.Start();
        Transform t(0.0f, 0.0f, 0.25f, 0.25f, 0.0f);
        for (int y = 0; y < 200; y++) {
            t.SetPosition(0.0f, t.GetPosition().y);
            for (int x = 0; x < 200; x++) {
                renderer.DrawQuad(k, t.GetModelMatrix());
                t.Translate(0.25, 0.0f);
            }
            t.Translate(0.0f, 0.25f);
        }

        renderer.End();
#ifdef _DEBUG
        std::cout << renderer.drawCalls << '\n';
#endif // _DEBUG

        if (InputManager::GetKey(GLFW_KEY_D)) {
            camera.transform.Translate(2 * kirbySpeed * deltaTime, 0.0f);
        }
        else if (InputManager::GetKey(GLFW_KEY_A)) {
            camera.transform.Translate(-2 * kirbySpeed * deltaTime, 0.0f);
        }

        if (InputManager::GetKey(GLFW_KEY_E)) {
            camera.transform.Translate(0.0f, 2 * kirbySpeed * deltaTime);
        }
        else if (InputManager::GetKey(GLFW_KEY_Q)) {
            camera.transform.Translate(0.0f, -2 * kirbySpeed * deltaTime);
        }

        if (InputManager::GetKeyDown(GLFW_KEY_S)) {
            camera.transform.ScaleFactor(2.0f, 2.0f);
        }
        else if (InputManager::GetKeyDown(GLFW_KEY_W)) {
            camera.transform.ScaleFactor(0.5f, 0.5f);
        }

        // Swap front and back buffers 
        window->SwapBuffers();
        // Update current frame inputs
        InputManager::Update();
        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    delete window;
    ResourceManager::FreeAll();
    return 0;
}