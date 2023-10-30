#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <random>
#include <ctime>

// Dichiarazioni delle costanti
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 20;

// Dichiarazioni delle variabili globali
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Rect fruitRect;
SDL_Texture* gSnakeTexture = nullptr;

// Dichiarazioni delle strutture dati
struct Point {
    int x;
    int y;
};

struct Fruit {
    SDL_Texture* texture;
    int points;
};

std::vector<Point> snake;
Fruit fruit1, fruit2;
Point food;
bool gameOver = false;
bool isPaused = false; // Aggiunta la variabile per la pausa
int score = 0;

// Funzione per caricare le immagini PNG
SDL_Texture* LoadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Errore durante il caricamento dell'immagine: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

// Funzione per inizializzare il gioco
bool Initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Impossibile inizializzare SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    gWindow = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        std::cerr << "Impossibile creare la finestra: " << SDL_GetError() << std::endl;
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        std::cerr << "Impossibile creare il renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    gSnakeTexture = LoadTexture("snake.png");
    if (!gSnakeTexture) {
        return false;
    }

    fruit1 = LoadFruit("fruit1.png", 10);
    fruit2 = LoadFruit("fruit2.png", 5);

    return true;
}

// Funzione per pulire e chiudere il gioco
void Close() {
    SDL_DestroyTexture(gSnakeTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

// Funzione per caricare i frutti
Fruit LoadFruit(const std::string& path, int points) {
    Fruit fruit;
    fruit.texture = LoadTexture(path);
    fruit.points = points;
    return fruit;
}

// Funzione per generare una nuova posizione casuale per il cibo
void SpawnFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> xDist(0, (SCREEN_WIDTH / GRID_SIZE) - 1);
    std::uniform_int_distribution<int> yDist(0, (SCREEN_HEIGHT / GRID_SIZE) - 1);

    int x, y;
    do {
        x = xDist(gen) * GRID_SIZE;
        y = yDist(gen) * GRID_SIZE;
    } while (std::find(snake.begin(), snake.end(), Point{x, y}) != snake.end());

    int randomFruitType = std::rand() % 2;
    food = { x, y, randomFruitType };
}

// Funzione per gestire gli input
void HandleInput(SDL_Event& e) {
    if (e.type == SDL_QUIT) {
        gameOver = true;
    }
    else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                // Codice per muovere il serpente verso l'alto
                break;
            case SDLK_DOWN:
                // Codice per muovere il serpente verso il basso
                break;
            case SDLK_LEFT:
                // Codice per muovere il serpente a sinistra
                break;
            case SDLK_RIGHT:
                // Codice per muovere il serpente a destra
                break;
            case SDLK_p: // Aggiunto il tasto "P" per mettere in pausa
                isPaused = !isPaused;
                break;
        }
    }
}

// Funzione per muovere il serpente
void MoveSnake() {
    if (isPaused) { // Se il gioco è in pausa, non muovere il serpente
        return;
    }
    // Codice per muovere il serpente
}

// Funzione per controllare le collisioni
void CheckCollisions() {
    if (isPaused) { // Se il gioco è in pausa, non controllare le collisioni
        return;
    }
    // Codice per controllare le collisioni del serpente con il cibo e i bordi
}

// Funzione per disegnare il gioco
void Render() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    // Disegna il serpente
    for (const Point& p : snake) {
        snakeRect.x = p.x;
        snakeRect.y = p.y;
        SDL_RenderCopy(gRenderer, gSnakeTexture, nullptr, &snakeRect);
    }

    // Disegna il cibo
    fruitRect.x = food.x;
    fruitRect.y = food.y;
    SDL_RenderCopy(gRenderer, fruits[food.type].texture, nullptr, &fruitRect);

    if (isPaused) { // Se il gioco è in pausa, mostra un messaggio di pausa
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 128);
        SDL_Rect pauseRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, 50 };
        SDL_RenderFillRect(gRenderer, &pauseRect);
    }

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* argv[]) {
    if (!Initialize()) {
        std::cerr << "Inizializzazione fallita." << std::endl;
        return 1;
    }

    // Inizializza il gioco
    snake.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    SpawnFood();

    // Ciclo principale del gioco
    SDL_Event e;
    while (!gameOver) {
        while (SDL_PollEvent(&e) != 0) {
            HandleInput(e);
        }

        MoveSnake();
        CheckCollisions();
        Render
