# Reactional Music Plugin for Unreal Engine

Welcome to the Reactional Music Plugin for Unreal Engine! This plugin enables dynamic, real-time music interaction within your Unreal Engine projects, powered by Reactional Music's API. This plugin includes a demo scene to help you explore and test the API’s capabilities through interactive blueprints and a custom editor widget.

## Table of Contents
1. [Features](#features)
2. [Installation](#installation)
3. [Setup](#setup)
4. [Using the Demo Scene](#using-the-demo-scene)
5. [Blueprints and Functionality](#blueprints-and-functionality)
6. [Editor Widget Usage](#editor-widget-usage)
7. [Custom Menu Bar](#custom-menu-bar)

---

## Features

- **Sub System API**: Real-time interaction with themes, tracks via our Engine Subsystem streamlining access and control.
- **Demo Scene**: A pre-built scene demonstrating core plugin functionality and showcasing API integration.
- **Blueprint Examples**: Ready-to-use blueprints that simplify working with the Reactional Music API.
- **BP_BasicPlayback**: A nifty example that demonstrates various ways to load, swap, and transition between tracks seamlessly. Whit lots of options.


---

## Installation

1. Download the plugin and extract it into your Unreal project’s `Plugins` folder.
   - Path: `[YourProjectFolder]/Plugins/ReactionalMusic`
2. Open Unreal Engine, navigate to **Edit > Plugins**, and enable the "Reactional Music" plugin.
3. Restart Unreal Engine to complete the installation.

---

## Setup

1. **Press the Reactional Menu Button** 
   - (Optional): To automatically initialize the editor widget.
   - The Widget lets you test your loaded bundle and see the names of the theme controls.

2. **Demo Scene**:
   - The plugin includes a pre-configured demo scene. You can find this map in the `Maps` folder:
     - Path: `Plugins/ReactionalMusic/Maps/DemoScene.umap`
   - This scene contains assets and blueprints to help you test and explore the plugin’s features.

3. **Basic Playback**:
   - This BP will show you different ways to use the theme and tracks on Play. 


---

## Using the Demo Scene

The demo scene provides a sandbox environment to test the Reactional Music plugin’s capabilities. This scene demonstrates how to use blueprints and the API to interact with themes, tracks, stingers, and other music elements.

1. **Open the Demo Scene**:
   - Navigate to `Plugins/ReactionalMusic/Maps` and open `DemoScene.umap`.
   
2. **Play the Minigame and Interact with the blueprints**:
   - Interact with the provided blueprints to test the API’s functionality.
   - Play the scene to experience reactional functionallity:
   
3. **Widget Interaction**:
   - Access the editor widget to control themes and tracks also in Editor and during runtime.

---

## Blueprints and Functionality

Each blueprint in the demo scene is designed to showcase specific interactions with the Reactional Music API. Below is an overview of the primary blueprints included:

- **BP_Reactional_ChangePartOnTrigger**: Enables part changes in the music when triggered.
- **BP_Reactional_PlayStingerOnPickup**: Plays a stinger sound when the player picks up an object.
- **BP_Reactional_PulseMaterialParamOnBeat**: Syncs a material’s parameter to the beat, creating a pulsing effect.
- **BP_Reactional_PulseTaggedActorsOnBeat**: Pulses actors with a specific tag in rhythm with the beat.
- **BP_Reactional_SequentialVFXOnTrigger**: Triggers sequential visual effects in response to an event.

These blueprints provide a practical foundation for using the Reactional Music API within your project.

---

## Editor Widget Usage

The plugin includes an editor widget that allows you to interact with music themes and tracks:

1. **Menu Button**: A Menu button is added top left in Unreal, giving you quick access to the editor widget.
2. **Widget Controls**: In the widget, you can:
   - Test and preview themes, tracks, and stingers.
   - Control the volumes in real-time.
   - Print theme controls to console.
   - Access various features of the Reactional Music API directly from the editor.

---

## Custom Menu Bar

Under Tools Tab in Unreal you can find the Reactional Menu where you can find quicklinks to: 

- platform
- documentation
- discord
- forum
- website

- Plugin Project Settings
- Reactional Editor Widget
- Download Games

- Readme
- Changelog


For more information, refer to the [Reactional Music API Documentation](https://docs.reactionalmusic.com/Unreal/Unreal%20API/Overview).

If you encounter any issues or need further assistance, please reach out to the support team or check the documentation for troubleshooting tips.

---

Thank you for using the Reactional Music Plugin! We hope it brings your Unreal Engine projects to life with dynamic, interactive music experiences.
