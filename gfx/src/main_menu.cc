#include <main_menu.h>
#include <functional>

GLdouble eyeX = 0, eyeY = 0, eyeZ = 0;
GLdouble centerX = 0, centerY = 0, centerZ = 0;
GLdouble upX = 0, upY = 0, upZ = 0;


MainMenu::MainMenu()
{

}

MainMenu::MainMenu(Config* config, WindowContent* windowContent)
{
    this->config = config;
    this->windowContent = windowContent;
    buttonVector = new vector<Button*>();
    floatingWindowMap = new map<string,FloatingWindow*>();

    /*
     * Creating "START GAME BUTTON"
     */
    Button* startGameButton =  new Button("Start Game",0.1f*config->screenWidth,0.5f* config->screenHeight,0.15f*config->screenHeight,0.05f*config->screenHeight,this->config, this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)> startGame = [](Config* config, WindowContent* windowContent){windowContent->gActive = windowContent->gGame;};
    startGameButton->setButtonClick(startGame);
    buttonVector->push_back(startGameButton);

    /*
     * Function adding "createServerButton, createServerFloatingWindow etc..
     */
    createServerGUI();

    /*
     * Function adding "findServerButton, findServerFloatingWindow etc..
     */

    findServerGUI();
    /*
     * Creating "EXIT BUTTON"
     */

    setttingsGUI();

    Button* exitButton =  new Button("Exit",0.1f*config->screenWidth,0.9f* config->screenHeight,0.15f*config->screenHeight,0.05f*config->screenHeight,this->config,this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)> closeWindow = [](Config* config, WindowContent* windowContent){config->running=false;};
    exitButton->setButtonClick(closeWindow);
    buttonVector->push_back(exitButton);

}

MainMenu::~MainMenu()
{
    delete config;
}

/**
 * Handles rendering of the main menu.
 */
int MainMenu::render()
{   /*
     * drawing content
     */

    for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
    {
        (*it)->draw();
    }
    if(0!=(windowContent->floatingWindowName.compare("")))
    {
        std::map<string, FloatingWindow *>::iterator it;
        it = floatingWindowMap->find(windowContent->floatingWindowName);
        if(it == floatingWindowMap->end()){
            printf("it == null\n");
        }
        else {
            it->second->draw();
        }
    }

    return SUCCESS;
}

/**
 * Handles all inputs (keyboard, mouse etc.) of the main menu.
 */
int MainMenu::handleInput(Config* config, vector<Drawable*> states)
{
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT)
        {
            config->running = false;
        }
        //Handle button events
        for(vector<Button*>::iterator it = buttonVector->begin(); it != buttonVector->end();it++)
        {
            (*it)->handle_events(&e);
        }
        if(0 != (windowContent->floatingWindowName.compare("")))
        {
            std::map<string, FloatingWindow *>::iterator it;
            it = floatingWindowMap->find(windowContent->floatingWindowName);
            if(it == floatingWindowMap->end()){
                printf("it == null\n");
            }
            else {
                it->second->handle_events(&e);
            }
        }
    }
    return SUCCESS;
}


void MainMenu::createServerGUI() {
    FloatingWindow* createServerFloatingWindow = new FloatingWindow(800,500,this->config);

    //TextBox with window name in a top bar
    TextBox* windowNameTextBox = new TextBox(50,-20,0.07f*config->screenHeight,0.08f*config->screenHeight,this->config,this->windowContent);
    windowNameTextBox->isEditingEnabled = false;
    windowNameTextBox->text = "Create server";
    windowNameTextBox->opacity = 0.0f;

    //button closing window
    Button* closeCreateServerButton =  new Button("x",760,5,0.02f*config->screenHeight,0.02f*config->screenHeight,this->config,this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)>
            closeSettings = [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="";};
    closeCreateServerButton->setButtonClick(closeSettings);
    closeCreateServerButton->setButtonColorNormal(1.0,0.0,0.0);
    closeCreateServerButton->setButtonColorHoover(1.0,0.2,0.0);
    closeCreateServerButton->setButtonColorPressed(1.0,0.0,0.2);

    //label for port input
    TextBox* portLabelTextBox = new TextBox(200,100,0.07f*config->screenHeight,0.08f*config->screenHeight,this->config,this->windowContent);
    portLabelTextBox->isEditingEnabled = false;
    portLabelTextBox->text = "Port:";
    portLabelTextBox->opacity = 0.0f;

    //port input
    TextBox* portInputTextBox = new TextBox(350,100,200,70,this->config,this->windowContent);
    portInputTextBox->text = "8080";

    //label localhost/internet
    TextBox* domainTextBox = new TextBox(200,200,0.07f*config->screenHeight,0.08f*config->screenHeight,this->config,this->windowContent);
    domainTextBox->isEditingEnabled = false;
    domainTextBox->text = "Domain (localhost/internet)";
    domainTextBox->opacity = 0.0f;

    //input localhost/internet
    TextBox* domainInputTextBox = new TextBox(350,200,200,70,this->config,this->windowContent);
    domainInputTextBox->text = "localhost";

    //button starting server and game
    Button* startServerButton =  new Button("Start server",250,300,150,75,this->config,this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)>
            startServer = [](Config* config, WindowContent* windowContent){};
    startServerButton->setButtonClick(startServer);
    startServerButton->setButtonColorNormal(1.0,0.0,0.0);
    startServerButton->setButtonColorHoover(1.0,0.2,0.0);
    startServerButton->setButtonColorPressed(1.0,0.0,0.2);


    createServerFloatingWindow->addChild(closeCreateServerButton);
    createServerFloatingWindow->addChild(windowNameTextBox);
    createServerFloatingWindow->addChild(portLabelTextBox);
    createServerFloatingWindow->addChild(portInputTextBox);
    createServerFloatingWindow->addChild(domainTextBox);
    createServerFloatingWindow->addChild(domainInputTextBox);
    createServerFloatingWindow->addChild(startServerButton);

    floatingWindowMap->insert(pair<string,FloatingWindow*>("createServerFloatingWindow",createServerFloatingWindow));

    /*
     * Creating button opening "SETTINGS FLOATING WINDOW"
     */
    Button* createServerButton =  new Button("Create server",0.1f*config->screenWidth,0.6f* config->screenHeight,0.15f*config->screenHeight,0.05f*config->screenHeight,this->config, this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)> openCreateServerFloatingWindow =
            [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="createServerFloatingWindow";};
    createServerButton->setButtonClick(openCreateServerFloatingWindow);
    buttonVector->push_back(createServerButton);
}

