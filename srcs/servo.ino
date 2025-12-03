/* CSM ENGR 100
   Single-Servo Non-Blocking Control in Degrees

   Type an angle in the Serial Monitor (in degrees) and press Enter:
     e.g., "30" or "45" or "90"

   Optional commands:
     "h"  -> home (0 degrees)
*/

#include <Servo.h>

// ================== SERVO TIMING PARAMETERS ==================

// Slew rate: how many microseconds to change per update step.
const int SERVO_STEP_US = 10;            // µs per step (~1 deg if ~10 µs/deg)
// How often to step (non-blocking).
const unsigned long SERVO_UPDATE_INTERVAL_MS = 40;  // ms between steps

// ================== SERIAL PARSER OUTPUTS ==================

char parsedChar = '\0';           // single-letter command
const byte MAX_PARSED_INTS = 8;
int  parsedInts[MAX_PARSED_INTS];
byte parsedIntCount = 0;

// ================== SERVO MODEL (STRUCT) ==================
//
// We can control the servo in DEGREES, using calibration from lab.
//
// Calibration model:
//   1) Convert world angle (thetaWorld) to servo-frame angle:
//        thetaServo = thetaWorld + angleOffsetDeg
//
//   2) Convert servo angle to pulse width:
//        pulse_us = usPerDeg * thetaServo + usIntercept
//
// where:
//   usPerDeg       = slope m from calibration (µs/deg)
//   usIntercept    = intercept b from calibration (µs)
//   angleOffsetDeg = desiredInitDeg - measuredDeg (mounting offset)
//
// CCW flag:
//   CCW = true  -> world angle increases → servo rotates "counterclockwise"
//   CCW = false -> world angle increases → servo rotates "clockwise"
//

struct SmoothServo {
  Servo s;        // underlying Servo
  int currentUS;  // current pulse width (µs)
  unsigned long lastUpdateMillis;

  float usPerDeg;        // slope m from calibration (µs/deg)
  float angleOffsetDeg;  // mounting offset (deg)
  float usIntercept;     // intercept b from calibration (µs)
  bool  CCW;             // true for CCW, false for CW in world frame
};

SmoothServo servo0;                // single servo for now
const int SERVO_PIN  = 3;          // change if needed

// Extreme safe boundaries (never exceed)
const int SAFE_MIN_US = 600;
const int SAFE_MAX_US = 2300;

// You can adjust this if your joint's world range is not 0–120 deg:
const float SERVO_WORLD_MAX_DEG = 120.0f;

// Target in DEGREES (students will command this via Serial)
float targetDegDeg = 0.0f;

// ================== FUNCTION DECLARATIONS ==================

bool parseSerial();
int  angleToUS(const SmoothServo &ss, float thetaWorldDeg);
void initSmoothServoDeg(SmoothServo &ss,
                        int pin,
                        float startAngleDeg,
                        float usPerDeg,
                        float angleOffsetDeg,
                        float usIntercept,
                        bool ccw);
bool updateSmoothServoDeg(SmoothServo &ss, float targetDeg);


// ================== SETUP ==================

void setup() {
  Serial.begin(9600);
  Serial.println("Single-Servo Non-Blocking Control (Degrees)");
  Serial.println("Type an angle in degrees and press Enter (e.g., 30)");
  Serial.println("Commands: h = home (0 deg)");

  // ======= TODO FOR STUDENTS: Insert your calibration numbers here =======
  //
  // From calibration lab:
  //   pulse_us ≈ m * theta_deg + b
  //   m -> usPerDeg
  //   b -> usIntercept for 0 deg
  //
  // Example placeholder values (students replace):
  float m0 = 10.65f;   // usPerDeg for this servo
  float b0 = 673.22f;  // usIntercept for this servo

  // Mounting offset example:
  //   desiredInitDeg = 90°
  //   measuredDeg    = 87°
  //   angleOffsetDeg = desiredInitDeg - measuredDeg = 3°
  float angleOffset0 = 0.0f;  // adjust this after mounting

  // For this single servo, assume CCW in world frame:
  initSmoothServoDeg(servo0, SERVO_PIN,
                     0.0f,       // startAngleDeg (world)
                     m0,         // usPerDeg
                     angleOffset0,
                     b0,
                     true);      // CCW = true

  targetDegDeg = 0.0f;  // initial target
}

// ================== MAIN LOOP ==================

void loop() {
  // 1. Non-blocking serial parsing
  bool serialEvent = parseSerial();

  // 2. Handle new commands (if any)
  if (serialEvent) {
    if (parsedChar == 'h') {
      // Home command: go to 0 degrees
      targetDegDeg = 0.0f;
      Serial.println("Command: home (0 deg)");
    } else if (parsedIntCount > 0) {
      // Use first integer as target angle
      targetDegDeg = parsedInts[0];
      Serial.print("New target angle: ");
      Serial.print(targetDegDeg);
      Serial.println(" deg");
    }

    // Clear parser outputs
    parsedChar = '\0';
    parsedIntCount = 0;
  }

  // 3. Non-blocking servo update (single function call)
  updateSmoothServoDeg(servo0, targetDegDeg);
}


