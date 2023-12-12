# IoT-Based Muscle Monitoring System for Post-Stroke Patients

## Introduction

The IoT-Based Muscle Monitoring System is designed to monitor and analyze muscle activity and provide diagnoses regarding the conditions for a post-stroke patients. This system aims to provide real-time data about muscle performance, enabling healthcare professionals to track the recovery progress and customize rehabilitation programs.

Video explainations and demo for the project :

[![Watch the Video](https://img.youtube.com/vi/ru1DrIL2GJY/0.jpg)](https://www.youtube.com/watch?v=ru1DrIL2GJY)

## Features

- Real-time muscle activity monitoring.
- Data visualization for healthcare professionals.
- Brief diagnoses regarding the patients conditions.  
- Customizable rehabilitation programs based on monitored data.
- User-friendly interface for patients and caregivers.

## System Architecture

Hardware used in this project:
- Arduino MKR1000
- GY-521 MPU6050
- EMG Muscle Sensor
- Tactile Push Button
- 9V Battery

Software used in this project:
- Arduino IDE
- Arduino IOT Cloud

## How it works

![WhatsApp Image 2023-12-12 at 15 55 27](https://github.com/idabble31/IOT-Muscle-Monitoring-System-For-Stroke-Patients/assets/86302503/e28e1504-fa54-4594-8119-aa80a6c511d4)

This system works to monitor the muscle activity of a post-stroke patient's lower limb. Three parameters are needed in order to determine the patient's condition:
- Gait cycle

  The gait cycle, representing the sequence of walking events, helps assess post-stroke patients by analyzing factors like step duration, length, joint movements, and forces. This aids in identifying issues like muscle weakness or spasticity, guiding tailored rehabilitation to improve walking function and track progress. There are 5 phases of a person's gait, which is Initial Contact (IC), Foot Flat (FF), Heel Off (HO), Toe Off (TO), and Swing. To determine those phases, we use tactile push buttons placed right under the sole of the patient's shoe. 
- EMG

  EMG, or electromyography, is a diagnostic technique that records and analyzes the electrical activity produced by skeletal muscles, providing information about neuromuscular  function. We used an EMG sensor placed on the surface of the tibialis anterior and gastrocnemius muscle.
- Ankle Velocity

  Ankle velocity refers to the rate of change of ankle joint position over time and is a key parameter in assessing lower limb movement. In post-stroke patients, analyzing ankle velocity can provide insights into motor control and functional capabilities. Reduced ankle velocity may indicate impairments in muscle strength, coordination, or spasticity, which are common challenges in post-stroke individuals. By assessing ankle velocity during various tasks such as walking or specific movements, clinicians can tailor rehabilitation interventions and track the progress of lower limb rehabilitation in post-stroke patients. To do that, we used two IMU sensor and placed on the calf and the other one on the instep.

![WhatsApp Image 2023-12-12 at 15 55 27(1)](https://github.com/idabble31/IOT-Muscle-Monitoring-System-For-Stroke-Patients/assets/86302503/23cd5446-23a5-482e-97e6-127c235652a8)

From all those data collected, we assess the patient's condition based on this diagram above. The diagram begins with the question "Foot Drop?" If the answer is "Yes," then the patient has foot drop. If the answer is "No," then the patient does not have foot drop.

If the patient has foot drop, the next question is "Sequential Gait Phase?" If the answer is "Yes," then the patient's walking gait is good. If the answer is "No," then the patient's walking gait is not good.

If the patient's walking gait is not good, the next question is "EMG active correctly?" If the answer is "Yes," then the assistive device settings are not appropriate. If the answer is "No," then the patient has nerve or muscle damage.

Based on the answers to these questions, the cause of foot drop in the patient can be diagnosed.

Here is a brief explanation of the diagnosis for each possible cause of foot drop:

1. **Good walking gait:**
   If the patient's walking gait is good, there is no nerve or muscle damage. This could be due to factors such as:
   - Fatigue
   - Dehydration
   - Balance disturbances
   - Improper footwear

2. **Incorrect assistive device settings:**
   If the assistive device settings are not appropriate, the device cannot properly support the foot, leading to foot drop.

3. **Nerve or muscle damage:**
   If the patient has nerve or muscle damage, the nerves or muscles controlling foot movement do not function properly. This could be caused by various factors, including:
   - Nerve injuries
   - Degenerative diseases
   - Infections
   - Tumors

The decision tree diagram can be utilized by healthcare professionals to quickly and accurately diagnose the cause of foot drop.

## The Cloud
We also provide a web-based and app-based user interface in order to ease the patients and the healthcare professionals to utilize this system. We used Arduino IOT Cloud and here's what it looks like :


https://github.com/idabble31/IOT-Muscle-Monitoring-System-For-Stroke-Patients/assets/86302503/c804cb90-a712-46dd-80f1-75ef13d91300
