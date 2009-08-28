// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __YARP2_RFMODULE__
#define __YARP2_RFMODULE__

/*
* Author: Lorenzo Natale.
* Copyright (C) 2009 The Robotcub consortium
* CopyPolicy: Released under the terms of the GNU GPL v2.0.
*/

#include <yarp/os/Port.h>
#include <yarp/os/PortReaderBuffer.h>
#include <yarp/os/ResourceFinder.h>

namespace yarp {
    namespace os {
        class RFModule;
    }
}


/**
* 
* Disclaimer: this is currently under development. A new base-class 
* for standard YARP modules.  This class is similar to a Module, but 
* it adds support for the ResourceFinder class.
*/
class yarp::os::RFModule {

public:
    /**
    * Constructor.
    */
    RFModule();

    /**
    * Destructor.
    */
    virtual ~RFModule();


    /**
    *
    * You can override this to control the approximate periodicity at which
    * updateModule() is called by runModule().  By default, it returns
    * 0 (no delay). Time here is in seconds.
    * @return the desired period between successive calls to updateModule()
    * 
    */
    virtual double getPeriod() {
        return 1.0;
    }

    /**
    * Override this to do whatever your module needs to do.  When
    * your module wants to stop, return false.  The module's actual
    * work could be done during this call, or it could just check the
    * state of a thread running in the background.  
    * @return true iff module should continue
    * 
    */
    virtual bool updateModule()=0;

    /**
    *
    * Calls updateModule() until that returns false. Make sure 
    * you first configure your module by calling the configure()
    * function. updateModule() is then called every getPeriod()
    * seconds.  Be aware that the the respond() command could be 
    * asycnhronously at any time, if there is input from the 
    * standard input or a port connected via attach().
    * @return 0 on success
    *
    * \note attachTerminal() is no longer called automatically.
    */
    virtual int runModule();

    /**
    * Simple helper method to call configure() and then runModule().
    * @param rf a previously initialized ResourceFinder
    * @return 0 upon success, non-zero upon failure
    */
    virtual int runModule(yarp::os::ResourceFinder &rf);

    /**
    * Configure the module, pass a ResourceFinder object to the module. 
    * @param rf a previously initialized ResourceFinder
    * @return true/false upon success/failure
    *
    * \note attachTerminal() is no longer called automatically. You 
    * can call it in the configure function.
    */
    virtual bool configure(yarp::os::ResourceFinder &rf)
    { return true; }

    /**
    * Respond to a message.  You can override this to respond
    * to messages in your own way.  It is useful, if your module
    * doesn't know what to do with a message, to call
    * Module::respond() for any default responses.
    * @param command the message received
    * @param reply the response you wish to make
    * @return true if there was no critical failure
    */
    virtual bool respond(const Bottle& command, Bottle& reply) {
        return basicRespond(command,reply);
    }

    /**
    * Make any input from a Port object go to the respond() method.
    * @param port the port to attach
    * @return true if port was attached correctly.
    */
    virtual bool attach(yarp::os::Port& source);

    /**
    * Make any input from standard input (usually the keyboard) go to
    * the respond() method.  The reply will be send to standard output.
    * @return true on success.
    */
    virtual bool attachTerminal();

    /**
    * Detach terminal.
    */
    virtual bool detachTerminal();

    /**
    *
    * Try to halt any ongoing operations by threads managed by the module.
    * This is called anynchronously just after a quit command is received.
    * By default it does nothing - you may want to override this.
    * If you have created any ports, and have any threads that are 
    * might be blocked on reading data from those ports, this is a 
    * good place to add calls to BufferedPort::interrupt() or
    * Port::interrupt().
    * @return true if there was no catastrophic failure
    *
    */
    virtual bool interruptModule() {
        return true;
    }

    /*
    * Close function. This is called automatically when the module closes, after
    * the last call to updateModule.
    * Override this to perform memory cleanup or other activities.
    * @return true/false on success failure.
    */
    virtual bool close()
    { return true; }


    /*
    * Ask the module to stop.
    * @param wait: specifies if stop should block and wait termination. This is
    * not implemented yet.
    */
    void stopModule(bool wait=false)
    {
        stopFlag=true;
        if (!interruptModule())
            fprintf(stderr, "interruptModule() returned an error there could be problems shutting down the module\n");
    }

    /*
    * Check if the module should stop.
    * @return true/false if the module should stop or not.
    */
    bool isStopping()
    { return stopFlag; }

    /**
    * Return name of module, as set with --name flag or setName().
    * @param subName get nested name with this at the end
    * @return the name of the module
    */
    ConstString getName(const char *subName = 0);

    /**
    * Set the name of the module.
    * @param name the desired name of the module
    */
    void setName(const char *name) {
        this->name = name;
    }


    /**
    * Wrapper around respond() that is guaranteed to process system messages.
    */
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    bool safeRespond(const Bottle& command, Bottle& reply);
#endif /*DOXYGEN_SHOULD_SKIP_THIS*/

private:
    ResourceFinder resourceFinder;
    void *implementation;
    bool stopFlag;
    ConstString name;

    virtual bool basicRespond(const Bottle& command, Bottle& reply);
};

#endif