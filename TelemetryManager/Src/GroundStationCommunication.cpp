

#include "GroundStationCommunication.hpp"


GroundStationCommunication::GroundStationCommunication() {
    // Constructor
}

GroundStationCommunication::~GroundStationCommunication() {
    // Destructor
}

// ** Implement transmit first **

void GroundStationCommunication::transmit(CircularBuffer &transmissionBuffer) {
    // START: Send the bytes in transmissionBuffer to the ground station via RFD900

    int bytesToTransmit = transmissionBuffer.getNumAvailBytes();

    uint8_t buf[bytesToTransmit]; // i think that we should just have a member variable of whatever size all of our other buffers will be, so that this isn't done dynamically. Or if we feel that that is too much memory being taken up, then I can implement it in a way where data is transmitted in maybe one byte or several bytes at a time
    transmissionBuffer.read(buf, bytesToTransmit);
    pRFD900->transmit(buf, bytesToTransmit);
    
    // END: Send the bytes in transmissionBuffer to the ground station via RFD900

    return;
}

void GroundStationCommunication::receiveInterruptServiceRoutine() { // call this method in drivers_callbacks.cpp

    int bytesReceived = pRFD900->getAvailDataSize(); // replace with actual number of bytes received

    // if GSC.DMAReceiveBuffer has enough space for the new data add it
    // otherwise discard the data
    if(DMAReceiveBuffer.getNumAvailBytes() > bytesReceived) {
        // add the new data to GSC.DMAReceiveBuffer

        uint8_t buf[bytesReceived];
        pRFD900->read(buf, bytesReceived);
        for (int i = 0; i < bytesReceived; ++i) {
            DMAReceiveBuffer.write(buf[i]);
        }
    }
    else{
        // discard the new data
        //not a great way to handle this, but it's a start

        uint8_t buf[bytesReceived];
        pRFD900->read(buf, bytesReceived);
    }

    // end of ISR
    return;
}