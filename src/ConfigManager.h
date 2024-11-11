#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>

class ConfigManager {
public:
    ConfigManager(const char *filename);
    bool initConfig();
    // Overloaded setConfigValue functions for different types
    double setConfigValue(const char *key, double defaultValue);
    int setConfigValue(const char *key, int defaultValue);
    bool setConfigValue(const char *key, bool defaultValue);
    String setConfigValue(const char *key, const String &defaultValue);
    const char *setConfigValue(const char *key, const char *defaultValue);

    // Function to update config values based on user input and return the updated value
    double updateConfigValue(const char *key, double newValue);
    int updateConfigValue(const char *key, int newValue);
    bool updateConfigValue(const char *key, bool newValue);
    String updateConfigValue(const char *key, const String &newValue);
    const char* updateConfigValue(const char *key, const char *newValue);


    // Function to print the configuration for debugging
    void printConfig();

private:
    const char *filename;
    JsonDocument doc;  // Dynamic JSON document with initial capacity, adjust as needed
    bool saveConfig();

};

// Constructor
ConfigManager::ConfigManager(const char *filename)
    : filename(filename) {}

bool ConfigManager::initConfig() {
    // Initialize LittleFS
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS, trying to format...");
        if (LittleFS.format()) {
            Serial.println("LittleFS formatted successfully!");
            if (!LittleFS.begin()) {
                Serial.println("Failed to mount LittleFS after formatting.");
                return false;
            }
        } else {
            Serial.println("Formatting failed...");
            return false;
        }
    }

    // Check if the configuration file exists
    if (!LittleFS.exists(filename)) {
        Serial.println("Config file not found. Creating an empty file.");
        
        // Create an empty config file
        File file = LittleFS.open(filename, "w");
        if (!file) {
            Serial.println("Failed to create config file");
            return false;
        }
        file.close();  // Close the file immediately after creating it
        Serial.println("Config file created successfully.");
    }

    // Load the configuration from the file
    File file = LittleFS.open(filename, "r");
    if (!file) {
        Serial.println("Failed to open config file for reading");
        return false;
    }

    // Check if the file is empty
    if (file.size() == 0) {
        Serial.println("Config file is empty. No data to load.");
        file.close();  // Close the file if it's empty
        return true;   // Allow the rest of the code to initialize defaults later
    }

    // Deserialize JSON data from the file
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse config file: ");
        Serial.println(error.c_str());
        return false;
    }

    return true;
}



















// Save configuration to file
bool ConfigManager::saveConfig() {
    File file = LittleFS.open(filename, "w");
    if (!file) {
        Serial.println("Failed to open config file for writing");
        return false;
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to config file");
        file.close();
        return false;
    }

    file.close();
    return true;
}

// SetConfigValue for double
double ConfigManager::setConfigValue(const char *key, double defaultValue) {
    if (!doc.containsKey(key)) {
        doc[key] = defaultValue;
        saveConfig();
        return defaultValue;
    }
    return doc[key].as<double>();
}

// SetConfigValue for int
int ConfigManager::setConfigValue(const char *key, int defaultValue) {
    if (!doc.containsKey(key)) {
        doc[key] = defaultValue;
        saveConfig();
        return defaultValue;
    }
    return doc[key].as<int>();
}

// SetConfigValue for bool
bool ConfigManager::setConfigValue(const char *key, bool defaultValue) {
    if (!doc.containsKey(key)) {
        doc[key] = defaultValue;
        saveConfig();
        return defaultValue;
    }
    return doc[key].as<bool>();
}

// SetConfigValue for String
String ConfigManager::setConfigValue(const char *key, const String &defaultValue) {
    if (!doc.containsKey(key)) {
        doc[key] = defaultValue;
        saveConfig();
        return defaultValue;
    }
    return doc[key].as<String>();
}

// SetConfigValue for const char*
const char *ConfigManager::setConfigValue(const char *key, const char *defaultValue) {
    if (!doc.containsKey(key)) {
        doc[key] = defaultValue;
        saveConfig();
        return defaultValue;
    }
    return doc[key].as<const char *>();
}

// Update a configuration value and return the updated value (double type)
double ConfigManager::updateConfigValue(const char *key, double newValue) {
    doc[key] = newValue;
    saveConfig();
    Serial.print(key);
    Serial.print(" updated to: ");
    Serial.println(newValue);
    return newValue;  // Return the updated double value
}

// Update a configuration value and return the updated value (int type)
int ConfigManager::updateConfigValue(const char *key, int newValue) {
    doc[key] = newValue;
    saveConfig();
    Serial.print(key);
    Serial.print(" updated to: ");
    Serial.println(newValue);
    return newValue;  // Return the updated int value
}

// Update a configuration value and return the updated value (bool type)
bool ConfigManager::updateConfigValue(const char *key, bool newValue) {
    doc[key] = newValue;
    saveConfig();
    Serial.print(key);
    Serial.print(" updated to: ");
    Serial.println(newValue ? "true" : "false");
    return newValue;  // Return the updated bool value
}

// Update a configuration value and return the updated value (String type)
String ConfigManager::updateConfigValue(const char *key, const String &newValue) {
    doc[key] = newValue;
    saveConfig();
    Serial.print(key);
    Serial.print(" updated to: ");
    Serial.println(newValue);
    return newValue;  // Return the updated String value
}

// Update a configuration value and return the updated value (const char* type)
const char* ConfigManager::updateConfigValue(const char *key, const char *newValue) {
    doc[key] = newValue;
    saveConfig();
    Serial.print(key);
    Serial.print(" updated to: ");
    Serial.println(newValue);
    return newValue;  // Return the updated const char* value
}


// Print the config file for debugging
void ConfigManager::printConfig() {
    Serial.print("Config file: ");
    Serial.println(filename);  // Print the filename

    File file = LittleFS.open(filename, "r");
    if (!file) {
        Serial.println("Failed to open config file for printing");
        return;
    }

    // Deserialize the JSON content into the document
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse config file: ");
        Serial.println(error.c_str());
        return;
    }

    // Print the JSON key-value pairs line by line
    Serial.println("Config file contents:");
    for (JsonPair keyValue : doc.as<JsonObject>()) {
        Serial.print(keyValue.key().c_str());
        Serial.print(": ");
        Serial.println(keyValue.value().as<String>());
    }
}

#endif // CONFIGMANAGER_H
