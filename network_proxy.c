#include "network_proxy.h"
#include "sht.h"
#include "payload.h"
#include "xbee/include/digi_api.h"
#include "co2-d1.h"

const uint8_t COORDINATOR_ADDRESS[8] = {0x00, 0x13, 0xA2, 0x00, 0x40, 0x48, 0x94, 0x94}; //Coor Laboratorio
//const uint8_t COORDINATOR_ADDRESS[8] = {0x00, 0x13, 0xA2, 0x00, 0x40, 0xBB, 0x3D, 0xD3}; // Coor Casa Kiko
const uint8_t SENSORS[2] = {SHT_ID, CO2D1_ID};
const uint8_t BROADCAST_RADIUS = 0x00;
const uint8_t TRANSMIT_OPTIONS = 0x00;

extern ShtData shtData;
extern Co2D1Data co2d1Data;

BOOL NetworkAwake(void) {
    return INTCONbits.INT0IF && INTCONbits.INT0IE;
}

void ClearNetworkInterrupt(void) {
    INTCONbits.INT0IF = 0;
}

void SendMeasures(void) {
    XBeePacket packet;
    Payload payload;
    XBeeCreatePacket(&packet);
    PayloadInit(&payload);
    PayloadPutByte(&payload, MOBILE);
    PayloadPutByte(&payload, sizeof(SENSORS));
    PayloadPutString(&payload, SENSORS);
    PayloadPutWord(&payload, shtData.temperature.i);
    PayloadPutWord(&payload, shtData.humidity.i);
    PayloadPutWord(&payload, co2d1Data.co2sense);
    PayloadPutWord(&payload, co2d1Data.co2ref);
    PayloadPutWord(&payload, shtData.temperature.i); 
    PayloadPutWord(&payload, CO2OFFSET);
    XBeeCreateTransmitRequestPacket(&packet, 0x06, (uint8_t*) COORDINATOR_ADDRESS,
            BROADCAST_RADIUS, TRANSMIT_OPTIONS, payload.data, payload.size);
    XBeeSendPacket(&packet);
}

