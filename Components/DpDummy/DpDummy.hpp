// ======================================================================
// \title  DpDummy.hpp
// \author devins
// \brief  hpp file for DpDummy component implementation class
// ======================================================================

#ifndef Components_DpDummy_HPP
#define Components_DpDummy_HPP

#include "Components/DpDummy/DpDummyComponentAc.hpp"

namespace Components {

class DpDummy final : public DpDummyComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct DpDummy object
    DpDummy(const char* const compName  //!< The component name
    );

    //! Destroy DpDummy object
    ~DpDummy();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command SEND_DATA
    //!
    //! async command
    void SEND_DATA_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                              U32 cmdSeq,           //!< The command sequence number
                              U32 silly_data) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for data products
    // ----------------------------------------------------------------------

    //! Receive a container of type C1
    void dpRecv_C1_handler(DpContainer& container,  //!< The container
                           Fw::Success::T status    //!< The container status
                           ) override;
};

}  // namespace Components

#endif