// ================== SERIAL PARSER IMPLEMENTATION ==================

bool parseSerial() {
  static char tokenBuf[8];  // buffer for current token
  static byte tokenIdx = 0;

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\r') continue;  // ignore carriage return

    // Delimiters: space, comma, newline
    if (c == ' ' || c == ',' || c == '\n') {

      // Process token if we have one
      if (tokenIdx > 0) {
        tokenBuf[tokenIdx] = '\0';
        tokenIdx = 0;

        // Single non-numeric char -> command
        if (strlen(tokenBuf) == 1 &&
            (tokenBuf[0] < '0' || tokenBuf[0] > '9') &&
            tokenBuf[0] != '-') {

          parsedChar = tokenBuf[0];
          parsedIntCount = 0;

          // Flush rest of line
          if (c != '\n') {
            while (Serial.available()) {
              char d = Serial.read();
              if (d == '\n') break;
            }
          }
          return true;
        } else {
          // Integer token
          if (parsedIntCount < MAX_PARSED_INTS) {
            parsedInts[parsedIntCount++] = atoi(tokenBuf);
          }
        }
      }

      // End-of-line: if we have integers, that's a full message
      if (c == '\n') {
        if (parsedIntCount > 0) {
          parsedChar = '\0';
          return true;
        }
      }

    } else {
      // Accumulate into token buffer
      if (tokenIdx < sizeof(tokenBuf) - 1) {
        tokenBuf[tokenIdx++] = c;
      }
    }
  }

  return false;  // no complete message yet
}


// ================== DEGREE → MICROSECOND CONVERSION ==================

int angleToUS(const SmoothServo &ss, float thetaWorldDeg) {
  // Apply mounting offset (world → servo frame)
  if (ss.CCW) {  // if servo should rotate CCW

    float thetaServo = thetaWorldDeg + ss.angleOffsetDeg;

    // Linear mapping from calibration:
    // us = m * thetaServo + b
    float us = ss.usPerDeg * thetaServo + ss.usIntercept;
    return (int)us;

  } else {
    float thetaServo = thetaWorldDeg + ss.angleOffsetDeg;

    // Flip angle so rotation is CW in world frame.
    // Example: if world range is 0..120, we map:
    //   world 0   -> servo 120
    //   world 120 -> servo 0
    float thetaCW = SERVO_WORLD_MAX_DEG - thetaServo;

    float us = ss.usPerDeg * thetaCW + ss.usIntercept;
    return (int)us;
  }
}


// ================== Initialization Code ==================

void initSmoothServoDeg(SmoothServo &ss,
                        int pin,
                        float startAngleDeg,
                        float usPerDeg,
                        float angleOffsetDeg,
                        float usIntercept,
                        bool ccw) {
  // Store calibration + direction
  ss.usPerDeg       = usPerDeg;
  ss.angleOffsetDeg = angleOffsetDeg;
  ss.usIntercept    = usIntercept;
  ss.CCW            = ccw;

  // Compute starting pulse
  int startUS = angleToUS(ss, startAngleDeg);

  // Clamp to safe range
  if (startUS < SAFE_MIN_US) startUS = SAFE_MIN_US;
  if (startUS > SAFE_MAX_US) startUS = SAFE_MAX_US;

  ss.s.attach(pin);
  ss.currentUS        = startUS;
  ss.lastUpdateMillis = millis();
  ss.s.writeMicroseconds(startUS);
}


// ================== NON-BLOCKING UPDATE position code ==================

// Non-blocking update in DEGREES
bool updateSmoothServoDeg(SmoothServo &ss, float targetDeg) {
  int targetUS = angleToUS(ss, targetDeg);  // convert degrees to us

  // Clamp to safe range
  if (targetUS < SAFE_MIN_US) targetUS = SAFE_MIN_US;
  if (targetUS > SAFE_MAX_US) targetUS = SAFE_MAX_US;

  if (ss.currentUS == targetUS) {
    return true;  // already there
  }

  unsigned long now = millis();

  // Only step when enough time has passed
  if (now - ss.lastUpdateMillis < SERVO_UPDATE_INTERVAL_MS) {
    return false;
  }

  ss.lastUpdateMillis = now;

  if (ss.currentUS < targetUS) {
    ss.currentUS += SERVO_STEP_US;
    if (ss.currentUS > targetUS) ss.currentUS = targetUS;
  } else {
    ss.currentUS -= SERVO_STEP_US;
    if (ss.currentUS < targetUS) ss.currentUS = targetUS;
  }

  ss.s.writeMicroseconds(ss.currentUS);
  return (ss.currentUS == targetUS);
}
