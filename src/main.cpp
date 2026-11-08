#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Include your animation headers here
#include "hitori_explode.h"
#include "miku_oeo.h"
#include "miku_pointing.h"
#include "true_huss_cat.h"
#include "zero_brain_cells.h"
#include "bongo_cat.h"
#include "cortisol_decrese.h"
#include "yippie.h"
#include "rish_mimu.h"
//#include "bad_apple.h" // Eats too much Flash memory


// Structure for animations
struct Animation {
    const unsigned char* const* frames;
    int frameCount;
    int framesDelay;
};

// Here you must register all animations into an array
// For reference template for your animation file, see "include/bongo_cat.h"
const Animation allAnimations[] = {
    { hitori_explode::frames, hitori_explode::count, hitori_explode::framesDelay },
    { miku_oeo::frames, miku_oeo::count, miku_oeo::framesDelay },
    { miku_pointing::frames, miku_pointing::count, miku_pointing::framesDelay },
    { true_huss_cat::frames, true_huss_cat::count, true_huss_cat::framesDelay },
    { zero_brain_cells::frames, zero_brain_cells::count, zero_brain_cells::framesDelay },
    { bongo_cat::frames, bongo_cat::count, bongo_cat::framesDelay },
    { cortisol_decrese::frames, cortisol_decrese::count, cortisol_decrese::framesDelay},
    { yippie::frames, yippie::count, yippie::framesDelay},
    //{ bad_apple::frames, bad_apple::count, bad_apple::framesDelay},
    { rish_mimu::frames, rish_mimu::count, rish_mimu::framesDelay }
};

const int GIF_COUNT = sizeof(allAnimations) / sizeof(allAnimations[0]);

// Display & Hardware Setup
Adafruit_SH1106G display(128, 64, &Wire, -1);

const int I2C_SDA = 5; // Yellow wire
const int I2C_SCL = 6; // Blue wire
const int buttonPin = 9; // Green wire
const uint8_t debounceDelay = 250; // Debounce delay in milliseconds, can be tweaked based on button behavior

// State Variables
int currentGifIndex = 0;
int currentFrameIndex = 0;
unsigned long lastFrameTime = 0;
unsigned long lastTimePressed = 0;


// Function prototypes
void startGif(int g);
void updateGif();
void changeGif(int newGifIndex);

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("--- BOOT / RESET ---\n");
    pinMode(buttonPin, INPUT_PULLUP);

    // Initialize I2C communication with custom pins
    Wire.begin(I2C_SDA, I2C_SCL);

    // Initialize the SH1106 display (often 0x3C address)
    if (!display.begin(0x3C, true)) { 
        Serial.println(F("SH1106 allocation failed. Check wiring!"));
        for (;;); // Stop execution if initialization fails
    }

    display.clearDisplay();
    display.display();
    
    startGif(0); // Start with the first GIF, you can change to different gif if using the index of the GIF you want to start with
    lastTimePressed = millis(); 
}

void loop() {
    int currentState = digitalRead(buttonPin);
    
    // Check for button press with debounce
    if (currentState == LOW && (millis() - lastTimePressed >= debounceDelay)) {
        currentGifIndex = (currentGifIndex + 1) % GIF_COUNT; // Cycle through GIFs safely
        changeGif(currentGifIndex); 
        
        Serial.print("Current GIF Index: ");
        Serial.println(currentGifIndex);
        lastTimePressed = millis(); 
    }

    // Continuously update/render the current animation frame non-blockingly
    updateGif();
}

void startGif(int g) {
    currentGifIndex = g;
    currentFrameIndex = 0;
    lastFrameTime = millis();
}

void updateGif() {
    // Grab the active animation struct
    Animation activeAnim = allAnimations[currentGifIndex];

    // Non-blocking frame timing using millis()
    if (millis() - lastFrameTime >= activeAnim.framesDelay) {
        lastFrameTime = millis();
        
        // Fetch the specific frame pointer out of PROGMEM
        const unsigned char* frameToDraw = (const unsigned char*)pgm_read_ptr(&(activeAnim.frames[currentFrameIndex]));

        // Render to OLED
        display.clearDisplay();
        display.drawBitmap(0, 0, frameToDraw, 128, 64, SH110X_WHITE);
        display.display();

        // Advance to next frame, loop back to 0 at the end of the animation
        currentFrameIndex = (currentFrameIndex + 1) % activeAnim.frameCount;
    }
}

void changeGif(int newGifIndex) {
    if (newGifIndex >= GIF_COUNT) return; // Bounds safety check

    currentGifIndex = newGifIndex;
    currentFrameIndex = 0; // Reset frame back to 0 when switching animations
    lastFrameTime = millis();
}