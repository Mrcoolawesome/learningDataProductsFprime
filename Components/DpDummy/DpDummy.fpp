module Components {
    @ Component for F Prime FSW framework.
    active component DpDummy {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port
        @ async command
        async command SEND_DATA(silly_data: U32)

        @ Data product stuff
        product request port productRequestOut

        @ asynchronous product recieve port (i think this requests and then recieves a buffer)
        async product recv port productRecvIn

        @ product send port for sending out the data products 
        product send port productSendOut

        @ A record containing variable-size U32 data
        product record NumberDataRecord: U32 id 0x00
        @ container for the one record we have
        product container C1

        # Buffer ports
        @ Allocation port for a buffer
        output port allocate: Fw.BufferGet

        @ Deallocation port for buffers
        output port deallocate: Fw.BufferSend

        ## EVENTS
        @ Allocation failed event
        event MemoryAllocationFailed() \
            severity warning low \
            format "EPS Failed to allocate memory"

        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}