#include <stdio.h>

struct SmartDevice {
    int deviceID;
    char deviceName[50];
    int status;             // 1: ON, 0: OFF
    float powerWatt;
};

struct EnergySensor {
    float voltageVolt;
    float currentAmper;
    int unoccupiedMinutes;
};

struct PowerReport {
    float totalPowerWatt;
    float totalCurrentAmper;
    float energyKWh;
    int overloadWarning;    // 1: Vuot 30A, 0: An toan
};

int main() {
    /* ==========================================
       1. KHAI BAO CAC STRUCT
       ========================================== */

    struct SmartDevice airConditioner;
    struct SmartDevice lighting;

    struct EnergySensor energySensor;

    struct PowerReport powerReport;

    /* ==========================================
       2. KHOI TAO DU LIEU 2 THIET BI
       ========================================== */

    airConditioner.deviceID = 101;

    /* strcpy khong can thiet vi ta co the khoi tao truc tiep */
    snprintf(
        airConditioner.deviceName,
        sizeof(airConditioner.deviceName),
        "Dieu hoa"
    );

    airConditioner.status = 1;
    airConditioner.powerWatt = 3500.0f;

    lighting.deviceID = 102;

    snprintf(
        lighting.deviceName,
        sizeof(lighting.deviceName),
        "Den chieu sang"
    );

    lighting.status = 1;
    lighting.powerWatt = 500.0f;

    /* ==========================================
       3. KHOI TAO CAM BIEN NANG LUONG
       ========================================== */

    energySensor.voltageVolt = 220.0f;
    energySensor.currentAmper = 18.18f;
    energySensor.unoccupiedMinutes = 20;

    /* ==========================================
       4. HIEN THI DU LIEU BAN DAU
       ========================================== */

    printf("============================================================\n");
    printf("              SMART HOME CENTRAL GATEWAY\n");
    printf("============================================================\n");

    printf("\n[THIET BI BAN DAU]\n");
    printf("------------------------------------------------------------\n");
    printf("%-8s %-20s %-10s %-15s\n",
           "ID", "Thiet bi", "Trang thai", "Cong suat");
    printf("------------------------------------------------------------\n");

    printf("%-8d %-20s %-10s %-10.2f W\n",
           airConditioner.deviceID,
           airConditioner.deviceName,
           airConditioner.status == 1 ? "ON" : "OFF",
           airConditioner.powerWatt);

    printf("%-8d %-20s %-10s %-10.2f W\n",
           lighting.deviceID,
           lighting.deviceName,
           lighting.status == 1 ? "ON" : "OFF",
           lighting.powerWatt);

    /* ==========================================
       5. HIEN THI DU LIEU CAM BIEN
       ========================================== */

    printf("\n[ENERGY SENSOR - REAL TIME]\n");
    printf("------------------------------------------------------------\n");
    printf("Dien ap van hanh       : %.2f V\n",
           energySensor.voltageVolt);

    printf("Dong dien do duoc      : %.2f A\n",
           energySensor.currentAmper);

    printf("Thoi gian phong trong  : %d phut\n",
           energySensor.unoccupiedMinutes);

    /* ==========================================
       6. KIEM TRA PHONG TRONG
       ========================================== */

    printf("\n[AUTOMATION]\n");
    printf("------------------------------------------------------------\n");

    if (energySensor.unoccupiedMinutes > 15) {

        printf("CANH BAO: Phong da trong hon 15 phut.\n");
        printf("Hanh dong: Tu dong tat dieu hoa.\n");

        airConditioner.status = 0;
        airConditioner.powerWatt = 0.0f;

    } else {

        printf("Phong chua trong qua 15 phut.\n");
        printf("Khong thuc hien tat dieu hoa.\n");
    }

    /* ==========================================
       7. TONG HOP DU LIEU VAO POWER REPORT
       ========================================== */

    powerReport.totalPowerWatt =
        airConditioner.powerWatt
        + lighting.powerWatt;

    /*
     * Tinh tong dong dien dua tren cong suat tong:
     *
     * I = P / U
     *
     * Vi dien ap phai lon hon 0 nen kiem tra truoc
     * de tranh phep chia cho 0.
     */

    if (energySensor.voltageVolt > 0) {

        powerReport.totalCurrentAmper =
            powerReport.totalPowerWatt
            / energySensor.voltageVolt;

    } else {

        powerReport.totalCurrentAmper = 0.0f;
    }

    /* ==========================================
       8. KIEM TRA QUA TAI
       ========================================== */

    if (powerReport.totalCurrentAmper > 30.0f) {

        powerReport.overloadWarning = 1;

    } else {

        powerReport.overloadWarning = 0;
    }

    /* ==========================================
       9. TINH DIEN NANG TIEU THU
       ========================================== */

    /*
     * Gia su ca lam viec = 8 gio.
     *
     * kWh = Watt x gio / 1000
     */

    powerReport.energyKWh =
        powerReport.totalPowerWatt
        * 8.0f
        / 1000.0f;

    /* ==========================================
       10. DASHBOARD TONG HOP
       ========================================== */

    printf("\n============================================================\n");
    printf("                    SMART HOME DASHBOARD\n");
    printf("============================================================\n");

    printf("\n[DEVICE STATUS]\n");
    printf("------------------------------------------------------------\n");
    printf("%-8s %-20s %-12s %-15s\n",
           "ID", "Thiet bi", "Trang thai", "Cong suat");
    printf("------------------------------------------------------------\n");

    printf("%-8d %-20s %-12s %10.2f W\n",
           airConditioner.deviceID,
           airConditioner.deviceName,
           airConditioner.status == 1 ? "ON" : "OFF",
           airConditioner.powerWatt);

    printf("%-8d %-20s %-12s %10.2f W\n",
           lighting.deviceID,
           lighting.deviceName,
           lighting.status == 1 ? "ON" : "OFF",
           lighting.powerWatt);

    printf("\n[SENSOR STATUS]\n");
    printf("------------------------------------------------------------\n");
    printf("Voltage                  : %.2f V\n",
           energySensor.voltageVolt);

    printf("Current sensor           : %.2f A\n",
           energySensor.currentAmper);

    printf("Room unoccupied          : %d minutes\n",
           energySensor.unoccupiedMinutes);

    printf("\n[POWER REPORT]\n");
    printf("------------------------------------------------------------\n");

    printf("Tong cong suat tai       : %.2f W\n",
           powerReport.totalPowerWatt);

    printf("Tong dong dien           : %.2f A\n",
           powerReport.totalCurrentAmper);

    printf("Dien nang uoc tinh       : %.2f kWh\n",
           powerReport.energyKWh);

    printf("Trang thai canh bao      : %s\n",
           powerReport.overloadWarning == 1
           ? "QUA TAI NGUY HIEM"
           : "AN TOAN");

    printf("\n============================================================\n");

    if (powerReport.overloadWarning == 1) {

        printf("!!! CANH BAO: TONG DONG DIEN VUOT QUA 30A !!!\n");

    } else {

        printf("He thong dang hoat dong trong nguong an toan.\n");
    }

    printf("============================================================\n");

    return 0;
}