#include "menu.h"

using json = nlohmann::json;

MenuWindow::MenuWindow(json data){
    int states[15] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    light1 = new SensorWindow(data["outputs"][0], std::pair<int,int>(0, 0));
    light2 = new SensorWindow(data["outputs"][1], std::pair<int,int>(0, 51));
    air = new SensorWindow(data["outputs"][2], std::pair<int,int>(3, 0));
    projector = new SensorWindow(data["outputs"][3], std::pair<int,int>(3, 51));
    alarmBuzz = new SensorWindow(data["outputs"][4], std::pair<int,int>(6, 0));
    sPresence = new SensorWindow(data["inputs"][0], std::pair<int,int>(6, 51));
    sSmoke = new SensorWindow(data["inputs"][1], std::pair<int,int>(9, 0));
    sWindow = new SensorWindow(data["inputs"][2], std::pair<int,int>(9, 51));
    sDoor = new SensorWindow(data["inputs"][3], std::pair<int,int>(12, 0));
    sCountIn = new SensorWindow(data["inputs"][4], std::pair<int,int>(12, 51));
    sCountOut = new SensorWindow(data["inputs"][5], std::pair<int,int>(15, 0));
    sTempHumid = new SensorWindow(data["sensor_temperatura"][0], std::pair<int,int>(15, 51));
}
void MenuWindow::refreshAll(uint8_t* states){
    light1->refreshIt(states[1]);
    light2->refreshIt(states[2]);
    air->refreshIt(states[3]);
    projector->refreshIt(states[4]);
    alarmBuzz->refreshIt(states[5]);
    sPresence->refreshIt(states[6]);
    sSmoke->refreshIt(states[7]);
    sWindow->refreshIt(states[8]);
    sDoor->refreshIt(states[9]);
    sCountIn->refreshIt(states[10]);
    sCountOut->refreshIt(states[11]);
    sTempHumid->refreshIt(states[12]);
}

SensorWindow::SensorWindow(json sensor, std::pair<int,int> pyx){
    SensorWindow::type = sensor["type"];
    SensorWindow::tag = sensor["tag"];
    SensorWindow::gpioPin = sensor["gpio"];
    SensorWindow::state = OFFLINEVALUE;
    SensorWindow::yx = pyx;
    SensorWindow::win = newwin(3, 50, yx.first, yx.second);
    refresh();
    box(win, 0, 0);
    mvwprintw(win, 1, 1, "%s: ", tag.data());
    wrefresh(win);
}

void SensorWindow::refreshIt(int state){
    SensorWindow::state = state;
    box(win, 0, 0);
    mvwprintw(win, 1, tag.size()+3, "%s", (state? "Y" : "N"));
    wrefresh(win);
}

void* menu(void *arg){
    initscr();

    std::ifstream f("configuracao_sala_01.json");
    json data = json::parse(f);
    char c = 0;
    uint8_t* response = (uint8_t*)arg;
    MenuWindow main_menu(data);
    int posit = 0;
    move(21, 0);

    while(1){
        if(!response[13]){
            main_menu.refreshAll(response);
            move(21, posit);
            response[13] = 0;
        } 
        posit++;
        refresh();
        sleep(1);
    }    
    endwin();
    return NULL;
}