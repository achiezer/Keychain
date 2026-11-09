# 🗝️ Custom GIF Keychain DIY Guide :3

Hi there! :3 

Welcome to the quick and cozy guide on how to build your very own custom animated keychain! 

I'm not a pro, so there might be some quirks along the way, but we will get through it together! :3

---

## 🌟 The Goal

The main goal of this project is to create a keychain that is super easy to work with and actually fun! 
I didn't want any lifeless pet tamagotchis—instead, the goal here is to **display cool GIFs or short videos**. 
*(Plus, with this keychain, I can finally larp wherever I walk! :3)*

---

## 🛒 Parts List

Here are the links for the parts you will need to bring this project to life: :3

* **Microcontroller:** [Esp32-C3 Super Mini](https://temu.to/k/ev8ewytznby)
* **Display:** [OLED SH1106 1.3"](https://temu.to/k/e8p68iafpdf)
* **Battery:** [Li-po 500mAh](https://temu.to/k/e8x9cyn16xk)
* **Power Supply:** [Powerbank module](https://temu.to/k/ekvgoltje3e)
* **Green Breadboard:** [4x6cm double-sided PCB](https://temu.to/k/ee8hrhw244g)
* **Button:** [Limit micro switch](https://temu.to/k/eapxk6e88j6)
* **Power Button:** [On-Off switch](https://temu.to/k/ee3xnovdfdh)
* **Wire:** [Nice wiring spool](https://temu.to/k/emenl2a31g5)

---

## ⚡ How to Wire It

In my project, I wired everything like this: :3

<img width="1200" height="882" alt="Keychain schematic" src="https://github.com/user-attachments/assets/d249820b-096f-47e8-999e-a87b0344ce0b" />

> **Note:** Sorry! All my budget went into larp gear, so I had to make the schematic in MS Paint. Take it or leave it! :3

---

## 💻 How to Program It

1. Make sure you have **VSCode** and the **PlatformIO** extension installed.
2. Download the `.zip` of this project or copy the repository link.
3. Open the project folder in VSCode.
4. Go to PlatformIO and press **"Build"**. :3
5. Connect your ESP32-C3 board to your PC via USB and press **"Upload"**.

<img width="397" height="547" alt="PlatformIO Upload" src="https://github.com/user-attachments/assets/7a4a3cd7-f674-4bcf-bc35-225cf6bfd91b" />

---

## 🎨 How to Add Your Own Animations

Head over to the awesome [OLED Animation Maker website](https://www.oledanimationmaker.com/)! :3

1. Go to the **Import page**.
2. Upload your animation.
3. Change the library dropdown to **"Adafruit SH110X"**.
4. Press **"Get code"**.

<img width="1533" height="757" alt="OLED Animation Maker" src="https://github.com/user-attachments/assets/641b00c5-d382-4bf6-8346-24408b51fc76" />

5. A new window will pop up. Press **".h"** to download the file.

<img width="902" height="110" alt="Download .h file" src="https://github.com/user-attachments/assets/2f31bf67-1092-48b2-a8ab-ccb962d74b16" />

6. Rename the file whatever you like and move it into the project's **`include`** folder! :3

<img width="345" height="392" alt="image" src="https://github.com/user-attachments/assets/3cbea485-5638-4221-bb96-aa20bb5ccafb" />

---

### 📝 Code Formatting Example

You will need to reformat your new `.h` file so it looks similar to the `bongo_cat.h` file included in the repo. 

Here is a short breakdown of how the code should look: :3

```cpp
#pragma once
#if defined(__AVR__)
  #include <avr/pgmspace.h>
#elif defined(ESP8266) || defined(ESP32)
  #include <pgmspace.h>
#endif
#include <cstdint>

// Here you must declare your animation namespace. It must match the name of your animation file. 
// For example, if your file is called "bongo_cat.h", your namespace must be "bongo_cat".
namespace bongo_cat {
  
  const int PROGMEM count = 5;         // Total number of frames in your animation
  const int PROGMEM framesDelay = 100; // Delay between frames. Change this to set desired FPS 
                                       // (100ms = 10FPS, 50ms = 20FPS, 33ms = 30FPS, etc.)

  // Your animation frames go here. You can add more frames by copying the frame structure 
  // and naming them frame2, frame3, etc. Make sure to update the count variable accordingly! :3
  
  const uint8_t PROGMEM frame0[] = {
    0x00, 0x00, 0x00, 0x00, 0xff, 0x00, /* ... frame data bytes ... */
  };

  const uint8_t PROGMEM frame1[] = {
    0x00, 0x00, 0x00, 0x00, 0xff, 0x00, /* ... frame data bytes ... */
  };

  // After inserting the frames, add them to the frames array below. 
  // The order here is the order they will play in the animation! :3
  const uint8_t* const frames[] PROGMEM = {
    frame0, frame1
  };
}
```
Reminder: Make sure you set up the const int PROGMEM count, const int PROGMEM framesDelay, and const uint8_t* const frames[] PROGMEM variables correctly for your animation! :3

Finally, initialize your animation in src/main.cpp by including your header file and adding it to the active array!

---

## 🎉 Wrapping Up
After all that hard work, you can finally build it, upload it, and enjoy your brand new keychain! :3

Have fun crafting, and happy larping! ✨

---

## 📬 Contact & Help
P.S. I'm not a professional programmer or mentor, so this guide might be a bit tricky for absolute beginners in some places. If you run into any trouble, feel free to reach out to me on Instagram: @achi.ezer! :3
