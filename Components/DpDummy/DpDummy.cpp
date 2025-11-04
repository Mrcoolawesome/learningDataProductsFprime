// ======================================================================
// \title  DpDummy.cpp
// \author devins
// \brief  cpp file for DpDummy component implementation class
// ======================================================================

#include "Components/DpDummy/DpDummy.hpp"

namespace Components {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DpDummy ::DpDummy(const char* const compName) : DpDummyComponentBase(compName) {}

DpDummy ::~DpDummy() {}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void DpDummy ::SEND_DATA_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 silly_data) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

// ----------------------------------------------------------------------
// Handler implementations for data products
// ----------------------------------------------------------------------

void DpDummy ::dpRecv_C1_handler(DpContainer& container, Fw::Success::T status) {
    // TODO 
    // this->productRequest_out()
    this->productRequestOut_out(0, container.getBaseId(), ); // this is the thing
    
}

}  // namespace Components