void MainMenu::findServerGUI() {
    /*
     * Creating "SETTINGS WINDOW"
     */
    FloatingWindow* findServerFloatingWindow = new FloatingWindow(800,500,this->config);

    TextBox* testTextBox = new TextBox(400,200,0.07f*config->screenHeight,0.08f*config->screenHeight,this->config,this->windowContent);

    Button* closeFindServerButton =  new Button("x",760,5,0.02f*config->screenHeight,0.02f*config->screenHeight,this->config,this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)>
            closeFindServer = [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="";};
    closeFindServerButton->setButtonClick(closeFindServer);
    closeFindServerButton->setButtonColorNormal(1.0,0.0,0.0);
    closeFindServerButton->setButtonColorHoover(1.0,0.2,0.0);
    closeFindServerButton->setButtonColorPressed(1.0,0.0,0.2);
    findServerFloatingWindow->addChild(closeFindServerButton);

    findServerFloatingWindow->addChild(testTextBox);

    floatingWindowMap->insert(pair<string,FloatingWindow*>("findServerFloatingWindow",findServerFloatingWindow));

    /*
     * Creating button opening "SETTINGS FLOATING WINDOW"
     */
    Button* findServerButton =  new Button("Find server",0.1f*config->screenWidth,0.7f* config->screenHeight,0.15f*config->screenHeight,0.05f*config->screenHeight,this->config, this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)> openFindServerFloatingWindow =
            [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="findServerFloatingWindow";};
    findServerButton->setButtonClick(openFindServerFloatingWindow);
    buttonVector->push_back(findServerButton);
}

void MainMenu::setttingsGUI() {
    /*
    * Creating "SETTINGS WINDOW"
    */
    FloatingWindow* settingsFloatingWindow = new FloatingWindow(800,500,this->config);

    TextBox* testTextBox = new TextBox(400,200,0.07f*config->screenHeight,0.08f*config->screenHeight,this->config,this->windowContent);

    Button* closeSettingsButton =  new Button("x",760,5,0.02f*config->screenHeight,0.02f*config->screenHeight,this->config,this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)>
            closeSettings = [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="";};
    closeSettingsButton->setButtonClick(closeSettings);
    closeSettingsButton->setButtonColorNormal(1.0,0.0,0.0);
    closeSettingsButton->setButtonColorHoover(1.0,0.2,0.0);
    closeSettingsButton->setButtonColorPressed(1.0,0.0,0.2);
    settingsFloatingWindow->addChild(closeSettingsButton);

    settingsFloatingWindow->addChild(testTextBox);

    floatingWindowMap->insert(pair<string,FloatingWindow*>("settingsFloatingWindow",settingsFloatingWindow));

    /*
     * Creating button opening "SETTINGS FLOATING WINDOW"
     */
    Button* settingsButton =  new Button("Settings",0.1f*config->screenWidth,0.8f* config->screenHeight,0.15f*config->screenHeight,0.05f*config->screenHeight,this->config, this->windowContent);
    std::function<void(Config* config, WindowContent* windowContent)> openSettingsFloatingWindow =
            [](Config* config, WindowContent* windowContent){windowContent->floatingWindowName="settingsFloatingWindow";};
    settingsButton->setButtonClick(openSettingsFloatingWindow);
    buttonVector->push_back(settingsButton);

}
