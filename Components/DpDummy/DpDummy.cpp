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

void DpDummy ::run_handler(FwIndexType portNum, U32 context) {
    // TODO
}

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

    this->numRecords = 0;
    this->dpPriority = 0;
}

DpDummy ::~DpDummy() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DpDummy ::Dp_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, DpDummy_DpReqType reqType, U32 priority) {
    // make sure DPs are available
    // they have a product get out port in their implementation alongside a product request port 
    // we just need a product request port from what i understand
    if (!this->isConnected_productRequestOut_OutputPort(0)) {
        this->log_WARNING_HI_DpsNotConnected();
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        return;
    }

    FwSizeType dpSize = sizeof(this->theSilly);

    this->numRecords = 1; // 1 records in current demo
    this->dpPriority = static_cast<FwDpPriorityType>(priority);
    this->log_ACTIVITY_LO_DpMemRequested(dpSize);

    if(reqType == DpDummy_DpReqType::IMMEDIATE) {
        Fw::Success stat = this->dpGet_C1(dpSize, this->dpContainer); // IDK WHY THIS IS NOT WORKING!!!
        // make sure we got the memory we wanted
        if (Fw::Success::FAILURE == stat) {
            this->log_WARNING_HI_DpMemoryFail();
            this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::EXECUTION_ERROR);
        } else {
            this->dpInProgress = true;
            this->log_ACTIVITY_LO_DpStarted(numRecords);
            this->log_ACTIVITY_LO_DpMemReceived(this->dpContainer.getBuffer().getSize());
            // override priority with requested priority
            this->dpContainer.setPriority(priority);
            this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
        }
    }
    else if (reqType == DpDummy_DpReqType::ASYNC) {
        this->dpRequest_C1(dpSize);
    }
    else {
        // should never get here
        FW_ASSERT(0, reqType.e);
    }

    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void DpDummy ::SEND_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 silly_data) {
    // Update the global variable 'theSilly' to be what the user inputed
    this->theSilly = silly_data;

    // deallocate the buffer bc we're done using it ig
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Handler implementations for data products
// ----------------------------------------------------------------------

void DpDummy ::dpRecv_C1_handler(DpContainer& container, Fw::Success::T status) {
    if (Fw::Success::SUCCESS == status) {
        this->dpContainer = container;
        this->dpInProgress = true;
        // set previously requested priority
        this->dpContainer.setPriority(this->dpPriority);
        this->log_ACTIVITY_LO_DpStarted(this->numRecords);
    } else {
        this->log_WARNING_HI_DpMemoryFail();
        // cleanup
        this->dpInProgress = false;
        this->numRecords = 0;
    }
}

void DpDummy ::cleanupAndSendDp() {
    this->dpSend(this->dpContainer);
    this->dpInProgress = false;
    this->numRecords = 0;
}

}  // namespace Components
