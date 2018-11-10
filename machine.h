#pragma once

class App;

class Machine
{
  public:
    enum class AppId { HOME, DIALOGUE_BOX, TODO_LIST };

    Machine();
    ~Machine();

    void tick();
    void SetApp(AppId app);
    bool GetRunning() const { return running; }
    void SetRunning(bool running) { this->running = running; }

protected:
    bool running;
    App * app;
};
