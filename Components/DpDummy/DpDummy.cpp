// ======================================================================
// \title  DpDummy.cpp
// \author devins
// \brief  cpp file for DpDummy component implementation class
// ======================================================================

#include "Components/DpDummy/DpDummy.hpp"
#include "lib/fprime/Svc/DpCatalog/DpCatalog.hpp" // need this to use the 'configure()' function
#include "lib/fprime/Svc/DpManager/DpManager.hpp"

namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DpDummy ::DpDummy(const char* const compName) : DpDummyComponentBase(compName) {
    // Fw::FileNameString directories[1] = ["bruh.txt"];
    // FwSizeType numDirs = 1;
    // Fw::FileNameString stateFile = "stateFile.txt";
    // FwEnumStoreType memId; // The id of the RAM memory segment used to store catalog state. Not needed for heap allocation.
    // Fw::MemAllocator allocator; // Memory allocator for RAM memory storage
    // Svc::DpCatalog::configure(["gaming.txt"], );

    // none of this works idk what im doing
    // I was trying to get data products to downlink, which is what the dpCatelog component does, which has a 'configure()' function to set what directories to look at and write to.
    // My logic was to put all this in the constructor of this active component, since I think that'd mean this would run upon startup to configure the catelog component correctly.
    // The configure() function's inputs are all custom fprime types that need you to request buffers to put data into them and I don't remember how to do that.
    // It also needs a memory allocator and I have no idea what that is.
    // It also needs the memory id of the exact RAM memory segment that's used to store catalog state. I have no idea how to get that info.
}

DpDummy ::~DpDummy() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DpDummy ::SEND_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 silly_data) {
    // Update the global variable 'theSilly' to be what the user inputed
    this->theSilly = silly_data;
    // Fw::Success success = Svc::DpManager::getBuffer()
    this->productSendOut_out(0, );
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Handler implementations for data products
// ----------------------------------------------------------------------

void DpDummy ::dpRecv_C1_handler(DpContainer& container, Fw::Success::T status) {
    // If we're here then we're reciving the dp container
    this->productRequestOut_out(0, container.getBaseId(), this->SIZE_OF_NumberDataRecord_RECORD); // request the memory 

    container.serializeRecord_NumberDataRecord(this->theSilly); // put the thing in the container

    this->dpSend(container); // send out the container
    
}

}  // namespace Components
