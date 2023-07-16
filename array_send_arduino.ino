const int maxArraySize = 1000;  // Set the maximum size of the array
float numbers[maxArraySize];    // Array to store the received numbers
int arraySize;                // Actual size of the array received

void setup() {
  Serial.begin(115200);         // Set the baud rate to match your computer's serial monitor
  Serial.setTimeout(1000);  // Increase the timeout to allow for the complete string to be received
}

void loop() {
  if (Serial.available() >= sizeof(arraySize)) {  // Check if the array size has been received
    Serial.readBytes((char*)&arraySize, sizeof(arraySize));  // Read the array size from serial
    if (arraySize <= maxArraySize) {
      int dataSize = arraySize * sizeof(float);
      byte* byteBuffer = (byte*)numbers;  // Treat the array as a byte buffer
      if (Serial.readBytes(byteBuffer, dataSize) == dataSize) {  // Read the array of numbers from serial
        float sum = 0;
        for (int i = 0; i < arraySize; i++) {
          sum += numbers[i];    // Perform the sum of the numbers
        }
        Serial.println(String(sum));    // Send the sum back to the computer
        arraySize = 0;          // Reset the array size for the next iteration
      }
    }
    else {
      Serial.println("Array size exceeds maximum allowed size.");  // Send an error message if array size is too large
      arraySize = 0;          // Reset the array size for error recovery
    }
  }
}
