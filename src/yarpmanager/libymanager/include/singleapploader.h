// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 *  Yarp Modules Manager
 *  Copyright: 2011 (C) Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef __SINGLEAPPLOADER__
#define __SINGLEAPPLOADER__

#include "ymm-types.h" 
#include "apploader.h"

//namespace ymm {


/**
 * Class SingleAppLoader  
 */
class SingleAppLoader : public AppLoader {

public: 
	SingleAppLoader(const char* szModule, const char* strHost);
	~SingleAppLoader();
	virtual bool init(void);
	virtual void fini(void);
	virtual Application* getNextApplication(void);
	
protected:

private:
	Application app;
	string strModule;
	string strHost;
};


 
//}

#endif //__SINGLEAPPLOADER__